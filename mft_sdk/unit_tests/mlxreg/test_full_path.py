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
Test script for building and running full-path register access tests.
Validates the fullPath feature that uses full ADB paths as field names.
Compares SDK C/C++ output with mlxreg_ext --show_reg --full_path.

Usage:
    ./test_full_path.py                    # Full test suite on first device
    ./test_full_path.py --compare -d D     # Compare C, C++, mlxreg_ext on specific device
    ./test_full_path.py --compare-all      # Compare on ALL devices
    ./test_full_path.py --compare-all --so # Compare on ALL devices (pre-installed .so)
    ./test_full_path.py --mlxreg           # Show mlxreg_ext --full_path output for first device
    ./test_full_path.py --so               # Full test suite using pre-installed binaries
    ./test_full_path.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from mlxreg_fields import (
    SECTION_FULL_PATH_METADATA, SECTION_FULL_PATH_GET,
    FIELD_FIELD_COUNT,
)
from utils import (
    MFT_SDK_REG_TOOL, tool_label, is_known_missing, STRICT_ORACLE,
    oracle_version,
    RED, GREEN, BLUE, YELLOW, RESET,
    BaseConfig, clean_value, format_sdk_command,
    CommandRunner,
    BaseCTestRunner, BaseCppTestRunner,
    BaseTestSuite,
    print_sdk_only_empty_agreement,
    print_usage as _print_usage_base, run_main,
)


def _verbose():
    return BaseConfig.VERBOSE


# =============================================================================
# Configuration
# =============================================================================


class Config(BaseConfig):
    """Configuration constants for the full-path test runner."""

    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxreg:full-path-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxreg:full-path-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxreg/full-path-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxreg/full-path-cpp-test"
    GTEST_FILTER = "MftSdkFullPathTest.*"
    SUITE_NAME = "FullPath"

    METADATA_REGISTERS = ["MGIR", "CREDENTIAL_HANDLE"]
    GET_REGISTERS = ["MGIR"]


# =============================================================================
# Parsers
# =============================================================================


class FullPathParser(object):
    """Parses full-path metadata and register GET sections from SDK test output."""

    @staticmethod
    def parse_metadata(output, register_name):
        """Parse Full Path Metadata section into a list of field dicts.

        Each dict has keys: name, addr, bit_offset, bit_size, access.
        """
        fields = []
        in_section = False
        pattern = re.compile(
            re.escape(SECTION_FULL_PATH_METADATA) + r':\s*' +
            re.escape(register_name))

        for line in output.split('\n'):
            if pattern.search(line):
                in_section = True
                continue
            if in_section:
                if line.strip() == '' or (
                    SECTION_FULL_PATH_METADATA + ':' in line and
                    register_name not in line
                ):
                    break
                if line.strip().startswith(SECTION_FULL_PATH_GET):
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

    @staticmethod
    def parse_metadata_field_names(output, register_name):
        """Extract just the field names from a Full Path Metadata section."""
        fields = FullPathParser.parse_metadata(output, register_name)
        return [f['name'] for f in fields]

    @staticmethod
    def parse_register_get(output, register_name):
        """Parse Full Path Register GET section into a dict of field_name -> hex_value."""
        fields = {}
        in_section = False
        pattern = re.compile(
            re.escape(SECTION_FULL_PATH_GET) + r'\s*:\s*' +
            re.escape(register_name))
        field_re = re.compile(r'^[a-zA-Z_][a-zA-Z0-9_.]*$')

        for line in output.split('\n'):
            stripped = line.strip()
            if not in_section:
                if pattern.match(stripped):
                    in_section = True
                continue
            if stripped == '':
                break
            if stripped.startswith('---'):
                continue
            if (stripped.startswith(SECTION_FULL_PATH_METADATA) or
                    stripped.startswith(SECTION_FULL_PATH_GET)):
                if not pattern.match(stripped):
                    break
            elif stripped.startswith('[') and len(stripped) > 1 and \
                    stripped[1] in ' =-':
                break
            elif ':' in line:
                parts = line.split(':', 1)
                if len(parts) == 2:
                    key = parts[0].strip()
                    val = clean_value(parts[1])
                    if key and field_re.match(key):
                        fields[key] = val
        return fields


class MlxregFullPathCliParser(object):
    """Parses mlxreg_ext --show_reg --full_path output."""

    @staticmethod
    def parse_show_reg(output):
        """Parse mlxreg_ext --show_reg output into a list of field names.

        Handles the pipe-separated table format:
          Field Name    | Data
          ==============|=========
          field_name    | addr info
        Also handles space-separated field metadata lines.
        """
        fields = []
        in_data = False
        for line in output.split('\n'):
            stripped = line.strip()
            if '====' in stripped or '----' in stripped:
                in_data = True
                continue
            if not stripped or 'Sending' in stripped:
                continue
            if in_data:
                if '|' in stripped:
                    parts = stripped.split('|', 1)
                    name = parts[0].strip()
                    if name and name != 'Field Name' and \
                            not name.startswith('-'):
                        fields.append(name)
                elif stripped and re.match(r'^[a-zA-Z_]', stripped):
                    parts = stripped.split()
                    if len(parts) >= 2:
                        fields.append(parts[0])
        return fields


# =============================================================================
# Comparison Tables
# =============================================================================


class FullPathMetadataComparisonTable(object):
    """Prints a comparison table of full-path field names from C, C++, and mlxreg_ext."""

    def __init__(self, register_name, c_names, cpp_names, mlxreg_names,
                 device=None, device_type=None, mlxreg_cmd="", sdk_cmd=""):
        self.register_name = register_name
        self.c_names = c_names
        self.cpp_names = cpp_names
        self.mlxreg_names = mlxreg_names
        self.device = device
        self.device_type = device_type
        self.mlxreg_cmd = mlxreg_cmd
        self.sdk_cmd = sdk_cmd

    def print_table(self):
        c_set = set(self.c_names)
        cpp_set = set(self.cpp_names)
        mlxreg_set = set(self.mlxreg_names)
        all_names = sorted(c_set | cpp_set | mlxreg_set)

        if not all_names:
            print("  No fields to compare")
            return True

        nw = max(len(n) for n in all_names) + 2
        # Oracle column: name it after the CLI that actually ran, but never
        # narrower than the historical width, so the table is byte-identical
        # under the default mlxreg_ext.
        oracle = tool_label(MFT_SDK_REG_TOOL)
        ow = max(len(oracle), 10)

        print("")
        print("=" * 70)
        title = "FULL PATH METADATA COMPARISON: {}".format(self.register_name)
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 70)
        if self.sdk_cmd:
            print("{}SDK command:    {}{}".format(BLUE, self.sdk_cmd, RESET))
        if self.mlxreg_cmd:
            print("{}{} command: {}{}".format(
                BLUE, oracle, self.mlxreg_cmd, RESET))
        print("")

        sep = "+-{}-+------+------+-{}-+---------+".format("-" * nw, "-" * ow)
        print(sep)
        print("| {:<{}} | C    | C++  | {:<{}} | Match   |".format(
            "Field Name", nw, oracle, ow))
        print(sep)

        match_count = 0
        known_count = 0
        ahead_count = 0
        for name in all_names:
            in_c = name in c_set
            in_cpp = name in cpp_set
            in_mlx = name in mlxreg_set
            c_col = " YES " if in_c else "  -  "
            cpp_col = " YES " if in_cpp else "  -  "
            mlx_col = "{:^{}}".format("YES" if in_mlx else "-", ow + 1)

            if not in_c and not in_cpp and in_mlx and is_known_missing(name):
                # CLI-only field listed in MFT_SDK_KNOWN_MISSING: an expected
                # product divergence (SDK register DB lags the CLI's), not a
                # DIFF.
                known_count += 1
                status = YELLOW + " KNOWN" + RESET
                print("| {:<{}} |{}|{}|{}| {} |".format(
                    name, nw, c_col, cpp_col, mlx_col, status))
                continue
            if (in_c and in_cpp and not in_mlx and not BaseConfig.SDK_ONLY
                    and not STRICT_ORACLE):
                # The mirror image: both SDK runners agree the field exists and
                # the oracle has never heard of it. That is the oracle being an
                # older MFT than the SDK's PRM, not an SDK defect -- and the
                # oracle cannot cross-check a field it does not know, so it is
                # unverifiable here rather than wrong. MFT_SDK_STRICT_ORACLE=1
                # restores the hard DIFF.
                ahead_count += 1
                status = YELLOW + " AHEAD" + RESET
                print("| {:<{}} |{}|{}|{}| {} |".format(
                    name, nw, c_col, cpp_col, mlx_col, status))
                continue
            if BaseConfig.SDK_ONLY:
                match = in_c and in_cpp
            else:
                # In compare mode an empty mlxreg_ext result must show as
                # DIFF, not silently degrade to a C-vs-C++-only check.
                match = in_c and in_cpp and in_mlx
            match_count += match
            status = GREEN + "  OK  " + \
                RESET if match else RED + "  DIFF" + RESET
            print("| {:<{}} |{}|{}|{}| {} |".format(
                name, nw, c_col, cpp_col, mlx_col, status))

        print(sep)
        compared = len(all_names) - known_count - ahead_count
        diff_count = compared - match_count
        summary = "Summary: {} fields, {} match, {} differ".format(
            compared, match_count, diff_count)
        if known_count:
            summary += ", {} expected-missing (MFT_SDK_KNOWN_MISSING)".format(
                known_count)
        if ahead_count:
            summary += (", {} SDK-ahead (oracle {} {} does not know them)".format(
                ahead_count, MFT_SDK_REG_TOOL, oracle_version()))
        print("\n" + summary)
        return match_count == compared


class CredentialHandleDisambiguationTable(object):
    """Verifies that CREDENTIAL_HANDLE has disambiguated 'state' fields."""

    def __init__(self, c_names, cpp_names, mlxreg_names,
                 device=None, device_type=None):
        self.c_names = c_names
        self.cpp_names = cpp_names
        self.mlxreg_names = mlxreg_names
        self.device = device
        self.device_type = device_type

    def print_table(self):
        expected = {"crypto_login_object.state", "credential_object.state"}

        print("")
        print("=" * 70)
        title = "CREDENTIAL_HANDLE DISAMBIGUATION CHECK"
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 70)

        results = {}
        no_data = set()
        cli_label = tool_label(MFT_SDK_REG_TOOL)
        for label, names in [("C", self.c_names), ("C++", self.cpp_names),
                             (cli_label, self.mlxreg_names)]:
            if not names:
                if label == cli_label:
                    if BaseConfig.SDK_ONLY:
                        continue
                    # In compare mode an empty CLI result is a failure,
                    # not a skip — otherwise a broken CLI run passes.
                    no_data.add(label)
                    results[label] = False
                    continue
                results[label] = None
                continue
            name_set = set(names)
            has_both = expected.issubset(name_set)
            has_bare_state = "state" in name_set
            results[label] = has_both and not has_bare_state

        for label, passed in results.items():
            if passed is None:
                print("  {:<12}: {}SKIP (no data){}".format(
                    label, YELLOW, RESET))
            elif label in no_data:
                print("  {:<12}: {}FAIL — CLI returned no fields{}".format(
                    label, RED, RESET))
            elif passed:
                print("  {:<12}: {}PASS — both full-path 'state' fields found, "
                      "bare 'state' absent{}".format(label, GREEN, RESET))
            else:
                print("  {:<12}: {}FAIL — disambiguation not working{}".format(
                    label, RED, RESET))

        valid = [v for v in results.values() if v is not None]
        if not valid and BaseConfig.SDK_ONLY:
            print_sdk_only_empty_agreement()
            return True
        return bool(valid) and all(valid)


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("C", Config, device)

    def get_metadata_field_names(self, register_name):
        return FullPathParser.parse_metadata_field_names(
            self.output, register_name)

    def get_register_get(self, register_name):
        return FullPathParser.parse_register_get(
            self.output, register_name)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("C++", Config, device)

    def get_metadata_field_names(self, register_name):
        return FullPathParser.parse_metadata_field_names(
            self.output, register_name)

    def get_register_get(self, register_name):
        return FullPathParser.parse_register_get(
            self.output, register_name)


class MlxregFullPathCliRunner(object):
    """Runs mlxreg_ext CLI commands with --full_path and captures output."""

    def __init__(self, device=None):
        self.device = device
        self.output = ""
        self.success = False

    def run(self, verbose=True):
        return self.run_show_reg("MGIR", verbose=verbose)

    def get_error(self):
        for line in self.output.split('\n'):
            stripped = line.strip()
            if stripped.startswith('-E-'):
                return stripped
        return None

    def _base_cmd(self):
        cmd = MFT_SDK_REG_TOOL
        if self.device:
            cmd += " -d " + self.device
        return cmd

    def run_show_reg(self, register_name, full_path=True, verbose=True):
        # --show_reg takes the register name as its own argument.
        cmd = self._base_cmd() + " --show_reg {}".format(register_name)
        if full_path:
            cmd += " --full_path"
        cmd = "echo '{}' | sudo su".format(cmd)
        # merge_stderr=False: parse_show_reg() takes everything before the
        # first '|' as a field name, so any stderr text becomes a phantom field.
        self.success, self.output = CommandRunner.run(
            cmd, "Running {} --show_reg {} {}on {}".format(
                MFT_SDK_REG_TOOL,
                register_name,
                "--full_path " if full_path else "",
                self.device),
            verbose, merge_stderr=False)
        return self.success

    def get_field_names(self):
        return MlxregFullPathCliParser.parse_show_reg(self.output)

    def print_full_path_output(self):
        """Show mlxreg_ext --show_reg --full_path output for key registers."""
        for reg in Config.METADATA_REGISTERS:
            self.run_show_reg(reg, full_path=True)
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
        self.mlxreg_runner = MlxregFullPathCliRunner(self.device)
        self.mlxlink_runner = self.mlxreg_runner

    def _get_mlxlink_cmd(self):
        # Derived from the runner (so it follows MFT_SDK_REG_TOOL) plus the
        # flags this suite adds per call.
        return self.mlxreg_runner._base_cmd() + " --show_reg --full_path"

    def run_comparison(self):
        v = _verbose()
        results = {}

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)

        # Compare full-path metadata for each register
        for reg_name in Config.METADATA_REGISTERS:
            if not BaseConfig.SDK_ONLY:
                self.mlxreg_runner.run_show_reg(reg_name, full_path=True,
                                                verbose=v)
            c_names = self.c_runner.get_metadata_field_names(reg_name)
            cpp_names = self.cpp_runner.get_metadata_field_names(reg_name)
            mlxreg_names = (self.mlxreg_runner.get_field_names()
                            if not BaseConfig.SDK_ONLY else [])

            sdk_cmd = format_sdk_command(
                binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
                keywords=["GetRegisterMetadata"])
            mlxreg_cmd = "{} --show_reg {} --full_path".format(
                self.mlxreg_runner._base_cmd(), reg_name)
            if not BaseConfig.SDK_ONLY and not mlxreg_names:
                err = self.mlxreg_runner.get_error()
                print("\n{}WARNING: '{}' returned no fields{}{}".format(
                    RED, mlxreg_cmd,
                    ": " + err if err else "", RESET))

            if c_names or cpp_names or mlxreg_names:
                results["Full Path Metadata ({})".format(reg_name)] = \
                    FullPathMetadataComparisonTable(
                        reg_name, c_names, cpp_names, mlxreg_names,
                        self.device, self.device_type,
                        mlxreg_cmd, sdk_cmd).print_table()
            elif BaseConfig.SDK_ONLY:
                print_sdk_only_empty_agreement("Full Path Metadata {}".format(reg_name))
                results["Full Path Metadata ({})".format(reg_name)] = True
            else:
                print("\n{}Full Path Metadata {}: all sources returned "
                      "empty{}".format(RED, reg_name, RESET))
                results["Full Path Metadata ({})".format(reg_name)] = False

        # CREDENTIAL_HANDLE disambiguation check
        c_cred = self.c_runner.get_metadata_field_names("CREDENTIAL_HANDLE")
        cpp_cred = self.cpp_runner.get_metadata_field_names("CREDENTIAL_HANDLE")
        if not BaseConfig.SDK_ONLY:
            self.mlxreg_runner.run_show_reg(
                "CREDENTIAL_HANDLE", full_path=True, verbose=v)
        mlxreg_cred = (self.mlxreg_runner.get_field_names()
                       if not BaseConfig.SDK_ONLY else [])
        results["CREDENTIAL_HANDLE Disambiguation"] = \
            CredentialHandleDisambiguationTable(
                c_cred, cpp_cred, mlxreg_cred,
                self.device, self.device_type).print_table()

        # Print summary
        self._print_test_summary(results)
        return self.RESULT_PASS if all(results.values()) else self.RESULT_FAIL

    def _print_test_summary(self, results):
        print("\n" + "=" * 70)
        title = "FULL PATH TEST SUMMARY"
        if self.device:
            title += " [{} - {}]".format(self.device, self.device_type)
        print(title)
        print("=" * 70)
        for name, passed in results.items():
            status = GREEN + "PASS" + RESET if passed else RED + "FAIL" + RESET
            print("  {:<45}: {}".format(name, status))
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
    _print_usage_base(
        "Show {} --full_path output for first device".format(MFT_SDK_REG_TOOL))


def main():
    return run_main(
        Config, TestSuite, MlxregFullPathCliRunner,
        lambda r: r.print_full_path_output(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
