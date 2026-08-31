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
Test script for building and running physical counters tests from C and C++ files.
Builds using bazel inside docker, runs tests locally.
Supports comparison mode to compare C, C++, and mlxlink outputs.

Usage:
    ./test_counters.py                    # Full test suite on first device
    ./test_counters.py --compare -d D     # Compare C, C++, mlxlink on specific device
    ./test_counters.py --compare-all      # Compare on ALL devices
    ./test_counters.py --compare-all --so # Compare on ALL devices (pre-installed .so)
    ./test_counters.py --mlxlink          # Show mlxlink counters only
    ./test_counters.py --so               # Full test suite using pre-installed binaries
    ./test_counters.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from mlxlink_fields import (
    FIELD_PHYSICAL_COUNTERS_AND_BER_INFO,
    FIELD_TIME_SINCE_LAST_CLEAR, FIELD_SYMBOL_ERRORS, FIELD_SYMBOL_BER,
    FIELD_EFFECTIVE_PHYSICAL_ERRORS, FIELD_EFFECTIVE_PHYSICAL_BER,
    FIELD_RAW_PHYSICAL_ERRORS_PER_LANE, FIELD_RAW_PHYSICAL_BER_PER_LANE,
    FIELD_RAW_PHYSICAL_BER, FIELD_LINK_DOWN_COUNTER,
    FIELD_LINK_ERROR_RECOVERY_COUNTER,
)
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


def _format_bit_ranges(bits):
    """Format a sorted list of ints into compact ranges, e.g. [0,1,2,3,4] -> '0-4'."""
    if not bits:
        return ""
    ranges = []
    start = prev = bits[0]
    for b in bits[1:]:
        if b == prev + 1:
            prev = b
        else:
            ranges.append("{}-{}".format(start, prev) if prev > start else str(start))
            start = prev = b
    ranges.append("{}-{}".format(start, prev) if prev > start else str(start))
    return ",".join(ranges)


# =============================================================================
# Configuration
# =============================================================================


class Config(BaseConfig):
    """Configuration constants for the counters test runner."""

    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:counters-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:counters-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/counters-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/counters-cpp-test"
    GTEST_FILTER = "MftSdkCountersTest.GetCountersInfo"
    MLXLINK_COUNTERS_ARGS = "--show_counters"
    SUITE_NAME = "Counters"

    # Maps each field to its bit position in MstCountersInfo.header.valid_fields_mask.
    # Mirrors the TELEMETRY_COUNTERS_INFO_* defines in mft_sdk_telemetry_types.h.
    # Insertion order matches mlxlink --show_counters output.
    FIELD_CAPABILITY_BIT = {
        FIELD_TIME_SINCE_LAST_CLEAR: 0,
        FIELD_SYMBOL_ERRORS: 1,
        FIELD_SYMBOL_BER: 2,
        FIELD_EFFECTIVE_PHYSICAL_ERRORS: 3,
        FIELD_EFFECTIVE_PHYSICAL_BER: 4,
        FIELD_RAW_PHYSICAL_ERRORS_PER_LANE: 5,
        FIELD_RAW_PHYSICAL_BER_PER_LANE: 6,
        FIELD_RAW_PHYSICAL_BER: 7,
        FIELD_LINK_DOWN_COUNTER: 8,
        FIELD_LINK_ERROR_RECOVERY_COUNTER: 9,
    }


# =============================================================================
# Parser
# =============================================================================


class CountersParser(object):
    """Parses Physical Counters and BER Info section from command output."""

    SECTION_HEADER = FIELD_PHYSICAL_COUNTERS_AND_BER_INFO
    _VALID_FIELDS_RE = re.compile(r'(?<!extended )valid fields mask:\s*(0x[0-9a-fA-F]+)', re.IGNORECASE)
    _EXTENDED_VALID_FIELDS_RE = re.compile(r'Extended valid fields mask:\s*(0x[0-9a-fA-F]+)', re.IGNORECASE)

    @staticmethod
    def extract_section(output):
        """Extract counters section from output."""
        lines = output.split('\n')
        result = []
        in_section = False

        for line in lines:
            if CountersParser.SECTION_HEADER in line:
                in_section = True
            elif in_section and line.strip() == '':
                break
            if in_section:
                result.append(line)

        return '\n'.join(result)

    @staticmethod
    def parse_valid_fields_mask(output):
        """Extract the combined valid_fields_mask from the test output.

        The SDK header splits the logical 128-bit mask across two uint64_t
        fields (valid_fields_mask for bits 0-63, extended_valid_fields_mask
        for bits 64-127).  Python supports arbitrary-precision integers, so
        we combine them into a single value.

        Returns the mask as an int, or None if not found.
        """
        m = CountersParser._VALID_FIELDS_RE.search(output)
        if not m:
            return None
        mask = int(m.group(1), 16)
        ext = CountersParser._EXTENDED_VALID_FIELDS_RE.search(output)
        if ext:
            mask |= int(ext.group(1), 16) << 64
        return mask

    @staticmethod
    def parse(output):
        """Parse counters section into a dictionary."""
        section = CountersParser.extract_section(output)
        fields = {}
        known = set(Config.FIELD_CAPABILITY_BIT)

        for line in section.split('\n'):
            if ':' not in line or '---' in line:
                continue
            if CountersParser.SECTION_HEADER in line:
                continue
            parts = line.split(':', 1)
            if len(parts) == 2:
                key = parts[0].strip()
                if key in known:
                    fields[key] = clean_value(parts[1])

        return fields


# =============================================================================
# Comparison Table
# =============================================================================


class ComparisonTable(object):
    """Prints a comparison table of Counters from multiple sources.

    Compares C, C++, and mlxlink values for all fields.
    The Valid fields mask column cross-checks whether the SDK's
    valid_fields_mask correctly reflects mlxlink data presence.
    """

    def __init__(self, c_fields, cpp_fields, mlxlink_fields,
                 valid_fields_mask=None,
                 device=None, device_type=None):
        self.c_fields = c_fields
        self.cpp_fields = cpp_fields
        self.mlxlink_fields = mlxlink_fields
        self.valid_fields_mask = valid_fields_mask
        self.device = device
        self.device_type = device_type

    @staticmethod
    def _mask_bit_parts(mask, bit_min=0, bit_max=64):
        """Return (on_str, off_str) with compact bit ranges.

        Only considers field bits in [bit_min, bit_max).  The mask is
        tested with the bit position shifted down by *bit_min* so that
        the extended mask (bits 64-127 stored in a uint64_t) works
        correctly.
        """
        all_bits = sorted(b for b in Config.FIELD_CAPABILITY_BIT.values()
                          if bit_min <= b < bit_max)
        on = [b for b in all_bits if mask & (1 << (b - bit_min))]
        off = [b for b in all_bits if not (mask & (1 << (b - bit_min)))]
        return (_format_bit_ranges(on), _format_bit_ranges(off))

    @staticmethod
    def _has_data(value):
        """Return True if a field value represents actual data (not missing/N/A)."""
        return value not in ("-", "N/A")

    def _is_bit_available(self, field_name):
        """Check whether a field is available according to valid_fields_mask."""
        bit = Config.FIELD_CAPABILITY_BIT.get(field_name)
        if bit is None:
            return True
        if self.valid_fields_mask is None:
            return True
        return bool(self.valid_fields_mask & (1 << bit))

    def _check_valid_mask(self, field_name, mlx_value):
        """Check if valid_fields_mask bit matches mlxlink data presence.

        Skipped in SDK-only mode because mlxlink was not run, so
        mlx_value is always "-" and the comparison would be meaningless.
        """
        if BaseConfig.SDK_ONLY:
            return None
        if self.valid_fields_mask is None:
            return None
        bit = Config.FIELD_CAPABILITY_BIT.get(field_name)
        if bit is None:
            return None
        return bool(self.valid_fields_mask & (1 << bit)) == self._has_data(mlx_value)

    def _tolerant_match(self, key, c, cpp, mlx):
        """Match with tolerance for live counter fields.

        Time Since Last Clear: allow ±0.5 min for sampling drift.
        Raw Physical Errors Per Lane: allow monotonic growth C <= C++ <= mlxlink.
        All other fields: exact equality.
        """
        if key == FIELD_TIME_SINCE_LAST_CLEAR:
            try:
                vals = [float(v) for v in (c, cpp, mlx)
                        if v not in ("-", "N/A")]
                if len(vals) >= 2:
                    return max(vals) - min(vals) <= 0.5
            except ValueError:
                pass

        if key == FIELD_RAW_PHYSICAL_ERRORS_PER_LANE:
            try:
                c_lanes = [int(x) for x in c.split(',')]
                cpp_lanes = [int(x) for x in cpp.split(',')]
                mlx_lanes = [int(x) for x in mlx.split(',')]
                if len(c_lanes) == len(cpp_lanes) == len(mlx_lanes):
                    return all(a <= b <= m
                               for a, b, m
                               in zip(c_lanes, cpp_lanes, mlx_lanes))
            except (ValueError, AttributeError):
                pass

        if BaseConfig.SDK_ONLY:
            return c == cpp
        return c == cpp == mlx

    @staticmethod
    def _status_cell(ok, labels, width=6):
        """Return a colored status cell padded to *width* visible characters."""
        if ok is None:
            txt = labels[2] if len(labels) > 2 else "--"
        else:
            txt = labels[0] if ok else labels[1]
        padded = "  {:<{}}".format(txt, width - 2)
        if ok is None:
            return padded
        return (GREEN if ok else RED) + padded + RESET

    def print_table(self):
        """Print the comparison table and return True if all compared fields match."""
        fields = Config.FIELD_CAPABILITY_BIT
        labels = {k: "{}: {}".format(bit, k) for k, bit in fields.items()}
        fw = max(len(v) for v in labels.values()) + 2
        cw = max(max(len(str(self.c_fields.get(k, "-")))
                 for k in fields), len("C")) + 2
        cpw = max(max(len(str(self.cpp_fields.get(k, "-")))
                  for k in fields), len("C++")) + 2
        mw = max(max(len(str(self.mlxlink_fields.get(k, "-")))
                 for k in fields), len("mlxlink")) + 2
        vfm = "Valid fields mask"

        print("")
        print("=" * 70)
        title = "COUNTERS COMPARISON"
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 70)
        sdk_cmd = format_sdk_command(
            binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
            keywords=["CountersInfo"])
        mlxlink_cmd = MFT_SDK_LINK_TOOL + " -d " + self.device + \
            " " + Config.MLXLINK_COUNTERS_ARGS if self.device else MFT_SDK_LINK_TOOL
        print("{}SDK command:    {}{}".format(BLUE, sdk_cmd, RESET))
        print("{}mlxlink command: {}{}".format(BLUE, mlxlink_cmd, RESET))
        if self.valid_fields_mask is not None:
            low = self.valid_fields_mask & ((1 << 64) - 1)
            high = self.valid_fields_mask >> 64
            for label, value, bmin, bmax in [
                ("Valid fields mask:         ", low, 0, 64),
                ("Extended valid fields mask:", high, 64, 128),
            ]:
                on, off = self._mask_bit_parts(value, bmin, bmax)
                parts = []
                if on:
                    parts.append("{}Bits {} set{}".format(GREEN, on, RESET))
                if off:
                    parts.append("{}Bits {} unset{}".format(RED, off, RESET))
                if not on and not off:
                    parts.append("no fields defined")
                detail = " ({})".format(", ".join(parts))
                print("{} 0x{:x}{}".format(label, value, detail))
        print("")

        vw = max(len(vfm), 6) + 2
        sep = "+-{}-+-{}-+-{}-+-{}-+---------+-{}-+".format(
            "-" * fw, "-" * cw, "-" * cpw, "-" * mw, "-" * vw)
        row_fmt = "| {:<{}} | {:<{}} | {:<{}} | {:<{}} | {} | {} |"
        print(sep)
        print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | Match   | {:<{}} |".format(
            "Field", fw, "C", cw, "C++", cpw, "mlxlink", mw, vfm, vw))
        print(sep)

        sdk_has_data = bool(self.c_fields) or bool(self.cpp_fields)

        match_count = 0
        diff_count = 0
        skip_count = 0
        mask_ok = 0
        mask_fail = 0
        for key in sorted(fields, key=lambda k: fields[k]):
            c = self.c_fields.get(key, "-")
            cpp = self.cpp_fields.get(key, "-")
            mlx = self.mlxlink_fields.get(key, "-")

            available = self._is_bit_available(key)
            if not available:
                skip_count += 1
                status = YELLOW + " SKIP " + RESET
            elif not sdk_has_data:
                diff_count += 1
                status = RED + "  FAIL" + RESET
            elif self._tolerant_match(key, c, cpp, mlx):
                match_count += 1
                status = GREEN + "  OK  " + RESET
            else:
                diff_count += 1
                status = RED + "  DIFF" + RESET

            mr = self._check_valid_mask(key, mlx)
            mask_ok += mr is True
            mask_fail += mr is False
            mask_str = self._status_cell(mr, ("OK", "FAIL"), vw)

            print(row_fmt.format(
                labels[key], fw, c, cw, cpp, cpw, mlx, mw, status, mask_str))

        print(sep)
        compared_count = match_count + diff_count
        parts = ["{} compared".format(compared_count),
                 "{} match".format(match_count),
                 "{} differ".format(diff_count)]
        if skip_count:
            parts.append("{} skipped (mask)".format(skip_count))
        if not sdk_has_data:
            parts.append("{}SDK tests produced no data{}".format(RED, RESET))
        print("\nMatch summary:              " + ", ".join(parts))
        if mask_ok or mask_fail:
            mask_total = mask_ok + mask_fail
            mask_status = "{}{} mismatch{}".format(RED, mask_fail, RESET) \
                if mask_fail else "{}all OK{}".format(GREEN, RESET)
            print("Valid fields mask summary:  {} checked, {}".format(
                mask_total, mask_status))

        return diff_count == 0


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("Counters C", Config, device)

    def get_counters(self):
        return CountersParser.parse(self.output)

    def get_valid_fields_mask(self):
        return CountersParser.parse_valid_fields_mask(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("Counters C++", Config, device)

    def get_counters(self):
        return CountersParser.parse(self.output)

    def get_valid_fields_mask(self):
        return CountersParser.parse_valid_fields_mask(self.output)


class MlxlinkCountersRunner(BaseMlxlinkRunner):
    def __init__(self, device=None):
        super(MlxlinkCountersRunner, self).__init__(
            "mlxlink counters", device)

    def _cmd(self):
        return self._base_cmd() + " " + Config.MLXLINK_COUNTERS_ARGS

    def get_counters(self):
        return CountersParser.parse(self.output)

    def print_counters_only(self):
        self.success, self.output = CommandRunner.run_quiet(
            self._cmd(), strip_ansi_escapes=True)
        print(CountersParser.extract_section(self.output))
        return 0 if self.success else 1


# =============================================================================
# Test Suite
# =============================================================================


class TestSuite(BaseTestSuite):
    def __init__(self, device_info):
        super(TestSuite, self).__init__(device_info, Config)
        self.c_runner = CTestRunner(self.device)
        self.cpp_runner = CppTestRunner(self.device)
        self.mlxlink_runner = MlxlinkCountersRunner(self.device)

    def run_comparison(self):
        c_fields, cpp_fields, mlxlink_fields = {}, {}, {}
        valid_fields_mask = None
        v = _verbose()

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
            c_fields = self.c_runner.get_counters()
            valid_fields_mask = self.c_runner.get_valid_fields_mask()

        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)
            cpp_fields = self.cpp_runner.get_counters()
            if valid_fields_mask is None:
                valid_fields_mask = self.cpp_runner.get_valid_fields_mask()

        if not BaseConfig.SDK_ONLY:
            self.mlxlink_runner.run(verbose=v)
            mlxlink_fields = self.mlxlink_runner.get_counters()

        if c_fields or cpp_fields:
            all_match = ComparisonTable(
                c_fields, cpp_fields, mlxlink_fields,
                valid_fields_mask=valid_fields_mask,
                device=self.device,
                device_type=self.device_type).print_table()
            return self.RESULT_PASS if all_match else self.RESULT_FAIL

        return self._compare_errors()


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base("Show mlxlink Physical Counters (first device)")


def main():
    return run_main(
        Config, TestSuite, MlxlinkCountersRunner,
        lambda r: r.print_counters_only(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
