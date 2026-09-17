#!/usr/bin/env python
# Copyright (c) 2020-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

"""
Test script for error handling tests (negative / invalid input tests).
SDK-only comparison (no mlxreg_ext CLI comparison needed).

Usage:
    ./test_error_handling.py                    # Full test suite on first device
    ./test_error_handling.py --compare -d D     # Compare C, C++ on specific device
    ./test_error_handling.py --compare-all      # Compare on ALL devices
    ./test_error_handling.py --help             # Show help
"""

from __future__ import print_function
import os
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from utils import (
    RED, GREEN, BLUE, RESET,
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
    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxreg:error-handling-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxreg:error-handling-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxreg/error-handling-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxreg/error-handling-cpp-test"
    GTEST_FILTER = "MftSdkErrorHandlingTest.*"
    SUITE_NAME = "ErrorHandling"


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("C", Config, device)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("C++", Config, device)


class DummyMlxregRunner(object):
    """Placeholder runner (error handling is SDK-only, no CLI comparison)."""
    def __init__(self, device=None):
        self.device = device
        self.output = ""
        self.success = True

    def run(self, verbose=True):
        return True

    def get_error(self):
        return None

    def print_mlxreg_output(self):
        print("Error handling tests are SDK-only (no mlxreg_ext comparison)")
        return 0


# =============================================================================
# Test Suite
# =============================================================================


class TestSuite(BaseTestSuite):
    def __init__(self, device_info):
        super(TestSuite, self).__init__(device_info, Config)
        self.c_runner = CTestRunner(self.device)
        self.cpp_runner = CppTestRunner(self.device)
        self.mlxreg_runner = DummyMlxregRunner(self.device)
        self.mlxlink_runner = self.mlxreg_runner

    def _get_mlxlink_cmd(self):
        return "(SDK-only error handling tests)"

    def run_comparison(self):
        v = _verbose()

        c_ok = False
        cpp_ok = False

        if os.path.exists(Config.C_TEST_BIN):
            c_ok = self.c_runner.run(verbose=v)
        if os.path.exists(Config.CPP_TEST_BIN):
            cpp_ok = self.cpp_runner.run(verbose=v)

        print("\n" + "=" * 70)
        title = "ERROR HANDLING (SDK-only)"
        if self.device:
            title += " [{} - {}]".format(self.device, self.device_type)
        print(title)
        print("=" * 70)
        sdk_cmd = format_sdk_command(
            binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
            keywords=["Register"])
        print("{}SDK command:    {}{}".format(BLUE, sdk_cmd, RESET))
        print("")

        c_status = GREEN + "PASS" + RESET if c_ok else RED + "FAIL" + RESET
        cpp_status = GREEN + "PASS" + RESET if cpp_ok else RED + "FAIL" + RESET
        print("  C test:   {}".format(c_status))
        print("  C++ test: {}".format(cpp_status))
        print("=" * 70)

        passed = c_ok and cpp_ok
        if passed:
            print("{}Overall: ALL TESTS PASSED{}".format(GREEN, RESET))
        else:
            print("{}Overall: SOME TESTS FAILED{}".format(RED, RESET))
        print("=" * 70)

        return self.RESULT_PASS if passed else self.RESULT_FAIL


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base("Error handling tests are SDK-only (no --mlxreg mode)")


def main():
    return run_main(
        Config, TestSuite, DummyMlxregRunner,
        lambda r: r.print_mlxreg_output(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
