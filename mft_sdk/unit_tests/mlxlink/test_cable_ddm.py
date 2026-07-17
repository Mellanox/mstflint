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
Test script for building and running Cable DDM tests from C and C++ files.
Builds using bazel inside docker, runs tests locally.
Supports comparison mode to compare C, C++, and mlxlink DDM outputs.

Usage:
    ./test_cable_ddm.py                    # Full test suite on first device
    ./test_cable_ddm.py --compare -d D     # Compare C, C++, mlxlink on specific device
    ./test_cable_ddm.py --compare-all      # Compare on ALL devices
    ./test_cable_ddm.py --compare-all --so # Compare on ALL devices (pre-installed .so)
    ./test_cable_ddm.py --mlxlink          # Show mlxlink DDM only
    ./test_cable_ddm.py --so               # Full test suite using pre-installed binaries
    ./test_cable_ddm.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from mlxlink_fields import (
    DDM_SECTION_CABLE_DDM_INFO, DDM_SECTION_DDM_FLAGS,
    DDM_SECTION_DDM_THRESHOLDS,
    DDM_FIELD_TEMPERATURE, DDM_FIELD_VOLTAGE, DDM_FIELD_CHANNELS,
    DDM_FIELD_RX_POWER, DDM_FIELD_TX_POWER, DDM_FIELD_TX_BIAS,
    DDM_FIELD_THRESHOLDS,
    DDM_FIELD_TEMPERATURE_ALARM_HIGH, DDM_FIELD_TEMPERATURE_ALARM_LOW,
    DDM_FIELD_TEMPERATURE_WARNING_HIGH, DDM_FIELD_TEMPERATURE_WARNING_LOW,
    DDM_FIELD_VOLTAGE_ALARM_HIGH, DDM_FIELD_VOLTAGE_ALARM_LOW,
    DDM_FIELD_VOLTAGE_WARNING_HIGH, DDM_FIELD_VOLTAGE_WARNING_LOW,
    DDM_FIELD_RX_POWER_ALARM_HIGH, DDM_FIELD_RX_POWER_ALARM_LOW,
    DDM_FIELD_RX_POWER_WARNING_HIGH, DDM_FIELD_RX_POWER_WARNING_LOW,
    DDM_FIELD_TX_POWER_ALARM_HIGH, DDM_FIELD_TX_POWER_ALARM_LOW,
    DDM_FIELD_TX_POWER_WARNING_HIGH, DDM_FIELD_TX_POWER_WARNING_LOW,
    DDM_FIELD_TX_BIAS_ALARM_HIGH, DDM_FIELD_TX_BIAS_ALARM_LOW,
    DDM_FIELD_TX_BIAS_WARNING_HIGH, DDM_FIELD_TX_BIAS_WARNING_LOW,
    DDM_FIELD_HIGH_ALARM_THRESHOLD, DDM_FIELD_LOW_ALARM_THRESHOLD,
    DDM_FIELD_HIGH_WARNING_THRESHOLD, DDM_FIELD_LOW_WARNING_THRESHOLD,
)
from utils import (
    RED, GREEN, BLUE, YELLOW, RESET,
    BaseConfig, clean_value, format_sdk_command,
    CommandRunner,
    BaseCTestRunner, BaseCppTestRunner, BaseMlxlinkRunner,
    BaseTestSuite,
    print_usage as _print_usage_base, run_main,
)


def _verbose():
    """Shorthand for verbose flag in comparison mode."""
    return BaseConfig.VERBOSE


_VOLTAGE_RE = re.compile(r'^([0-9.]+)\s*V$', re.IGNORECASE)


def _parse_voltage(val):
    """Extract numeric voltage value from a string like '3313.0000V'."""
    m = _VOLTAGE_RE.match(val.strip())
    return float(m.group(1)) if m else None


def _ddm_info_match_fn(field_name, c_val, cpp_val, mlx_val):
    """Custom match for DDM info fields.

    Voltage: SDK returns millivolts, mlxlink returns volts.  Convert SDK
    values by dividing by 1000 and compare with 0.02V tolerance — the three
    values come from three separate hardware reads seconds apart, so the
    supply voltage jitters a few mV between them (a wrong-unit bug is a
    1000x error and still trips this easily).
    """
    if field_name == DDM_FIELD_VOLTAGE:
        mlx_v = _parse_voltage(mlx_val)
        if mlx_v is None:
            return None
        c_v = _parse_voltage(c_val)
        cpp_v = _parse_voltage(cpp_val)
        if c_v is not None and c_v > 100:
            c_v /= 1000.0
        if cpp_v is not None and cpp_v > 100:
            cpp_v /= 1000.0
        vals = [v for v in (c_v, cpp_v, mlx_v) if v is not None]
        if len(vals) >= 2:
            return max(vals) - min(vals) < 0.02
    return None


_MEASURE_RE = re.compile(r'^(-?(?:inf|[0-9]+(?:\.[0-9]+)?))\s*([A-Za-z]+)$')


def _parse_measure(val):
    """Parse '<number><unit>' like '0.910687 dBm', '-infdBm' or '13C' into
    (float, unit); the space before the unit is optional (mlxlink omits it)."""
    m = _MEASURE_RE.match(val.strip())
    return (float(m.group(1)), m.group(2)) if m else None


def _threshold_match_fn(field_name, c_val, cpp_val, mlx_val):
    """Thresholds are static values; mlxlink rounds them to 3 decimals and
    omits the space before the unit, so compare numerically (0.001 covers
    the display rounding) instead of textually."""
    vals = [c_val, cpp_val] if BaseConfig.SDK_ONLY else [c_val, cpp_val, mlx_val]
    parsed = [_parse_measure(v) for v in vals]
    if any(p is None for p in parsed):
        return None
    if len(set(u for _, u in parsed)) != 1:
        return False
    nums = [n for n, _ in parsed]
    if any(abs(n) == float("inf") for n in nums):
        return all(n == nums[0] for n in nums)
    return max(nums) - min(nums) <= 0.001


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
    """Configuration constants for the Cable DDM test runner."""

    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:cable-ddm-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:cable-ddm-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/cable-ddm-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/cable-ddm-cpp-test"
    GTEST_FILTER = "MftSdkCableDDMTest.GetCableDDMInfo"
    MLXLINK_DDM_ARGS = "--cable --ddm"
    SUITE_NAME = "Cable DDM"

    FIELD_CAPABILITY_BIT = {
        DDM_FIELD_TEMPERATURE: 0,
        DDM_FIELD_VOLTAGE: 1,
        "Number of Channels": 2,
        "Flags": 3,
        DDM_FIELD_CHANNELS: 4,
        DDM_FIELD_RX_POWER: 4,
        DDM_FIELD_TX_POWER: 4,
        DDM_FIELD_TX_BIAS: 4,
        DDM_FIELD_THRESHOLDS: 5,
    }


# =============================================================================
# Field Display Orders (match mlxlink output ordering)
# =============================================================================

DDM_FLAG_ORDER = [
    DDM_FIELD_TEMPERATURE_ALARM_HIGH,
    DDM_FIELD_TEMPERATURE_WARNING_HIGH,
    DDM_FIELD_TEMPERATURE_WARNING_LOW,
    DDM_FIELD_TEMPERATURE_ALARM_LOW,
    DDM_FIELD_VOLTAGE_ALARM_HIGH,
    DDM_FIELD_VOLTAGE_WARNING_HIGH,
    DDM_FIELD_VOLTAGE_WARNING_LOW,
    DDM_FIELD_VOLTAGE_ALARM_LOW,
]

CHANNEL_FLAG_ORDER = [
    DDM_FIELD_RX_POWER_ALARM_HIGH,
    DDM_FIELD_RX_POWER_WARNING_HIGH,
    DDM_FIELD_RX_POWER_WARNING_LOW,
    DDM_FIELD_RX_POWER_ALARM_LOW,
    DDM_FIELD_TX_POWER_ALARM_HIGH,
    DDM_FIELD_TX_POWER_WARNING_HIGH,
    DDM_FIELD_TX_POWER_WARNING_LOW,
    DDM_FIELD_TX_POWER_ALARM_LOW,
    DDM_FIELD_TX_BIAS_ALARM_HIGH,
    DDM_FIELD_TX_BIAS_WARNING_HIGH,
    DDM_FIELD_TX_BIAS_WARNING_LOW,
    DDM_FIELD_TX_BIAS_ALARM_LOW,
]

THRESHOLD_ORDER = [
    DDM_FIELD_HIGH_ALARM_THRESHOLD,
    DDM_FIELD_HIGH_WARNING_THRESHOLD,
    DDM_FIELD_LOW_WARNING_THRESHOLD,
    DDM_FIELD_LOW_ALARM_THRESHOLD,
]

THRESHOLD_FIELDS = [
    DDM_FIELD_TEMPERATURE,
    DDM_FIELD_VOLTAGE,
    DDM_FIELD_RX_POWER,
    DDM_FIELD_TX_POWER,
    DDM_FIELD_TX_BIAS,
]

THRESHOLD_NAMES = set(THRESHOLD_ORDER)


# =============================================================================
# DDM Data Structures
# =============================================================================


class DDMChannelInfo(object):
    def __init__(self, channel, rx_power="-", tx_power="-", tx_bias="-"):
        self.channel = channel
        self.rx_power = rx_power
        self.tx_power = tx_power
        self.tx_bias = tx_bias


class DDMResult(object):
    def __init__(self):
        self.fields = {}
        self.channels = []
        self.ddm_flags = {}
        self.channel_flags = []
        self.thresholds = {}
        self.supported = False
        self.error_message = ""


# =============================================================================
# Parser
# =============================================================================


class CableDDMParser(object):
    """Parses Cable DDM output from C/C++ tests and mlxlink."""

    _VALID_FIELDS_RE = re.compile(r'(?<!extended )valid fields mask:\s*(0x[0-9a-fA-F]+)', re.IGNORECASE)
    _EXTENDED_VALID_FIELDS_RE = re.compile(r'Extended valid fields mask:\s*(0x[0-9a-fA-F]+)', re.IGNORECASE)
    _SEPARATOR_RE = re.compile(r'^-+$')

    @staticmethod
    def parse_valid_fields_mask(output):
        """Extract the combined valid_fields_mask from the test output.

        The SDK header splits the logical 128-bit mask across two uint64_t
        fields (valid_fields_mask for bits 0-63, extended_valid_fields_mask
        for bits 64-127).  Python supports arbitrary-precision integers, so
        we combine them into a single value.
        """
        m = CableDDMParser._VALID_FIELDS_RE.search(output)
        if not m:
            return None
        mask = int(m.group(1), 16)
        ext = CableDDMParser._EXTENDED_VALID_FIELDS_RE.search(output)
        if ext:
            mask |= int(ext.group(1), 16) << 64
        return mask

    @staticmethod
    def parse_c_cpp(output):
        """Parse C/C++ test output for all DDM sections."""
        result = DDMResult()

        if 'Failed to get cable DDM info' in output:
            for line in output.split('\n'):
                if 'Failed to get cable DDM info' in line:
                    result.error_message = clean_value(line)
                    break
            return result

        section = 'pre'
        current_channel = None
        current_threshold_group = None
        ch_flags_idx = -1

        for raw_line in output.split('\n'):
            stripped = raw_line.strip()
            if not stripped:
                continue

            if stripped.startswith('[') or CableDDMParser._SEPARATOR_RE.match(stripped):
                continue

            if stripped.startswith('Cable DDM') and 'Failed' not in stripped:
                section = 'info'
                result.supported = True
                current_channel = None
                continue

            if re.match(r'^DDM Flags\s*:?\s*$', stripped):
                section = 'ddm_flags'
                current_channel = None
                continue

            ch_flags_m = re.match(r'^Channel\s+(\d+)\s+Flags\s*:?\s*$', stripped)
            if ch_flags_m:
                section = 'channel_flags'
                ch_flags_idx = int(ch_flags_m.group(1)) - 1
                while len(result.channel_flags) <= ch_flags_idx:
                    result.channel_flags.append({})
                continue

            if ':' not in stripped:
                continue

            parts = stripped.split(':', 1)
            if len(parts) != 2:
                continue
            key = parts[0].strip()
            raw_val = parts[1].strip()

            if key in THRESHOLD_FIELDS and not raw_val:
                section = 'threshold'
                current_threshold_group = key
                continue

            val = clean_value(raw_val)

            if section == 'pre' and key in (DDM_FIELD_TEMPERATURE, DDM_FIELD_VOLTAGE):
                section = 'info'
                result.supported = True

            ch_m = re.match(r'^Channel\s+(\d+)$', key)
            if ch_m and section == 'info':
                current_channel = int(ch_m.group(1))
                while len(result.channels) < current_channel:
                    result.channels.append(DDMChannelInfo(len(result.channels) + 1))
                continue

            if section == 'info':
                if key == DDM_FIELD_TEMPERATURE:
                    result.fields[DDM_FIELD_TEMPERATURE] = val
                elif key == DDM_FIELD_VOLTAGE:
                    result.fields[DDM_FIELD_VOLTAGE] = val
                elif key == DDM_FIELD_CHANNELS:
                    result.fields[DDM_FIELD_CHANNELS] = val
                elif current_channel and current_channel <= len(result.channels):
                    ch = result.channels[current_channel - 1]
                    if key == DDM_FIELD_RX_POWER:
                        ch.rx_power = val
                    elif key == DDM_FIELD_TX_POWER:
                        ch.tx_power = val
                    elif key == DDM_FIELD_TX_BIAS:
                        ch.tx_bias = val

            elif section == 'ddm_flags':
                result.ddm_flags[key] = val

            elif section == 'channel_flags' and ch_flags_idx >= 0:
                result.channel_flags[ch_flags_idx][key] = val

            elif section == 'threshold' and current_threshold_group and key in THRESHOLD_NAMES:
                result.thresholds[(key, current_threshold_group)] = val

        return result

    @staticmethod
    def parse_mlxlink(output):
        """Parse mlxlink --cable --ddm output for all DDM sections."""
        result = DDMResult()

        if 'No plugged cable detected' in output or 'Showing DDM info raised' in output:
            for line in output.split('\n'):
                if 'No plugged cable' in line or 'DDM info raised' in line:
                    result.error_message = clean_value(line)
                    break
            return result

        section = None
        ch_flags_idx = -1
        threshold_field_names = []

        for raw_line in output.split('\n'):
            stripped = raw_line.strip()
            if not stripped:
                continue

            if CableDDMParser._SEPARATOR_RE.match(stripped):
                continue

            if stripped == DDM_SECTION_CABLE_DDM_INFO:
                section = 'info'
                result.supported = True
                continue
            if stripped == DDM_SECTION_DDM_FLAGS:
                section = 'ddm_flags'
                continue
            ch_flags_m = re.match(r'^Channel\s+(\d+)\s+Flags$', stripped)
            if ch_flags_m:
                section = 'channel_flags'
                ch_flags_idx = int(ch_flags_m.group(1)) - 1
                while len(result.channel_flags) <= ch_flags_idx:
                    result.channel_flags.append({})
                continue
            if stripped == 'Channel Flags':
                section = 'channel_flags'
                ch_flags_idx = 0
                while len(result.channel_flags) <= ch_flags_idx:
                    result.channel_flags.append({})
                continue
            if stripped == DDM_SECTION_DDM_THRESHOLDS:
                section = 'thresholds'
                continue

            # Other mlxlink section headers reset context
            if (not stripped.startswith((' ', '\t')) and
                    stripped.endswith((' Info', ' info', 'Troubleshooting Info',
                                      'Information', 'Thresholds')) and
                    section is not None and ':' not in stripped):
                section = None
                continue

            if ':' not in stripped:
                continue

            parts = stripped.split(':', 1)
            if len(parts) != 2:
                continue
            key = parts[0].strip()
            raw_val = parts[1].strip()

            if section == 'info':
                if key == DDM_FIELD_TEMPERATURE:
                    result.fields[DDM_FIELD_TEMPERATURE] = clean_value(raw_val)
                elif key == DDM_FIELD_VOLTAGE:
                    result.fields[DDM_FIELD_VOLTAGE] = clean_value(raw_val)
                elif key == DDM_FIELD_CHANNELS:
                    ch_names = [v.strip() for v in raw_val.split(',') if v.strip()]
                    result.fields[DDM_FIELD_CHANNELS] = str(len(ch_names))
                    while len(result.channels) < len(ch_names):
                        result.channels.append(
                            DDMChannelInfo(len(result.channels) + 1))
                elif key in (DDM_FIELD_RX_POWER, DDM_FIELD_TX_POWER, DDM_FIELD_TX_BIAS):
                    vals = [clean_value(v) for v in raw_val.split(',') if v.strip()]
                    for idx, v in enumerate(vals):
                        while len(result.channels) <= idx:
                            result.channels.append(
                                DDMChannelInfo(len(result.channels) + 1))
                        ch = result.channels[idx]
                        if key == DDM_FIELD_RX_POWER:
                            ch.rx_power = v
                        elif key == DDM_FIELD_TX_POWER:
                            ch.tx_power = v
                        elif key == DDM_FIELD_TX_BIAS:
                            ch.tx_bias = v

            elif section == 'ddm_flags':
                result.ddm_flags[key] = clean_value(raw_val)

            elif section == 'channel_flags' and ch_flags_idx >= 0:
                result.channel_flags[ch_flags_idx][key] = clean_value(raw_val)

            elif section == 'thresholds':
                if key == DDM_FIELD_THRESHOLDS:
                    threshold_field_names = [
                        clean_value(v) for v in raw_val.split(',') if v.strip()]
                else:
                    vals = [clean_value(v) for v in raw_val.split(',') if v.strip()]
                    th_key = None
                    for tn in THRESHOLD_NAMES:
                        if tn.lower() == key.lower():
                            th_key = tn
                            break
                    if th_key:
                        for i, v in enumerate(vals):
                            if i < len(threshold_field_names):
                                result.thresholds[(th_key, threshold_field_names[i])] = v

        if DDM_FIELD_CHANNELS not in result.fields and result.channels:
            result.fields[DDM_FIELD_CHANNELS] = str(len(result.channels))

        return result


# =============================================================================
# Comparison Tables
# =============================================================================


class ComparisonTable(object):
    """Prints comparison tables for Cable DDM data from multiple sources.

    Generates a separate table for each DDM section:
      - Cable DDM Information (scalars + per-channel data)
      - DDM Flags (temperature/voltage alarm/warning flags)
      - Channel N Flags (per-channel RX/TX/Bias flags)
      - DDM Thresholds (alarm/warning threshold values)
    """

    def __init__(self, c_result, cpp_result, mlxlink_result,
                 valid_fields_mask=None,
                 device=None, device_type=None):
        self.c_result = c_result
        self.cpp_result = cpp_result
        self.mlxlink_result = mlxlink_result
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
        all_bits = sorted(set(b for b in Config.FIELD_CAPABILITY_BIT.values()
                              if bit_min <= b < bit_max))
        on = [b for b in all_bits if mask & (1 << (b - bit_min))]
        off = [b for b in all_bits if not (mask & (1 << (b - bit_min)))]
        return (_format_bit_ranges(on), _format_bit_ranges(off))

    @staticmethod
    def _has_data(value):
        """Return True if a field value represents actual data (not missing/N/A)."""
        return value not in ("-", "N/A")

    def _is_bit_available(self, bit):
        if self.valid_fields_mask is None:
            return True
        return bool(self.valid_fields_mask & (1 << bit))

    def _valid_mask_for_bit(self, bit, mlx_value):
        """Check if valid_fields_mask bit matches mlxlink data presence.

        Skipped in SDK-only mode because mlxlink was not run, so
        mlx_value is always "-" and the comparison would be meaningless.
        """
        if BaseConfig.SDK_ONLY:
            return None
        if self.valid_fields_mask is None:
            return None
        return bool(self.valid_fields_mask & (1 << bit)) == self._has_data(mlx_value)

    def _info_valid_fn(self, field_name, mlx_value):
        """Valid-mask checker for the Cable DDM Information section."""
        if field_name == DDM_FIELD_TEMPERATURE:
            return self._valid_mask_for_bit(0, mlx_value)
        if field_name == DDM_FIELD_VOLTAGE:
            return self._valid_mask_for_bit(1, mlx_value)
        return self._valid_mask_for_bit(4, mlx_value)

    def _flags_valid_fn(self, field_name, mlx_value):
        """Valid-mask checker for DDM Flags and Channel Flags sections."""
        return self._valid_mask_for_bit(3, mlx_value)

    def _threshold_valid_fn(self, field_name, mlx_value):
        """Valid-mask checker for the DDM Thresholds section."""
        return self._valid_mask_for_bit(5, mlx_value)

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

    @staticmethod
    def _print_section_table(title, rows, cap_fn=None, valid_fn=None,
                             match_fn=None):
        """Print one comparison section table.

        Args:
            title:    section title string
            rows:     list of (field_name, c_val, cpp_val, mlx_val) tuples
            cap_fn:   optional callable(field_name) -> bool for availability
            valid_fn: optional callable(field_name, mlx_val) -> bool/None
            match_fn: optional callable(field_name, c, cpp, mlx) ->
                      True/False/None for custom match logic

        Returns:
            (match_count, diff_count, skip_count, mask_ok, mask_fail) tuple
        """
        if not rows:
            return 0, 0, 0, 0, 0

        fw = max(max(len(r[0]) for r in rows), len("Field"))
        cw = max(max(len(str(r[1])) for r in rows), len("C"))
        cpw = max(max(len(str(r[2])) for r in rows), len("C++"))
        mw = max(max(len(str(r[3])) for r in rows), len("mlxlink"))

        has_valid = valid_fn is not None
        vfm = "Valid fields mask"
        vw = max(len(vfm), 6) if has_valid else 0

        if has_valid:
            sep = "+-{}-+-{}-+-{}-+-{}-+---------+-{}-+".format(
                "-" * fw, "-" * cw, "-" * cpw, "-" * mw, "-" * vw)
        else:
            sep = "+-{}-+-{}-+-{}-+-{}-+---------+".format(
                "-" * fw, "-" * cw, "-" * cpw, "-" * mw)

        print("\n" + title)
        print(sep)
        if has_valid:
            print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | Match   | {:<{}} |".format(
                "Field", fw, "C", cw, "C++", cpw, "mlxlink", mw, vfm, vw))
        else:
            print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | Match   |".format(
                "Field", fw, "C", cw, "C++", cpw, "mlxlink", mw))
        print(sep)

        match_count = 0
        diff_count = 0
        skip_count = 0
        mask_ok = 0
        mask_fail = 0

        for key, c_val, cpp_val, mlx_val in rows:
            available = cap_fn(key) if cap_fn else True

            if not available:
                skip_count += 1
                status = YELLOW + " SKIP " + RESET
            else:
                custom = match_fn(key, c_val, cpp_val, mlx_val) if match_fn else None
                default_ok = (c_val == cpp_val) if BaseConfig.SDK_ONLY else (c_val == cpp_val == mlx_val)
                if custom is True or (custom is None and default_ok):
                    match_count += 1
                    status = GREEN + "  OK  " + RESET
                else:
                    diff_count += 1
                    status = RED + "  DIFF" + RESET

            if has_valid:
                mr = valid_fn(key, mlx_val)
                mask_ok += mr is True
                mask_fail += mr is False
                mask_str = ComparisonTable._status_cell(
                    mr, ("OK", "FAIL"), vw)
                print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | {} | {} |".format(
                    key, fw, c_val, cw, cpp_val, cpw, mlx_val, mw,
                    status, mask_str))
            else:
                print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | {} |".format(
                    key, fw, c_val, cw, cpp_val, cpw, mlx_val, mw, status))

        print(sep)
        return match_count, diff_count, skip_count, mask_ok, mask_fail

    # ----- Row Builders -----

    def _build_info_rows(self):
        rows = []
        for key in (DDM_FIELD_TEMPERATURE, DDM_FIELD_VOLTAGE):
            rows.append((key,
                         self.c_result.fields.get(key, "-"),
                         self.cpp_result.fields.get(key, "-"),
                         self.mlxlink_result.fields.get(key, "-")))

        rows.append((DDM_FIELD_CHANNELS,
                     self.c_result.fields.get(DDM_FIELD_CHANNELS, "-"),
                     self.cpp_result.fields.get(DDM_FIELD_CHANNELS, "-"),
                     self.mlxlink_result.fields.get(DDM_FIELD_CHANNELS, "-")))

        max_ch = max(len(self.c_result.channels),
                     len(self.cpp_result.channels),
                     len(self.mlxlink_result.channels))
        for i in range(max_ch):
            c_ch = (self.c_result.channels[i] if i < len(self.c_result.channels)
                    else DDMChannelInfo(i + 1))
            cpp_ch = (self.cpp_result.channels[i] if i < len(self.cpp_result.channels)
                      else DDMChannelInfo(i + 1))
            mlx_ch = (self.mlxlink_result.channels[i] if i < len(self.mlxlink_result.channels)
                      else DDMChannelInfo(i + 1))
            pfx = "Ch{} ".format(i + 1)
            for metric, attr in [(DDM_FIELD_RX_POWER, "rx_power"),
                                 (DDM_FIELD_TX_POWER, "tx_power"),
                                 (DDM_FIELD_TX_BIAS, "tx_bias")]:
                rows.append((pfx + metric,
                             getattr(c_ch, attr),
                             getattr(cpp_ch, attr),
                             getattr(mlx_ch, attr)))
        return rows

    def _info_cap_fn(self, field_name):
        if field_name == DDM_FIELD_TEMPERATURE:
            return self._is_bit_available(0)
        if field_name == DDM_FIELD_VOLTAGE:
            return self._is_bit_available(1)
        return self._is_bit_available(4)

    def _build_ddm_flags_rows(self):
        rows = []
        for flag in DDM_FLAG_ORDER:
            rows.append((flag,
                         self.c_result.ddm_flags.get(flag, "-"),
                         self.cpp_result.ddm_flags.get(flag, "-"),
                         self.mlxlink_result.ddm_flags.get(flag, "-")))
        return rows

    def _build_channel_flags_rows(self, ch_idx):
        c_flags = (self.c_result.channel_flags[ch_idx]
                   if ch_idx < len(self.c_result.channel_flags) else {})
        cpp_flags = (self.cpp_result.channel_flags[ch_idx]
                     if ch_idx < len(self.cpp_result.channel_flags) else {})
        mlx_flags = (self.mlxlink_result.channel_flags[ch_idx]
                     if ch_idx < len(self.mlxlink_result.channel_flags) else {})
        rows = []
        for flag in CHANNEL_FLAG_ORDER:
            rows.append((flag,
                         c_flags.get(flag, "-"),
                         cpp_flags.get(flag, "-"),
                         mlx_flags.get(flag, "-")))
        return rows

    def _build_threshold_rows(self):
        rows = []
        for th in THRESHOLD_ORDER:
            for field in THRESHOLD_FIELDS:
                label = "{} - {}".format(th, field)
                rows.append((label,
                             self.c_result.thresholds.get((th, field), "-"),
                             self.cpp_result.thresholds.get((th, field), "-"),
                             self.mlxlink_result.thresholds.get((th, field), "-")))
        return rows

    # ----- Main Print Method -----

    def print_tables(self):
        """Print all comparison tables and return True if values match and mask checks pass."""
        print("")
        print("=" * 80)
        title = "CABLE DDM COMPARISON"
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 80)

        sdk_cmd = format_sdk_command(
            binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
            keywords=["CableDDM"])
        mlxlink_cmd = ("mlxlink_ext -d " + self.device + " " + Config.MLXLINK_DDM_ARGS
                       if self.device else "mlxlink_ext")
        print("{}SDK command:    {}{}".format(BLUE, sdk_cmd, RESET))
        print("{}mlxlink command: {}{}".format(BLUE, mlxlink_cmd, RESET))

        any_supported = (self.c_result.supported or
                         self.cpp_result.supported or
                         self.mlxlink_result.supported)
        if not any_supported:
            print("\n{}Cable DDM not available on this device{}".format(
                YELLOW, RESET))
            if self.mlxlink_result.error_message:
                print("mlxlink: " + self.mlxlink_result.error_message)
            if self.c_result.error_message:
                print("C:       " + self.c_result.error_message)
            if self.cpp_result.error_message:
                print("C++:     " + self.cpp_result.error_message)
            return True

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

        total_match = 0
        total_diff = 0
        total_skip = 0
        total_mask_ok = 0
        total_mask_fail = 0

        # Table 1: Cable DDM Information
        rows = self._build_info_rows()
        m, d, s, mo, mf = self._print_section_table(
            DDM_SECTION_CABLE_DDM_INFO, rows, self._info_cap_fn,
            self._info_valid_fn, match_fn=_ddm_info_match_fn)
        total_match += m
        total_diff += d
        total_skip += s
        total_mask_ok += mo
        total_mask_fail += mf

        # Table 2: DDM Flags
        def flags_cap(_): return self._is_bit_available(3)
        rows = self._build_ddm_flags_rows()
        m, d, s, mo, mf = self._print_section_table(
            DDM_SECTION_DDM_FLAGS, rows, flags_cap, self._flags_valid_fn)
        total_match += m
        total_diff += d
        total_skip += s
        total_mask_ok += mo
        total_mask_fail += mf

        # Tables 3+: Channel N Flags
        max_ch_flags = max(
            len(self.c_result.channel_flags),
            len(self.cpp_result.channel_flags),
            len(self.mlxlink_result.channel_flags))
        for i in range(max_ch_flags):
            rows = self._build_channel_flags_rows(i)
            m, d, s, mo, mf = self._print_section_table(
                "Channel {} Flags".format(i + 1), rows, flags_cap,
                self._flags_valid_fn)
            total_match += m
            total_diff += d
            total_skip += s
            total_mask_ok += mo
            total_mask_fail += mf

        # Table: DDM Thresholds
        def thresh_cap(_): return self._is_bit_available(5)
        rows = self._build_threshold_rows()
        m, d, s, mo, mf = self._print_section_table(
            DDM_SECTION_DDM_THRESHOLDS, rows, thresh_cap, self._threshold_valid_fn,
            match_fn=_threshold_match_fn)
        total_match += m
        total_diff += d
        total_skip += s
        total_mask_ok += mo
        total_mask_fail += mf

        # Summary
        compared = total_match + total_diff
        parts = ["{} compared".format(compared),
                 "{} match".format(total_match),
                 "{} differ".format(total_diff)]
        if total_skip:
            parts.append("{} skipped (not available)".format(total_skip))
        print("\nMatch summary:              " + ", ".join(parts))
        if total_mask_ok or total_mask_fail:
            mask_total = total_mask_ok + total_mask_fail
            mask_status = "{}{} mismatch{}".format(
                RED, total_mask_fail, RESET) \
                if total_mask_fail else "{}all OK{}".format(GREEN, RESET)
            print("Valid fields mask summary:  {} checked, {}".format(
                mask_total, mask_status))

        return total_diff == 0 and total_mask_fail == 0


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("DDM C", Config, device)

    def get_ddm(self):
        return CableDDMParser.parse_c_cpp(self.output)

    def get_valid_fields_mask(self):
        return CableDDMParser.parse_valid_fields_mask(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("DDM C++", Config, device)

    def get_ddm(self):
        return CableDDMParser.parse_c_cpp(self.output)

    def get_valid_fields_mask(self):
        return CableDDMParser.parse_valid_fields_mask(self.output)


class MlxlinkDDMRunner(BaseMlxlinkRunner):
    def __init__(self, device=None):
        super(MlxlinkDDMRunner, self).__init__("mlxlink DDM", device)

    def _cmd(self):
        return self._base_cmd() + " " + Config.MLXLINK_DDM_ARGS

    def get_ddm(self):
        return CableDDMParser.parse_mlxlink(self.output)

    def print_ddm_only(self):
        self.success, self.output = CommandRunner.run_quiet(self._cmd())
        result = self.get_ddm()
        if result.supported:
            print(self.output)
        else:
            print("Cable DDM not available")
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
        self.mlxlink_runner = MlxlinkDDMRunner(self.device)

    def _get_mlxlink_cmd(self):
        cmd = "mlxlink_ext -d " + self.device if self.device else "mlxlink_ext"
        return cmd + " " + Config.MLXLINK_DDM_ARGS

    def run_comparison(self):
        result = self._check_operational()
        if result is not None:
            return result

        c_result = DDMResult()
        cpp_result = DDMResult()
        mlxlink_result = DDMResult()
        valid_fields_mask = None

        v = _verbose()

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
            c_result = self.c_runner.get_ddm()
            valid_fields_mask = self.c_runner.get_valid_fields_mask()

        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)
            cpp_result = self.cpp_runner.get_ddm()
            if valid_fields_mask is None:
                valid_fields_mask = self.cpp_runner.get_valid_fields_mask()

        if not BaseConfig.SDK_ONLY:
            self.mlxlink_runner.run(verbose=v)
            mlxlink_result = self.mlxlink_runner.get_ddm()

        if c_result.supported or cpp_result.supported or mlxlink_result.supported:
            all_match = ComparisonTable(
                c_result, cpp_result, mlxlink_result,
                valid_fields_mask=valid_fields_mask,
                device=self.device,
                device_type=self.device_type).print_tables()
            return self.RESULT_PASS if all_match else self.RESULT_FAIL

        return self._compare_errors()


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base("Show mlxlink Cable DDM info (first device)")


def main():
    return run_main(
        Config, TestSuite, MlxlinkDDMRunner,
        lambda r: r.print_ddm_only(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
