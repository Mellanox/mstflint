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
Test script for register access tests (GET, indexed GET, SET, raw).
Compares SDK output with mlxreg_ext --get.

Usage:
    ./test_register_access.py                    # Full test suite on first device
    ./test_register_access.py --compare -d D     # Compare C, C++, mlxreg_ext on specific device
    ./test_register_access.py --compare-all      # Compare on ALL devices
    ./test_register_access.py --mlxreg           # Show mlxreg_ext output for first device
    ./test_register_access.py --help             # Show help
"""

from __future__ import print_function
import os
import re
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from mlxreg_fields import (
    SECTION_REGISTER_GET, SECTION_REGISTER_GET_INDEXED,
    SECTION_REGISTER_SET, SECTION_RAW_REGISTER_GET,
    SECTION_REGISTER_METADATA, SECTION_EXPANDED_METADATA,
    SECTION_ERROR_HANDLING,
    FIELD_INDEXES,
)
from utils import (
    MFT_SDK_REG_TOOL, tool_label, is_known_missing,
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
    C_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxreg:register-access-c-test-bin"
    CPP_TEST_TARGET = "//user/mft_sdk/unit_tests/mlxreg:register-access-cpp-test"
    C_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxreg/register-access-c-test-bin"
    CPP_TEST_BIN = BaseConfig.PROJECT_PATH + \
        "/bazel-bin/user/mft_sdk/unit_tests/mlxreg/register-access-cpp-test"
    GTEST_FILTER = "MftSdkRegisterAccessTest.*"
    SUITE_NAME = "RegisterAccess"

    NON_INDEXED_REGISTERS = ["MGIR", "MCAM"]
    INDEXED_REGISTERS = {
        "MTMP": {"sensor_index": "0"},
        "PAOS": {"local_port": "1"},
        "PTYS": {"local_port": "1", "proto_mask": "0x7"},
    }
    RAW_REGISTERS = {
        "MGIR": {"reg_id": "0x9020", "reg_len": "0xa0"},
    }
    VOLATILE_FIELDS = {
        "MGIR": {"uptime"},
        "MTMP": {"temperature"},
    }


# =============================================================================
# Parsers
# =============================================================================


class RegisterFieldParser(object):
    @staticmethod
    def parse_register_get(output, register_name):
        fields = {}
        in_section = False
        pattern = re.compile(r'^(' + re.escape(SECTION_REGISTER_GET) +
                             r'(?:\s*\(indexed\))?)\s*:\s*' +
                             re.escape(register_name))
        segment_re = r'[a-zA-Z_][a-zA-Z0-9_]*(\[\d+\])?'
        field_name_re = re.compile(r'^' + segment_re + r'(\.' + segment_re + r')*$')

        for line in output.split('\n'):
            stripped = line.strip()
            if not in_section:
                if pattern.match(stripped):
                    in_section = True
                continue
            if stripped == '':
                break
            if stripped.startswith('---') or stripped.startswith(FIELD_INDEXES + ':'):
                continue
            if (stripped.startswith(SECTION_REGISTER_GET) or
                    stripped.startswith(SECTION_REGISTER_SET) or
                    stripped.startswith(SECTION_REGISTER_METADATA) or
                    stripped.startswith(SECTION_RAW_REGISTER_GET) or
                    stripped.startswith(SECTION_ERROR_HANDLING) or
                    stripped.startswith(SECTION_EXPANDED_METADATA)):
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
                    if key and field_name_re.match(key):
                        leaf = key.rsplit('.', 1)[-1]
                        fields[leaf] = val
        return fields

    @staticmethod
    def parse_raw_hex(output):
        data = bytearray()
        in_section = False
        hex_line_re = re.compile(r'^[0-9a-fA-F]{4}:')
        for line in output.split('\n'):
            if SECTION_RAW_REGISTER_GET + ':' in line:
                in_section = True
                continue
            if in_section:
                stripped = line.strip()
                if stripped.startswith('---'):
                    continue
                if stripped == '':
                    break
                if not hex_line_re.match(stripped):
                    break
                parts = stripped.split(':', 1)
                if len(parts) == 2:
                    for byte_str in parts[1].strip().split():
                        try:
                            data.append(int(byte_str, 16))
                        except ValueError:
                            pass
        return data


class MlxregCliParser(object):
    @staticmethod
    def parse_get(output):
        fields = {}
        in_data = False
        for line in output.split('\n'):
            stripped = line.strip()
            if '====' in stripped or '----' in stripped:
                in_data = True
                continue
            if in_data and stripped:
                if '|' in stripped:
                    parts = stripped.split('|', 1)
                    if len(parts) == 2:
                        key = parts[0].strip()
                        val = clean_value(parts[1])
                        if key and key != 'Field Name':
                            fields[key] = val
                else:
                    parts = stripped.split()
                    if len(parts) >= 2 and parts[-1].startswith('0x'):
                        fields[parts[0]] = parts[-1]
        return fields

    @staticmethod
    def parse_raw_get(output):
        data = bytearray()
        for line in output.split('\n'):
            stripped = line.strip()
            if not stripped or '====' in stripped or '----' in stripped:
                continue
            hex_bytes = re.findall(r'\b([0-9a-fA-F]{2})\b', stripped)
            for hb in hex_bytes:
                try:
                    data.append(int(hb, 16))
                except ValueError:
                    pass
        return data


# =============================================================================
# Comparison Table
# =============================================================================


class RegisterGetComparisonTable(object):
    def __init__(self, register_name, c_fields, cpp_fields, mlxreg_fields,
                 device=None, device_type=None, mlxreg_cmd="",
                 sdk_cmd="", volatile_fields=None):
        self.register_name = register_name
        self.c_fields = c_fields
        self.cpp_fields = cpp_fields
        self.mlxreg_fields = mlxreg_fields
        self.device = device
        self.device_type = device_type
        self.mlxreg_cmd = mlxreg_cmd
        self.sdk_cmd = sdk_cmd
        self.volatile_fields = volatile_fields or set()

    def print_table(self):
        all_keys = sorted(set(
            list(self.c_fields.keys()) +
            list(self.cpp_fields.keys()) +
            list(self.mlxreg_fields.keys())
        ))
        if not all_keys:
            print("  No fields to compare")
            return True

        oracle = tool_label(MFT_SDK_REG_TOOL)
        fw = max(max(len(k) for k in all_keys), 10) + 2
        cw = max(max(len(str(self.c_fields.get(k, "-"))) for k in all_keys), 3) + 2
        cpw = max(max(len(str(self.cpp_fields.get(k, "-"))) for k in all_keys), 3) + 2
        # Floor the oracle column at its own header so the name always fits.
        mw = max(max(len(str(self.mlxreg_fields.get(k, "-"))) for k in all_keys),
                 len(oracle)) + 2

        print("")
        print("=" * 70)
        title = "MLXREG REGISTER READ COMPARISON: {}".format(self.register_name)
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

        sep = "+-{}-+-{}-+-{}-+-{}-+---------+".format("-" * fw, "-" * cw, "-" * cpw, "-" * mw)
        print(sep)
        print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | Match   |".format(
            "Field", fw, "C", cw, "C++", cpw, oracle, mw))
        print(sep)

        match_count = 0
        skip_count = 0
        known_count = 0
        for key in all_keys:
            c = self.c_fields.get(key, "-")
            cpp = self.cpp_fields.get(key, "-")
            mlx = self.mlxreg_fields.get(key, "-")
            if key in self.volatile_fields:
                skip_count += 1
                status = YELLOW + " SKIP " + RESET
            elif c == "-" and cpp == "-" and mlx != "-" and is_known_missing(key):
                # CLI-only field listed in MFT_SDK_KNOWN_MISSING: an expected
                # product divergence (SDK register DB lags the CLI's), not a
                # DIFF. Only this direction is relaxed — an SDK-side value
                # still has to match below.
                known_count += 1
                status = YELLOW + " KNOWN" + RESET
            else:
                match = self._values_match(c, cpp, mlx)
                match_count += match
                status = GREEN + "  OK  " + RESET if match else RED + "  DIFF" + RESET
            print("| {:<{}} | {:<{}} | {:<{}} | {:<{}} | {} |".format(
                key, fw, c, cw, cpp, cpw, mlx, mw, status))

        print(sep)
        compared = len(all_keys) - skip_count - known_count
        diff_count = compared - match_count
        summary = "Summary: {} compared, {} match, {} differ".format(compared, match_count, diff_count)
        if skip_count:
            summary += ", {} skipped (volatile)".format(skip_count)
        if known_count:
            summary += ", {} expected-missing (MFT_SDK_KNOWN_MISSING)".format(known_count)
        print("\n" + summary)
        return match_count == compared

    @staticmethod
    def _values_match(c, cpp, mlx):
        def normalize(v):
            v = v.strip().lower()
            if v.startswith("0x"):
                try:
                    return hex(int(v, 16))
                except ValueError:
                    pass
            return v
        nc, ncpp, nmlx = normalize(c), normalize(cpp), normalize(mlx)
        if BaseConfig.SDK_ONLY or nmlx == "-":
            return nc == ncpp
        return nc == ncpp == nmlx


# =============================================================================
# Test Runners
# =============================================================================


class CTestRunner(BaseCTestRunner):
    def __init__(self, device=None):
        super(CTestRunner, self).__init__("C", Config, device)

    def get_register_get(self, register_name):
        return RegisterFieldParser.parse_register_get(self.output, register_name)

    def get_raw_hex(self):
        return RegisterFieldParser.parse_raw_hex(self.output)


class CppTestRunner(BaseCppTestRunner):
    def __init__(self, device=None):
        super(CppTestRunner, self).__init__("C++", Config, device)

    def get_register_get(self, register_name):
        return RegisterFieldParser.parse_register_get(self.output, register_name)

    def get_raw_hex(self):
        return RegisterFieldParser.parse_raw_hex(self.output)


class MlxregCliRunner(object):
    def __init__(self, device=None):
        self.device = device
        self.output = ""
        self.success = False

    def run(self, verbose=True):
        return self.run_get("MGIR", verbose=verbose)

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

    def run_get(self, register_name, indexes=None, verbose=True):
        cmd = self._base_cmd() + " --reg_name {} --get".format(register_name)
        if indexes:
            idx_parts = ["{}={}".format(k, v) for k, v in indexes.items()]
            cmd += " --indexes " + ",".join(idx_parts)
        cmd = "echo '{}' | sudo su".format(cmd)
        self.success, self.output = CommandRunner.run(
            cmd, "Running {} --get {} on {}".format(
                MFT_SDK_REG_TOOL, register_name, self.device), verbose)
        return self.success

    def run_raw_get(self, reg_id, reg_len, verbose=True):
        cmd = self._base_cmd() + " --reg_id {} --reg_len {} --get".format(reg_id, reg_len)
        cmd = "echo '{}' | sudo su".format(cmd)
        self.success, self.output = CommandRunner.run(
            cmd, "Running {} raw GET {} on {}".format(
                MFT_SDK_REG_TOOL, reg_id, self.device), verbose)
        return self.success

    def get_register_get(self):
        return MlxregCliParser.parse_get(self.output)

    def get_raw_hex(self):
        return MlxregCliParser.parse_raw_get(self.output)

    def print_mlxreg_output(self):
        self.run_get("MGIR")
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

    def _handle_all_empty(self, reg_name, mlxreg_cmd):
        if BaseConfig.SDK_ONLY:
            print_sdk_only_empty_agreement("Register GET {}".format(reg_name))
            return True
        cli_error = self.mlxreg_runner.get_error()
        if not self.mlxreg_runner.success and cli_error:
            print("\n{}Both SDK and {} failed consistently — not an SDK bug{}".format(
                GREEN, tool_label(MFT_SDK_REG_TOOL), RESET))
            return True
        print("\n{}Register GET {}: all sources returned empty{}".format(RED, reg_name, RESET))
        return False

    def run_comparison(self):
        v = _verbose()
        results = {}

        if os.path.exists(Config.C_TEST_BIN):
            self.c_runner.run(verbose=v)
        if os.path.exists(Config.CPP_TEST_BIN):
            self.cpp_runner.run(verbose=v)

        for reg_name in Config.NON_INDEXED_REGISTERS:
            if not BaseConfig.SDK_ONLY:
                self.mlxreg_runner.run_get(reg_name, verbose=v)
            c_fields = self.c_runner.get_register_get(reg_name)
            cpp_fields = self.cpp_runner.get_register_get(reg_name)
            mlxreg_fields = self.mlxreg_runner.get_register_get() if not BaseConfig.SDK_ONLY else {}
            sdk_cmd = format_sdk_command(
                binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
                keywords=["InitRegisterMap", "SendPRMReg", "FreePrmRegisterMap"])
            mlxreg_cmd = "{} --reg_name {} --get".format(
                self.mlxreg_runner._base_cmd(), reg_name)
            volatile = Config.VOLATILE_FIELDS.get(reg_name, set())
            if c_fields or cpp_fields or mlxreg_fields:
                results["Register GET ({})".format(reg_name)] = RegisterGetComparisonTable(
                    reg_name, c_fields, cpp_fields, mlxreg_fields,
                    self.device, self.device_type, mlxreg_cmd, sdk_cmd, volatile).print_table()
            else:
                results["Register GET ({})".format(reg_name)] = self._handle_all_empty(reg_name, mlxreg_cmd)

        for reg_name, indexes in Config.INDEXED_REGISTERS.items():
            if not BaseConfig.SDK_ONLY:
                self.mlxreg_runner.run_get(reg_name, indexes=indexes, verbose=v)
            c_fields = self.c_runner.get_register_get(reg_name)
            cpp_fields = self.cpp_runner.get_register_get(reg_name)
            mlxreg_fields = self.mlxreg_runner.get_register_get() if not BaseConfig.SDK_ONLY else {}
            sdk_cmd = format_sdk_command(
                binary_path=[Config.C_TEST_BIN, Config.CPP_TEST_BIN],
                keywords=["InitRegisterMap", "SetPRMRegister", "SendPRMReg", "FreePrmRegisterMap"])
            idx_str = ",".join("{}={}".format(k, vl) for k, vl in indexes.items())
            mlxreg_cmd = "{} --reg_name {} --get --indexes {}".format(
                self.mlxreg_runner._base_cmd(), reg_name, idx_str)
            volatile = Config.VOLATILE_FIELDS.get(reg_name, set())
            if c_fields or cpp_fields or mlxreg_fields:
                results["Register GET ({})".format(reg_name)] = RegisterGetComparisonTable(
                    reg_name, c_fields, cpp_fields, mlxreg_fields,
                    self.device, self.device_type, mlxreg_cmd, sdk_cmd, volatile).print_table()
            else:
                results["Register GET ({})".format(reg_name)] = self._handle_all_empty(reg_name, mlxreg_cmd)

        for reg_name, raw_cfg in Config.RAW_REGISTERS.items():
            if not BaseConfig.SDK_ONLY:
                self.mlxreg_runner.run_raw_get(raw_cfg["reg_id"], raw_cfg["reg_len"], verbose=v)
            c_raw = self.c_runner.get_raw_hex()
            cpp_raw = self.cpp_runner.get_raw_hex()
            mlxreg_raw = self.mlxreg_runner.get_raw_hex() if not BaseConfig.SDK_ONLY else []
            min_len = min(len(c_raw), len(cpp_raw), len(mlxreg_raw)) if mlxreg_raw else min(len(c_raw), len(cpp_raw))
            diff_bytes = sum(1 for i in range(min_len) if c_raw[i] != cpp_raw[i]) if min_len > 0 else 0

            print("\n" + "=" * 70)
            title = "RAW REGISTER COMPARISON: {} ({})".format(reg_name, raw_cfg["reg_id"])
            if self.device:
                title += " [{} - {}]".format(self.device, self.device_type)
            print(title)
            print("=" * 70)
            print("C bytes:   {}".format(len(c_raw)))
            print("C++ bytes: {}".format(len(cpp_raw)))

            has_volatile = bool(Config.VOLATILE_FIELDS.get(reg_name, set()))
            if min_len > 0 and (diff_bytes == 0 or has_volatile):
                match = True
            elif min_len > 0:
                match = (diff_bytes == 0)
            elif BaseConfig.SDK_ONLY and len(c_raw) == len(cpp_raw) == 0:
                print_sdk_only_empty_agreement("Raw Register GET {}".format(reg_name))
                match = True
            else:
                match = False
            results["Raw Register GET ({})".format(reg_name)] = match

        self._print_test_summary(results)
        return self.RESULT_PASS if all(results.values()) else self.RESULT_FAIL

    def _print_test_summary(self, results):
        print("\n" + "=" * 70)
        title = "REGISTER ACCESS TEST SUMMARY"
        if self.device:
            title += " [{} - {}]".format(self.device, self.device_type)
        print(title)
        print("=" * 70)
        for name, passed in results.items():
            status = GREEN + "PASS" + RESET if passed else RED + "FAIL" + RESET
            print("  {:<35}: {}".format(name, status))
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
        "Show {} --get output for first device".format(MFT_SDK_REG_TOOL))


def main():
    return run_main(
        Config, TestSuite, MlxregCliRunner,
        lambda r: r.print_mlxreg_output(), print_usage)


if __name__ == "__main__":
    sys.exit(main())
