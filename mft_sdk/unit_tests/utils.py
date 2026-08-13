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
Shared utilities for the mstflint SDK test scripts.

Synced from the MFT repo's user/mft_sdk/unit_tests/utils.py — keep
divergence minimal. This copy runs tests against installed packages only
(--so mode); building test binaries from this tree is not supported.
Provides common infrastructure: device discovery, command execution,
test runner bases, and CLI argument handling.
"""

from __future__ import print_function
import platform
import subprocess
import sys
import os
import re

# =============================================================================
# ANSI Colors
# =============================================================================

RED = "\033[91m"
GREEN = "\033[92m"
BLUE = "\033[94m"
YELLOW = "\033[93m"
RESET = "\033[0m"

# =============================================================================
# System Library Paths (per-distro)
# =============================================================================


# Maps (pkg_type, arch) -> system library directory.
# Mirrors SYSTEM_LIB_DIR_VARIANTS in pkg/linux/sdk_pkg.bzl.
# To support a new distro just add a row here.
_SYSTEM_LIB_DIR = {
    ("rpm", "x86_64"): "/usr/lib64",
    ("rpm", "aarch64"): "/usr/lib64",
    ("deb", "x86_64"): "/usr/lib/x86_64-linux-gnu",
    ("deb", "aarch64"): "/usr/lib/aarch64-linux-gnu",
}

# Try internal first, fall back to external; either satisfies the framework.
# libmstflint_sdk.so is the open-source mstflint SDK (used with MFT_SDK_SO_DIR
# pointing at its lib dir, e.g. /usr/lib64/mstflint/sdk).
_SDK_SO_CANDIDATES = ("libmft_sdk_int.so.1", "libmft_sdk.so.1", "libmstflint_sdk.so")

# CLI tool the mlxreg compare (non --sdk-only) flow diffs the SDK against.
# Override with MFT_SDK_REG_TOOL (bare name or absolute path) — e.g. mstreg
# to compare against mstflint's CLI instead of MFT's mlxreg_ext.
MFT_SDK_REG_TOOL = os.environ.get("MFT_SDK_REG_TOOL", "mlxreg_ext")

# Same knob for the mlxlink compare flow. Override with MFT_SDK_LINK_TOOL
# (bare name or absolute path) — e.g. mstlink to compare against mstflint's
# CLI instead of MFT's mlxlink_ext. Defaults keep the MFT flow untouched.
MFT_SDK_LINK_TOOL = os.environ.get("MFT_SDK_LINK_TOOL", "mlxlink_ext")


def tool_label(tool):
    """Short display name of a reference CLI, for report headers.

    An override may be an absolute path; the reports only need the tool name,
    and a full path would wreck the fixed-width comparison tables.
    """
    return os.path.basename(tool) if tool else tool


# Known product divergences: register names, field leaf names, or dotted full
# paths that the reference CLI knows but the SDK under test does not — e.g.
# when validating the open-source mstflint SDK, whose bundled register DB lags
# MFT's ADB. A CLI-only entry in this set is reported as an expected
# difference instead of a FAIL; it never relaxes any other direction (an
# SDK-side value that exists still has to match). Comma-separated via env;
# write underscores for spaces in names (the value crosses the shell
# unquoted); default empty = fully strict comparison (the MFT flow).
MFT_SDK_KNOWN_MISSING = frozenset(
    n.strip()
    for n in os.environ.get("MFT_SDK_KNOWN_MISSING", "").split(",")
    if n.strip())


def is_known_missing(name):
    """True when `name` (or its dotted leaf) is a known SDK-missing entry.

    Spaces in `name` match underscores in the env list, which stays
    shell-safe (no quoting needed through the ssh/sudo layers).
    """
    for cand in (name, name.rsplit(".", 1)[-1]):
        if (cand in MFT_SDK_KNOWN_MISSING or
                cand.replace(" ", "_") in MFT_SDK_KNOWN_MISSING):
            return True
    return False


# The reference CLI is whatever MFT happens to be installed on the lab machine
# -- the harness only ever checks that it EXISTS. When that MFT predates a PRM
# alignment it knows fewer register fields than the SDK under test, and every
# newly-added field shows up as an SDK-vs-CLI difference. The oracle cannot
# validate a field it has never heard of, so by default those count as
# "unverifiable here" rather than as failures; fields the two DO share are
# still compared strictly, in both name and attributes. Set
# MFT_SDK_STRICT_ORACLE=1 where the oracle is pinned to the SDK's PRM revision
# to restore a hard failure.
STRICT_ORACLE = os.environ.get("MFT_SDK_STRICT_ORACLE", "").strip() not in ("", "0")


def oracle_version(tool=None):
    """Version banner of the reference CLI, for the report.

    Best effort and purely diagnostic -- never a pass/fail input. Recording it
    is the difference between "6 fields DIFFER" and "6 fields the 4.36 oracle
    does not know", which is the whole triage.

    `tool` defaults to the mlxreg oracle; pass MFT_SDK_LINK_TOOL to report the
    mlxlink side instead.
    """
    tool = tool or MFT_SDK_REG_TOOL
    for cmd in ("{} -v".format(tool),
                "{} --version".format(tool)):
        try:
            p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                                 stderr=subprocess.STDOUT)
            out = p.communicate()[0].decode("utf-8", errors="replace").strip()
        except Exception:  # noqa: BLE001 - diagnostics must never break a run
            continue
        if p.returncode == 0 and out:
            return out.splitlines()[0].strip()
    return "unknown version"


# MFT SDK install directory (distro-independent).
_MFT_SDK_INSTALL_LIB_DIR = "/usr/lib64/mft_sdk"


def _default_cpp_so_test_bin():
    """Installed unified gtest harness: prefer the current name
    (mft_sdk_cpp_so_test); fall back to the pre-rename mft_sdk_so_test so
    packages built before the rename keep working."""
    tests_dir = os.path.join(_MFT_SDK_INSTALL_LIB_DIR, "tests")
    for name in ("mft_sdk_cpp_so_test", "mft_sdk_so_test"):
        path = os.path.join(tests_dir, name)
        if os.path.isfile(path):
            return path
    return os.path.join(tests_dir, "mft_sdk_cpp_so_test")


def _c_so_test_bin():
    """Installed unified C test driver (mft_sdk_c_so_test): one dynamically
    linked binary hosting every C suite, selected by argv[1]. Resolves the
    SDK from libmft_sdk.so.1 at runtime exactly like the gtest harness.
    MFT_SDK_C_SO_TEST_BIN env overrides (e.g. the mstflint flow's seeded
    copy); returns None when the binary is not installed.
    """
    path = os.environ.get(
        "MFT_SDK_C_SO_TEST_BIN",
        os.path.join(_MFT_SDK_INSTALL_LIB_DIR, "tests", "mft_sdk_c_so_test"))
    return path if os.path.isfile(path) else None


def _c_suite_key(config):
    """The unified C driver's suite key (its argv[1]), derived from the
    suite's bazel target name: <x>-c-test-bin -> <x>."""
    target = getattr(config, "C_TEST_TARGET", "") or ""
    name = target.rsplit(":", 1)[-1]
    if not name.endswith("-c-test-bin"):
        return None
    return name[:-len("-c-test-bin")].replace("-", "_")


def _detect_pkg_type():
    """Detect the package type of the running system."""
    if os.path.exists("/etc/debian_version"):
        return "deb"
    return "rpm"


def _detect_arch():
    """Return normalised architecture string matching Bazel platform names."""
    machine = platform.machine()
    if machine in ("x86_64", "amd64"):
        return "x86_64"
    if machine in ("aarch64", "arm64"):
        return "aarch64"
    return machine


def get_system_lib_dir():
    """Return the system library directory for the current OS and architecture.

    Uses the same (pkg_type, arch) mapping that Bazel uses at build time
    (see SYSTEM_LIB_DIR_VARIANTS in pkg/linux/sdk_pkg.bzl).
    """
    key = (_detect_pkg_type(), _detect_arch())
    lib_dir = _SYSTEM_LIB_DIR.get(key)
    if lib_dir is None:
        raise RuntimeError(
            "Unsupported OS/arch combination: pkg_type={}, arch={}. "
            "Add an entry to _SYSTEM_LIB_DIR in utils.py.".format(*key))
    return lib_dir

# =============================================================================
# SDK-Only Mode Validation
# =============================================================================


_PCI_BDF_RE = re.compile(
    r'^(?:[0-9a-fA-F]{4}:)?[0-9a-fA-F]{2}:[0-9a-fA-F]{2}\.[0-9a-fA-F]$')


def _normalize_bdf(bdf):
    """Normalize a PCI BDF to domain-qualified format (DDDD:BB:DD.F)."""
    if re.match(r'^[0-9a-fA-F]{4}:', bdf):
        return bdf
    return "0000:" + bdf


def _get_pci_devices_lspci():
    """Discover Mellanox/NVIDIA PCI devices using lspci (no MFT needed).

    Used in --sdk-only mode where MST is not available.
    """
    lspci_bin = None
    for p in ["/usr/sbin/lspci", "/sbin/lspci", "/usr/bin/lspci"]:
        if os.path.exists(p):
            lspci_bin = p
            break
    if lspci_bin is None:
        lspci_bin = "lspci"
    try:
        output = subprocess.check_output(
            [lspci_bin, "-d", "15b3:"],
            stderr=subprocess.STDOUT).decode('utf-8', errors='replace')
        devices = []
        for line in output.strip().split('\n'):
            if not line.strip():
                continue
            pci_match = re.match(
                r'((?:[0-9a-f]{4}:)?[0-9a-f]{2}:[0-9a-f]{2}\.[0-9])\s',
                line, re.IGNORECASE)
            if pci_match:
                pci = _normalize_bdf(pci_match.group(1))
                desc = line[len(pci_match.group(0)):].strip()
                # lspci prints "<class>: <vendor> <model>". Only network-controller
                # functions are openable by mstGetDeviceHandle; skip everything else
                # (notably the BlueField-3 DPU's own Mellanox-vendor PCIe bridge at
                # 0000:00:00.0, which otherwise sorted first so the caller's devs[0]
                # picked an un-openable BDF -> FAILED_TO_OPEN_DEVICE / status 10).
                pci_class = desc.split(':', 1)[0].strip() if ':' in desc else ''
                if not re.match(r'(ethernet|infiniband|network)\s+controller',
                                pci_class, re.IGNORECASE):
                    continue
                dev_type = re.sub(r'^[^:]*:\s*', '', desc).strip()
                cx = re.search(r'(ConnectX[^\s,]*|BlueField[^\s,]*)',
                               dev_type, re.IGNORECASE)
                if cx:
                    dev_type = cx.group(1)
                devices.append(DeviceInfo(
                    pci, dev_type, rdma="lspci", user_specified=False))
        return devices
    except (subprocess.CalledProcessError, OSError):
        return []


# =============================================================================
# Project Root
# =============================================================================


def find_project_root():
    """Get project root (2 levels up from mft_sdk/unit_tests)."""
    path = os.path.dirname(os.path.realpath(__file__))
    for _ in range(2):
        path = os.path.dirname(path)
    return path


# =============================================================================
# Shared Helpers
# =============================================================================


_ANSI_RE = re.compile(r'\x1b\[[0-9;]*m')


def strip_ansi(text):
    """Remove ANSI SGR escapes from a captured tool output.

    Per-value cleanup (clean_value) is not enough for every oracle: mlxlink
    colours a value and emits the reset AFTER the newline
    (mlxlink/modules/printutil/mlxlink_record.cpp), so the escape lands at the
    START of the next line. mstflint's mstlink does exactly that, which makes
    "\\x1b[0mPhysical state" the parsed key (never matches) and turns the blank
    line that terminates a section into a non-empty "\\x1b[0m" (section never
    ends). Measured on apps-180: OperationalInfoParser saw 1 of 7 fields.
    Stripping the whole captured text at the seam fixes both, and is a no-op
    for an oracle that emits no colour at all.
    """
    return _ANSI_RE.sub('', text)


def clean_value(value):
    """Clean a value by stripping ANSI codes and normalizing whitespace."""
    value = strip_ansi(value)
    value = ' '.join(value.split())
    return value if value else "-"


# =============================================================================
# SDK Function Extraction
# =============================================================================

_SDK_BOILERPLATE = frozenset([
    "mstGetDeviceHandle",
    "mstReleaseDeviceHandle",
    "mstGetLastErrorString",
])


def extract_sdk_functions(source_path, exclude=None):
    """Extract unique mst* SDK function names from a C/C++ source file.

    Returns a list in order of first appearance, excluding common boilerplate
    (mstGetDeviceHandle, mstReleaseDeviceHandle, mstGetLastErrorString).
    """
    if exclude is None:
        exclude = _SDK_BOILERPLATE
    try:
        with open(source_path, 'r') as f:
            content = f.read()
        seen = set()
        result = []
        for m in re.finditer(r'\b(mst[A-Z]\w*)\s*\(', content):
            name = m.group(1)
            if name not in seen and name not in exclude:
                seen.add(name)
                result.append(name)
        return result
    except IOError:
        return []


def _parse_nm_mst_symbols(output, keywords=None, exclude=None):
    """Parse nm output and return matching mst* symbol names."""
    if exclude is None:
        exclude = _SDK_BOILERPLATE
    names = set()
    for line in output.split('\n'):
        parts = line.strip().split()
        for part in parts:
            if part.startswith('mst') and len(part) > 3 and part[3].isupper():
                if part not in exclude:
                    if keywords is None or any(kw in part for kw in keywords):
                        names.add(part)
    return names


def extract_sdk_functions_from_binary(binary_path, keywords=None, exclude=None):
    """Extract mst* SDK function names from a compiled binary using nm.

    Tries two strategies:
      1. ``nm -D --undefined-only`` -- finds dynamically linked SDK symbols
         (--so mode where the binary links against libmft_sdk.so).
      2. ``nm`` (all symbols) -- finds statically linked SDK symbols
         (default mode where the SDK is baked into the binary).

    When *keywords* is provided, only functions whose name contains at
    least one keyword are included (needed for the unified mft_sdk_so_test
    binary which contains all test suites).

    Returns an alphabetically sorted list of function names.
    """
    nm_commands = [
        ["nm", "-D", "--undefined-only", binary_path],
        ["nm", binary_path],
    ]
    for cmd in nm_commands:
        try:
            output = subprocess.check_output(
                cmd, stderr=subprocess.STDOUT).decode('utf-8', errors='replace')
            names = _parse_nm_mst_symbols(output, keywords, exclude)
            if names:
                return sorted(names)
        except (subprocess.CalledProcessError, OSError):
            continue
    return []


def format_sdk_command(binary_path=None, keywords=None, exclude=None):
    """Extract SDK functions from a compiled binary and format as 'func(), func()'.

    Uses ``nm -D --undefined-only`` to find which mst* SDK functions the
    binary links against.  *keywords* filter the results per test suite
    (needed for the unified mft_sdk_so_test binary).

    *binary_path* can be a single path (str) or a list of paths to try
    in order -- the first existing binary is used.

    Args:
        binary_path: Path (or list of paths) to compiled test binary.
        keywords: List of substrings to filter nm output per suite
                  (e.g. ["CountersInfo"]).
        exclude: Optional set of function names to exclude (defaults to boilerplate).

    Returns:
        Formatted string like "mstGetFoo(), mstFreeFoo()" or empty string.
    """
    if binary_path is None:
        return ""
    if isinstance(binary_path, str):
        binary_path = [binary_path]
    for path in binary_path:
        if os.path.exists(path):
            result = extract_sdk_functions_from_binary(
                path, keywords, exclude)
            if result:
                return ", ".join(name + "()" for name in result)
    return ""


# =============================================================================
# Base Configuration
# =============================================================================


class BaseConfig(object):
    """Shared configuration constants. Subclasses add test-specific settings."""

    PROJECT_PATH = find_project_root()

    # mft_sdk_so linking mode (set by --so CLI flag)
    MFT_SDK_SO = False
    SDK_SO_PATH = None  # Resolved at runtime by find_system_lib()

    # Pre-installed test binary (same path on all distros), shipped by mft-sdk.
    # MFT_SDK_SO_TEST_BIN env var overrides (e.g. when validating the mstflint SDK).
    MFT_SDK_SO_TEST_BIN = (os.environ.get("MFT_SDK_SO_TEST_BIN")
                           or _default_cpp_so_test_bin())

    # Verbose mode (set by --verbose CLI flag)
    VERBOSE = False

    # SDK-only mode (set by --sdk-only CLI flag):
    # Run C/C++ tests only, no tool commands, no MST, no MFT needed.
    SDK_ONLY = False

    # Coverage mode (set by --coverage CLI flag):
    # Pass COVFILE=/tmp/mft.cov to test binaries via sudo.
    COVERAGE = False

    # Subclasses must define:
    #   SUITE_NAME       - display name (e.g., "FEC Histogram")
    #   C_TEST_TARGET    - bazel target for C test
    #   CPP_TEST_TARGET  - bazel target for C++ test
    #   C_TEST_BIN       - local path to C test binary
    #   CPP_TEST_BIN     - local path to C++ test binary
    #   GTEST_FILTER     - gtest filter string


# =============================================================================
# Device Discovery
# =============================================================================


class DeviceInfo(object):
    """Information about a PCI device from mst status."""

    def __init__(self, pci, dev_type, rdma="", net="", state="",
                 user_specified=False):
        self.pci = pci
        self.dev_type = dev_type
        self.rdma = rdma
        self.net = net
        self.state = state
        self.user_specified = user_specified

    def is_operational(self):
        """Check if device is in a state that can be queried.

        Note the second case is NOT "no driver loaded" -- mlx5_core can be
        resident and simply have failed to bind to this device (e.g. firmware
        stuck in pre-init), and mstflint reaches devices over pciconf/VSEC
        without needing a bound driver at all. All this says is that port-level
        telemetry is unlikely to be answerable, which is advisory, not a defect.
        """
        if self.state.lower() == "recovery":
            return False, "Device is in recovery mode"
        if not self.rdma and not self.net and not self.user_specified:
            return False, "No RDMA/NET interface (no driver bound to this device)"
        return True, ""


def get_pci_devices():
    """Get list of DeviceInfo objects.

    In SDK-only mode uses lspci; otherwise uses ``mst status -v``.
    """
    if BaseConfig.SDK_ONLY:
        return _get_pci_devices_lspci()
    try:
        output = subprocess.check_output(
            "sudo mst status -v", shell=True, stderr=subprocess.STDOUT).decode()
        devices = []
        for line in output.split('\n'):
            pci_match = re.search(
                r'\b([0-9a-f]{2}:[0-9a-f]{2}\.[0-9])\b', line, re.IGNORECASE)
            if not pci_match:
                continue
            pci = _normalize_bdf(pci_match.group(1))
            parts = line.split()
            dev_type = re.sub(r'\(rev:\d+\)', '',
                              parts[0]) if parts else "Unknown"
            rdma_match = re.search(r'\b(mlx5_\d+)\b', line)
            net_match = re.search(r'\b(net-\S+)\b', line)
            rdma = rdma_match.group(1) if rdma_match else ""
            net = net_match.group(1) if net_match else ""
            state = "recovery" if 'recovery' in line.lower() else ""
            devices.append(DeviceInfo(pci, dev_type, rdma, net, state))
        return devices
    except BaseException:
        return []


# =============================================================================
# Command Runner
# =============================================================================


class CommandRunner(object):
    """Handles execution of shell commands."""

    @staticmethod
    def run(cmd, description, verbose=True, merge_stderr=True,
            strip_ansi_escapes=False):
        """Run a command and return (success, output).

        When BaseConfig.VERBOSE is True, output is streamed in real-time
        and errors are shown even for quiet (verbose=False) commands.

        strip_ansi_escapes=True removes ANSI SGR codes from the RETURNED text
        (the live stream stays coloured). Opt-in, not the default: mlxreg
        output is byte-identical between the oracles today and must stay so,
        and the C/C++ SDK runners are parsed as-is. See strip_ansi() for why
        the mlxlink oracle needs it.

        merge_stderr=False keeps the command's stderr OUT of the returned
        text. Pass it whenever the output is going to be machine-parsed.

        Why this matters: the default 2>&1 merge means any diagnostic the
        reference tool writes to stderr is spliced into the stdout we parse
        as a table -- and because the tool's stdout is a block-buffered pipe
        while stderr is unbuffered, it lands in the MIDDLE of a row. A
        Bullseye-coverage-instrumented mlxreg_ext (COVFILE unset) did exactly
        that on 2026-08-06 and split one row of `--show_reg --full_path` in
        two, which the parsers then read as an SDK field mismatch: 15 red
        rows across apps-174 and apps-08-03 blaming the SDK for a message
        printed by the oracle. The SDK output was correct throughout.
        """
        show_header = verbose or BaseConfig.VERBOSE
        if show_header and description:
            print("\n" + "=" * 60)
            print("[INFO] " + description)
            print("[CMD] " + cmd)
            print("=" * 60)
            sys.stdout.flush()
        if BaseConfig.VERBOSE:
            # Stream output line-by-line in real-time while capturing it
            process = subprocess.Popen(
                cmd, shell=True, stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT if merge_stderr else subprocess.DEVNULL)
            output_lines = []
            for line in iter(process.stdout.readline, b''):
                decoded = line.decode('utf-8', errors='replace')
                sys.stdout.write(decoded)
                sys.stdout.flush()
                output_lines.append(decoded)
            process.wait()
            output = ''.join(output_lines)
        else:
            process = subprocess.Popen(
                cmd, shell=True, stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT if merge_stderr else subprocess.DEVNULL)
            output, _ = process.communicate()
            output = output.decode('utf-8', errors='replace')
        if strip_ansi_escapes:
            output = strip_ansi(output)
        success = process.returncode == 0
        if show_header and description:
            status = "[SUCCESS]" if success else "[ERROR]"
            msg = " completed successfully" if success else " failed with return code " + \
                str(process.returncode)
            print(status + " " + description + msg)
        return success, output

    @staticmethod
    def run_quiet(cmd, strip_ansi_escapes=False):
        """Run a command quietly and return (success, output)."""
        return CommandRunner.run(cmd, "", verbose=False,
                                 strip_ansi_escapes=strip_ansi_escapes)


# =============================================================================
# MST Manager
# =============================================================================


class MstManager(object):
    """Manages MST (Mellanox Software Tools) lifecycle for the test session."""

    _started = False

    @staticmethod
    def start():
        """Start MST. Skipped in SDK-only mode. Raises RuntimeError on failure."""
        if BaseConfig.SDK_ONLY:
            return
        print("\n[MST] Starting MST...")
        success, output = CommandRunner.run("sudo mst start", "Starting MST")
        if not success:
            raise RuntimeError(
                "Failed to start MST. Cannot proceed with tests.\n"
                "Output: " + output)
        MstManager._started = True

    @staticmethod
    def stop():
        """Stop MST (best-effort, errors are ignored). Skipped in SDK-only mode."""
        if BaseConfig.SDK_ONLY or not MstManager._started:
            return
        print("\n[MST] Stopping MST...")
        CommandRunner.run("sudo -n mst stop", "Stopping MST", verbose=False)


# =============================================================================
# Error Parsing
# =============================================================================

_SDK_ERROR_RE = re.compile(r'Failed to get.*?got status \d+:\s*(.+)')
_GTEST_ERROR_RE = re.compile(r'Failed to get.*?:\s*(.+)')
_MLXLINK_ERROR_RE = re.compile(
    r'(?:-E-|raised the following exception:)\s*(.+)')


def _find_first_match(pattern, output):
    """Return first regex match group(1) across lines, or None."""
    for line in output.split('\n'):
        m = pattern.search(line)
        if m:
            return m.group(1).strip()
    return None


def parse_sdk_error(output):
    """Extract the error message from a failed SDK C test output."""
    return _find_first_match(_SDK_ERROR_RE, output)


def parse_gtest_error(output):
    """Extract the error message from a failed SDK C++ (gtest) output."""
    return _find_first_match(_GTEST_ERROR_RE, output)


def parse_mlxlink_error(output):
    """Extract the error message from a failed mlxlink output."""
    return _find_first_match(_MLXLINK_ERROR_RE, output)


# =============================================================================
# Test Runner Bases
# =============================================================================


class TestRunner(object):
    """Base class for test runners."""

    def __init__(self, name):
        self.name = name
        self.output = ""
        self.success = False

    def run(self, verbose=True):
        raise NotImplementedError


class BaseCTestRunner(TestRunner):
    """Base C test runner. Subclasses add result-parsing methods."""

    def __init__(self, name, config, device=None):
        super(BaseCTestRunner, self).__init__(name)
        self.device = device
        self.config = config

    def _device_arg(self):
        return _normalize_bdf(self.device) if self.device else ""

    @staticmethod
    def _sudo_prefix():
        """Build sudo prefix for running test binaries.

        MFT_SDK_SO_DIR env var points at a non-standard SDK lib dir (e.g. the
        mstflint SDK); it is forwarded through sudo via `env` because sudoers
        strips LD_* from the environment.
        """
        so_dir = os.environ.get("MFT_SDK_SO_DIR")
        env_part = "env LD_LIBRARY_PATH={} ".format(so_dir) if so_dir else ""
        if BaseConfig.COVERAGE:
            covfile = os.environ.get("COVFILE", "/tmp/mft.cov")
            return "sudo " + env_part + "COVFILE={} ".format(covfile)
        return "sudo " + env_part

    def run(self, verbose=True):
        if not os.path.exists(self.config.C_TEST_BIN):
            if verbose:
                print("[ERROR] {} C test binary not found: {}".format(
                    self.config.SUITE_NAME, self.config.C_TEST_BIN))
            return False

        cmd = self._sudo_prefix() + self.config.C_TEST_BIN
        # In --so mode the C column is the unified C driver when installed
        # (suite selected by argv[1], BDF positional); only when it falls
        # back to the gtest harness does the invocation need a filter.
        c_suite = getattr(self.config, "C_SO_SUITE", None)
        if BaseConfig.MFT_SDK_SO and c_suite and \
                self.config.C_TEST_BIN != BaseConfig.MFT_SDK_SO_TEST_BIN:
            cmd += " " + c_suite
            if self.device:
                cmd += " " + self._device_arg()
        elif BaseConfig.MFT_SDK_SO:
            cmd += ' --gtest_filter="' + self.config.GTEST_FILTER + '"'
            if self.device:
                cmd += " -d " + self.device
        else:
            cmd += " " + self._device_arg()
        self.success, self.output = CommandRunner.run(
            cmd, "Running {} C test on {}".format(self.config.SUITE_NAME, self.device), verbose)
        if not self.success and self.output and verbose:
            print("[WARNING] C test exited with non-zero rc on {} "
                  "(output still captured)".format(self.device))
        if verbose:
            print("\n[OUTPUT]\n" + "-" * 60 + "\n" + self.output + "-" * 60)
        return self.success

    def get_error(self):
        if BaseConfig.MFT_SDK_SO and \
                self.config.C_TEST_BIN == BaseConfig.MFT_SDK_SO_TEST_BIN:
            return parse_gtest_error(self.output)
        return parse_sdk_error(self.output)


class BaseCppTestRunner(TestRunner):
    """Base C++ test runner. Subclasses add result-parsing methods."""

    def __init__(self, name, config, device=None):
        super(BaseCppTestRunner, self).__init__(name)
        self.device = device
        self.config = config

    def run(self, verbose=True):
        if not os.path.exists(self.config.CPP_TEST_BIN):
            if verbose:
                print("[ERROR] {} C++ test binary not found: {}".format(
                    self.config.SUITE_NAME, self.config.CPP_TEST_BIN))
            return False
        prefix = BaseCTestRunner._sudo_prefix()
        cmd = prefix + self.config.CPP_TEST_BIN + \
            ' --gtest_filter="' + self.config.GTEST_FILTER + '"'
        if self.device:
            cmd += " -d " + self.device
        self.success, self.output = CommandRunner.run(
            cmd, "Running {} C++ test on {}".format(self.config.SUITE_NAME, self.device), verbose)
        if not self.success and self.output and verbose:
            print("[WARNING] C++ test exited with non-zero rc on {} "
                  "(output still captured)".format(self.device))
        if verbose:
            print("\n[OUTPUT]\n" + "-" * 60 + "\n" + self.output + "-" * 60)
        return self.success

    def get_error(self):
        return parse_gtest_error(self.output)


class BaseMlxlinkRunner(TestRunner):
    """Base mlxlink runner. Subclasses add parsing and display methods."""

    def __init__(self, name, device=None):
        super(BaseMlxlinkRunner, self).__init__(name)
        self.device = device

    def _base_cmd(self):
        """Build base mlxlink command (without extra flags)."""
        base = MFT_SDK_LINK_TOOL
        if self.device:
            base += " -d " + self.device
        return base

    def _cmd(self):
        """Build full mlxlink command. Override to add extra flags."""
        return self._base_cmd()

    def run(self, verbose=True):
        cmd = "echo '{}' | sudo su".format(self._cmd())
        # strip_ansi_escapes: this is the oracle output every mlxlink parser
        # reads. mstlink resets colour after the newline, so the escapes leak
        # onto the next line's key and onto the section-terminating blank line.
        self.success, self.output = CommandRunner.run(
            cmd, "Running {} on {}".format(self.name, self.device), verbose,
            strip_ansi_escapes=True)
        return self.success

    def get_error(self):
        return parse_mlxlink_error(self.output)


# =============================================================================
# Base Test Suite
# =============================================================================


def print_sdk_only_empty_agreement(label=None):
    """Under SDK_ONLY mode, C and C++ both returning empty is agreement
    (no SDK divergence), not a failure. `label` is an optional context
    string printed before the message (e.g. "Register GET FOO").
    """
    prefix = "{}: ".format(label) if label else ""
    print("\n{}{}C and C++ agree (both empty) — "
          "not an SDK divergence{}".format(GREEN, prefix, RESET))


class BaseTestSuite(object):
    """Base test suite with shared infrastructure.

    Subclasses must:
      - Set self.c_runner, self.cpp_runner, self.mlxlink_runner in __init__
      - Implement run_comparison()
    """

    RESULT_PASS = 0
    RESULT_FAIL = 1
    RESULT_SKIP = 2

    def __init__(self, device_info, config):
        self.results = {}
        self.device_info = device_info
        self.device = device_info.pci
        self.device_type = device_info.dev_type
        self.config = config
        # Subclasses must set: self.c_runner, self.cpp_runner, self.mlxlink_runner

    def _get_mlxlink_cmd(self):
        """Display command for the reference CLI, for the report header.

        Derived from the runner that actually executes, so the header can
        never name a tool the run did not use (it follows MFT_SDK_LINK_TOOL /
        MFT_SDK_REG_TOOL for free). Override only to ADD semantics, e.g. flags
        the runner appends per call rather than in _cmd().
        """
        return self.mlxlink_runner._cmd()

    def _print_header(self, status_type):
        """Print the standard header box for a device test."""
        device_label = self.device
        if self.device_type:
            device_label += " - " + self.device_type
        print("\n" + "=" * 70)
        print("{} [{}]".format(status_type, device_label))
        print("=" * 70)
        print("{}Command: {}{}".format(BLUE, self._get_mlxlink_cmd(), RESET))

    def _print_summary(self):
        """Print the test results summary."""
        title = "{} TEST SUMMARY".format(self.config.SUITE_NAME.upper())
        print("\n" + "=" * 60 + "\n" + title + "\n" + "=" * 60)
        for name, passed in self.results.items():
            print("  {}: {}".format(name, "PASS" if passed else "FAIL"))
        print("=" * 60 + "\nOverall: " + (
            "ALL TESTS PASSED" if all(
                self.results.values()) else "SOME TESTS FAILED"
        ) + "\n" + "=" * 60)

    def _check_operational(self):
        """Return a result code if the device cannot be tested, else None.

        Recovery is a transient state and short-circuits to SKIP.

        Anything else -- in practice "no interface / no driver bound" -- is
        NOT decided here. It used to return FAIL, which short-circuited the
        very fallback written for this case: every caller ends in
        _compare_errors(), which PASSes when the C runner, the C++ runner and
        mlxlink all fail identically (no SDK divergence, which is the only
        thing this suite exists to detect) and FAILs the moment they disagree.
        Deciding here instead threw that evidence away and reported an
        unreachable device as an SDK failure -- on 2026-08-12 one BlueField3
        whose firmware never left pre-init produced 16 of the run's 40
        failures this way, while mlxreg and the mlxlink counters suite, which
        do not call this gate, PASSed on the same devices at the same instant
        by comparing errors.

        So: print the condition as an advisory and return None to let the
        comparison run. It costs three tool invocations per device and
        strictly increases detection power.
        """
        is_operational, reason = self.device_info.is_operational()
        if is_operational:
            return None
        if "recovery" in reason.lower():
            self._print_header("SKIP")
            print("{}Reason: {}{}".format(RED, reason, RESET))
            return self.RESULT_SKIP
        self._print_header("ADVISORY")
        print("{}{}{} - port-level data is likely unavailable; comparing what "
              "each runner reports instead of assuming an SDK fault.".format(
                  YELLOW, reason, RESET))
        return None

    def _compare_errors(self):
        """Compare error messages from all runners when no data was produced.

        Extracts the error from each runner that produced output,
        prints them, and returns RESULT_PASS if all runners reported an error,
        RESULT_FAIL if any runner failed to produce an error message.
        """
        errors = {}
        if self.c_runner.output:
            errors["C"] = self.c_runner.get_error()
        if self.cpp_runner.output:
            errors["C++"] = self.cpp_runner.get_error()
        if self.mlxlink_runner.output:
            errors["mlxlink"] = self.mlxlink_runner.get_error()

        self._print_header("ERROR COMPARISON")

        if not errors:
            print("{}No output from any runner{}".format(RED, RESET))
            return self.RESULT_FAIL

        nw = max(len(k) for k in errors) + 2
        all_have_errors = all(v for v in errors.values())
        unique = set(v for v in errors.values() if v)
        all_same = all_have_errors and len(unique) == 1

        for name, err in errors.items():
            if err:
                color = GREEN if all_have_errors else RED
                print("  {:<{}} : {}{}{}".format(name, nw, color, err, RESET))
            else:
                print("  {:<{}} : {}(no error extracted){}".format(
                    name, nw, RED, RESET))

        if all_same:
            print("\n{}All runners returned the same error{}".format(
                GREEN, RESET))
        elif all_have_errors:
            print("\n{}All runners returned an error{}".format(
                GREEN, RESET))
        else:
            print("\n{}Some runners failed to produce an error{}".format(
                RED, RESET))
            return self.RESULT_FAIL

        return self.RESULT_PASS

    def run_full_suite(self):
        """Run the full test suite against pre-installed binaries (--so only).

        In SDK-only mode the tool command (mlxlink/mlxreg_ext) is skipped.
        """
        name = self.config.SUITE_NAME
        if not BaseConfig.MFT_SDK_SO:
            print("\n{}[ERROR] {} full suite requires --so in the mstflint tree "
                  "(building test binaries here is not supported).{}".format(
                      RED, name, RESET))
            return 1
        if BaseConfig.SDK_ONLY:
            print("\n" + "=" * 60 +
                  "\n{} Test Runner\nSDK-only mode: C/C++ tests only\n".format(name) + "=" * 60)
        else:
            print("\n" + "=" * 60 +
                  "\n{} Test Runner\nUsing pre-installed binaries (--so mode)\n".format(name) + "=" * 60)

        self.results['c_run'] = self.c_runner.run()
        self.results['cpp_run'] = self.cpp_runner.run()
        if not BaseConfig.SDK_ONLY:
            self.results['mlxlink_run'] = self.mlxlink_runner.run()
        self._print_summary()
        return 0 if all(self.results.values()) else 1

    def run_comparison(self):
        """Run comparison mode. Subclasses must implement."""
        raise NotImplementedError


# =============================================================================
# CLI Utilities
# =============================================================================


def parse_cli_args():
    """Parse common CLI arguments.

    Returns:
        (device_pci, do_build, mft_sdk_so, sdk_only, coverage, remaining_args) tuple.
    """
    args = sys.argv[1:]
    device_pci = None
    do_build = False
    mft_sdk_so = False
    sdk_only = False
    coverage = False

    if '--verbose' in args:
        BaseConfig.VERBOSE = True
        args.remove('--verbose')
    if '--so' in args:
        mft_sdk_so = True
        args.remove('--so')
    if '--sdk-only' in args:
        sdk_only = True
        args.remove('--sdk-only')
    if '--coverage' in args:
        coverage = True
        args.remove('--coverage')
    if '--build' in args:
        do_build = True
        args.remove('--build')
    if '-d' in args:
        idx = args.index('-d')
        if idx + 1 < len(args):
            device_pci = args[idx + 1]
            args = args[:idx] + args[idx + 2:]

    return device_pci, do_build, mft_sdk_so, sdk_only, coverage, args


def resolve_device(device_pci, all_devices, arg):
    """Resolve DeviceInfo from CLI args.

    Returns DeviceInfo or None.
    """
    if device_pci:
        if not _PCI_BDF_RE.match(device_pci):
            raise ValueError(
                "Invalid PCI address '{}'. "
                "Expected format: [DDDD:]BB:DD.F".format(device_pci))
        device_pci = _normalize_bdf(device_pci)
        for dev in all_devices:
            if dev.pci == device_pci:
                return dev
        return DeviceInfo(device_pci, "Unknown", user_specified=True)
    elif all_devices and arg != '--compare':
        return all_devices[0]
    return None


def list_devices(all_devices):
    """Print available PCI devices with operational status."""
    for dev in all_devices:
        is_ok, reason = dev.is_operational()
        status = GREEN + "OK" + RESET if is_ok else RED + reason + RESET
        print("{} ({}) - {}".format(dev.pci, dev.dev_type, status))


def print_usage(mlxlink_description):
    """Print common usage help.

    Args:
        mlxlink_description: Description for the --mlxlink option.
    """
    print("""Usage: {} [OPTIONS]

Options:
  (no args)       Run full test suite on first device
  --compare -d D  Compare C, C++, mlxlink on specific device (requires -d)
  --compare-all   Compare on ALL devices
  --mlxlink       {}
  -d DEVICE       Specify device (e.g., -d 81:00.1)
  --list          List available PCI devices
  --verbose       Show all output in real-time (build logs, test output, errors)
  --so            Use pre-installed mft_sdk_so binaries (no build, .so auto-detected)
  --sdk-only      SDK-only mode: run C/C++ tests and compare without tool commands.
                  No mst start, no device discovery via MST (uses lspci instead).
                  Use --so for pre-installed mft_sdk_so test binaries.
  --coverage      Coverage mode: pass COVFILE=/tmp/mft.cov to test binaries via sudo.
                  Requires a coverage-instrumented MFT build and mft.cov in /tmp.
  --help          Show this help message""".format(sys.argv[0], mlxlink_description))


def run_compare_all(all_devices, test_suite_class, config, do_build):
    """Run comparison on all devices and print final summary.

    Returns 0 if no failures, 1 otherwise.
    """
    if not all_devices:
        print("No devices found")
        return 1
    if do_build:
        print("{}[ERROR] --build is not supported in the mstflint tree; "
              "use --so with installed packages.{}".format(RED, RESET))
        return 1

    passed, failed, skipped = 0, 0, 0
    for dev in all_devices:
        result = test_suite_class(dev).run_comparison()
        if result == BaseTestSuite.RESULT_PASS:
            passed += 1
        elif result == BaseTestSuite.RESULT_SKIP:
            skipped += 1
        else:
            failed += 1

    print("\n" + "=" * 70)
    print("FINAL SUMMARY")
    print("=" * 70)
    print("Total devices: {}".format(passed + failed + skipped))
    print("{}  Passed:  {}{}".format(GREEN, passed, RESET))
    print("{}  Failed:  {}{}".format(RED, failed, RESET))
    print("{}  Skipped: {}{}".format(YELLOW, skipped, RESET))
    print("=" * 70)
    return 0 if failed == 0 else 1


def run_main(config, test_suite_class, mlxlink_runner_class, mlxlink_action, print_usage_fn):
    """Common main() entry point for test scripts.

    Starts MST once before any test/device operations and stops it in a
    finally block.  If ``sudo mst start`` fails the run is aborted with a
    RuntimeError.

    Args:
        config: Config class with test targets and settings.
        test_suite_class: TestSuite class (takes device_info).
        mlxlink_runner_class: Mlxlink runner class (takes device).
        mlxlink_action: callable(runner) -> int for --mlxlink mode.
        print_usage_fn: callable for --help mode.

    Returns:
        Exit code (0 = success).
    """
    device_pci, do_build, mft_sdk_so, sdk_only, coverage, args = parse_cli_args()

    if do_build:
        print("{}[ERROR] --build is not supported in the mstflint tree "
              "(test binaries are not built from mstflint); use --so with "
              "installed packages.{}".format(RED, RESET))
        return 1

    if coverage:
        BaseConfig.COVERAGE = True
        os.environ.setdefault("COVFILE", "/tmp/mft.cov")
        print("[INFO] Coverage mode: COVFILE will be passed to test binaries")
    arg = args[0] if args else None

    if arg in ('--help', '-h'):
        print_usage_fn()
        return 0

    # Configure SDK-only mode (--so is never implied)
    if sdk_only:
        BaseConfig.SDK_ONLY = True
        print("[INFO] SDK-only mode: C/C++ comparison only (no tool commands)")
        if not mft_sdk_so:
            missing = []
            if not os.path.isfile(config.C_TEST_BIN):
                missing.append(config.C_TEST_BIN)
            if not os.path.isfile(config.CPP_TEST_BIN):
                missing.append(config.CPP_TEST_BIN)
            if missing:
                print(
                    "{}[ERROR] SDK-only without --so requires built test binaries.{}".format(
                        RED, RESET))
                for p in missing:
                    print("  missing: {}".format(p))
                print("Use --so for pre-installed mft_sdk_so binaries.")
                return 1

    # Configure mft_sdk_so linking mode (run-only, no building)
    if mft_sdk_so:
        BaseConfig.MFT_SDK_SO = True
        # C column: prefer the unified C driver (mft_sdk_c_so_test). Like
        # the gtest harness it links libmft_sdk.so.1 dynamically, so
        # MFT_SDK_SO_DIR selects which SDK it tests (works for the mstflint
        # flow too, via its seeded copy). Falls back to the harness when
        # the driver is not installed.
        c_bin = _c_so_test_bin()
        c_suite = _c_suite_key(config)
        if c_bin and c_suite:
            config.C_TEST_BIN = c_bin
            config.C_SO_SUITE = c_suite
            print("[INFO] C column: unified C driver {} (suite {})".format(
                c_bin, c_suite))
        else:
            config.C_TEST_BIN = BaseConfig.MFT_SDK_SO_TEST_BIN
            print("[INFO] C column: gtest harness (unified C driver not installed)")
        config.CPP_TEST_BIN = BaseConfig.MFT_SDK_SO_TEST_BIN
        print("[INFO] mft_sdk_so mode: using pre-installed binaries (build disabled)")

        # MFT_SDK_SO_DIR env var overrides the system lib dir (e.g. the
        # mstflint SDK under /usr/local/lib/mstflint/sdk).
        lib_dir = os.environ.get("MFT_SDK_SO_DIR")
        if lib_dir:
            print("[INFO] MFT_SDK_SO_DIR override: {}".format(lib_dir))
        else:
            try:
                lib_dir = get_system_lib_dir()
            except RuntimeError as e:
                print("{}[ERROR] {}{}".format(RED, e, RESET))
                return 1
            print("[INFO] detected OS: pkg_type={}, arch={} -> {}".format(
                _detect_pkg_type(), _detect_arch(), lib_dir))
        for name in _SDK_SO_CANDIDATES:
            candidate = os.path.join(lib_dir, name)
            if os.path.exists(candidate):
                BaseConfig.SDK_SO_PATH = candidate
                break
        if BaseConfig.SDK_SO_PATH is None:
            tried = ", ".join(os.path.join(lib_dir, n) for n in _SDK_SO_CANDIDATES)
            print("{}[ERROR] no SDK shared library found - tried: {} - is the MFT package installed?{}".format(
                RED, tried, RESET))
            return 1
        print("[INFO] .so verified: {}".format(BaseConfig.SDK_SO_PATH))
        if not os.path.exists(BaseConfig.MFT_SDK_SO_TEST_BIN):
            print("{}[ERROR] {} not found - is the MFT package installed?{}".format(
                RED, BaseConfig.MFT_SDK_SO_TEST_BIN, RESET))
            return 1
        print("[INFO] test binary verified: {}".format(BaseConfig.MFT_SDK_SO_TEST_BIN))

    # --mlxlink is not available in SDK-only mode
    if BaseConfig.SDK_ONLY and arg == '--mlxlink':
        print("{}[ERROR] --mlxlink is not available in --sdk-only mode "
              "(no tool commands).{}".format(RED, RESET))
        return 1

    MstManager.start()
    try:
        all_devices = get_pci_devices()
        try:
            device_info = resolve_device(device_pci, all_devices, arg)
        except ValueError as e:
            print("{}[ERROR] {}{}".format(RED, e, RESET))
            return 1

        if not BaseConfig.SDK_ONLY and device_pci and arg != '--list':
            known_pcis = {dev.pci for dev in all_devices}
            normalized_pci = _normalize_bdf(device_pci)
            if normalized_pci not in known_pcis:
                print("{}[ERROR] Device '{}' not found on this machine.{}".format(
                    RED, device_pci, RESET))
                print("Available devices:")
                if all_devices:
                    list_devices(all_devices)
                else:
                    print("  (none)")
                return 1

        if arg == '--list':
            list_devices(all_devices)
            return 0
        elif arg == '--mlxlink':
            device = device_info.pci if device_info else None
            runner = mlxlink_runner_class(device)
            return mlxlink_action(runner)
        elif arg == '--compare':
            if not device_info:
                print("ERROR: --compare requires -d DEVICE to specify which device to test")
                print(
                    "Use --list to see available devices, or use --compare-all for all devices")
                return 1
            return test_suite_class(device_info).run_comparison()
        elif arg == '--compare-all':
            return run_compare_all(all_devices, test_suite_class, config, do_build)
        elif arg:
            print("Unknown option: " + arg)
            print_usage_fn()
            return 1

        if not device_info:
            if BaseConfig.SDK_ONLY:
                print("{}[ERROR] No devices found via lspci. "
                      "Specify a device with -d DEVICE.{}".format(RED, RESET))
            else:
                print("No devices found")
            return 1
        return test_suite_class(device_info).run_full_suite()
    finally:
        MstManager.stop()  # no-op in SDK-only mode
