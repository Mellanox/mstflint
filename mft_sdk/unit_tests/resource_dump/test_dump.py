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
Test script for the resource dump tests.
Compares the SDK's dump with `resourcedump dump --bin` structurally: the
sequence of (segment type, length) pairs and the total size. Payload bytes are
deliberately not compared — a dump carries live device state, so two dumps of
the same resource legitimately differ byte-for-byte.

Usage:
    ./test_dump.py                    # Full test suite on first device
    ./test_dump.py --compare -d D     # Compare C, C++, resourcedump on specific device
    ./test_dump.py --compare-all      # Compare on ALL devices
    ./test_dump.py --mlxreg           # Show resourcedump dump output for first device
    ./test_dump.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import struct
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from resource_dump_fields import (
    RD_SECTION_RESOURCE_DUMP,
    RD_FIELD_SEGMENT_TYPE,
    RD_FIELD_SIZE,
    RD_FIELD_SEGMENTS,
    RD_FIELD_LAYOUT,
    RD_FIELD_FILE,
    RD_FIELD_TOTAL,
    RD_FIELD_SKIPPED,
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


SEGMENT_HEADER_SIZE = 4
CLI_DUMP_PATH = "/tmp/mft_sdk_resource_dump_cli_{}.bin"


def _verbose():
    return BaseConfig.VERBOSE


# =============================================================================
# Configuration
# =============================================================================


class Config(BaseConfig):
    C_TEST_TARGET = "//user/mft_sdk/unit_tests/resource_dump:dump-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/resource_dump:dump-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/resource_dump/dump-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/resource_dump/dump-cpp-test"
    GTEST_FILTER = "MftSdkResourceDumpTest.*"
    C_SO_SUITE = "resource_dump"
    SUITE_NAME = "ResourceDump"


# =============================================================================
# Parsers
# =============================================================================


def parse_binary_layout(path):
    """Walk a resource dump file into a [(segment_type, length_dw)] list.

    Returns None when the file is missing or is not a well-framed segment
    stream, which is itself a comparison failure worth reporting.
    """
    try:
        with open(path, 'rb') as dump_file:
            data = dump_file.read()
    except IOError:
        return None

    # `resourcedump dump --bin` writes big endian whatever the host is, and the
    # wire header carries the length ahead of the type - the reverse of the host
    # order struct (see resource_dump_segments_be.h).
    segments = []
    offset = 0
    while offset + SEGMENT_HEADER_SIZE <= len(data):
        length_dw, segment_type = struct.unpack_from('>HH', data, offset)
        length = length_dw * 4
        if length < SEGMENT_HEADER_SIZE or offset + length > len(data):
            return None
        segments.append((segment_type, length_dw))
        offset += length
    return segments if offset == len(data) else None


class SdkDumpParser(object):
    """Parses the `Resource Dump` section the C/C++ tests print."""

    _RECORD = re.compile(
        r'^' + re.escape(RD_FIELD_SEGMENT_TYPE) + r':\s*(0x[0-9a-fA-F]+)$')
    _SIZE = re.compile(r'^' + re.escape(RD_FIELD_SIZE) + r':\s*(\d+)$')
    _SEGMENTS = re.compile(r'^' + re.escape(RD_FIELD_SEGMENTS) + r':\s*(-?\d+)$')
    _LAYOUT = re.compile(r'^' + re.escape(RD_FIELD_LAYOUT) + r':\s*(.*)$')
    _FILE = re.compile(r'^' + re.escape(RD_FIELD_FILE) + r':\s*(\S+)$')

    @staticmethod
    def _parse_layout(text):
        layout = []
        for pair in text.split():
            if ':' not in pair:
                return None
            segment_type, _, length = pair.partition(':')
            try:
                layout.append((int(segment_type, 16), int(length)))
            except ValueError:
                return None
        return layout

    @staticmethod
    def parse(output):
        records = {}
        current = None
        in_section = False
        for line in output.split('\n'):
            if RD_SECTION_RESOURCE_DUMP in line:
                in_section = True
                continue
            if not in_section:
                continue
            stripped = line.strip()
            if stripped.startswith(RD_FIELD_TOTAL + ':') or \
                    stripped.startswith(RD_FIELD_SKIPPED + ':'):
                continue

            record_match = SdkDumpParser._RECORD.match(stripped)
            if record_match:
                current = {}
                records[int(record_match.group(1), 16)] = current
                continue
            if current is None:
                continue

            size_match = SdkDumpParser._SIZE.match(stripped)
            if size_match:
                current["size"] = int(size_match.group(1))
                continue
            segments_match = SdkDumpParser._SEGMENTS.match(stripped)
            if segments_match:
                current["segments"] = int(segments_match.group(1))
                continue
            layout_match = SdkDumpParser._LAYOUT.match(stripped)
            if layout_match:
                current["layout"] = SdkDumpParser._parse_layout(
                    layout_match.group(1))
                continue
            file_match = SdkDumpParser._FILE.match(stripped)
            if file_match:
                current["file"] = file_match.group(1)
        return records


# =============================================================================
# Comparison Table
# =============================================================================


class DumpComparisonTable(object):
    def __init__(self, sdk_records, cli_layouts, device=None, device_type=None,
                 c_records=None, cpp_records=None):
        self.sdk_records = sdk_records or {}
        self.cli_layouts = cli_layouts or {}
        self._c_records = c_records
        self._cpp_records = cpp_records
        self.device = device
        self.device_type = device_type

    def _print_header(self):
        print("")
        print("=" * 78)
        title = "RESOURCE DUMP STRUCTURAL COMPARISON"
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 78)
        sdk_cmd = format_sdk_command(
            binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
            keywords=["DumpResource"])
        cli_cmd = "{} dump -d {} -s <segment> -b <file>".format(
            MFT_SDK_RESOURCE_DUMP_TOOL, self.device or "<device>")
        print("{}SDK command:          {}{}".format(BLUE, sdk_cmd, RESET))
        print("{}resourcedump command: {}{}".format(BLUE, cli_cmd, RESET))
        print("{}Payload bytes are not compared — a dump carries live device "
              "state.{}".format(YELLOW, RESET))
        print("")

    @staticmethod
    def _format_layout(layout):
        if layout is None:
            return "<unparseable>"
        return " ".join("0x{:x}:{}".format(t, n) for t, n in layout)

    def print_table(self):
        self._print_header()

        if BaseConfig.SDK_ONLY:
            return self._print_sdk_only()

        sdk_types = set(self.sdk_records)
        cli_types = set(self.cli_layouts)
        common = sorted(sdk_types & cli_types)
        print("SDK dumps:          {}".format(len(sdk_types)))
        print("resourcedump dumps: {}".format(len(cli_types)))
        print("{}Common:             {}{}".format(GREEN, len(common), RESET))
        print("")

        if not common:
            print("{}FAIL: no resource was dumped by both sources{}".format(RED, RESET))
            return False

        failures = 0
        sep = "+------------+-------+-------+----------+----------+-------+"
        print(sep)
        print("| {:<10} | {:<5} | {:<5} | {:<8} | {:<8} | Match |".format(
            "Resource", "SDKsz", "CLIsz", "SDKsegs", "CLIsegs"))
        print(sep)
        for segment_type in common:
            sdk = self.sdk_records[segment_type]
            sdk_layout = sdk.get("layout")
            cli_layout = self.cli_layouts[segment_type]
            sdk_size = sdk.get("size", -1)
            cli_size = sum(n * 4 for _, n in cli_layout) if cli_layout else -1

            match = (sdk_layout is not None and cli_layout is not None and
                     sdk_layout == cli_layout and sdk_size == cli_size)
            mark = GREEN + " YES " + RESET if match else RED + " NO  " + RESET
            print("| 0x{:<8x} | {:<5} | {:<5} | {:<8} | {:<8} |{}|".format(
                segment_type, sdk_size, cli_size,
                len(sdk_layout) if sdk_layout else -1,
                len(cli_layout) if cli_layout else -1, mark))
            if not match:
                failures += 1
                print("|   SDK layout: {}".format(self._format_layout(sdk_layout)))
                print("|   CLI layout: {}".format(self._format_layout(cli_layout)))
        print(sep)

        sdk_only = sorted(sdk_types - cli_types)
        cli_only = sorted(cli_types - sdk_types)
        if sdk_only:
            print("\n{}SDK only ({}):{} {}".format(
                YELLOW, len(sdk_only), RESET,
                ", ".join("0x{:x}".format(t) for t in sdk_only)))
        if cli_only:
            print("\n{}resourcedump only ({}):{} {}".format(
                YELLOW, len(cli_only), RESET,
                ", ".join("0x{:x}".format(t) for t in cli_only)))

        print("\nSummary: {} common dumps, {} structural mismatches".format(
            len(common), failures))
        if failures:
            print("{}FAIL: {} dumps differ structurally from resourcedump{}".format(
                RED, failures, RESET))
            return False
        print("{}All common dumps match structurally{}".format(GREEN, RESET))
        return True

    def _print_sdk_only(self):
        c_records = self._c_records or {}
        cpp_records = self._cpp_records or {}
        if not c_records or not cpp_records:
            print("{}SDK-only mode: missing C or C++ dump output{}".format(RED, RESET))
            return False
        mismatches = []
        for segment_type in sorted(set(c_records) & set(cpp_records)):
            if c_records[segment_type].get("layout") != cpp_records[segment_type].get("layout"):
                mismatches.append(segment_type)
        if mismatches:
            print("{}SDK-only mode: C and C++ dump layouts differ for {}{}".format(
                RED, ", ".join("0x{:x}".format(t) for t in mismatches), RESET))
            return False
        print("{}SDK-only mode: C and C++ dump layouts match "
              "({} resources){}".format(
                  GREEN, len(set(c_records) & set(cpp_records)), RESET))
        return True


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("C", Config, device)

    def get_dumps(self):
        return SdkDumpParser.parse(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("C++", Config, device)

    def get_dumps(self):
        return SdkDumpParser.parse(self.output)


class ResourceDumpCliRunner(object):
    def __init__(self, device=None):
        self.device = device
        self.output = ""
        self.success = False

    def run(self, verbose=True):
        return self.run_dump(0xffff, verbose=verbose)

    def get_error(self):
        for line in self.output.split('\n'):
            if line.strip().startswith('-E-'):
                return line.strip()
        return None

    def run_dump(self, segment_type, verbose=True):
        """Dump one resource to a binary file; returns its path or None."""
        path = CLI_DUMP_PATH.format("0x{:x}".format(segment_type))
        cmd = "{} dump -d {} -s {} -b {}".format(
            MFT_SDK_RESOURCE_DUMP_TOOL, self.device,
            "0x{:x}".format(segment_type), path)
        self.success, self.output = CommandRunner.run(
            "echo '{}' | sudo su".format(cmd),
            "Dumping resource 0x{:x} with resourcedump on {}".format(
                segment_type, self.device),
            verbose)
        return path if self.success else None

    def collect_layouts(self, segment_types, verbose=True):
        layouts = {}
        for segment_type in segment_types:
            path = self.run_dump(segment_type, verbose=verbose)
            if path is None:
                continue
            layout = parse_binary_layout(path)
            if layout is not None:
                layouts[segment_type] = layout
        return layouts

    def print_cli_output(self):
        self.run_dump(0xffff)
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
        return "{} dump -d {} -s <segment> -b <file>".format(
            MFT_SDK_RESOURCE_DUMP_TOOL, self.device or "<device>")

    def run_comparison(self):
        v = _verbose()

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)

        c_records = self.c_runner.get_dumps()
        cpp_records = self.cpp_runner.get_dumps()
        sdk_records = c_records if c_records else cpp_records

        cli_layouts = {}
        if not BaseConfig.SDK_ONLY and sdk_records:
            # Ask the CLI for exactly the resources the SDK dumped, so the two
            # sides describe the same set.
            cli_layouts = self.cli_runner.collect_layouts(
                sorted(sdk_records), verbose=v)

        if sdk_records or cli_layouts:
            passed = DumpComparisonTable(
                sdk_records, cli_layouts,
                self.device, self.device_type,
                c_records=c_records, cpp_records=cpp_records).print_table()
            return self.RESULT_PASS if passed else self.RESULT_FAIL

        print("\n{}No resource dump data from any source{}".format(RED, RESET))
        return self._compare_errors()


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base("Show resourcedump dump output for first device")


def main():
    return run_main(
        Config, TestSuite, ResourceDumpCliRunner,
        lambda r: r.print_cli_output(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
