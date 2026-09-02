#!/usr/bin/env python
# SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
# Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#  Version: $Id$
#

"""
Test script for building and running operationalInfo tests from C and C++ files.
Builds using bazel inside docker, runs tests locally.
Supports comparison mode to compare C, C++, and mlxlink outputs.

Usage:
    ./test_operational_info.py              # Full test suite
    ./test_operational_info.py --compare    # Compare C, C++, mlxlink outputs
    ./test_operational_info.py --mlxlink    # Show mlxlink Operational Info only
    ./test_operational_info.py --help       # Show help
"""

from __future__ import print_function
import os
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from mlxlink_fields import (
    FIELD_OPERATIONAL_INFO, NA_FIELD_VALUE,
    FIELD_STATE, FIELD_PHYSICAL_STATE, FIELD_SPEED, FIELD_WIDTH,
    FIELD_FEC, FIELD_LOOPBACK_MODE, FIELD_AUTO_NEGOTIATION,
)
from utils import (
    RED, GREEN, YELLOW, BLUE, RESET,
    BaseConfig, clean_value, format_sdk_command, is_known_missing,
    MFT_SDK_LINK_TOOL,
    CommandRunner,
    BaseCTestRunner, BaseCppTestRunner, BaseMlxlinkRunner,
    BaseTestSuite,
    print_usage as _print_usage_base, run_main,
)


def _verbose():
    """Shorthand for verbose flag in comparison mode."""
    return BaseConfig.VERBOSE


# =============================================================================
# Configuration
# =============================================================================


class Config(BaseConfig):
    """Configuration constants for the operational info test runner."""

    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:op-info-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:op-info-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/op-info-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/op-info-cpp-test"
    # Whole fixture, not one named case — new MftSdkTelemetryTest cases (e.g.
    # DefaultPortAfterSpecificPortDoesNotThrow) must run here automatically.
    GTEST_FILTER = "MftSdkTelemetryTest.*"
    SUITE_NAME = "OperationalInfo"

    OPERATIONAL_INFO_FIELDS = [
        FIELD_STATE, FIELD_PHYSICAL_STATE, FIELD_SPEED, FIELD_WIDTH,
        FIELD_FEC, FIELD_LOOPBACK_MODE, FIELD_AUTO_NEGOTIATION,
    ]


# =============================================================================
# Parser
# =============================================================================


class OperationalInfoParser(object):
    """Parses Operational Info section from command output."""

    SECTION_HEADER = FIELD_OPERATIONAL_INFO

    @staticmethod
    def extract_section(output):
        """Extract Operational Info section from output."""
        lines = output.split('\n')
        result = []
        in_section = False

        for line in lines:
            if OperationalInfoParser.SECTION_HEADER in line:
                in_section = True
            elif in_section and line.strip() == '':
                break
            if in_section:
                result.append(line)

        return '\n'.join(result)

    @staticmethod
    def parse(output):
        """Parse Operational Info section into a dictionary."""
        section = OperationalInfoParser.extract_section(output)
        fields = {}
        known = set(Config.OPERATIONAL_INFO_FIELDS)

        for line in section.split('\n'):
            if ':' in line and '---' not in line and OperationalInfoParser.SECTION_HEADER not in line:
                parts = line.split(':', 1)
                if len(parts) == 2:
                    key = parts[0].strip()
                    if key in known:
                        fields[key] = clean_value(parts[1])

        # Normalize Width: strip trailing 'x' (e.g., "4x" -> "4")
        if FIELD_WIDTH in fields:
            fields[FIELD_WIDTH] = fields[FIELD_WIDTH].rstrip("xX")

        return fields


# =============================================================================
# Comparison Table
# =============================================================================


class ComparisonTable(object):
    """Prints a comparison table of Operational Info from multiple sources."""

    def __init__(self, c_fields, cpp_fields, mlxlink_fields, device=None, device_type=None):
        self.c_fields = c_fields
        self.cpp_fields = cpp_fields
        self.mlxlink_fields = mlxlink_fields
        self.device = device
        self.device_type = device_type

    def print_table(self):
        """Print the comparison table and return True if all fields match."""
        keys = Config.OPERATIONAL_INFO_FIELDS
        fw = max(len(k) for k in keys) + 2
        cw = max(len(str(self.c_fields.get(k, "-"))) for k in keys) + 2
        cpw = max(len(str(self.cpp_fields.get(k, "-"))) for k in keys) + 2
        mw = max(len(str(self.mlxlink_fields.get(k, "-"))) for k in keys) + 2

        print("")
        print("=" * 70)
        title = "OPERATIONAL INFO COMPARISON"
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 70)
        sdk_cmd = format_sdk_command(
            binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
            keywords=["OperationalInfo"])
        mlxlink_cmd = (MFT_SDK_LINK_TOOL + " -d " + self.device
                       if self.device else MFT_SDK_LINK_TOOL)
        print("{}SDK command:    {}{}".format(BLUE, sdk_cmd, RESET))
        print("{}mlxlink command: {}{}".format(BLUE, mlxlink_cmd, RESET))
        print("")

        sep = "+-{}-+-{}-+-{}-+-{}-+---------+".format(
            "-" * fw, "-" * cw, "-" * cpw, "-" * mw)
        print(sep)
        print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | Match   |".format(
            "Field", fw, "C", cw, "C++", cpw, "mlxlink", mw))
        print(sep)

        sdk_has_data = bool(self.c_fields) or bool(self.cpp_fields)

        match_count = 0
        known_count = 0
        for key in keys:
            c, cpp, mlx = self.c_fields.get(
                key, "-"), self.cpp_fields.get(key, "-"), self.mlxlink_fields.get(key, "-")
            if not sdk_has_data:
                status = RED + "  FAIL" + RESET
            elif (c == cpp and c in (NA_FIELD_VALUE, "-") and
                  mlx not in (NA_FIELD_VALUE, "-") and is_known_missing(key)):
                # Field the CLI reports but the SDK under test does not
                # populate, listed in MFT_SDK_KNOWN_MISSING: an expected
                # product divergence, not a DIFF. Only this direction is
                # relaxed — an SDK-side value still has to match below.
                known_count += 1
                status = YELLOW + " KNOWN" + RESET
            else:
                match = (c == cpp) if BaseConfig.SDK_ONLY else (c == cpp == mlx)
                match_count += match
                status = GREEN + "  OK  " + RESET if match else RED + "  DIFF" + RESET
            print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | {} |".format(
                key, fw, c, cw, cpp, cpw, mlx, mw, status))

        print(sep)
        diff_count = len(keys) - match_count - known_count
        parts = ["{} fields match".format(match_count),
                 "{} fields differ".format(diff_count)]
        if known_count:
            parts.append("{} expected-missing (MFT_SDK_KNOWN_MISSING)".format(known_count))
        if not sdk_has_data:
            parts.append("{}SDK tests produced no data{}".format(RED, RESET))
        print("\nSummary: " + ", ".join(parts))

        return match_count == len(keys) - known_count


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("C", Config, device)

    def get_operational_info(self):
        return OperationalInfoParser.parse(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("C++", Config, device)

    def get_operational_info(self):
        return OperationalInfoParser.parse(self.output)


class MlxlinkRunner(BaseMlxlinkRunner):
    def __init__(self, device=None):
        super(MlxlinkRunner, self).__init__("mlxlink", device)

    def get_operational_info(self):
        return OperationalInfoParser.parse(self.output)

    def print_operational_info_only(self):
        self.success, self.output = CommandRunner.run_quiet(
            self._cmd(), strip_ansi_escapes=True)
        print(OperationalInfoParser.extract_section(self.output))
        return 0 if self.success else 1


# =============================================================================
# Test Suite
# =============================================================================


class TestSuite(BaseTestSuite):
    def __init__(self, device_info):
        super(TestSuite, self).__init__(device_info, Config)
        self.c_runner = CTestRunner(self.device)
        self.cpp_runner = CppTestRunner(self.device)
        self.mlxlink_runner = MlxlinkRunner(self.device)

    def run_comparison(self):
        result = self._check_operational()
        if result is not None:
            return result

        c_fields, cpp_fields, mlxlink_fields = {}, {}, {}
        v = _verbose()

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
            c_fields = self.c_runner.get_operational_info()

        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)
            cpp_fields = self.cpp_runner.get_operational_info()

        if not BaseConfig.SDK_ONLY:
            if self.mlxlink_runner.run(verbose=v):
                mlxlink_fields = self.mlxlink_runner.get_operational_info()

        if c_fields or cpp_fields or mlxlink_fields:
            all_match = ComparisonTable(
                c_fields, cpp_fields, mlxlink_fields,
                self.device, self.device_type).print_table()
            return self.RESULT_PASS if all_match else self.RESULT_FAIL

        # No data from any runner — defer to error comparison so that runners
        # agreeing on a failure count as PASS (no SDK divergence).
        return self._compare_errors()


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base("Show mlxlink Operational Info (first device)")


def main():
    return run_main(
        Config, TestSuite, MlxlinkRunner,
        lambda r: r.print_operational_info_only(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
