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
(utils.py); this test points both at the VARIANT's dirs, creates the
libmft_sdk.so.1 compat symlink inside the variant libdir, and asserts the
DEFAULT paths are absent — so nothing can silently fall back to a stale copy.
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
    MFT_SDK_SO_TEST_BIN    installed gtest harness binary (default:
                           /usr/lib64/mft_sdk/tests/mft_sdk_mstflint_so_test)
"""

from __future__ import print_function
import json
import os
import platform
import subprocess
import sys
from collections import OrderedDict

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from utils import (  # noqa: E402
    RED, GREEN, BLUE, RESET,
    CommandRunner,
    _get_pci_devices_lspci, _normalize_bdf,
)

YELLOW = "\033[93m"

DEFAULT_HARNESS = "/usr/lib64/mft_sdk/tests/mft_sdk_mstflint_so_test"
GTEST_EXCLUSIONS = "-*I2c*:*NullDeviceToAllApis*:*TelemetryJson*:*FreeJsonString*"

# Every package identity this suite may install or must clean away. The wipe
# below removes exactly these + the SDK install dirs; it deliberately does NOT
# touch the MFT CLI tools (mlxreg_ext — the compare reference) nor the seeded
# harness binary under /usr/lib64/mft_sdk/tests (unowned file, survives rpm -e).
SDK_PKGS = ["mft-sdk-int", "mft-sdk", "mstflint-sdk", "sdkv-mstflint-sdk"]

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
        self.harness = os.environ.get("MFT_SDK_SO_TEST_BIN", DEFAULT_HARNESS)
        self.smoke_bin = "/tmp/packaging_smoke_{}".format(os.getpid())

    # -- result helpers -----------------------------------------------------
    def _record(self, name, status, detail=""):
        self.results[name] = status
        color = {"PASS": GREEN, "FAIL": RED, "SKIP": YELLOW}[status]
        line = "  {:28s}: {}{}{}".format(name, color, status, RESET)
        if detail:
            line += "  ({})".format(detail)
        print(line)
        return status != "FAIL"

    # -- steps ---------------------------------------------------------------
    def wipe(self, label="clean_slate"):
        c = self.ctx
        for p in SDK_PKGS:
            if c.pkg == "rpm":
                _run("sudo rpm -e {} 2>/dev/null".format(p))
            else:
                _run("sudo dpkg --purge {} 2>/dev/null".format(p))
        dirs = []
        for flavor_defaults in (_default_dirs("rpm"), _default_dirs("deb")):
            dirs += [os.path.join(flavor_defaults["libdir"], "mstflint")]
        dirs += ["/usr/include/mstflint", "/usr/share/mstflint",
                 "/usr/include/mft_sdk", "/usr/share/mft_sdk", "/etc/mft_sdk",
                 c.dirs["prefix"] if c.relocated else None]
        dirs = [d for d in dirs if d and d != "/usr"]
        _run("sudo rm -rf " + " ".join(dirs))
        _ldconfig()

        leftovers = [d for d in dirs if os.path.exists(d)]
        pkgs_left = []
        for p in SDK_PKGS:
            probe = "rpm -q {}".format(p) if c.pkg == "rpm" \
                else "dpkg -s {} 2>/dev/null | grep -q 'Status:.*installed'".format(p)
            if _run(probe)[0] == 0:
                pkgs_left.append(p)
        if leftovers or pkgs_left:
            return self._record(label, "FAIL",
                                "leftovers: {} {}".format(leftovers, pkgs_left))
        return self._record(label, "PASS")

    def install_variant(self):
        c = self.ctx
        if not c.pkg_file:
            return self._record("install", "FAIL",
                                "variant package not in cache — run Build & Run once")
        if c.pkg == "rpm":
            rc, out = _run("sudo rpm -Uvh --nodeps {}".format(c.pkg_file))
        else:
            rc, out = _run("sudo dpkg -i {}".format(c.pkg_file))
        if rc != 0:
            return self._record("install", "FAIL", out.strip().splitlines()[-1][:120])
        # compat symlink INSIDE the variant libdir so the harness's NEEDED
        # libmft_sdk.so.1 resolves there (and only there) via LD_LIBRARY_PATH
        _run("sudo ln -sf {0}/libmstflint_sdk.so {0}/libmft_sdk.so.1".format(c.sdk_libdir))
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
        defaults = _default_dirs(c.pkg)
        bad = [p for p in (os.path.join(defaults["libdir"], "mstflint"),
                           "/usr/include/mstflint", "/usr/share/mstflint")
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
        return self._record("runtime_smoke", "PASS" if rc == 0 else "FAIL", detail)

    def harness_gtest(self):
        c = self.ctx
        if not os.path.exists(self.harness):
            return self._record("harness_discovery", "SKIP",
                                self.harness + " missing — run Build & Run")
        # WRONGLIB gate first: the harness must resolve libmft_sdk.so.1 into
        # the VARIANT libdir — otherwise we would be testing some other lib.
        rc, out = _run("env LD_LIBRARY_PATH={} ldd {} 2>/dev/null | grep libmft_sdk.so.1"
                       .format(c.sdk_libdir, self.harness))
        if c.sdk_libdir not in out:
            return self._record("harness_discovery", "FAIL",
                                "libmft_sdk.so.1 resolves outside variant libdir: " +
                                out.strip()[:100])
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
        the variant install) vs the MFT CLI — reuses the sibling suite."""
        if self.sdk_only:
            return self._record("cli_compare", "SKIP", "--sdk-only mode")
        if not self.device:
            return self._record("cli_compare", "SKIP", "no device")
        if _run("command -v mlxreg_ext")[0] != 0:
            return self._record("cli_compare", "SKIP",
                                "mlxreg_ext (MFT CLI reference) not installed")
        script = os.path.join(os.path.dirname(os.path.dirname(
            os.path.abspath(__file__))), "mlxreg", "test_register_access.py")
        env = os.environ.copy()
        env["MFT_SDK_SO_DIR"] = self.ctx.sdk_libdir
        env["MFT_SDK_SO_TEST_BIN"] = self.harness
        try:
            p = subprocess.Popen(
                [sys.executable, script, "--compare", "-d", self.device, "--so"],
                stdout=subprocess.PIPE, stderr=subprocess.STDOUT, env=env)
            out, _ = p.communicate(timeout=600)
            rc, out = p.returncode, out.decode("utf-8", errors="replace")
        except Exception as e:  # noqa: BLE001
            rc, out = 1, str(e)
        if self.verbose:
            print(out)
        ok = rc == 0 and "ALL TESTS PASSED" in out
        return self._record("cli_compare", "PASS" if ok else "FAIL",
                            "register_access vs mlxreg_ext, rc={}".format(rc))

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
        if c.pkg == "rpm":
            rc, out = _run("sudo rpm -Uvh --nodeps {}".format(c.default_pkg_file))
        else:
            rc, out = _run("sudo dpkg -i {}".format(c.default_pkg_file))
        if c.relocated:
            both = (_run("rpm -q mstflint-sdk")[0] == 0 if c.pkg == "rpm"
                    else _run("dpkg -s mstflint-sdk 2>/dev/null | grep -q installed")[0] == 0)
            ok = rc == 0 and both
            if c.pkg == "rpm":
                _run("sudo rpm -e mstflint-sdk 2>/dev/null")
            else:
                _run("sudo dpkg --purge mstflint-sdk 2>/dev/null")
            return self._record("coexist_or_conflict", "PASS" if ok else "FAIL",
                                "renamed+relocated coexists with default")
        # renamed at default paths: the install MUST be refused on file conflicts
        conflicted = rc != 0 and ("conflicts" in out or "trying to overwrite" in out)
        if rc == 0:  # unexpectedly installed — undo to keep the variant state
            if c.pkg == "rpm":
                _run("sudo rpm -e mstflint-sdk 2>/dev/null")
            else:
                _run("sudo dpkg --purge mstflint-sdk 2>/dev/null")
        return self._record("coexist_or_conflict", "PASS" if conflicted else "FAIL",
                            "default-package install correctly refused (file conflict)"
                            if conflicted else "expected a file conflict, rc={}".format(rc))

    def restore_default(self):
        """Leave the machine as the rest of the flow expects: default package
        installed at default paths + standard compat symlink."""
        c = self.ctx
        self.wipe(label="cleanup_wipe")
        if not c.default_pkg_file:
            return self._record("restore_default", "SKIP",
                                "default package not in cache")
        if c.pkg == "rpm":
            rc, out = _run("sudo rpm -Uvh --nodeps {}".format(c.default_pkg_file))
        else:
            rc, out = _run("sudo dpkg -i {}".format(c.default_pkg_file))
        d = os.path.join(_default_dirs(c.pkg)["libdir"], "mstflint", "sdk")
        _run("sudo ln -sf {0}/libmstflint_sdk.so {0}/libmft_sdk.so.1".format(d))
        _ldconfig()
        ok = rc == 0 and os.path.exists(os.path.join(d, "libmstflint_sdk.so"))
        return self._record("restore_default", "PASS" if ok else "FAIL")

    # -- driver ---------------------------------------------------------------
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
            steps = [self.wipe, self.install_variant, self.check_identity,
                     self.check_layout, self.check_no_default_paths,
                     self.check_data_path, self.compile_smoke,
                     self.runtime_smoke, self.harness_gtest,
                     self.cli_compare, self.coexist_or_conflict]
            for step in steps:
                if not step():
                    break  # a FAIL aborts the variant; restore still runs
        finally:
            self.restore_default()
            _run("rm -f {}".format(self.smoke_bin))
        self._summary()
        return 0 if all(s != "FAIL" for s in self.results.values()) else 1

    def _summary(self):
        title = "PACKAGING TEST SUMMARY ({})".format(self.ctx.variant)
        print("\n" + "=" * 60 + "\n" + title + "\n" + "=" * 60)
        for name, status in self.results.items():
            print("  {}: {}".format(name, status))
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
