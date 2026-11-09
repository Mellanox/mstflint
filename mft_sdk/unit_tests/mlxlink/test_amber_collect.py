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
Test script for building and running amBER collect tests from C and C++ files.
Builds using bazel inside docker, runs tests locally.
Supports comparison mode to compare C, C++, and mlxlink outputs.

The SDK side is read from the AMBER_* records that amber_collect_test_common.h
prints -- this module is the regression parser that header refers to. The
oracle is `<link tool> --amber_collect <csv>`, whose header row carries the same
field vocabulary in the same order as mstGetAmberReport().

Usage:
    ./test_amber_collect.py                # Full test suite
    ./test_amber_collect.py --compare      # Compare C, C++, mlxlink outputs
    ./test_amber_collect.py --mlxlink      # Show mlxlink amBER collect only
    ./test_amber_collect.py --help         # Show help
"""

from __future__ import print_function
import binascii
import os
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from utils import (
    RED, GREEN, YELLOW, BLUE, RESET,
    BaseConfig, CommandRunner, MFT_SDK_LINK_TOOL, tool_label,
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
    """Configuration constants for the amBER collect test runner."""

    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:amber-collect-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxlink:amber-collect-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/amber-collect-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxlink/amber-collect-cpp-test"
    # The whole fixture, not one named case: new cases must run here
    # automatically. The PCIe collect cases are left out: their AMBER_* records
    # would mix into the network collect that is diffed against mlxlink.
    GTEST_FILTER = ("MftSdkAmberCollectTest.*-"
                    "MftSdkAmberCollectTest.GetAmberCollectPcie*")
    SUITE_NAME = "amBER Collect"

    # The unified C driver also hosts amber_sheet_select (sheet-filtered
    # collect; argv is <BDF> <PORT> <SHEET_ID>). It has no Config of its own --
    # without this line nothing invokes it and it is reachable only by hand.
    # GENERAL is the sheet every amBER-capable device populates, so the filter
    # is never vacuously satisfied by an empty sheet.
    C_SO_EXTRA_SUITES = (("amber_sheet_select", ("", "1")),)

    # amberSheetSelectTestRun() prints this for every field whose sheet_id is
    # not the requested one, but still exits 0 -- so the filter contract is
    # enforced here rather than by the C suite's return code.
    SHEET_SELECT_VIOLATION = "SHEET_SELECT_UNEXPECTED_SHEET_ID"

    # mft_sdk_amber.h: MST_AMBER_VALUE_MAX is the BUFFER size, NUL included, so
    # mstGetAmberReport() can only ever return 63 characters. The header says so
    # ("truncated to their buffer sizes ... Prefer mstGetAmberJson"), and this
    # suite asserts that contract instead of quietly tolerating a difference.
    VALUE_MAX = 64

    # Fields that move between two collections taken seconds apart, so the SDK
    # and the CLI can never agree on them. Measured by running mlxlink_ext
    # against itself twice: on an idle port exactly these change.
    VOLATILE_FIELDS = frozenset([
        "TimeStamp",
        "Time_since_last_clear_[Min]",
    ])

    # The CLI echoes the device string it was invoked with; the SDK leaves it
    # empty. Not a collection difference, so it cannot be compared -- but it is
    # a real SDK gap, so it is reported rather than silently dropped.
    UNPOPULATED_BY_SDK = frozenset(["Device_Description"])

    # The SDK build under test and the installed mlxlink_ext are independent
    # builds; their version strings legitimately differ.
    BUILD_STAMP_FIELDS = frozenset(["collection_tool_version"])

    # amBER is a 16nm-and-later feature. Both sides say so in their own words,
    # and the suite SKIPs rather than fails only when they AGREE -- a device the
    # CLI collects but the SDK refuses is a real defect, not an unsupported part.
    # Verified on ConnectX-4 (apps-40-03) and ConnectX-5EX (apps-124-002).
    SDK_UNSUPPORTED_MARKER = "supported on 16nm devices and above"
    CLI_UNSUPPORTED_MARKER = "amber_collect is not available for this device"


# =============================================================================
# Parsers
# =============================================================================


def _unhex(token):
    """Decode one hex payload from an AMBER_*_HEX record ('' -> '')."""
    if not token:
        return ""
    return binascii.unhexlify(token.encode("ascii")).decode("utf-8", "replace")


class AmberRecordParser(object):
    """Parses the AMBER_* record stream emitted by amber_collect_test_common.h.

    Returns a dict with:
        json_status / report_status : int or None
        json_error  / report_error  : decoded error strings
        json_fields                 : {name: value} from the JSON body
        report_fields               : [(name, value)] in emission order
    """

    @staticmethod
    def parse(output):
        result = {
            "json_status": None, "report_status": None,
            "json_error": "", "report_error": "",
            "json_body": "", "json_fields": {}, "report_fields": [],
        }
        lines = output.split("\n")
        i = 0
        pending_name = None
        while i < len(lines):
            line = lines[i].rstrip("\r")
            if line.startswith("AMBER_JSON_STATUS "):
                result["json_status"] = int(line.split()[1])
            elif line.startswith("AMBER_REPORT_STATUS "):
                result["report_status"] = int(line.split()[1])
            elif line.startswith("AMBER_JSON_ERROR_HEX"):
                result["json_error"] = _unhex(line.partition(" ")[2].strip())
            elif line.startswith("AMBER_REPORT_ERROR_HEX"):
                result["report_error"] = _unhex(line.partition(" ")[2].strip())
            elif line == "AMBER_JSON_BEGIN":
                body = []
                i += 1
                while i < len(lines) and lines[i].rstrip("\r") != "AMBER_JSON_END":
                    body.append(lines[i])
                    i += 1
                result["json_body"] = "\n".join(body)
            elif line.startswith("AMBER_REPORT_FIELD "):
                # "AMBER_REPORT_FIELD <sheet_id> <hex name>"
                parts = line.split()
                pending_name = _unhex(parts[2]) if len(parts) > 2 else ""
            elif line.startswith("AMBER_REPORT_VALUE_HEX"):
                value = _unhex(line.partition(" ")[2].strip())
                if pending_name is not None:
                    result["report_fields"].append((pending_name, value))
                    pending_name = None
            i += 1

        result["json_fields"] = AmberRecordParser._json_fields(result["json_body"])
        return result

    @staticmethod
    def _json_fields(body):
        """Flatten the amBER JSON into {field_name: value} across all ports."""
        if not body.strip():
            return {}
        try:
            import json
            doc = json.loads(body)
        except Exception:
            return {}
        fields = {}
        ports = doc.get("ports", {})
        entries = ports.values() if isinstance(ports, dict) else ports
        for port in entries:
            if isinstance(port, dict):
                for name, value in port.items():
                    fields[name] = value if isinstance(value, str) else str(value)
        return fields


class AmberCsvParser(object):
    """Parses the CSV the link tool's --amber_collect writes.

    One header row plus one data row per collection; the last row is the most
    recent. Temp_sensor_name carries embedded NULs, so the file is not clean
    text and is read as bytes.
    """

    @staticmethod
    def parse(path):
        try:
            raw = open(path, "rb").read()
        except (IOError, OSError):
            return {}, []
        text = raw.replace(b"\x00", b"").decode("utf-8", "replace")
        rows = [r for r in text.splitlines() if r.strip()]
        if len(rows) < 2:
            return {}, []
        names = rows[0].split(",")
        values = rows[-1].split(",")
        if len(values) != len(names):
            return {}, names
        return dict(zip(names, values)), names


# =============================================================================
# Comparison
# =============================================================================


class ComparisonTable(object):
    """Compares the SDK's report and JSON views against the mlxlink CSV."""

    def __init__(self, sdk, csv_fields, csv_names, device, device_type, label):
        self.sdk = sdk
        self.csv_fields = csv_fields
        self.csv_names = csv_names
        self.device = device
        self.device_type = device_type
        self.label = label

    @staticmethod
    def _is_number(text):
        try:
            float(text.replace("E", "e"))
            return True
        except (ValueError, AttributeError):
            return False

    def print_table(self):
        print("\n" + "=" * 70)
        print("AMBER COLLECT COMPARISON [{} - {}] ({})".format(
            self.device, self.device_type, self.label))
        print("=" * 70)
        print("{}SDK command:     mstGetAmberReport() / mstGetAmberJson(){}".format(BLUE, RESET))
        print("{}mlxlink command: {} -d {} --amber_collect <csv>{}".format(
            BLUE, tool_label(MFT_SDK_LINK_TOOL), self.device, RESET))

        report = self.sdk["report_fields"]
        json_fields = self.sdk["json_fields"]
        report_names = [n for n, _ in report]

        ok = True

        # 1. Schema: the report must carry exactly the CLI's vocabulary, in order.
        if report_names != self.csv_names:
            ok = False
            missing = [n for n in self.csv_names if n not in report_names]
            extra = [n for n in report_names if n not in self.csv_names]
            print("{}Schema mismatch: SDK {} fields, mlxlink {} fields{}".format(
                RED, len(report_names), len(self.csv_names), RESET))
            if missing:
                print("  missing from SDK : {}".format(", ".join(missing[:10])))
            if extra:
                print("  absent from CLI  : {}".format(", ".join(extra[:10])))
            if not missing and not extra:
                print("  same names, different order")
        else:
            print("{}Schema: {} fields, identical names and order{}".format(
                GREEN, len(report_names), RESET))

        # 2. Values.
        compared = matched = live = truncated = 0
        mismatches = []
        for name, sdk_value in report:
            if name in Config.VOLATILE_FIELDS or name in Config.BUILD_STAMP_FIELDS:
                continue
            if name not in self.csv_fields:
                continue
            cli_value = self.csv_fields[name]
            if name in Config.UNPOPULATED_BY_SDK:
                if sdk_value == "":
                    print("{}Note: {} is empty from the SDK and {!r} from the CLI "
                          "(the SDK does not populate it){}".format(
                              YELLOW, name, cli_value, RESET))
                continue
            compared += 1
            if sdk_value == cli_value:
                matched += 1
                continue
            # Documented truncation: MST_AMBER_VALUE_MAX includes the NUL, so a
            # longer value must come back as its VALUE_MAX-1 prefix -- asserted,
            # not tolerated. The JSON view must still carry it whole.
            limit = Config.VALUE_MAX - 1
            if len(cli_value) > limit and sdk_value == cli_value[:limit]:
                truncated += 1
                whole = json_fields.get(name)
                if whole == cli_value:
                    matched += 1
                else:
                    ok = False
                    mismatches.append((name, sdk_value, cli_value,
                                       "JSON must not truncate (got {!r})".format(whole)))
                continue
            # A number that moved between the two collections is a live counter,
            # not an SDK divergence.
            if self._is_number(sdk_value) and self._is_number(cli_value):
                live += 1
                continue
            ok = False
            mismatches.append((name, sdk_value, cli_value, ""))

        for name, sdk_value, cli_value, note in mismatches:
            print("{}  {:<38} SDK={!r} mlxlink={!r} {}{}".format(
                RED, name, sdk_value, cli_value, note, RESET))

        colour = GREEN if ok and not mismatches else RED
        print("{}Match summary: {} compared, {} match, {} differ, "
              "{} live, {} truncated-as-documented{}".format(
                  colour, compared, matched, len(mismatches), live, truncated, RESET))
        return ok and not mismatches


# =============================================================================
# Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("C", Config, device)

    def get_amber(self):
        return AmberRecordParser.parse(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("C++", Config, device)

    def get_amber(self):
        return AmberRecordParser.parse(self.output)


class MlxlinkRunner(BaseMlxlinkRunner):
    """--amber_collect writes a CSV rather than printing, so the runner owns a
    scratch path and reads it back after the command returns."""

    def __init__(self, device=None):
        super(MlxlinkRunner, self).__init__("mlxlink", device)
        self.csv_path = "/tmp/mft_sdk_amber_{}.csv".format(
            (device or "nodev").replace(":", "-").replace(".", "-"))

    def _cmd(self):
        return "{} --amber_collect {}".format(self._base_cmd(), self.csv_path)

    def run(self, verbose=True):
        # A stale CSV from an earlier run would be parsed as this run's output.
        CommandRunner.run_quiet("sudo rm -f {}".format(self.csv_path))
        return super(MlxlinkRunner, self).run(verbose)

    def get_amber_csv(self):
        return AmberCsvParser.parse(self.csv_path)

    def print_amber_only(self):
        self.success, self.output = CommandRunner.run_quiet(
            "echo '{}' | sudo su".format(self._cmd()))
        fields, names = self.get_amber_csv()
        if not names:
            print(self.output)
            return 1
        print("amBER fields collected by {}: {}".format(
            tool_label(MFT_SDK_LINK_TOOL), len(names)))
        for name in names:
            print("  {:<44} {}".format(name, fields.get(name, "")))
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

        v = _verbose()
        c_amber = cpp_amber = None

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
            c_amber = self.c_runner.get_amber()
            # Unsupported parts are settled further down by the SKIP path, which
            # needs both sides to agree; only a real failure is fatal here.
            extra_out = self.c_runner.extra_output
            if not self.c_runner.extra_ok and Config.SDK_UNSUPPORTED_MARKER not in extra_out:
                print("{}amber_sheet_select failed on {}{}".format(RED, self.device, RESET))
                return self.RESULT_FAIL
            if Config.SHEET_SELECT_VIOLATION in extra_out:
                print("{}sheet-filtered collect returned fields from other sheets "
                      "on {}{}".format(RED, self.device, RESET))
                return self.RESULT_FAIL

        cpp_gtest_ok = True
        if os.path.exists(Config.CPP_TEST_BIN):
            cpp_gtest_ok = self.cpp_runner.run(verbose=v)
            cpp_amber = self.cpp_runner.get_amber()
            if not cpp_gtest_ok and Config.SDK_UNSUPPORTED_MARKER not in (
                    cpp_amber.get("json_error", "") + cpp_amber.get("report_error", "")):
                print("{}gtest binary reported failures for {}{}".format(
                    RED, Config.GTEST_FILTER, RESET))
            elif not cpp_gtest_ok:
                cpp_gtest_ok = True  # unsupported part: the gtest skipped, not failed

        # The C and C++ drivers call the same SDK on the same device: their
        # field vocabularies must agree even when no tool is available.
        if c_amber and cpp_amber:
            c_names = [n for n, _ in c_amber["report_fields"]]
            cpp_names = [n for n, _ in cpp_amber["report_fields"]]
            if c_names != cpp_names:
                print("{}C and C++ disagree on the amBER field list "
                      "({} vs {} fields){}".format(RED, len(c_names), len(cpp_names), RESET))
                return self.RESULT_FAIL

        if BaseConfig.SDK_ONLY:
            sdk = c_amber or cpp_amber
            if not sdk or not sdk["report_fields"]:
                return self._compare_errors()
            print("{}SDK-only: {} amBER fields collected, C and C++ agree{}".format(
                GREEN, len(sdk["report_fields"]), RESET))
            return self.RESULT_PASS if cpp_gtest_ok else self.RESULT_FAIL

        cli_ok = self.mlxlink_runner.run(verbose=v)

        # Unsupported part: both sides refuse, for the same documented reason.
        sdk_err = ""
        for sdk in (c_amber, cpp_amber):
            if sdk:
                sdk_err += (sdk.get("json_error") or "") + (sdk.get("report_error") or "")
        cli_out = self.mlxlink_runner.output or ""
        if (Config.SDK_UNSUPPORTED_MARKER in sdk_err and
                Config.CLI_UNSUPPORTED_MARKER in cli_out):
            # The framework's own device-header idiom (see BaseTestSuite.
            # _check_operational): a "SKIP [dev - type]" box plus a Reason line
            # is what the report layer parses into a SKIP row.
            self._print_header("SKIP")
            print("{}Reason: amBER collect not supported on this device -- "
                  "the SDK and {} agree it is 16nm-and-later only{}".format(
                      YELLOW, tool_label(MFT_SDK_LINK_TOOL), RESET))
            return self.RESULT_SKIP

        if not cli_ok:
            return self._compare_errors()
        csv_fields, csv_names = self.mlxlink_runner.get_amber_csv()
        if not csv_names:
            print("{}{} produced no amBER CSV{}".format(
                RED, tool_label(MFT_SDK_LINK_TOOL), RESET))
            return self._compare_errors()

        all_ok = True
        for label, sdk in (("C", c_amber), ("C++", cpp_amber)):
            if not sdk or not sdk["report_fields"]:
                continue
            table = ComparisonTable(sdk, csv_fields, csv_names,
                                    self.device, self.device_type, label)
            all_ok = table.print_table() and all_ok

        if c_amber is None and cpp_amber is None:
            return self._compare_errors()
        return self.RESULT_PASS if (all_ok and cpp_gtest_ok) else self.RESULT_FAIL


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base("Show mlxlink amBER collect fields (first device)")


def main():
    return run_main(
        Config, TestSuite, MlxlinkRunner,
        lambda r: r.print_amber_only(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
