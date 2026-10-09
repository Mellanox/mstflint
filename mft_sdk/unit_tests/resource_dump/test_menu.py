#!/usr/bin/env python
# Copyright (c) 2020-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software product is a proprietary product of Nvidia Corporation and its affiliates
# (the "Company") and all right, title, and interest in and to the software
# product, including all associated intellectual property rights, are and
# shall remain exclusively with the Company.
#
# This software product is governed by the End User License Agreement
# provided with the software product.

"""
Test script for the resource menu tests.
Compares SDK resource menu output with `resourcedump query`.

Usage:
    ./test_menu.py                    # Full test suite on first device
    ./test_menu.py --compare -d D     # Compare C, C++, resourcedump on specific device
    ./test_menu.py --compare-all      # Compare on ALL devices
    ./test_menu.py --mlxreg           # Show resourcedump query output for first device
    ./test_menu.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
# The SDK reports record names exactly as the device does, so they are decoded here with the same
# helper the resourcedump CLI uses rather than a second copy of the rule.
sys.path.insert(0, os.path.join(
    os.path.dirname(os.path.abspath(__file__)).split(os.sep + "mft_sdk" + os.sep)[0], "resourcetools"))

from resourceparse_lib.utils.common_functions import reverse_string_endian

from resource_dump_fields import (
    RD_SECTION_RESOURCE_MENU,
    RD_FIELD_SEGMENT_TYPE,
    RD_FIELD_NAME,
    RD_FIELD_SPECIAL,
    RD_FIELD_TOTAL,
    DUMP_PARAMS,
)
from utils import (
    MFT_SDK_RESOURCE_DUMP_TOOL,
    RED, GREEN, BLUE, YELLOW, RESET,
    BaseConfig, format_sdk_command,
    CommandRunner,
    BaseCTestRunner, BaseCppTestRunner,
    BaseTestSuite,
    print_usage as _print_usage_base, run_main,
)


def _verbose():
    return BaseConfig.VERBOSE


# =============================================================================
# Configuration
# =============================================================================


class Config(BaseConfig):
    C_TEST_TARGET = "//user/mft_sdk/unit_tests/resource_dump:menu-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/resource_dump:menu-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/resource_dump/menu-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/resource_dump/menu-cpp-test"
    GTEST_FILTER = "MftSdkResourceMenuTest.*"
    C_SO_SUITE = "resource_menu"
    SUITE_NAME = "ResourceMenu"


# =============================================================================
# Parsers
# =============================================================================
#
# Both parsers produce the same shape so the two sides can be diffed directly:
#
#   {segment_type: {"name": str,
#                   "index1": (applicability, name),
#                   "num_of_obj1": (applicability, special_values),
#                   "index2": (applicability, name),
#                   "num_of_obj2": (applicability, special_values)}}


class SdkMenuParser(object):
    """Parses the `Resource Menu` section the C/C++ tests print."""

    _RECORD = re.compile(
        r'^' + re.escape(RD_FIELD_SEGMENT_TYPE) + r':\s*(0x[0-9a-fA-F]+)\s*\((.*)\)$')
    _PARAM = re.compile(
        r'^\s+(' + '|'.join(re.escape(p) for p in DUMP_PARAMS) +
        r'):\s*(\S+)\s+(?:' + re.escape(RD_FIELD_NAME) + '|' +
        re.escape(RD_FIELD_SPECIAL) + r')=(.*)$')

    @staticmethod
    def decode_name(hex_name):
        """Turns a hex encoded raw record name into the text the CLI prints."""
        name = bytearray.fromhex(hex_name)
        # Guarded on the host byte order the same way the CLI's MenuRecord guards its own call.
        if sys.byteorder == "little":
            name = reverse_string_endian(name)
        return bytes(name).decode("ascii", "replace").replace("\0", "")

    @staticmethod
    def parse(output):
        records = {}
        current = None
        in_section = False
        for line in output.split('\n'):
            if RD_SECTION_RESOURCE_MENU in line:
                in_section = True
                continue
            if not in_section:
                continue
            if line.strip().startswith(RD_FIELD_TOTAL + ':'):
                break

            record_match = SdkMenuParser._RECORD.match(line.strip())
            if record_match:
                segment_type = int(record_match.group(1), 16)
                current = {"name": SdkMenuParser.decode_name(record_match.group(2).strip())}
                records[segment_type] = current
                continue

            param_match = SdkMenuParser._PARAM.match(line.rstrip())
            if param_match and current is not None:
                value = param_match.group(3).strip()
                if RD_FIELD_NAME in line:
                    value = SdkMenuParser.decode_name(value)
                current[param_match.group(1)] = (param_match.group(2), value)
        return records


class ResourceDumpCliParser(object):
    """Parses the menu table `resourcedump query` prints."""

    _RECORD = re.compile(
        r'Segment Type\s*-\s*(0x[0-9a-fA-F]+)\s*\((.*)\)')
    _PARAM = re.compile(
        r'^(' + '|'.join(re.escape(p) for p in DUMP_PARAMS) +
        r')\s*(?:\((.*?)\))?\s{2,}(\S+(?:\s\S+)*?)\s{2,}(\S+.*?)\s*$')

    @staticmethod
    def parse_query(output):
        records = {}
        current = None
        for raw_line in output.split('\n'):
            line = raw_line.rstrip()
            record_match = ResourceDumpCliParser._RECORD.search(line)
            if record_match:
                segment_type = int(record_match.group(1), 16)
                current = {"name": record_match.group(2).strip()}
                records[segment_type] = current
                continue

            param_match = ResourceDumpCliParser._PARAM.match(line.strip())
            if param_match and current is not None:
                param = param_match.group(1)
                index_name = (param_match.group(2) or "").strip()
                applicability = param_match.group(3).strip()
                special = param_match.group(4).strip()
                # index rows carry a name, num_of_obj rows carry special values
                second = index_name if param.startswith("index") else special
                current[param] = (applicability, second)
        return records


# =============================================================================
# Comparison Table
# =============================================================================


class MenuComparisonTable(object):
    def __init__(self, sdk_records, cli_records, device=None, device_type=None,
                 c_records=None, cpp_records=None):
        self.sdk_records = sdk_records or {}
        self.cli_records = cli_records or {}
        self._c_records = c_records
        self._cpp_records = cpp_records
        self.device = device
        self.device_type = device_type

    def _print_header(self):
        print("")
        print("=" * 78)
        title = "RESOURCE MENU COMPARISON"
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 78)
        sdk_cmd = format_sdk_command(
            binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
            keywords=["ResourceMenu"])
        cli_cmd = "{} query -d {}".format(
            MFT_SDK_RESOURCE_DUMP_TOOL, self.device or "<device>")
        print("{}SDK command:          {}{}".format(BLUE, sdk_cmd, RESET))
        print("{}resourcedump command: {}{}".format(BLUE, cli_cmd, RESET))
        print("")

    def _compare_record(self, segment_type):
        """Returns (mismatches, rows) for one resource."""
        sdk = self.sdk_records.get(segment_type)
        cli = self.cli_records.get(segment_type)
        rows = []
        mismatches = []

        sdk_name = sdk.get("name", "") if sdk else "-"
        cli_name = cli.get("name", "") if cli else "-"
        if sdk and cli and sdk_name != cli_name:
            mismatches.append("name")
        rows.append((RD_FIELD_NAME, sdk_name, cli_name, bool(sdk and cli and sdk_name == cli_name)))

        for param in DUMP_PARAMS:
            sdk_value = sdk.get(param) if sdk else None
            cli_value = cli.get(param) if cli else None
            sdk_text = " ".join(v for v in sdk_value if v) if sdk_value else "-"
            cli_text = " ".join(v for v in cli_value if v) if cli_value else "-"
            match = bool(sdk_value and cli_value and sdk_value == cli_value)
            if sdk_value and cli_value and not match:
                mismatches.append(param)
            rows.append((param, sdk_text, cli_text, match))
        return mismatches, rows

    def print_table(self):
        self._print_header()

        sdk_types = set(self.sdk_records)
        cli_types = set(self.cli_records)
        common = sorted(sdk_types & cli_types)
        sdk_only = sorted(sdk_types - cli_types)
        cli_only = sorted(cli_types - sdk_types)

        print("SDK resources:          {}".format(len(sdk_types)))
        print("resourcedump resources: {}".format(len(cli_types)))
        print("{}Common:                 {}{}".format(GREEN, len(common), RESET))
        print("")

        if BaseConfig.SDK_ONLY:
            return self._print_sdk_only()

        failures = 0
        for segment_type in common:
            mismatches, rows = self._compare_record(segment_type)
            name = self.sdk_records[segment_type].get("name", "")
            header = "Resource 0x{:x} ({})".format(segment_type, name)
            status = GREEN + "OK" + RESET if not mismatches else RED + "MISMATCH" + RESET
            print("{:<40} {}".format(header, status))
            if mismatches or _verbose():
                sep = "  +--------------+------------------------+------------------------+-------+"
                print(sep)
                print("  | {:<12} | {:<22} | {:<22} | Match |".format(
                    "Field", "SDK", "resourcedump"))
                print(sep)
                for field, sdk_text, cli_text, match in rows:
                    mark = GREEN + " YES " + RESET if match else RED + " NO  " + RESET
                    print("  | {:<12} | {:<22} | {:<22} |{}|".format(
                        field, sdk_text[:22], cli_text[:22], mark))
                print(sep)
            failures += len(mismatches)

        if sdk_only:
            print("\n{}SDK only ({}):{} {}".format(
                YELLOW, len(sdk_only), RESET,
                ", ".join("0x{:x}".format(t) for t in sdk_only)))
        if cli_only:
            print("\n{}resourcedump only ({}):{} {}".format(
                YELLOW, len(cli_only), RESET,
                ", ".join("0x{:x}".format(t) for t in cli_only)))

        print("\nSummary: {} common resources, {} field mismatches".format(
            len(common), failures))

        if not common:
            print("{}FAIL: no resource is reported by both sources{}".format(RED, RESET))
            return False
        # A resource only one side knows is a product divergence worth showing,
        # but the comparison verdict is about the fields both sides describe.
        if failures:
            print("{}FAIL: {} field mismatches between SDK and resourcedump{}".format(
                RED, failures, RESET))
            return False
        if cli_only:
            print("{}resourcedump reports {} resources the SDK does not{}".format(
                RED, len(cli_only), RESET))
            return False
        print("{}All common resources match field-by-field{}".format(GREEN, RESET))
        return True

    def _print_sdk_only(self):
        c_records = self._c_records or {}
        cpp_records = self._cpp_records or {}
        if not c_records or not cpp_records:
            print("{}SDK-only mode: missing C or C++ menu output{}".format(RED, RESET))
            return False
        if c_records != cpp_records:
            print("{}SDK-only mode: C and C++ resource menus differ{}".format(RED, RESET))
            for segment_type in sorted(set(c_records) | set(cpp_records)):
                if c_records.get(segment_type) != cpp_records.get(segment_type):
                    print("  0x{:x}: C={} C++={}".format(
                        segment_type, c_records.get(segment_type),
                        cpp_records.get(segment_type)))
            return False
        print("{}SDK-only mode: C and C++ resource menus match "
              "({} resources){}".format(GREEN, len(c_records), RESET))
        return True


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("C", Config, device)

    def get_menu(self):
        return SdkMenuParser.parse(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("C++", Config, device)

    def get_menu(self):
        return SdkMenuParser.parse(self.output)


class ResourceDumpCliRunner(object):
    def __init__(self, device=None):
        self.device = device
        self.output = ""
        self.success = False

    def run(self, verbose=True):
        return self.run_query(verbose=verbose)

    def get_error(self):
        for line in self.output.split('\n'):
            if line.strip().startswith('-E-'):
                return line.strip()
        return None

    def _base_cmd(self):
        cmd = MFT_SDK_RESOURCE_DUMP_TOOL + " query"
        if self.device:
            cmd += " -d " + self.device
        return cmd

    def run_query(self, verbose=True):
        cmd = "echo '{}' | sudo su".format(self._base_cmd())
        self.success, self.output = CommandRunner.run(
            cmd, "Running resourcedump query on {}".format(self.device), verbose)
        return self.success

    def get_menu(self):
        return ResourceDumpCliParser.parse_query(self.output)

    def print_cli_output(self):
        self.run_query()
        print(self.output)
        return 0 if self.success else 1


# =============================================================================
# Test Suite
# =============================================================================


class TestSuite(BaseTestSuite):
    def __init__(self, device_info):
        super(TestSuite, self).__init__(device_info, Config)
        self.c_runner = CTestRunner(self.device)
        self.cpp_runner = CppTestRunner(self.device)
        self.cli_runner = ResourceDumpCliRunner(self.device)
        self.mlxlink_runner = self.cli_runner

    def _get_mlxlink_cmd(self):
        return "{} query -d {}".format(
            MFT_SDK_RESOURCE_DUMP_TOOL, self.device) if self.device \
            else MFT_SDK_RESOURCE_DUMP_TOOL + " query"

    def run_comparison(self):
        v = _verbose()

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)
        if not BaseConfig.SDK_ONLY:
            self.cli_runner.run_query(verbose=v)

        c_records = self.c_runner.get_menu()
        cpp_records = self.cpp_runner.get_menu()
        cli_records = (self.cli_runner.get_menu()
                       if not BaseConfig.SDK_ONLY else {})
        sdk_records = c_records if c_records else cpp_records

        if sdk_records or cli_records:
            passed = MenuComparisonTable(
                sdk_records, cli_records,
                self.device, self.device_type,
                c_records=c_records, cpp_records=cpp_records).print_table()
            return self.RESULT_PASS if passed else self.RESULT_FAIL

        print("\n{}No resource menu data from any source{}".format(RED, RESET))
        return self._compare_errors(positive=True)


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base("Show resourcedump query output for first device")


def main():
    return run_main(
        Config, TestSuite, ResourceDumpCliRunner,
        lambda r: r.print_cli_output(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
