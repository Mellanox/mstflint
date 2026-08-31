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
Test script for building and running FEC histogram tests from C and C++ files.
Builds using bazel inside docker, runs tests locally.
Supports comparison mode to compare C, C++, and mlxlink histogram outputs.

Usage:
    ./test_fec_histogram.py                    # Full test suite on first device
    ./test_fec_histogram.py --compare -d D     # Compare C, C++, mlxlink on specific device
    ./test_fec_histogram.py --compare-all      # Compare on ALL devices
    ./test_fec_histogram.py --mlxlink          # Show mlxlink histogram only
    ./test_fec_histogram.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from mlxlink_fields import FIELD_HISTOGRAM_OF_FEC_ERRORS
from utils import (
    RED, GREEN, BLUE, YELLOW, RESET,
    BaseConfig, clean_value, format_sdk_command, MFT_SDK_LINK_TOOL,
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
    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:fec-histogram-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:fec-histogram-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/fec-histogram-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/fec-histogram-cpp-test"
    GTEST_FILTER = "MftSdkFecHistogramTest.GetFecHistogram"
    MLXLINK_HISTOGRAM_ARGS = "--show_histogram --rx_fec_histogram"
    SUITE_NAME = "FEC Histogram"


# =============================================================================
# FEC Histogram Data Structures
# =============================================================================


class FecHistogramBin(object):
    def __init__(self, index, min_range, max_range, occurrences):
        self.index = index
        self.min_range = min_range
        self.max_range = max_range
        self.occurrences = occurrences

    def range_str(self):
        if self.min_range == self.max_range:
            return "[{}]".format(self.min_range)
        return "[{}:{}]".format(self.min_range, self.max_range)

    def display_str(self):
        return "{} {}".format(self.range_str(), self.occurrences)


class FecHistogramResult(object):
    def __init__(self):
        self.bins = []
        self.supported = False
        self.error_message = ""

    def num_bins(self):
        return len(self.bins)


# =============================================================================
# Parser
# =============================================================================


class FecHistogramParser(object):
    HISTOGRAM_HEADER = FIELD_HISTOGRAM_OF_FEC_ERRORS

    @staticmethod
    def _parse_bin_lines(output):
        """Parse bin lines from output (mlxlink-compatible and legacy C/C++ formats)."""
        bins = []
        for line in output.split('\n'):
            match = re.match(
                r'\s*Bin\s+(\d+)\s*:\s*\[(\d+)(?::(\d+))?\]\s+(\d+)', line)
            if match:
                idx, min_r = int(match.group(1)), int(match.group(2))
                max_r = int(match.group(3)) if match.group(3) else min_r
                bins.append(FecHistogramBin(
                    idx, min_r, max_r, int(match.group(4))))
                continue
            legacy = re.match(
                r'\s*Bin\s+(\d+)\s*:\s*minRange=(\d+)\s+maxRange=(\d+)\s+numOfErrors=(\d+)', line)
            if legacy:
                bins.append(FecHistogramBin(
                    int(legacy.group(1)), int(legacy.group(2)),
                    int(legacy.group(3)), int(legacy.group(4))))
        return bins

    @staticmethod
    def parse_mlxlink(output):
        """Parse mlxlink histogram output."""
        result = FecHistogramResult()
        if FecHistogramParser.HISTOGRAM_HEADER in output:
            result.supported = True
            result.bins = FecHistogramParser._parse_bin_lines(output)
            return result
        lines = output.split('\n')
        in_errors = False
        for line in lines:
            stripped = line.strip()
            if stripped == "Errors":
                in_errors = True
                continue
            if in_errors and stripped.startswith('---'):
                continue
            if in_errors and 'FEC Histogram' in line:
                error_lines = []
                for eline in lines[lines.index(line):]:
                    if eline.strip() == '':
                        break
                    error_lines.append(eline.strip())
                result.error_message = ' '.join(error_lines)
                break
        return result

    @staticmethod
    def parse_c_cpp(output):
        """Parse C/C++ test output for FEC histogram data."""
        result = FecHistogramResult()
        result.bins = FecHistogramParser._parse_bin_lines(output)
        if result.bins:
            result.supported = True
            return result
        for line in output.split('\n'):
            if 'Failed to get FEC histogram' in line:
                result.error_message = clean_value(line)
                break
        return result


# =============================================================================
# Comparison Table
# =============================================================================


class ComparisonTable(object):
    def __init__(self, c_result, cpp_result, mlxlink_result, device=None, device_type=None):
        self.c_result = c_result
        self.cpp_result = cpp_result
        self.mlxlink_result = mlxlink_result
        self.device = device
        self.device_type = device_type

    def print_table(self):
        """Print the comparison table and return True if all bins match."""
        print("\n" + "=" * 70)
        title = "FEC HISTOGRAM COMPARISON"
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 70)
        sdk_cmd = format_sdk_command(
            binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
            keywords=["FecHistogram"])
        mlxlink_cmd = MFT_SDK_LINK_TOOL + " -d " + self.device + " " + \
            Config.MLXLINK_HISTOGRAM_ARGS if self.device else MFT_SDK_LINK_TOOL
        print("{}SDK command:    {}{}".format(BLUE, sdk_cmd, RESET))
        print("{}mlxlink command: {}{}".format(BLUE, mlxlink_cmd, RESET))

        any_supported = self.c_result.supported or self.cpp_result.supported or self.mlxlink_result.supported
        if not any_supported:
            print("\n{}FEC Histogram not supported on this device{}".format(
                YELLOW, RESET))
            if self.mlxlink_result.error_message:
                print("mlxlink: " + self.mlxlink_result.error_message)
            if self.c_result.error_message:
                print("C:       " + self.c_result.error_message)
            if self.cpp_result.error_message:
                print("C++:     " + self.cpp_result.error_message)
            return True

        max_bins = max(self.c_result.num_bins(
        ), self.cpp_result.num_bins(), self.mlxlink_result.num_bins())
        c_strs = [self._bin_display(self.c_result, i) for i in range(max_bins)]
        cpp_strs = [self._bin_display(self.cpp_result, i)
                    for i in range(max_bins)]
        mlx_strs = [self._bin_display(self.mlxlink_result, i)
                    for i in range(max_bins)]

        bw = max(len("Bin"), max(len("Bin " + str(i))
                 for i in range(max_bins))) + 2
        cw = max(len("C"), max(len(s) for s in c_strs) if c_strs else 0) + 2
        cpw = max(len("C++"), max(len(s)
                  for s in cpp_strs) if cpp_strs else 0) + 2
        mw = max(len("mlxlink"), max(len(s)
                 for s in mlx_strs) if mlx_strs else 0) + 2

        print("")
        sep = "+-{}-+-{}-+-{}-+-{}-+---------+".format(
            "-" * bw, "-" * cw, "-" * cpw, "-" * mw)
        print(sep)
        print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | Match   |".format(
            "Bin", bw, "C", cw, "C++", cpw, "mlxlink", mw))
        print(sep)

        sdk_has_data = self.c_result.supported or self.cpp_result.supported

        match_count = 0
        for i in range(max_bins):
            if not sdk_has_data:
                status = RED + "  FAIL" + RESET
            else:
                match = self._bins_match(
                    self.c_result, self.cpp_result, self.mlxlink_result, i)
                match_count += match
                status = GREEN + "  OK  " + RESET if match else RED + "  DIFF" + RESET
            print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | {} |".format(
                "Bin " + str(i), bw, c_strs[i], cw, cpp_strs[i], cpw, mlx_strs[i], mw, status))
        print(sep)

        if BaseConfig.SDK_ONLY:
            num_bins_match = (self.c_result.num_bins() == self.cpp_result.num_bins())
            print("\nBin count: C={}, C++={}{}".format(
                self.c_result.num_bins(), self.cpp_result.num_bins(),
                "" if num_bins_match else RED + " (MISMATCH)" + RESET))
        else:
            num_bins_match = (self.c_result.num_bins() ==
                              self.cpp_result.num_bins() ==
                              self.mlxlink_result.num_bins())
            print("\nBin count: C={}, C++={}, mlxlink={}{}".format(
                self.c_result.num_bins(), self.cpp_result.num_bins(),
                self.mlxlink_result.num_bins(),
                "" if num_bins_match else RED + " (MISMATCH)" + RESET))
        diff_count = max_bins - match_count
        parts = ["{} bins match".format(match_count),
                 "{} bins differ".format(diff_count)]
        if not sdk_has_data:
            parts.append("{}SDK tests produced no data{}".format(RED, RESET))
        print("Summary: " + ", ".join(parts))
        return match_count == max_bins and num_bins_match and sdk_has_data

    @staticmethod
    def _bin_display(result, index):
        if not result.supported:
            return "-"
        if index < result.num_bins():
            b = result.bins[index]
            return "{} {}".format(b.range_str(), b.occurrences)
        return "(missing)"

    @staticmethod
    def _get_bin(result, index):
        if not result.supported or index >= result.num_bins():
            return None
        return result.bins[index]

    @staticmethod
    def _bins_match(c_result, cpp_result, mlxlink_result, index):
        """Check if bins match across sources.

        In SDK-only mode only C and C++ are compared (exact match).
        Otherwise occurrences may be monotonically non-decreasing
        (C <= C++ <= mlxlink) since live counters increment between reads.
        """
        c_bin = ComparisonTable._get_bin(c_result, index)
        cpp_bin = ComparisonTable._get_bin(cpp_result, index)

        if BaseConfig.SDK_ONLY:
            if c_bin is None and cpp_bin is None:
                return True
            if c_bin is None or cpp_bin is None:
                return False
            return (c_bin.range_str() == cpp_bin.range_str() and
                    c_bin.occurrences == cpp_bin.occurrences)

        mlx_bin = ComparisonTable._get_bin(mlxlink_result, index)
        available = [b for b in (c_bin, cpp_bin, mlx_bin) if b is not None]
        if not available:
            return True
        if len(available) != 3:
            return False
        if not (c_bin.range_str() == cpp_bin.range_str() == mlx_bin.range_str()):
            return False
        if c_bin.occurrences == cpp_bin.occurrences == mlx_bin.occurrences:
            return True
        return c_bin.occurrences <= cpp_bin.occurrences <= mlx_bin.occurrences


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("Histogram C", Config, device)

    def get_histogram(self):
        return FecHistogramParser.parse_c_cpp(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("Histogram C++", Config, device)

    def get_histogram(self):
        return FecHistogramParser.parse_c_cpp(self.output)


class MlxlinkHistogramRunner(BaseMlxlinkRunner):
    def __init__(self, device=None):
        super(MlxlinkHistogramRunner, self).__init__(
            "mlxlink histogram", device)

    def _cmd(self):
        return self._base_cmd() + " " + Config.MLXLINK_HISTOGRAM_ARGS

    def get_histogram(self):
        return FecHistogramParser.parse_mlxlink(self.output)

    def print_histogram_only(self):
        self.success, self.output = CommandRunner.run_quiet(
            self._cmd(), strip_ansi_escapes=True)
        result = self.get_histogram()
        if result.supported:
            print(FIELD_HISTOGRAM_OF_FEC_ERRORS)
            print("-----------------------")
            print("{:<35}: {:<10} {}".format("Header", "Range", "Occurrences"))
            for b in result.bins:
                print("{:<35}: {:<10} {}".format(
                    "Bin " + str(b.index), b.range_str(), b.occurrences))
        else:
            print("FEC Histogram not supported")
            if result.error_message:
                print(result.error_message)
        return 0 if self.success else 1


# =============================================================================
# Test Suite
# =============================================================================


class TestSuite(BaseTestSuite):
    def __init__(self, device_info):
        super(TestSuite, self).__init__(device_info, Config)
        self.c_runner = CTestRunner(self.device)
        self.cpp_runner = CppTestRunner(self.device)
        self.mlxlink_runner = MlxlinkHistogramRunner(self.device)

    @staticmethod
    def _print_raw_output(label, output):
        lines = output.split('\n')
        in_raw = False
        print("\n--- Raw {} output ---".format(label))
        for line in lines:
            if 'Raw FEC Histogram Data' in line:
                in_raw = True
            if in_raw:
                print(line)
                if line.strip() == '' and in_raw:
                    break
        if not in_raw:
            print("(no raw debug section found - rebuild with --build)")
        print("--- end {} ---".format(label))

    def run_comparison(self):
        result = self._check_operational()
        if result is not None:
            return result

        c_result = FecHistogramResult()
        cpp_result = FecHistogramResult()
        mlxlink_result = FecHistogramResult()

        v = _verbose()
        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
            c_result = self.c_runner.get_histogram()
        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)
            cpp_result = self.cpp_runner.get_histogram()
        if not BaseConfig.SDK_ONLY:
            self.mlxlink_runner.run(verbose=v)
            mlxlink_result = self.mlxlink_runner.get_histogram()

        if c_result.supported or cpp_result.supported or mlxlink_result.supported:
            all_match = ComparisonTable(
                c_result, cpp_result, mlxlink_result,
                self.device, self.device_type).print_table()
            return self.RESULT_PASS if all_match else self.RESULT_FAIL

        if c_result.error_message or cpp_result.error_message or mlxlink_result.error_message:
            ComparisonTable(
                c_result, cpp_result, mlxlink_result,
                self.device, self.device_type).print_table()
            return self.RESULT_SKIP

        # No data and no error message from any runner — defer to error
        # comparison so runners agreeing on a failure count as PASS.
        return self._compare_errors()


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base("Show mlxlink FEC histogram only (first device)")


def main():
    return run_main(
        Config, TestSuite, MlxlinkHistogramRunner,
        lambda r: r.print_histogram_only(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
