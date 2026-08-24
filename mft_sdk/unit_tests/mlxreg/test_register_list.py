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
Test script for register list discovery tests.
Compares SDK register list output with mlxreg_ext --show_regs.

Usage:
    ./test_register_list.py                    # Full test suite on first device
    ./test_register_list.py --compare -d D     # Compare C, C++, mlxreg_ext on specific device
    ./test_register_list.py --compare-all      # Compare on ALL devices
    ./test_register_list.py --mlxreg           # Show mlxreg_ext output for first device
    ./test_register_list.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from mlxreg_fields import (
    SECTION_REGISTER_LIST,
    FIELD_TOTAL,
)
from utils import (
    MFT_SDK_REG_TOOL, tool_label, is_known_missing,
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
    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxreg:register-list-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxreg:register-list-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxreg/register-list-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxreg/register-list-cpp-test"
    GTEST_FILTER = "MftSdkRegisterListTest.*"
    SUITE_NAME = "RegisterList"


# =============================================================================
# Parsers
# =============================================================================


class RegisterListParser(object):
    @staticmethod
    def parse(output):
        names = []
        in_section = False
        for line in output.split('\n'):
            if SECTION_REGISTER_LIST in line:
                in_section = True
                continue
            if in_section:
                stripped = line.strip()
                if stripped.startswith('---') or stripped == '':
                    continue
                if stripped.startswith(FIELD_TOTAL + ':'):
                    break
                if stripped:
                    names.append(stripped)
        return sorted(names)


class MlxregCliParser(object):
    @staticmethod
    def parse_show_regs(output):
        names = []
        for line in output.split('\n'):
            stripped = line.strip()
            if not stripped or stripped.startswith('-') or 'Supported' in stripped:
                continue
            # Register names are NOT all-uppercase: the PRM DB also holds
            # mixed-case ones (Loopback_Control_Register, PTASv2, SLTPv2,
            # Resource_dump_registers). An [A-Z]-only pattern dropped those
            # four from the CLI side and reported them as bogus "SDK only"
            # rows on every device. Every other line of --show_regs output is
            # multi-word ("Available Access Registers") or punctuation
            # ("======"), so a single bare identifier is always a register.
            if re.match(r'^[A-Za-z][A-Za-z0-9_]*$', stripped):
                names.append(stripped)
        return sorted(names)


# =============================================================================
# Comparison Table
# =============================================================================


class RegisterListComparisonTable(object):
    def __init__(self, sdk_names, mlxreg_names, device=None, device_type=None,
                 c_names=None, cpp_names=None):
        self.sdk_names = set(sdk_names)
        self.mlxreg_names = set(mlxreg_names)
        self._c_names = c_names
        self._cpp_names = cpp_names
        self.device = device
        self.device_type = device_type

    def print_table(self):
        all_names = sorted(self.sdk_names | self.mlxreg_names)
        sdk_only = self.sdk_names - self.mlxreg_names
        mlxreg_only = self.mlxreg_names - self.sdk_names
        common = self.sdk_names & self.mlxreg_names

        print("")
        print("=" * 70)
        title = "MLXREG REGISTER LIST COMPARISON"
        if self.device:
            title += " [" + self.device
            if self.device_type:
                title += " - " + self.device_type
            title += "]"
        print(title)
        print("=" * 70)
        sdk_cmd = format_sdk_command(
            binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
            keywords=["ShowAll", "NamesArray"])
        # Name the oracle after the CLI that actually ran (MFT_SDK_REG_TOOL).
        oracle = tool_label(MFT_SDK_REG_TOOL)
        mlxreg_cmd = "{} -d {} --show_regs".format(
            MFT_SDK_REG_TOOL, self.device) if self.device \
            else MFT_SDK_REG_TOOL + " --show_regs"
        print("{}SDK command:    {}{}".format(BLUE, sdk_cmd, RESET))
        print("{}{} command: {}{}".format(BLUE, oracle, mlxreg_cmd, RESET))
        print("")

        # Label column stays 22 wide for the default oracle -- the historical
        # layout -- and grows only if a longer tool name needs it.
        lw = max(22, len(oracle) + 12)
        print("{:<{}}{}".format("SDK registers:", lw, len(self.sdk_names)))
        print("{:<{}}{}".format(oracle + " registers:", lw, len(self.mlxreg_names)))
        print("{}{:<{}}{}{}".format(GREEN, "Common:", lw, len(common), RESET))
        if sdk_only:
            print("{}{:<{}}{}{}".format(YELLOW, "SDK only:", lw, len(sdk_only), RESET))
        if mlxreg_only:
            print("{}{:<{}}{}{}".format(
                YELLOW, oracle + " only:", lw, len(mlxreg_only), RESET))
        print("")

        nw = max(len(n) for n in all_names) + 2 if all_names else 20
        ow = max(len(oracle), 10)
        sep = "+-{}-+------+-{}-+---------+".format("-" * nw, "-" * ow)
        print(sep)
        print("| {:<{}} | SDK  | {:<{}} | Match   |".format(
            "Register Name", nw, oracle, ow))
        print(sep)
        for name in all_names:
            in_sdk = name in self.sdk_names
            in_mlxreg = name in self.mlxreg_names
            sdk_col = " YES " if in_sdk else "  -  "
            mlxreg_col = "{:^{}}".format("YES" if in_mlxreg else "-", ow + 1)
            if in_sdk and in_mlxreg:
                status = GREEN + "  OK  " + RESET
            elif in_sdk:
                status = YELLOW + "SDK   " + RESET
            else:
                status = YELLOW + "MLXR_E" + RESET
            print("| {:<{}} |{}|{}| {} |".format(name, nw, sdk_col, mlxreg_col, status))
        print(sep)

        if sdk_only:
            print("\n{}SDK only ({}):{} registers present in SDK "
                  "but not in {}:".format(
                      YELLOW, len(sdk_only), RESET, oracle))
            for name in sorted(sdk_only):
                print("  {}".format(name))
        if mlxreg_only:
            print("\n{}{} only ({}):{} registers present in "
                  "{} but not in SDK:".format(
                      YELLOW, oracle, len(mlxreg_only), RESET, oracle))
            for name in sorted(mlxreg_only):
                print("  {}".format(name))

        print("\nSummary: {} total, {} common, {} SDK-only, "
              "{} {}-only".format(
                  len(all_names), len(common), len(sdk_only),
                  len(mlxreg_only), oracle))

        if BaseConfig.SDK_ONLY:
            c_names = set(self._c_names) if self._c_names else set()
            cpp_names = set(self._cpp_names) if self._cpp_names else set()
            if c_names and cpp_names:
                if c_names != cpp_names:
                    print("\n{}SDK-only mode: C and C++ register lists differ{}".format(RED, RESET))
                    return False
                print("\n{}SDK-only mode: C and C++ register lists match "
                      "({} registers){}".format(GREEN, len(c_names), RESET))
            return True

        # CLI-only registers listed in MFT_SDK_KNOWN_MISSING are an expected
        # product divergence (e.g. mstflint's register DB lagging MFT's ADB),
        # not a failure.
        expected_missing = set(n for n in mlxreg_only if is_known_missing(n))
        unexpected_missing = mlxreg_only - expected_missing
        if expected_missing:
            print("{}Expected differences (MFT_SDK_KNOWN_MISSING), not counted "
                  "as failures: {}{}".format(
                      YELLOW, ", ".join(sorted(expected_missing)), RESET))
        if unexpected_missing:
            print("{}FAIL: {} has {} registers missing from SDK{}".format(
                RED, oracle, len(unexpected_missing), RESET))
        elif sdk_only or expected_missing:
            print("{}SDK covers all comparable {} registers "
                  "(common registers validate correctly){}".format(
                      YELLOW, oracle, RESET))
        else:
            print("{}All registers match{}".format(GREEN, RESET))

        return len(unexpected_missing) == 0


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("C", Config, device)

    def get_register_list(self):
        return RegisterListParser.parse(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("C++", Config, device)

    def get_register_list(self):
        return RegisterListParser.parse(self.output)


class MlxregCliRunner(object):
    def __init__(self, device=None):
        self.device = device
        self.output = ""
        self.success = False

    def run(self, verbose=True):
        return self.run_show_regs(verbose=verbose)

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

    def run_show_regs(self, verbose=True):
        cmd = "echo '{}' | sudo su".format(self._base_cmd() + " --show_regs")
        self.success, self.output = CommandRunner.run(
            cmd, "Running {} --show_regs on {}".format(
                MFT_SDK_REG_TOOL, self.device), verbose)
        return self.success

    def get_register_list(self):
        return MlxregCliParser.parse_show_regs(self.output)

    def print_mlxreg_output(self):
        self.run_show_regs()
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
        self.mlxreg_runner = MlxregCliRunner(self.device)
        self.mlxlink_runner = self.mlxreg_runner

    def _get_mlxlink_cmd(self):
        # mlxreg suite: the oracle is the mlxreg CLI runner, so derive the
        # header from it and it follows MFT_SDK_REG_TOOL automatically.
        return self.mlxreg_runner._base_cmd()

    def run_comparison(self):
        v = _verbose()

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)
        if not BaseConfig.SDK_ONLY:
            self.mlxreg_runner.run_show_regs(verbose=v)

        c_names = self.c_runner.get_register_list()
        cpp_names = self.cpp_runner.get_register_list()
        mlxreg_names = (self.mlxreg_runner.get_register_list()
                        if not BaseConfig.SDK_ONLY else [])
        sdk_names = c_names if c_names else cpp_names

        if sdk_names or mlxreg_names:
            passed = RegisterListComparisonTable(
                sdk_names, mlxreg_names,
                self.device, self.device_type,
                c_names=c_names, cpp_names=cpp_names).print_table()
            return self.RESULT_PASS if passed else self.RESULT_FAIL

        print("\n{}No register list data from any source{}".format(RED, RESET))
        return self.RESULT_FAIL


# =============================================================================
# CLI
# =============================================================================


def print_usage():
    _print_usage_base(
        "Show {} --show_regs output for first device".format(MFT_SDK_REG_TOOL))


def main():
    return run_main(
        Config, TestSuite, MlxregCliRunner,
        lambda r: r.print_mlxreg_output(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
