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
Packaging test for the mstflint SDK build_sdk.sh customization flags:
--prefix/--libdir/--includedir/--datadir (install-dir relocation) and
--rpm-name/--deb-name (package identity rename).

mstflint-SDK-ONLY suite: it installs/uninstalls mstflint-sdk package VARIANTS,
so it must run LAST (after every other suite) and never for the MFT product.

Per variant it: wipes ALL previous MFT-SDK/mstflint-SDK installs (verified
clean slate), installs the variant package from the shared cache, asserts
package identity + install layout + compiled-in PRM db path, compiles and
runs a C smoke client against the variant's headers/libs on a live device,
spot-checks the installed gtest harness through the variant libdir, and (in
compare mode) re-runs the mlxreg register-access compare against the CLI to
prove the relocated SDK is functionally identical. Restores the default
package at the end (even on failure), so the machine is left in the state
the rest of the flow expects.

The fixed-location problem: existing --so tests already resolve the SDK .so
via the MFT_SDK_SO_DIR env override and the harness via MFT_SDK_SO_TEST_BIN
(utils.py); this test points both at the VARIANT's dirs and asserts the DEFAULT
paths are absent — so nothing can silently fall back to a stale copy. The
harness links the SDK's real soname, steered into the variant libdir by
LD_LIBRARY_PATH alone.
Headers have no runtime consumer in --so mode, so they are covered by the
compile step of packaging_smoke.c against the variant includedir.

Usage:
    ./test_build_flags.py --variant paths_only --compare -d D --so
    ./test_build_flags.py --variant name_only  --compare-all --so [--sdk-only]
    ./test_build_flags.py --variant both       --compare-all --so
    ./test_build_flags.py --help

Env:
    MSTFLINT_PKG_CACHE     package cache root (required); variants live at
                           <cache>/variants/<variant>/<arch>/ and
                           <cache>/variants/manifest.json
    MFT_SDK_SO_TEST_BIN    gtest harness binary (default: this tree's
                           unit_tests/build-tests/mstflint_sdk_cpp_test,
                           built by `make -C mft_sdk/unit_tests unified`)
"""

from __future__ import print_function
import json
import os
import platform
import re
import subprocess
import sys
import time
from collections import OrderedDict

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from utils import (  # noqa: E402
    RED, GREEN, BLUE, RESET,
    CommandRunner, MFT_SDK_REG_TOOL,
    _get_pci_devices_lspci, _normalize_bdf,
    strip_ansi, device_not_answering, device_not_answering_detail,
    announce_device_not_answering,
)

YELLOW = "\033[93m"

# The harness is built from this tree by mft_sdk/unit_tests/Makefile and links
# libmstflint_sdk.so, the only SDK library the mstflint-sdk package ships.
# MFT_SDK_SO_TEST_BIN overrides this for a non-default BUILD_DIR.
_TESTS_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_HARNESS = os.path.join(_TESTS_DIR, "build-tests", "mstflint_sdk_cpp_test")
SDK_SONAME = "libmstflint_sdk.so"
GTEST_EXCLUSIONS = "-*I2c*:*NullDeviceToAllApis*:*TelemetryJson*:*FreeJsonString*"

# Every package identity this suite may install or must clean away. The wipe
# below removes exactly these + the SDK install dirs; it deliberately does NOT
# touch the CLI tools that serve as the compare reference (mstreg/mstlink ship
# outside these packages) nor the harness, which is built in the source tree.
SDK_PKGS = ["mstflint-sdk", "sdkv-mstflint-sdk"]

VARIANTS = ("paths_only", "name_only", "both")


def _run(cmd, desc="", verbose=False, timeout=None):
    """Run a shell command; return (rc, output). Never raises."""
    if verbose and desc:
        print("{}[CMD]{} {}".format(BLUE, RESET, cmd))
    try:
        p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE,
                             stderr=subprocess.STDOUT)
        out, _ = p.communicate(timeout=timeout) if sys.version_info[0] >= 3 \
            else (p.communicate()[0], None)
        return p.returncode, out.decode("utf-8", errors="replace")
    except Exception as e:  # noqa: BLE001 - a broken command is a test FAIL, not a crash
        return 1, str(e)


def _pkg_type():
    """Which packaging this DISTRO uses -- not merely which tools are present.

    The old test was `dpkg and not rpm -> deb`, which misreads any Debian
    machine that happens to have /usr/bin/rpm installed (a perfectly normal
    thing: rpm2cpio, or a cross-inspection tool). apps-124-002 (Ubuntu 24.04,
    aarch64) has both, was classified rpm, and then hunted for
    mstflint-sdk-*.rpm in an aarch64 cache holding only a .deb -- 3 red
    "variant package not in cache" rows for a machine whose deb was right
    there. The sibling apps-124-003 (Debian 13, no rpm binary) passed the same
    suite, which is the asymmetry that gave it away.

    Ask /etc/os-release first; fall back to dpkg OWNING its own binary (true
    only on a real dpkg distro), and only then to bare tool presence.
    """
    try:
        with open("/etc/os-release") as fh:
            osr = fh.read().lower()
        ids = " ".join(l.split("=", 1)[1].strip().strip('"')
                       for l in osr.splitlines() if l.startswith(("id=", "id_like=")))
        if any(d in ids for d in ("debian", "ubuntu")):
            return "deb"
        if any(d in ids for d in ("rhel", "fedora", "centos", "suse", "mariner", "azurelinux")):
            return "rpm"
    except Exception:  # noqa: BLE001 - fall through to the probes below
        pass
    # dpkg owning its own binary is true only where dpkg is the system manager.
    if os.path.exists("/usr/bin/dpkg") and subprocess.call(
            "dpkg -S /usr/bin/dpkg >/dev/null 2>&1", shell=True) == 0:
        return "deb"
    return "rpm" if os.path.exists("/usr/bin/rpm") else "deb"


def _arch():
    return platform.machine()


def _default_dirs(pkg):
    """System-default autotools dirs per package flavor."""
    if pkg == "rpm":
        libdir = "/usr/lib64"
    else:
        libdir = "/usr/lib/{}-linux-gnu".format(_arch())
    return {"prefix": "/usr", "libdir": libdir,
            "includedir": "/usr/include", "datadir": "/usr/share"}


def _ldconfig():
    _run("sudo ldconfig 2>/dev/null || sudo /sbin/ldconfig 2>/dev/null || true")


# =============================================================================
# dpkg lock
# =============================================================================
#
# Every `sudo dpkg` below mutates the package database, which dpkg refuses to
# do while anyone else holds its lock. On 2026-10-07 Ubuntu's apt-daily.service
# (unattended-upgrade --download-only) held /var/lib/dpkg/lock-frontend on
# apps-102-bf from 07:55:19 to 08:02:17 UTC, and SDK-Verify's purge/install at
# 08:01:29-31 failed with "dpkg frontend lock was locked by another process".
# So every mutation first waits the lock out -- within a budget.

DPKG_LOCKS = ("/var/lib/dpkg/lock-frontend", "/var/lib/dpkg/lock")
PKG_LOCK_POLL_S = 5
PKG_LOCK_BUDGET_S = 420

# dpkg's/apt's own words for "someone else has the lock".
_LOCK_ERROR_RE = re.compile(
    r"locked by another process|unable to (?:acquire|lock)|could not get lock",
    re.I)


def _pkg_lock_budget():
    """Seconds ONE script may spend waiting for the dpkg lock, all waits
    together: SDKV_PKG_LOCK_WAIT, default 420. The apt-daily hold above
    lasted 418 s. SDK-Verify sets the same 420 and gives each pkg_flags
    script TIMEOUTS.pythonSuite (900 s) PLUS this budget
    (config.TIMEOUTS.pkgFlagsScript, 1320 s), so a full wait does not eat
    into the 900 s the variant's own steps had before the wait existed."""
    try:
        return max(0, int(os.environ.get("SDKV_PKG_LOCK_WAIT",
                                         str(PKG_LOCK_BUDGET_S))))
    except ValueError:
        return PKG_LOCK_BUDGET_S


def _proc_comm(pid):
    try:
        with open("/proc/{}/comm".format(pid)) as fh:
            return fh.read().strip() or "?"
    except (IOError, OSError):
        return "?"


class PkgLockWaiter(object):
    """Waits while a dpkg lock is held, against a cumulative budget.

    Holders come from the kernel's own lock table, /proc/locks: it lists each
    lock as "<n>: POSIX ADVISORY WRITE <pid> <maj>:<min>:<inode> ...", so the
    lock file's key from os.stat names the holder -- no tool, no sudo. lslocks
    was blind on the very host this wait was written for: util-linux 2.37.x
    (Ubuntu 22.04) prints an EMPTY path for every lock on a device whose major
    needs three hex digits, and apps-102-bf keeps /var/lib/dpkg on NVMe 259:2
    ("103:02"). Fixed upstream in 2.38. SDK-Verify's own wait
    (install.js pkgLockHolderSh) reads /proc/locks the same way.
    Not matched: a lock file on a btrfs subvolume, whose st_dev is not the
    device /proc/locks prints -- every DEB host measured is ext4.

    Only where /proc/locks cannot be read: `lslocks`, else `fuser` (missing on
    apps-119-001), both through `sudo -n`, since a normal user cannot resolve
    the fds of root's apt. With none of them it cannot tell, says so once and
    does not wait. It never touches the lock itself -- even a probing fcntl()
    on dpkg's lock could fail a real apt run.
    """

    def __init__(self, budget=None, paths=DPKG_LOCKS, poll=PKG_LOCK_POLL_S,
                 sudo="sudo -n ", run=None, sleep=None, clock=None,
                 proc_locks="/proc/locks", stat=None):
        self.budget = _pkg_lock_budget() if budget is None else budget
        self.waited = 0.0
        # Canonical, because that is what lslocks prints in its PATH column:
        # a symlinked alias of the lock would never match it.
        self.paths = tuple(os.path.realpath(p) for p in paths)
        self.poll = poll
        self.sudo = sudo
        self._run = run or _run
        self._sleep = sleep or time.sleep
        self._clock = clock or getattr(time, "monotonic", time.time)
        self.proc_locks = proc_locks
        self._stat = stat or os.stat
        # "proc" / "lslocks" / "fuser" / "" (none) -- resolved once
        self.method = None

    def _resolve(self):
        if self.method is None:
            if self.proc_locks and os.access(self.proc_locks, os.R_OK):
                self.method = "proc"
            elif self._run("command -v lslocks >/dev/null 2>&1")[0] == 0:
                self.method = "lslocks"
            elif self._run("command -v fuser >/dev/null 2>&1 || "
                           "test -x /usr/sbin/fuser || test -x /sbin/fuser")[0] == 0:
                self.method = "fuser"
            else:
                self.method = ""
                print("PKG_LOCK_WAIT: /proc/locks is not readable and neither "
                      "lslocks nor fuser is installed - cannot tell whether "
                      "the dpkg lock is held, not waiting")
        return self.method

    def _proc_holders(self):
        """[(path, pid, command)] from /proc/locks. The kernel prints the
        device as %02x:%02x of its major:minor, and lists a blocked waiter
        right after the lock's holder on a "->" line, which is skipped. A
        lock file that does not exist cannot be held."""
        keys = {}
        for path in self.paths:
            try:
                st = self._stat(path)
            except OSError:
                continue
            keys["{:02x}:{:02x}:{}".format(os.major(st.st_dev),
                                           os.minor(st.st_dev),
                                           st.st_ino)] = path
        found = []
        if not keys:
            return found
        try:
            with open(self.proc_locks) as fh:
                lines = fh.read().splitlines()
        except (IOError, OSError):
            return found
        for line in lines:
            parts = line.split()
            if len(parts) < 3 or parts[1] == "->":
                continue
            for i in range(2, len(parts)):
                path = keys.get(parts[i])
                if path is not None:
                    found.append((path, parts[i - 1], _proc_comm(parts[i - 1])))
                    break
        return found

    def holders(self):
        """[(path, pid, command)] holding one of the watched locks now."""
        method = self._resolve()
        found = []
        if method == "proc":
            found = self._proc_holders()
        elif method == "lslocks":
            _, out = self._run("{}lslocks -n -o PID,COMMAND,PATH 2>/dev/null"
                               .format(self.sudo))
            for line in out.splitlines():
                parts = line.split()
                if len(parts) >= 3 and parts[-1] in self.paths:
                    found.append((parts[-1], parts[0], " ".join(parts[1:-1])))
        elif method == "fuser":
            for path in self.paths:
                # PIDs on stdout; the name and access letters go to stderr.
                _, out = self._run("{}fuser {} 2>/dev/null".format(self.sudo, path))
                for tok in out.split():
                    pid = tok.rstrip("cefFrm")
                    if pid.isdigit():
                        found.append((path, pid, _proc_comm(pid)))
        return found

    @staticmethod
    def describe(held):
        return "; ".join("{} held by pid {} ({})".format(path, pid, comm)
                         for path, pid, comm in held)

    def wait(self):
        """Block while a watched lock is held, within what is left of the
        budget. Returns "" once free (or when it cannot tell), else the
        holder(s) when the budget ran out -- the caller then runs dpkg anyway
        and lets it fail with its own message.

        The budget is wall-clock time spent waiting, the holder queries
        included: lslocks alone measured 0.8-0.9 s per call on a dev host,
        which counting only the sleeps would have left off the books."""
        seen = set()
        start = self.waited
        last = self._clock()
        while True:
            held = self.holders()
            now = self._clock()
            if seen:  # everything since the previous check was waiting
                self.waited += now - last
            last = now
            if not held:
                if seen:
                    print("PKG_LOCK_WAIT: dpkg lock free after {:.0f}s".format(
                        self.waited - start))
                return ""
            for path, pid, comm in held:
                if (path, pid) not in seen:
                    seen.add((path, pid))
                    print("PKG_LOCK_WAIT: {} held by pid {} ({})".format(
                        path, pid, comm))
            left = self.budget - self.waited
            if left <= 0:
                print("PKG_LOCK_WAIT: budget exhausted ({:.0f}s of {}s "
                      "SDKV_PKG_LOCK_WAIT spent in this script) - running dpkg "
                      "anyway".format(self.waited, self.budget))
                return self.describe(held)
            self._sleep(min(self.poll, left))


class VariantContext(object):
    """Resolved paths/expectations for one variant on this machine."""

    def __init__(self, variant, manifest, cache, pkg):
        entry = manifest["variants"].get(variant)
        if entry is None:
            raise RuntimeError("variant '{}' not in manifest".format(variant))
        self.variant = variant
        self.pkg = pkg
        self.flavors = entry.get("flavors", ["rpm", "deb"])
        defaults = _default_dirs(pkg)
        self.dirs = {k: entry.get(k) or defaults[k]
                     for k in ("prefix", "libdir", "includedir", "datadir")}
        self.relocated = any(entry.get(k) for k in ("prefix", "libdir",
                                                    "includedir", "datadir"))
        self.pkg_name = entry.get("pkgName", {}).get(pkg, "mstflint-sdk")
        self.renamed = self.pkg_name != "mstflint-sdk"

        self.sdk_libdir = os.path.join(self.dirs["libdir"], "mstflint", "sdk")
        self.sdk_incdir = os.path.join(self.dirs["includedir"], "mstflint", "sdk")
        self.data_path = os.path.join(self.dirs["datadir"], "mstflint", "sdk")

        vdir = os.path.join(cache, "variants", variant, _arch())
        pat = "{}-[0-9]*.rpm" if pkg == "rpm" else "{}_[0-9]*.deb"
        rc, out = _run("ls -1 {}/{} 2>/dev/null | head -1".format(
            vdir, pat.format(self.pkg_name)))
        self.pkg_file = out.strip() if rc == 0 and out.strip() else None

        rc, out = _run("ls -1 {}/{}/{} 2>/dev/null | head -1".format(
            cache, _arch(), pat.format("mstflint-sdk")))
        self.default_pkg_file = out.strip() if rc == 0 and out.strip() else None


class PackagingSuite(object):
    def __init__(self, ctx, device, sdk_only, verbose):
        self.ctx = ctx
        self.device = device
        self.sdk_only = sdk_only
        self.verbose = verbose
        self.results = OrderedDict()
        # step -> "not run: <root cause> failed", for the steps gating skipped
        self.not_run = OrderedDict()
        # runtime_smoke FAILED and the MGIR probe pinned it on the device
        # (the "device not answering" detail): the one smoke FAIL that also
        # holds cli_compare back -- see STEPS.
        self.smoke_device_dead = False
        self.harness = os.environ.get("MFT_SDK_SO_TEST_BIN", DEFAULT_HARNESS)
        self.smoke_bin = "/tmp/packaging_smoke_{}".format(os.getpid())
        # One waiter per script: SDKV_PKG_LOCK_WAIT is a budget for the run.
        self.lock = PkgLockWaiter()

    # -- result helpers -----------------------------------------------------
    def _record(self, name, status, detail=""):
        self.results[name] = status
        color = {"PASS": GREEN, "FAIL": RED, "SKIP": YELLOW}[status]
        line = "  {:28s}: {}{}{}".format(name, color, status, RESET)
        if detail:
            line += "  ({})".format(detail)
        print(line)
        return status != "FAIL"

    def _pkg_cmd(self, cmd):
        """Run one package-database mutation (`sudo rpm`/`sudo dpkg`); on DEB
        first wait out a held dpkg lock, and retry once a lock refusal that
        came right after a free wait. Returns (rc, output, lock_note):
        lock_note names the holder when dpkg ran against a held lock (budget
        spent) or failed on one, so the step's FAIL detail says who had it."""
        note = ""
        deb = self.ctx.pkg == "deb"
        if deb:
            note = self.lock.wait()
        rc, out = _run(cmd)
        if rc != 0 and deb and not note and _LOCK_ERROR_RE.search(out):
            # Taken between the wait and dpkg's own start -- apt-daily's
            # timer fires at a random time. dpkg refuses the lock before it
            # changes anything, so wait it out again and retry, once.
            note = self.lock.wait()
            rc, out = _run(cmd)
        if rc != 0 and deb and not note and _LOCK_ERROR_RE.search(out):
            # Refused again, and the waiter saw no holder: name it anyway --
            # from the waiter's probe, else from dpkg's own "... with pid N".
            note = PkgLockWaiter.describe(self.lock.holders())
            if not note:
                m = re.search(r"locked by another process with pid (\d+)", out)
                note = ("held by pid {} ({}), per dpkg".format(
                    m.group(1), _proc_comm(m.group(1))) if m
                    else "dpkg reported its lock busy, holder not identified")
        return rc, out, note

    @staticmethod
    def _with_lock(detail, note):
        return "{}; dpkg lock: {}".format(detail, note) if note else detail

    # -- steps ---------------------------------------------------------------
    def _pkg_installed(self, p):
        """Is the package installed right now?

        The dpkg status must match EXACTLY. 'Status:.*installed' also matches
        "purge ok not-installed" and "install ok half-installed", so a package
        that had only ever been purged read back as present. That was harmless
        while it only fed the leftovers report, but as the pre-erase gate it
        makes wipe() "remove" a package that is not there and then call the
        resulting no-op an erase failure. The name_only variant hits it every
        run, because coexist_or_conflict purges the default-named package just
        before restore_default.
        """
        if self.ctx.pkg == "rpm":
            return _run("rpm -q {} >/dev/null 2>&1".format(p))[0] == 0
        return _run("dpkg-query -W -f='${{Status}}' {} 2>/dev/null "
                    "| grep -q '^install ok installed$'".format(p))[0] == 0

    def wipe(self, label="clean_slate"):
        c = self.ctx
        # Erase only what is actually installed, and KEEP rc and output.
        # "not installed" is the normal case for most of SDK_PKGS and must not
        # be mistaken for an erase that was refused, so the old blanket
        # `rpm -e ... 2>/dev/null` (rc and stderr both discarded) could not
        # tell the two apart -- which is exactly why the one time it mattered
        # the logs held no evidence of why.
        erase_errors = []
        for p in SDK_PKGS:
            if not self._pkg_installed(p):
                continue
            rc, out, note = self._pkg_cmd(
                ("sudo rpm -e {}" if c.pkg == "rpm" else "sudo dpkg --purge {}")
                .format(p))
            if rc != 0 or self._pkg_installed(p):
                erase_errors.append(self._with_lock("{}: rc={} {}".format(
                    p, rc, " ".join(out.split())[:200] or "(no output)"), note))

        # A refused erase must NOT be followed by rm -rf. Deleting the files
        # while the package database still registers them leaves the host
        # half-removed: a plain reinstall is then refused as "already
        # installed" and every later SDK suite on that machine fails. Stop
        # here, while it is still recoverable, and say what rpm/dpkg actually
        # reported. (Seen on apps-132, 2026-08-12: the erase was blocked but
        # the rm -rf ran anyway and took the install dirs with it.)
        if erase_errors:
            return self._record(
                label, "FAIL",
                "package erase failed - install dirs deliberately left intact "
                "so the host stays recoverable: " + "; ".join(erase_errors))

        # The SDK's OWN subdirectory in each of these trees, never the parent:
        # /usr/lib64/mstflint, /usr/include/mstflint and /usr/share/mstflint
        # belong to the main mstflint package (its binaries' register database
        # lives in /usr/share/mstflint/prm_dbs), which this suite neither
        # installs nor erases. Deleting the parent took the CLI reference's
        # database with it and left mstreg/mstlink broken for every later
        # compare on that machine.
        # In the libdir not even that: <libdir>/mstflint/sdk also holds the
        # CLI package's libresource_dump_sdk.so, so name the SDK's own files.
        dirs = []
        files = []
        for flavor_defaults in (_default_dirs("rpm"), _default_dirs("deb")):
            sdkdir = os.path.join(flavor_defaults["libdir"], "mstflint", "sdk")
            # libmft_sdk.so.1 is no longer created; keep removing it so the
            # stale alias earlier runs left behind is cleared.
            files += [os.path.join(sdkdir, "libmstflint_sdk.so"),
                      os.path.join(sdkdir, "libmft_sdk.so.1"),
                      os.path.join(flavor_defaults["libdir"], "pkgconfig",
                                   "mstflint_sdk.pc")]
        dirs += ["/usr/include/mstflint/sdk", "/usr/share/mstflint/sdk",
                 c.dirs["prefix"] if c.relocated else None]
        dirs = [d for d in dirs if d and d != "/usr"]
        _run("sudo rm -f " + " ".join(files))
        _run("sudo rm -rf " + " ".join(dirs))
        _ldconfig()

        leftovers = [d for d in dirs if os.path.exists(d)]
        pkgs_left = [p for p in SDK_PKGS if self._pkg_installed(p)]
        if leftovers or pkgs_left:
            return self._record(label, "FAIL",
                                "leftovers: {} {}".format(leftovers, pkgs_left))
        return self._record(label, "PASS")

    def install_variant(self):
        c = self.ctx
        if not c.pkg_file:
            return self._record("install", "FAIL",
                                "variant package not in cache — run Build & Run once")
        rc, out, note = self._pkg_cmd(
            ("sudo rpm -Uvh --nodeps {}" if c.pkg == "rpm" else "sudo dpkg -i {}")
            .format(c.pkg_file))
        if rc != 0:
            # The last line, except for a lock refusal: dpkg ends that with
            # two lines of boilerplate ("... See <https://wiki.debian.org/
            # Teams/Dpkg/FAQ>.", apps-102-bf 2026-10-07); the error is the
            # line naming the lock.
            lines = out.strip().splitlines() or ["(no output)"]
            last = next((l for l in lines if _LOCK_ERROR_RE.search(l)),
                        lines[-1])[:120]
            return self._record("install", "FAIL", self._with_lock(last, note))
        _ldconfig()
        return self._record("install", "PASS", os.path.basename(c.pkg_file))

    def check_identity(self):
        c = self.ctx
        if c.pkg == "rpm":
            ok = _run("rpm -q {}".format(c.pkg_name))[0] == 0
            other = "mstflint-sdk" if c.renamed else "sdkv-mstflint-sdk"
            ok = ok and _run("rpm -q {}".format(other))[0] != 0
        else:
            ok = _run("dpkg -s {} 2>/dev/null | grep -q 'Status:.*installed'".format(
                c.pkg_name))[0] == 0
        return self._record("package_identity", "PASS" if ok else "FAIL", c.pkg_name)

    def check_layout(self):
        c = self.ctx
        expect = [
            os.path.join(c.sdk_libdir, "libmstflint_sdk.so"),
            os.path.join(c.sdk_incdir, "mft_sdk", "mft_sdk.h"),
            os.path.join(c.data_path, "prm_dbs", "hca", "ext",
                         "register_access_table.adb"),
            os.path.join(c.dirs["libdir"], "pkgconfig", "mstflint_sdk.pc"),
        ]
        missing = [p for p in expect if not os.path.exists(p)]
        if missing:
            return self._record("install_layout", "FAIL", "missing: " + missing[0])
        # .pc values may be absolute (RPM flavor) or ${prefix}-relative (DEB
        # flavor) — expand pkg-config variables before comparing.
        pc_vars = {}
        for line in open(expect[3]).read().splitlines():
            if "=" in line and not line.lstrip().startswith("#"):
                k, _, v = line.partition("=")
                for var, val in pc_vars.items():
                    v = v.replace("${%s}" % var, val)
                pc_vars[k.strip()] = v.strip()
        if pc_vars.get("libdir") != c.sdk_libdir or \
           pc_vars.get("includedir") != c.sdk_incdir:
            return self._record(
                "install_layout", "FAIL",
                ".pc dirs wrong: libdir={} includedir={}".format(
                    pc_vars.get("libdir"), pc_vars.get("includedir")))
        return self._record("install_layout", "PASS")

    def check_no_default_paths(self):
        c = self.ctx
        if not c.relocated:
            return self._record("no_default_paths", "SKIP",
                                "variant installs to default paths")
        d = _default_dirs(c.pkg)
        # Name exact SDK files: /usr/{lib64,include,share}/mstflint belong to the
        # main mstflint package, and even .../mstflint/sdk is shared -- the CLI
        # rpm ships libresource_dump_sdk.so there.
        bad = [p for p in (os.path.join(d["libdir"], "mstflint", "sdk",
                                        "libmstflint_sdk.so"),
                           os.path.join(d["includedir"], "mstflint", "sdk", "mft_sdk"),
                           os.path.join(d["datadir"], "mstflint", "sdk", "prm_dbs"),
                           os.path.join(d["libdir"], "pkgconfig", "mstflint_sdk.pc"))
               if os.path.exists(p)]
        return self._record("no_default_paths", "PASS" if not bad else "FAIL",
                            ", ".join(bad))

    def check_data_path(self):
        """The compiled-in PRM db root must equal the variant datadir."""
        c = self.ctx
        so = os.path.join(c.sdk_libdir, "libmstflint_sdk.so")
        want = (c.data_path + "/").encode()
        try:
            with open(so, "rb") as f:
                found = want in f.read()
        except IOError as e:
            return self._record("data_path_consistency", "FAIL", str(e))
        return self._record("data_path_consistency", "PASS" if found else "FAIL",
                            c.data_path)

    def compile_smoke(self):
        c = self.ctx
        src = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                           "packaging_smoke.c")
        cmd = ("gcc -O2 -o {out} {src} -I{inc} -L{lib} -lmstflint_sdk "
               "-Wl,-rpath,{lib} -Wl,--allow-shlib-undefined").format(
            out=self.smoke_bin, src=src, inc=c.sdk_incdir, lib=c.sdk_libdir)
        rc, out = _run(cmd, "compile smoke client", self.verbose)
        if rc != 0:
            return self._record("compile_smoke", "FAIL",
                                out.strip().splitlines()[-1][:120])
        return self._record("compile_smoke", "PASS")

    def runtime_smoke(self):
        if not self.device:
            return self._record("runtime_smoke", "SKIP", "no device")
        if not os.path.exists(self.smoke_bin):
            return self._record("runtime_smoke", "SKIP", "compile_smoke failed")
        rc, out = _run("sudo {} {}".format(self.smoke_bin, self.device),
                       timeout=120)
        detail = out.strip().splitlines()[-1][:120] if out.strip() else ""
        if rc != 0:
            # The variant SDK, or a device that answers nothing? Ask the
            # device for MGIR through the CLI oracle, a package this suite
            # never wipes. If it cannot read MGIR either, this FAIL is device
            # state and says so: on 2026-10-07 apps-127 failed all three
            # variants with "mstSendPRMRegister(MGIR, GET) failed, status=11",
            # each reported as an unclassified SDK failure.
            dead, why = device_not_answering(
                None if self.sdk_only else self.device, [detail])
            if dead:
                self.smoke_device_dead = True
                announce_device_not_answering(self.device, why)
                detail = "{} - smoke: {}".format(
                    device_not_answering_detail(why), detail)
        return self._record("runtime_smoke", "PASS" if rc == 0 else "FAIL", detail)

    def harness_gtest(self):
        c = self.ctx
        if not os.path.exists(self.harness):
            return self._record("harness_discovery", "FAIL",
                                self.harness + " missing — run: "
                                "make -C mft_sdk/unit_tests unified")
        # WRONGLIB gate first: whichever SDK library the harness links must
        # resolve into the VARIANT libdir — otherwise we would be testing some
        # other lib. Keep "no SDK library in the ldd output" distinct from
        # "resolves elsewhere", or a soname mismatch reports an empty detail.
        rc, out = _run("env LD_LIBRARY_PATH={} ldd {} 2>/dev/null"
                       .format(c.sdk_libdir, self.harness))
        sdk_lines = [l.strip() for l in out.splitlines() if SDK_SONAME in l]
        if not sdk_lines:
            return self._record("harness_discovery", "FAIL",
                                "harness links no SDK library ({}): ldd said {}".format(
                                    SDK_SONAME,
                                    out.strip().replace("\n", " ")[:100] or "nothing"))
        stray = [l for l in sdk_lines if c.sdk_libdir not in l]
        if stray:
            return self._record("harness_discovery", "FAIL",
                                "SDK library resolves outside variant libdir {}: {}".format(
                                    c.sdk_libdir, "; ".join(stray)[:120]))
        dev = " -d " + self.device if self.device else ""
        rc, out = _run('sudo env LD_LIBRARY_PATH={} {} --gtest_filter="MftSdkDiscovery*{}"{}'
                       .format(c.sdk_libdir, self.harness, GTEST_EXCLUSIONS, dev),
                       timeout=300)
        passed = rc == 0 and "[  FAILED  ]" not in out
        tail = [l for l in out.splitlines() if "PASSED" in l or "FAILED" in l]
        return self._record("harness_discovery", "PASS" if passed else "FAIL",
                            tail[-1].strip() if tail else "rc={}".format(rc))

    def cli_compare(self):
        """Functional equivalence: mlxreg register-access compare, SDK (from
        the variant install) vs the reference CLI — reuses the sibling suite.

        The gate must ask about the SAME tool the sibling suite will run, i.e.
        MFT_SDK_REG_TOOL (mlxreg_ext by default, mstreg for the mstflint SDK).
        Probing mlxreg_ext unconditionally would skip this test on a machine
        that has only mstreg, and run it on one that has only mlxreg_ext while
        the child then fails to find its actual oracle.

        Either oracle comes from a package this suite does not touch (MFT's
        mft, or mstflint's own CLI package), so the variant install/wipe
        cannot move it and the configured path is used as-is.
        """
        if self.sdk_only:
            return self._record("cli_compare", "SKIP", "--sdk-only mode")
        if not self.device:
            return self._record("cli_compare", "SKIP", "no device")
        reg_tool = MFT_SDK_REG_TOOL
        if _run("command -v {}".format(reg_tool))[0] != 0:
            return self._record("cli_compare", "SKIP",
                                "{} (CLI reference) not installed".format(reg_tool))
        script = os.path.join(os.path.dirname(os.path.dirname(
            os.path.abspath(__file__))), "mlxreg", "test_register_access.py")
        # os.environ.copy(): MFT_SDK_REG_TOOL (and MFT_SDK_LINK_TOOL) reach the
        # child, so the sibling suite compares against the same oracle.
        env = os.environ.copy()
        env["MFT_SDK_SO_DIR"] = self.ctx.sdk_libdir
        env["MFT_SDK_SO_TEST_BIN"] = self.harness
        env["MFT_SDK_REG_TOOL"] = reg_tool
        try:
            p = subprocess.Popen(
                [sys.executable, script, "--compare", "-d", self.device, "--so"],
                stdout=subprocess.PIPE, stderr=subprocess.STDOUT, env=env)
            out, _ = p.communicate(timeout=600)
            rc, out = p.returncode, out.decode("utf-8", errors="replace")
        except Exception as e:  # noqa: BLE001
            rc, out = 1, str(e)
        if self.verbose:
            # Minus the child's DEVICE NOT ANSWERING line: it is announced
            # again below as this script's own, and the contract is one such
            # line per device per script.
            print(re.sub(r"(?m)^DEVICE NOT ANSWERING: [^\n]*\n?", "", out))
        ok = rc == 0 and "ALL TESTS PASSED" in out
        detail = "register_access vs {}, rc={}".format(reg_tool, rc)
        # The child's own verdict on a device that did not answer -- its
        # output is not printed here, so carry the marker up.
        m = re.search(r"^DEVICE NOT ANSWERING: \S+: (.*)$", strip_ansi(out), re.M)
        if not ok and m:
            announce_device_not_answering(self.device, m.group(1).strip())
            detail = "{} - {}".format(
                device_not_answering_detail(m.group(1).strip()), detail)
        return self._record("cli_compare", "PASS" if ok else "FAIL", detail)

    def coexist_or_conflict(self):
        """Rename semantics vs the default package.

        renamed+relocated (both):   coexists — no shared identity, no shared files
        renamed only (name_only):   MUST file-conflict — same files, new identity
        relocated only (paths_only): same identity — nothing to coexist with (SKIP)
        """
        c = self.ctx
        if not c.renamed:
            return self._record("coexist_or_conflict", "SKIP",
                                "same package identity as default")
        if not c.default_pkg_file:
            return self._record("coexist_or_conflict", "SKIP",
                                "default package not in cache")
        erase_default = ("sudo rpm -e mstflint-sdk 2>/dev/null" if c.pkg == "rpm"
                         else "sudo dpkg --purge mstflint-sdk 2>/dev/null")
        rc, out, note = self._pkg_cmd(
            ("sudo rpm -Uvh --nodeps {}" if c.pkg == "rpm" else "sudo dpkg -i {}")
            .format(c.default_pkg_file))
        if c.relocated:
            both = (_run("rpm -q mstflint-sdk")[0] == 0 if c.pkg == "rpm"
                    else _run("dpkg -s mstflint-sdk 2>/dev/null | grep -q installed")[0] == 0)
            ok = rc == 0 and both
            self._pkg_cmd(erase_default)
            return self._record("coexist_or_conflict", "PASS" if ok else "FAIL",
                                self._with_lock("renamed+relocated coexists with default",
                                                "" if ok else note))
        # renamed at default paths: the install MUST be refused on file conflicts
        conflicted = rc != 0 and ("conflicts" in out or "trying to overwrite" in out)
        if rc == 0:  # unexpectedly installed — undo to keep the variant state
            self._pkg_cmd(erase_default)
        return self._record("coexist_or_conflict", "PASS" if conflicted else "FAIL",
                            "default-package install correctly refused (file conflict)"
                            if conflicted else self._with_lock(
                                "expected a file conflict, rc={}".format(rc), note))

    def restore_default(self):
        """Leave the machine as the rest of the flow expects: default package
        installed at default paths + standard compat symlink."""
        c = self.ctx
        self.wipe(label="cleanup_wipe")
        if not c.default_pkg_file:
            return self._record("restore_default", "SKIP",
                                "default package not in cache")
        # --replacepkgs/--force-confnew so this can still heal a host whose
        # package database claims the package is present while its files are
        # gone; without it rpm refuses with "already installed" and the machine
        # stays broken for every later suite.
        rc, out, note = self._pkg_cmd(
            ("sudo rpm -Uvh --replacepkgs --nodeps {}" if c.pkg == "rpm"
             else "sudo dpkg -i --force-confnew {}").format(c.default_pkg_file))
        d = os.path.join(_default_dirs(c.pkg)["libdir"], "mstflint", "sdk")
        _ldconfig()
        so = os.path.join(d, "libmstflint_sdk.so")
        ok = rc == 0 and os.path.exists(so)
        # Always carry a detail: a bare FAIL here reads as an unexplained
        # assertion when it is nearly always a cascade from the wipe above.
        return self._record(
            "restore_default", "PASS" if ok else "FAIL",
            "{} reinstalled at {}".format(os.path.basename(c.default_pkg_file), d) if ok
            else self._with_lock(
                "reinstall rc={}, {} {} - host may need manual repair: {}".format(
                    rc, so, "missing" if not os.path.exists(so) else "present",
                    " ".join(out.split())[:200] or "(no output)"), note))

    # -- driver ---------------------------------------------------------------
    # (row, method, prerequisites). A step runs only when every prerequisite
    # ran and did not FAIL; otherwise it still gets its row -- "SKIP (not run:
    # <root cause> failed)" in the step lines AND the summary block. This was
    # a bare `break` on the first FAIL: when runtime_smoke failed on apps-127
    # (2026-10-07), harness_discovery, cli_compare and coexist_or_conflict
    # left no row at all (30 rows instead of 39 over the three variants),
    # though two of them need no register access. A trailing '?' marks the one
    # SOFT edge: cli_compare -> runtime_smoke stands for "the device answers
    # register access", which only a smoke FAIL that the MGIR probe pinned on
    # the device disproves (smoke_device_dead). A smoke that never ran
    # (compile_smoke failed) proved nothing, and cli_compare brings its own
    # harness; a smoke that failed on a device that answers points at the
    # variant SDK, which is exactly when cli_compare's own evidence counts.
    # cleanup_wipe and restore_default are not steps: restore_default always
    # runs.
    STEPS = (
        ("clean_slate", "wipe", ()),
        ("install", "install_variant", ("clean_slate",)),
        ("package_identity", "check_identity", ("install",)),
        ("install_layout", "check_layout", ("install",)),
        ("no_default_paths", "check_no_default_paths", ("install",)),
        ("data_path_consistency", "check_data_path", ("install",)),
        ("compile_smoke", "compile_smoke", ("install",)),
        ("runtime_smoke", "runtime_smoke", ("compile_smoke",)),
        ("harness_discovery", "harness_gtest", ("install",)),
        ("cli_compare", "cli_compare", ("install", "runtime_smoke?")),
        ("coexist_or_conflict", "coexist_or_conflict", ("install",)),
    )
    # What a prerequisite stands for, named in the not-run reason.
    PREREQ_MEANS = {"runtime_smoke": "device register access"}

    def _blocker(self, needs):
        """The not-run reason for a step with these prerequisites, or None.
        A prerequisite that did not run passes on ITS root cause."""
        for need in needs:
            soft = need.endswith("?")
            need = need.rstrip("?")
            if need in self.not_run:
                if soft:
                    continue
                return self.not_run[need]
            if self.results.get(need) == "FAIL":
                if soft and not self.smoke_device_dead:
                    continue
                means = self.PREREQ_MEANS.get(need)
                return "not run: {} failed{}".format(
                    need, " ({})".format(means) if means else "")
        return None

    def _guarded(self, name, step):
        """Run one step; an exception is that step's FAIL, not the end of
        the variant and of every row after it."""
        try:
            step()
        except Exception as e:  # noqa: BLE001
            self._record(name, "FAIL", "raised {}: {}".format(
                type(e).__name__, " ".join(str(e).split())[:160]))

    def run(self):
        c = self.ctx
        print("\n" + "=" * 70)
        print("PACKAGING VARIANT [{} - {} {}] pkg={} dirs={}".format(
            c.variant, c.pkg, _arch(), c.pkg_name, c.dirs))
        print("=" * 70)
        if c.pkg not in c.flavors:
            self._record("variant_supported", "SKIP",
                         "build_sdk.sh has no per-dir customization on the {} path"
                         .format(c.pkg))
            self._summary()
            return 0
        try:
            for name, method, needs in self.STEPS:
                reason = self._blocker(needs)
                if reason:
                    self.not_run[name] = reason
                    self._record(name, "SKIP", reason)
                    continue
                self._guarded(name, getattr(self, method))
        finally:
            self._guarded("restore_default", self.restore_default)
            _run("rm -f {}".format(self.smoke_bin))
        self._summary()
        return 0 if all(s != "FAIL" for s in self.results.values()) else 1

    def _summary(self):
        title = "PACKAGING TEST SUMMARY ({})".format(self.ctx.variant)
        print("\n" + "=" * 60 + "\n" + title + "\n" + "=" * 60)
        for name, status in self.results.items():
            reason = self.not_run.get(name)
            print("  {}: {}{}".format(
                name, status, " ({})".format(reason) if reason else ""))
        failed = [n for n, s in self.results.items() if s == "FAIL"]
        print("=" * 60 + "\nOverall: " + (
            "ALL TESTS PASSED" if not failed else "SOME TESTS FAILED") +
            "\n" + "=" * 60)


def print_usage():
    print(__doc__)


def main():
    variant = None
    device = None
    sdk_only = False
    verbose = False
    so_mode = False
    args = sys.argv[1:]
    i = 0
    while i < len(args):
        a = args[i]
        if a in ("--help", "-h"):
            print_usage()
            return 0
        elif a == "--variant":
            i += 1
            variant = args[i] if i < len(args) else None
        elif a == "-d":
            i += 1
            device = _normalize_bdf(args[i]) if i < len(args) else None
        elif a in ("--compare", "--compare-all"):
            pass  # device selection handled via -d / auto-discovery
        elif a == "--so":
            so_mode = True
        elif a == "--sdk-only":
            sdk_only = True
        elif a == "--verbose":
            verbose = True
        elif a == "--coverage":
            pass  # no instrumented binaries in this suite
        elif a == "--build":
            print("{}[ERROR] packaging tests only support --so (installed packages){}"
                  .format(RED, RESET))
            return 1
        else:
            print("{}[ERROR] unknown argument: {}{}".format(RED, a, RESET))
            return 1
        i += 1

    if variant not in VARIANTS:
        print("{}[ERROR] --variant must be one of {}{}".format(RED, VARIANTS, RESET))
        return 1
    if not so_mode:
        print("{}[ERROR] packaging tests require --so (they test installed packages){}"
              .format(RED, RESET))
        return 1

    cache = os.environ.get("MSTFLINT_PKG_CACHE")
    if not cache:
        print("{}[ERROR] MSTFLINT_PKG_CACHE env var is required "
              "(package cache root holding variants/manifest.json){}"
              .format(RED, RESET))
        return 1
    manifest_path = os.path.join(cache, "variants", "manifest.json")
    if not os.path.isfile(manifest_path):
        print("{}[ERROR] variants manifest not found: {} — run Build & Run once{}"
              .format(RED, manifest_path, RESET))
        return 1
    with open(manifest_path) as f:
        manifest = json.load(f)

    if device is None:
        devs = _get_pci_devices_lspci()
        if devs:
            device = devs[0].pci
            print("[INFO] auto-selected device: {}".format(device))
        else:
            print("{}[WARN] no Mellanox device found — device steps will SKIP{}"
                  .format(YELLOW, RESET))

    ctx = VariantContext(variant, manifest, cache, _pkg_type())
    return PackagingSuite(ctx, device, sdk_only, verbose).run()


if __name__ == "__main__":
    sys.exit(main())
