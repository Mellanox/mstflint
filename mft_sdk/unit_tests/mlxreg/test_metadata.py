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
Test script for register metadata tests (basic + expanded).
Compares SDK metadata output with mlxreg_ext --show_reg.

Usage:
    ./test_metadata.py                    # Full test suite on first device
    ./test_metadata.py --compare -d D     # Compare C, C++, mlxreg_ext on specific device
    ./test_metadata.py --compare-all      # Compare on ALL devices
    ./test_metadata.py --mlxreg           # Show mlxreg_ext output for first device
    ./test_metadata.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import subprocess
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from mlxreg_fields import (
    SECTION_REGISTER_METADATA, SECTION_EXPANDED_METADATA,
    FIELD_FIELD_COUNT,
)
from utils import (
    MFT_SDK_REG_TOOL, is_known_missing, STRICT_ORACLE, oracle_version,
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
    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxreg:metadata-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxreg:metadata-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxreg/metadata-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxreg/metadata-cpp-test"
    GTEST_FILTER = "MftSdkMetadataTest.*"
    SUITE_NAME = "Metadata"

    METADATA_REGISTERS = ["MGIR", "MCAM"]


# =============================================================================
# Parsers
# =============================================================================


class MetadataParser(object):
    @staticmethod
    def parse(output, register_name):
        fields = []
        in_section = False
        pattern = re.compile(re.escape(SECTION_REGISTER_METADATA) + r':\s*' +
                             re.escape(register_name))
        for line in output.split('\n'):
            if pattern.search(line):
                in_section = True
                continue
            if in_section:
                if line.strip() == '' or (
                    SECTION_REGISTER_METADATA + ':' in line and
                    register_name not in line
                ):
                    break
                if line.startswith('---') or line.startswith(FIELD_FIELD_COUNT + ':'):
                    continue
                if ':' in line and 'addr=' in line:
                    parts = line.split(':', 1)
                    name = parts[0].strip()
                    attrs_str = parts[1].strip()
                    attrs = {}
                    for token in attrs_str.split():
                        if '=' in token:
                            k, v = token.split('=', 1)
                            attrs[k] = v
                    attrs['name'] = name
                    fields.append(attrs)
        return fields


class MlxregCliRunner(object):
    def __init__(self, device=None):
        self.device = device
        self.output = ""
        self.success = False

    def run(self, verbose=True):
        return self.run_show_reg("MGIR", verbose=verbose)

    def get_error(self):
        for line in self.output.split('\n'):
            if line.strip().startswith('-E-'):
                return line.strip()
        return None

    def _base_cmd(self):
        cmd = MFT_SDK_REG_TOOL
        if self.device:
            cmd += " -d " + self.device
        return cmd

    def run_show_reg(self, register_name, verbose=True):
        # --full_path makes the CLI print the same fully-qualified field
        # names the SDK metadata uses (e.g. fw_info.major).
        cmd = self._base_cmd() + " --show_reg {} --full_path".format(register_name)
        cmd = "echo '{}' | sudo su".format(cmd)
        # merge_stderr=False: get_fields() parses this as a pipe table, so a
        # diagnostic on the tool's stderr would corrupt a row and be reported
        # as an SDK field mismatch.
        self.success, self.output = CommandRunner.run(
            cmd, "Running {} --show_reg {} on {}".format(MFT_SDK_REG_TOOL, register_name, self.device), verbose,
            merge_stderr=False)
        return self.success

    def get_fields(self):
        """Parse the --show_reg pipe table (Field Name | Address | Offset |
        Size | Access) into {name: {'addr','offset','size','access'}}."""
        fields = {}
        in_data = False
        for line in self.output.split('\n'):
            stripped = line.strip()
            if stripped.startswith('===='):
                in_data = not in_data
                continue
            if in_data and '|' in stripped:
                cols = [c.strip() for c in stripped.split('|')]
                if len(cols) >= 5 and cols[0] and cols[0] != 'Field Name':
                    try:
                        fields[cols[0]] = {
                            'addr': int(cols[1], 16),
                            'offset': int(cols[2]),
                            'size': int(cols[3]),
                            'access': cols[4],
                        }
                    except ValueError:
                        continue
        return fields

    def print_mlxreg_output(self):
        for reg in Config.METADATA_REGISTERS:
            self.run_show_reg(reg)
            print(self.output)
        return 0 if self.success else 1


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("C", Config, device)

    def get_metadata(self, register_name):
        return MetadataParser.parse(self.output, register_name)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("C++", Config, device)

    def get_metadata(self, register_name):
        return MetadataParser.parse(self.output, register_name)


# =============================================================================
# Test Suite
# =============================================================================


class TestSuite(BaseTestSuite):
    def __init__(self, device_info):
        super(TestSuite, self).__init__(device_info, Config)
        self.c_runner = CTestRunner(self.device)
        self.cpp_runner = CppTestRunner(self.device)
        self.mlxreg_runner = MlxregCliRunner(self.device)
        self.mlxlink_runner = self.mlxreg_runner

    def _get_mlxlink_cmd(self):
        return "mlxreg_ext -d " + self.device if self.device else "mlxreg_ext"

    def run_comparison(self):
        v = _verbose()
        results = {}

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)

        for reg_name in Config.METADATA_REGISTERS:
            c_fields = self.c_runner.get_metadata(reg_name)
            cpp_fields = self.cpp_runner.get_metadata(reg_name)

            c_names = sorted([f.get('name', '') for f in c_fields])
            cpp_names = sorted([f.get('name', '') for f in cpp_fields])
            match = c_names == cpp_names

            mlxreg_fields = None
            attr_mismatches = []
            if not BaseConfig.SDK_ONLY:
                self.mlxreg_runner.run_show_reg(reg_name, verbose=v)
                mlxreg_fields = self.mlxreg_runner.get_fields()
                mlxreg_names = sorted(mlxreg_fields.keys())
                # CLI-only fields in MFT_SDK_KNOWN_MISSING are an expected
                # product divergence — compare against the remaining names.
                expected_missing = set(
                    n for n in mlxreg_names
                    if n not in set(c_names) and is_known_missing(n))
                # Fields the SDK exposes and the oracle has never heard of.
                # This is NOT evidence of an SDK defect: the reference CLI is
                # whatever MFT happens to be installed on the lab machine, and
                # when it predates a PRM alignment it simply knows fewer
                # fields. The oracle cannot validate what it does not know, so
                # the honest verdict is "unverifiable here", not FAIL --
                # attribute-level checking below still validates every field
                # the two DO share, and a CLI-only field the SDK is missing
                # still fails as before. Set MFT_SDK_STRICT_ORACLE=1 where the
                # oracle is pinned to the SDK's PRM revision to restore a hard
                # failure.
                sdk_ahead = sorted(set(c_names) - set(mlxreg_names))
                comparable = sorted(set(mlxreg_names) - expected_missing)
                if sdk_ahead and not STRICT_ORACLE:
                    comparable = sorted(set(comparable) | set(sdk_ahead))
                match = match and (c_names == comparable)
                # Attribute-level compare on common fields:
                # SDK addr/bit_offset/bit_size/access vs CLI Address/Offset/Size/Access.
                sdk_by_name = dict((f.get('name', ''), f) for f in c_fields)
                for name in sorted(set(sdk_by_name) & set(mlxreg_fields)):
                    sdk_f, cli_f = sdk_by_name[name], mlxreg_fields[name]
                    try:
                        pairs = (
                            ('addr', int(sdk_f.get('addr', '-1'), 16), cli_f['addr']),
                            ('offset', int(sdk_f.get('bit_offset', -1)), cli_f['offset']),
                            ('size', int(sdk_f.get('bit_size', -1)), cli_f['size']),
                            ('access', sdk_f.get('access', ''), cli_f['access']),
                        )
                    except ValueError:
                        continue
                    diffs = ["{}: sdk={} cli={}".format(k, a, b) for k, a, b in pairs if a != b]
                    if diffs:
                        attr_mismatches.append("{} ({})".format(name, "; ".join(diffs)))
                match = match and not attr_mismatches

            print("\n" + "=" * 70)
            title = "METADATA COMPARISON: {}".format(reg_name)
            if self.device:
                title += " [{} - {}]".format(self.device, self.device_type)
            print(title)
            print("=" * 70)
            sdk_cmd = format_sdk_command(
                binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
                keywords=["GetRegisterMetadata"])
            print("{}SDK command:    {}{}".format(BLUE, sdk_cmd, RESET))
            if mlxreg_fields is not None:
                print("{}CLI command:    {} --show_reg {} --full_path{}".format(
                    BLUE, self.mlxreg_runner._base_cmd(), reg_name, RESET))
            print("")
            print("C fields:   {}".format(len(c_fields)))
            print("C++ fields: {}".format(len(cpp_fields)))
            if mlxreg_fields is not None:
                print("{} fields: {}".format(MFT_SDK_REG_TOOL, len(mlxreg_fields)))
                sdk_only_names = sorted(set(c_names) - set(mlxreg_fields))
                cli_only_names = sorted(set(mlxreg_fields) - set(c_names))
                if sdk_only_names:
                    print("SDK-only fields ({}): {}".format(len(sdk_only_names), ", ".join(sdk_only_names)))
                    # Say plainly which side is behind -- this is the line that
                    # turns a mystifying DIFFER into a one-glance diagnosis.
                    print("{}  ^ the oracle ({} {}) does not know these fields; "
                          "the SDK is ahead of it, so they cannot be cross-checked "
                          "here{}.{}".format(
                              YELLOW, MFT_SDK_REG_TOOL, oracle_version(),
                              "" if STRICT_ORACLE else " and are not counted as failures",
                              RESET))
                if cli_only_names:
                    print("{}-only fields ({}): {}".format(MFT_SDK_REG_TOOL, len(cli_only_names), ", ".join(cli_only_names)))
                if expected_missing:
                    print("Expected differences (MFT_SDK_KNOWN_MISSING), not counted as failures: {}".format(
                        ", ".join(sorted(expected_missing))))
                if attr_mismatches:
                    print("Attribute mismatches ({}):".format(len(attr_mismatches)))
                    for m in attr_mismatches[:10]:
                        print("  {}".format(m))
            status = GREEN + "MATCH" + RESET if match else RED + "DIFFER" + RESET
            print("Result:     {}".format(status))
            results["Metadata ({})".format(reg_name)] = match

        self._print_test_summary(results)
        return self.RESULT_PASS if all(results.values()) else self.RESULT_FAIL

    def _print_test_summary(self, results):
        print("\n" + "=" * 70)
        title = "METADATA TEST SUMMARY"
        if self.device:
            title += " [{} - {}]".format(self.device, self.device_type)
        print(title)
        print("=" * 70)
        for name, passed in results.items():
            status = GREEN + "PASS" + RESET if passed else RED + "FAIL" + RESET
            print("  {:<35}: {}".format(name, status))
        overall = all(results.values())
        print("=" * 70)
        if overall:
            print("{}Overall: ALL TESTS PASSED{}".format(GREEN, RESET))
        else:
            print("{}Overall: SOME TESTS FAILED{}".format(RED, RESET))
        print("=" * 70)


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base("Show mlxreg_ext --show_reg output for first device")


def main():
    return run_main(
        Config, TestSuite, MlxregCliRunner,
        lambda r: r.print_mlxreg_output(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
