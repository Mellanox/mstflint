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
Test script for the resource dump error handling tests.
Checks that the C and C++ APIs return the same status for every rejection case,
and that `resourcedump` rejects an unadvertised segment just like the SDK does.

Usage:
    ./test_error_handling.py                    # Full test suite on first device
    ./test_error_handling.py --compare -d D     # Compare C, C++, resourcedump on a device
    ./test_error_handling.py --compare-all      # Compare on ALL devices
    ./test_error_handling.py --mlxreg           # Show resourcedump output for first device
    ./test_error_handling.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from resource_dump_fields import (
    RD_SECTION_ERROR_HANDLING,
    RD_FIELD_CASE,
    RD_FIELD_STATUS,
    RD_FIELD_TOTAL,
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


# Kept in step with UNSUPPORTED_SEGMENT in the C/C++ error handling tests.
UNSUPPORTED_SEGMENT = 0xdead

# Cases whose status the SDK must report identically from C and C++.
EXPECTED_STATUS = {
    "NullDeviceMenu": "MST_ERROR_INVALID_ARGUMENT",
    "NullMenuOut": "MST_ERROR_INVALID_ARGUMENT",
    "FreeNullMenu": "MST_ERROR_INVALID_ARGUMENT",
    "NullDeviceDump": "MST_ERROR_INVALID_ARGUMENT",
    "NullRequest": "MST_ERROR_INVALID_ARGUMENT",
    "NullDumpOut": "MST_ERROR_INVALID_ARGUMENT",
    "FreeNullDump": "MST_ERROR_INVALID_ARGUMENT",
    "NullFilename": "MST_ERROR_INVALID_ARGUMENT",
    "UndersizedBuffer": "MST_ERROR_INSUFFICIENT_BUFFER",
    "UnwritableFile": "MST_ERROR_FAILED_TO_DUMP_RESOURCE",
}


def _verbose():
    return BaseConfig.VERBOSE


# =============================================================================
# Configuration
# =============================================================================


class Config(BaseConfig):
    C_TEST_TARGET = "//user/mft_sdk/unit_tests/resource_dump:error-handling-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/resource_dump:error-handling-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/resource_dump/error-handling-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/resource_dump/error-handling-cpp-test"
    GTEST_FILTER = "MftSdkResourceDumpErrorTest.*"
    C_SO_SUITE = "resource_dump_error_handling"
    SUITE_NAME = "ResourceDumpErrorHandling"


# =============================================================================
# Parser
# =============================================================================


class ErrorCaseParser(object):
    """Parses the `Case:` / `Status:` pairs the C/C++ tests print."""

    _CASE = re.compile(r'^' + re.escape(RD_FIELD_CASE) + r':\s*(\S+)$')
    _STATUS = re.compile(r'^' + re.escape(RD_FIELD_STATUS) + r':\s*(\S+)$')

    @staticmethod
    def parse(output):
        cases = {}
        current = None
        in_section = False
        for line in output.split('\n'):
            if RD_SECTION_ERROR_HANDLING in line:
                in_section = True
                continue
            if not in_section:
                continue
            stripped = line.strip()
            if stripped.startswith(RD_FIELD_TOTAL + ':'):
                continue
            case_match = ErrorCaseParser._CASE.match(stripped)
            if case_match:
                current = case_match.group(1)
                continue
            status_match = ErrorCaseParser._STATUS.match(stripped)
            if status_match and current is not None:
                cases[current] = status_match.group(1)
                current = None
        return cases


# =============================================================================
# Comparison Table
# =============================================================================


class ErrorComparisonTable(object):
    def __init__(self, c_cases, cpp_cases, cli_rejected, device=None,
                 device_type=None):
        self.c_cases = c_cases or {}
        self.cpp_cases = cpp_cases or {}
        self.cli_rejected = cli_rejected
        self.device = device
        self.device_type = device_type

    def print_table(self):
        print("")
        print("=" * 78)
        title = "RESOURCE DUMP ERROR HANDLING COMPARISON"
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 78)
        sdk_cmd = format_sdk_command(
            binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
            keywords=["ResourceDump"])
        print("{}SDK command:          {}{}".format(BLUE, sdk_cmd, RESET))
        print("{}resourcedump command: {} dump -d {} -s 0x{:x}{}".format(
            BLUE, MFT_SDK_RESOURCE_DUMP_TOOL, self.device or "<device>",
            UNSUPPORTED_SEGMENT, RESET))
        print("")

        all_cases = sorted(set(self.c_cases) | set(self.cpp_cases) |
                           set(EXPECTED_STATUS))
        sep = "+----------------------+-----------------------------------+-----------------------------------+-------+"
        print(sep)
        print("| {:<20} | {:<33} | {:<33} | Match |".format(
            "Case", "C", "C++"))
        print(sep)

        failures = 0
        for case in all_cases:
            c_status = self.c_cases.get(case, "-")
            cpp_status = self.cpp_cases.get(case, "-")
            expected = EXPECTED_STATUS.get(case)
            match = (c_status == cpp_status and c_status != "-")
            if match and expected is not None and c_status != expected:
                match = False
            mark = GREEN + " YES " + RESET if match else RED + " NO  " + RESET
            print("| {:<20} | {:<33} | {:<33} |{}|".format(
                case, c_status, cpp_status, mark))
            if not match:
                failures += 1
                if expected is not None and c_status not in ("-", expected):
                    print("|   expected {}".format(expected))
        print(sep)

        if not BaseConfig.SDK_ONLY:
            print("")
            if self.cli_rejected is None:
                print("{}resourcedump was not run for the unsupported "
                      "segment{}".format(YELLOW, RESET))
            elif self.cli_rejected:
                print("{}resourcedump also rejects segment 0x{:x}{}".format(
                    GREEN, UNSUPPORTED_SEGMENT, RESET))
            else:
                print("{}resourcedump accepted segment 0x{:x} that the SDK "
                      "rejects{}".format(RED, UNSUPPORTED_SEGMENT, RESET))
                failures += 1

        print("\nSummary: {} cases, {} mismatches".format(
            len(all_cases), failures))
        if failures:
            print("{}FAIL: {} error handling mismatches{}".format(
                RED, failures, RESET))
            return False
        print("{}All error handling cases agree{}".format(GREEN, RESET))
        return True


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("C", Config, device)

    def get_cases(self):
        return ErrorCaseParser.parse(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("C++", Config, device)

    def get_cases(self):
        return ErrorCaseParser.parse(self.output)


class ResourceDumpCliRunner(object):
    def __init__(self, device=None):
        self.device = device
        self.output = ""
        self.success = False

    def run(self, verbose=True):
        return self.run_unsupported_segment(verbose=verbose)

    def get_error(self):
        for line in self.output.split('\n'):
            if line.strip().startswith('-E-'):
                return line.strip()
        return None

    def run_unsupported_segment(self, verbose=True):
        cmd = "{} dump -d {} -s 0x{:x}".format(
            MFT_SDK_RESOURCE_DUMP_TOOL, self.device, UNSUPPORTED_SEGMENT)
        self.success, self.output = CommandRunner.run(
            "echo '{}' | sudo su".format(cmd),
            "Dumping unsupported segment with resourcedump on {}".format(
                self.device),
            verbose)
        return self.success

    def rejected_unsupported_segment(self):
        """True when the CLI refused the segment, the way the SDK does."""
        return (not self.success) or self.get_error() is not None

    def print_cli_output(self):
        self.run_unsupported_segment()
        print(self.output)
        return 0


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
        return "{} dump -d {} -s 0x{:x}".format(
            MFT_SDK_RESOURCE_DUMP_TOOL, self.device or "<device>",
            UNSUPPORTED_SEGMENT)

    def run_comparison(self):
        v = _verbose()

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)

        cli_rejected = None
        if not BaseConfig.SDK_ONLY:
            self.cli_runner.run_unsupported_segment(verbose=v)
            cli_rejected = self.cli_runner.rejected_unsupported_segment()

        c_cases = self.c_runner.get_cases()
        cpp_cases = self.cpp_runner.get_cases()

        if c_cases or cpp_cases:
            passed = ErrorComparisonTable(
                c_cases, cpp_cases, cli_rejected,
                self.device, self.device_type).print_table()
            return self.RESULT_PASS if passed else self.RESULT_FAIL

        print("\n{}No error handling data from any source{}".format(RED, RESET))
        return self.RESULT_FAIL


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base(
        "Show resourcedump output for an unsupported segment on first device")


def main():
    return run_main(
        Config, TestSuite, ResourceDumpCliRunner,
        lambda r: r.print_cli_output(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
