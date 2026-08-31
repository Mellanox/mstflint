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
Test script for building and running Module Info tests from C and C++ files.
Builds using bazel inside docker, runs tests locally.
Supports comparison mode to compare C, C++, and mlxlink Module Info outputs.

Usage:
    ./test_module_info.py                    # Full test suite on first device
    ./test_module_info.py --compare -d D     # Compare C, C++, mlxlink on specific device
    ./test_module_info.py --compare-all      # Compare on ALL devices
    ./test_module_info.py --compare-all --so # Compare on ALL devices (pre-installed .so)
    ./test_module_info.py --mlxlink          # Show mlxlink Module Info only
    ./test_module_info.py --so               # Full test suite using pre-installed binaries
    ./test_module_info.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import sys
from collections import OrderedDict
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from mlxlink_fields import (
    FIELD_MODULE_INFO, FIELD_ATTENUATION,
    FIELD_SNR_MEDIA_LANES, FIELD_SNR_HOST_LANES, NA_FIELD_VALUE,
)
from utils import (
    RED, GREEN, BLUE, RESET,
    BaseConfig, clean_value, format_sdk_command, MFT_SDK_LINK_TOOL,
    CommandRunner,
    BaseCTestRunner, BaseCppTestRunner, BaseMlxlinkRunner,
    BaseTestSuite,
    print_usage as _print_usage_base, run_main,
)


def _verbose():
    """Shorthand for verbose flag in comparison mode."""
    return BaseConfig.VERBOSE


def _ordered_union(first, second):
    """Keys of *first* in their output order, then keys only in *second*."""
    return list(first) + [k for k in second if k not in first]


def _attenuation_label(rate):
    """Per-rate attenuation label. Keep in sync with module_info_test.c."""
    return "{} ({}) [dB]".format(FIELD_ATTENUATION, rate)


# mlxlink prints one combined attenuation row whose key lists the rates,
# e.g. "Attenuation (5g,7g,12g,25g)[dB]"; the SDK tests print one row per
# rate.  Both forms are normalized to per-rate labels while parsing.
_ATTENUATION_KEY_RE = re.compile(
    r'^' + re.escape(FIELD_ATTENUATION) + r'\s*\(([^)]*)\)')

# SNR is a live measurement; C and C++ read it seconds apart, so allow
# per-lane jitter between the two reads (a structural bug — wrong lane,
# zeroed data — is far larger than this).
_SNR_TOLERANCE_DB = 3.0


def _lanes_close(a, b):
    """Compare two comma-separated numeric lane lists within the SNR
    tolerance.  Returns None when either side is not such a list."""
    try:
        a_vals = [float(x) for x in a.split(',')]
        b_vals = [float(x) for x in b.split(',')]
    except (ValueError, AttributeError):
        return None
    return (len(a_vals) == len(b_vals) and
            all(abs(x - y) <= _SNR_TOLERANCE_DB
                for x, y in zip(a_vals, b_vals)))


# =============================================================================
# Configuration
# =============================================================================


class Config(BaseConfig):
    """Configuration constants for the Module Info test runner."""

    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:module-info-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:module-info-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/module-info-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/module-info-cpp-test"
    GTEST_FILTER = "MftSdkModuleInfoTest.GetModuleInfo"
    MLXLINK_MODULE_ARGS = "--show_module"
    SUITE_NAME = "Module Info"


# The SDK tests print the raw SDK value for these labels, which mlxlink
# (by construction) renders differently, so they are compared between the
# C and C++ outputs only and skipped in the mlxlink comparison:
#   - enum ints:    the SDK stores the raw enum value, mlxlink decodes a name
#   - per-lane:     the SDK prints all MAX_NUM_OF_LANES lanes, mlxlink only
#                   the active ones (any "[per lane]" label plus the four
#                   lane arrays below)
#   - reformatted:  units/precision/layout differ, e.g. FW Version: the SDK
#                   stores the parts in uint8 fields, truncating free-running
#                   numbers > 255
MLX_INCOMPATIBLE_FIELDS = frozenset([
    # enum ints
    "Identifier", "Cable Technology", "Cable Type", "OUI",
    "Module State", "Rx Power Type", "Error Code Response",
    # per-lane arrays without the "[per lane]" label suffix
    "CDR RX", "CDR TX", FIELD_SNR_MEDIA_LANES, FIELD_SNR_HOST_LANES,
    # reformatted values
    "FW Version", "Transfer Distance [m]", "Intra-ASIC Latency [ns]",
    "Module Datapath Latency [ns]", "Round Trip Latency [ns]",
    "Memory Map Revision", "Linear Direct Drive", "SMF Length",
    "Cable Rx AMP", "Cable Rx Emphasis (Pre)", "Cable Rx Post Emphasis",
    "Cable Tx Equalization", "Wavelength Tolerance", "Nominal bit rate",
    "Manufacturing Date", "Module FW Fault", "DataPath FW Fault",
])


def _mlx_comparable(key):
    """True when the SDK renders *key* exactly as mlxlink prints it."""
    return (key not in MLX_INCOMPATIBLE_FIELDS and
            not key.endswith("[per lane]"))


# =============================================================================
# Parser
# =============================================================================


class ModuleInfoParser(object):
    """Parses Module Info section from command output."""

    SECTION_HEADER = FIELD_MODULE_INFO
    _MASK_RE = re.compile(
        r'^((?:Extended )?valid fields mask):\s*(0x[0-9a-fA-F]+)',
        re.IGNORECASE | re.MULTILINE)

    @staticmethod
    def extract_section(output):
        """Extract Module Info section from output."""
        lines = output.split('\n')
        result = []
        in_section = False

        for line in lines:
            if ModuleInfoParser.SECTION_HEADER in line:
                in_section = True
            elif in_section and line.strip() == '':
                break
            if in_section:
                result.append(line)

        return '\n'.join(result)

    @staticmethod
    def parse_masks(output):
        """Parse the mask lines the SDK tests print above the section into
        an ordered {label: int} mapping (empty for mlxlink, which prints
        no mask lines)."""
        masks = OrderedDict()
        for m in ModuleInfoParser._MASK_RE.finditer(output):
            masks[m.group(1)] = int(m.group(2), 16)
        return masks

    @staticmethod
    def parse(output):
        """Parse Module Info section into an ordered {label: value} mapping.

        One generic parser for the C test, the C++ test and mlxlink: every
        "label: value" row of the section is taken as-is, except attenuation
        rows, which are split into per-rate labels (see _ATTENUATION_KEY_RE).
        """
        section = ModuleInfoParser.extract_section(output)
        fields = OrderedDict()

        for line in section.split('\n'):
            if ':' not in line or '---' in line:
                continue
            if ModuleInfoParser.SECTION_HEADER in line:
                continue
            key, value = line.split(':', 1)
            key = key.strip()
            att = _ATTENUATION_KEY_RE.match(key)
            if att:
                rates = [r.strip() for r in att.group(1).split(',') if r.strip()]
                vals = [clean_value(v) for v in value.split(',')]
                for rate, val in zip(rates, vals):
                    fields[_attenuation_label(rate)] = val
            else:
                fields[key] = clean_value(value)

        return fields


# =============================================================================
# Comparison Table
# =============================================================================


class ComparisonTable(object):
    """Prints a comparison table of Module Info from multiple sources.

    C and C++ are compared over the union of their labels — a label missing
    from one side is a difference.  mlxlink is additionally compared for
    every shared label the SDK renders mlxlink-compatibly (the C test
    intentionally prints mlxlink-compatible labels).  The SDK masks are
    compared directly between C and C++, and their popcount is cross-checked
    against the number of fields printed with data.
    """

    def __init__(self, c_fields, cpp_fields, mlxlink_fields,
                 c_masks=None, cpp_masks=None,
                 device=None, device_type=None):
        self.c_fields = c_fields
        self.cpp_fields = cpp_fields
        self.mlxlink_fields = mlxlink_fields
        self.c_masks = c_masks or {}
        self.cpp_masks = cpp_masks or {}
        self.device = device
        self.device_type = device_type

    def _row_match(self, key):
        """True when C and C++ (and mlxlink, where comparable) agree on *key*."""
        if key not in self.c_fields or key not in self.cpp_fields:
            return False
        c, cpp = self.c_fields[key], self.cpp_fields[key]
        if key in (FIELD_SNR_MEDIA_LANES, FIELD_SNR_HOST_LANES):
            close = _lanes_close(c, cpp)
            if close is not None:
                return close
        if c != cpp:
            return False
        if (BaseConfig.SDK_ONLY or not _mlx_comparable(key) or
                key not in self.mlxlink_fields):
            return True
        return c == self.mlxlink_fields[key]

    @staticmethod
    def _status(ok):
        return (GREEN + "OK" if ok else RED + "MISMATCH") + RESET

    def _print_masks(self):
        """Print the C vs C++ mask values and the coverage cross-check.

        The C and C++ tests print the same SDK header masks, so the values
        must match exactly.  Coverage checks that the number of set mask
        bits equals the number of fields printed with data — every printed
        field is guarded by exactly one mask bit.

        Returns True when the masks agree and coverage is consistent.
        """
        ok = True
        for label in _ordered_union(self.c_masks, self.cpp_masks):
            c = self.c_masks.get(label)
            cpp = self.cpp_masks.get(label)
            row = "{:<28} C: {:<22} C++: {:<22}".format(
                label + ":",
                "0x{:x}".format(c) if c is not None else "-",
                "0x{:x}".format(cpp) if cpp is not None else "-")
            if c is not None and cpp is not None:
                same = c == cpp
                ok = ok and same
                row += " " + self._status(same)
            print(row)

        fields = self.c_fields or self.cpp_fields
        masks = self.c_masks or self.cpp_masks
        if fields and masks:
            bits = sum(bin(v).count('1') for v in masks.values())
            data = sum(1 for v in fields.values() if v != NA_FIELD_VALUE)
            same = bits == data
            ok = ok and same
            print("{:<28} {} mask bits set, {}/{} printed fields have data {}".format(
                "Coverage:", bits, data, len(fields), self._status(same)))
        return ok

    def print_table(self):
        """Print the comparison table and return True if everything matches."""
        keys = _ordered_union(self.c_fields, self.cpp_fields)
        fw = max(max(len(k) for k in keys), len("Field")) + 2
        cw = max(max(len(self.c_fields.get(k, "-"))
                 for k in keys), len("C")) + 2
        cpw = max(max(len(self.cpp_fields.get(k, "-"))
                  for k in keys), len("C++")) + 2
        mw = max(max(len(self.mlxlink_fields.get(k, "-"))
                 for k in keys), len("mlxlink")) + 2

        print("")
        print("=" * 70)
        title = "MODULE INFO COMPARISON"
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 70)
        sdk_cmd = format_sdk_command(
            binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
            keywords=["ModuleInfo"])
        mlxlink_cmd = MFT_SDK_LINK_TOOL + " -d " + self.device + \
            " " + Config.MLXLINK_MODULE_ARGS if self.device else MFT_SDK_LINK_TOOL
        print("{}SDK command:    {}{}".format(BLUE, sdk_cmd, RESET))
        print("{}mlxlink command: {}{}".format(BLUE, mlxlink_cmd, RESET))
        masks_ok = self._print_masks()
        print("")

        sep = "+-{}-+-{}-+-{}-+-{}-+---------+".format(
            "-" * fw, "-" * cw, "-" * cpw, "-" * mw)
        print(sep)
        print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | Match   |".format(
            "Field", fw, "C", cw, "C++", cpw, "mlxlink", mw))
        print(sep)

        match_count = 0
        for key in keys:
            match = self._row_match(key)
            match_count += match
            status = GREEN + "  OK  " + RESET if match else RED + "  DIFF" + RESET
            print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | {} |".format(
                key, fw, self.c_fields.get(key, "-"), cw,
                self.cpp_fields.get(key, "-"), cpw,
                self.mlxlink_fields.get(key, "-"), mw, status))

        print(sep)
        diff_count = len(keys) - match_count
        print("\nMatch summary: {} compared, {} match, {} differ".format(
            len(keys), match_count, diff_count))

        return diff_count == 0 and masks_ok


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("Module Info C", Config, device)

    def get_module_info(self):
        return ModuleInfoParser.parse(self.output)

    def get_masks(self):
        return ModuleInfoParser.parse_masks(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("Module Info C++", Config, device)

    def get_module_info(self):
        return ModuleInfoParser.parse(self.output)

    def get_masks(self):
        return ModuleInfoParser.parse_masks(self.output)


class MlxlinkModuleRunner(BaseMlxlinkRunner):
    def __init__(self, device=None):
        super(MlxlinkModuleRunner, self).__init__(
            "mlxlink module info", device)

    def _cmd(self):
        return self._base_cmd() + " " + Config.MLXLINK_MODULE_ARGS

    def get_module_info(self):
        return ModuleInfoParser.parse(self.output)

    def print_module_info_only(self):
        self.success, self.output = CommandRunner.run_quiet(
            self._cmd(), strip_ansi_escapes=True)
        print(ModuleInfoParser.extract_section(self.output))
        return 0 if self.success else 1


# =============================================================================
# Test Suite
# =============================================================================


class TestSuite(BaseTestSuite):
    def __init__(self, device_info):
        super(TestSuite, self).__init__(device_info, Config)
        self.c_runner = CTestRunner(self.device)
        self.cpp_runner = CppTestRunner(self.device)
        self.mlxlink_runner = MlxlinkModuleRunner(self.device)

    def run_comparison(self):
        result = self._check_operational()
        if result is not None:
            return result

        c_fields, cpp_fields, mlxlink_fields = {}, {}, {}
        c_masks, cpp_masks = {}, {}
        v = _verbose()

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
            c_fields = self.c_runner.get_module_info()
            c_masks = self.c_runner.get_masks()

        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)
            cpp_fields = self.cpp_runner.get_module_info()
            cpp_masks = self.cpp_runner.get_masks()

        if not BaseConfig.SDK_ONLY:
            self.mlxlink_runner.run(verbose=v)
            mlxlink_fields = self.mlxlink_runner.get_module_info()

        if c_fields or cpp_fields:
            all_match = ComparisonTable(
                c_fields, cpp_fields, mlxlink_fields,
                c_masks=c_masks, cpp_masks=cpp_masks,
                device=self.device,
                device_type=self.device_type).print_table()
            return self.RESULT_PASS if all_match else self.RESULT_FAIL

        return self._compare_errors()


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base("Show mlxlink Module Info (first device)")


def main():
    return run_main(
        Config, TestSuite, MlxlinkModuleRunner,
        lambda r: r.print_module_info_only(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
