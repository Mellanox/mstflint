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
Packaging test for the mstflint SDK ldconfig registration (mstflint PR #1855).

libmstflint_sdk.so is installed into a PRIVATE directory ($(libdir)/mstflint/sdk)
that no dynamic linker searches by default, so a consumer linking it by soname
alone -- DOCA's libdoca_mgmt does -- died with "libmstflint_sdk.so => not found".
PR #1855 fixes that by shipping an /etc/ld.so.conf.d snippet naming the private
directory and running ldconfig from the packaging scriptlets.

The failure this suite exists to catch is silent: everything still builds,
installs and passes every other suite when the snippet is missing, wrong, or
points somewhere ldconfig never reads. Only a consumer that links by soname
without an rpath notices -- which is why the last check is exactly that consumer.

Six groups, cheapest first. Groups A-D need only the source tree (offline: no
device, no sudo, no installed package). Groups E-F read the INSTALLED package and
self-SKIP with a precise reason when there is none, so the suite is still useful
on a build host:

  A  build_sdk.sh    --ldsoconfdir/--no-ldsoconf are documented, and map onto
                     --with-ldsoconfdir=DIR / --without-ldsoconfdir (real
                     build_sdk.sh, stub autogen.sh/configure/make: ~1s versus
                     minutes for a real configure)
  B  configure.ac    the AC_ARG_WITH block extracted VERBATIM into a micro
                     configure.ac, autoconf'd, and driven over the argument
                     matrix -- including the trap the block was written for: the
                     snippet dir must NOT follow --prefix/--sysconfdir, because
                     ldconfig only ever reads the real /etc
  C  Makefile.am     the install-data-local/uninstall-local recipe extracted
                     VERBATIM and run by make into a DESTDIR, including the
                     `ldsoconffile=` override the RPM and DEB packaging use to
                     name the snippet after a renamed package
  D  packaging       spec %post/%postun ldconfig + %config(noreplace), and the
                     debian rules/triggers pair (unprefixed `triggers`, so a
                     --deb-name build keeps it)
  E  installed pkg   the package owns the snippet, marks it config, carries the
                     ldconfig hook, and the snippet names the real private
                     libdir -- which must not already be on the default path,
                     or the snippet proves nothing
  F  the consumer    compile a client, link -lmstflint_sdk with NO rpath and NO
                     LD_LIBRARY_PATH, and run it. This is the libdoca_mgmt case
                     and the only check that fails the way the bug failed.

Usage:
    ./test_ldconfig.py --so
    ./test_ldconfig.py --so --keep --workdir /data/tmp/ldsoconf
    ./test_ldconfig.py --help

Env:
    SDKV_TMP_ROOT   scratch root (default: /data/tmp)
    MFT_SDK_SO_DIR  installed SDK library dir; probed when unset
"""

from __future__ import print_function
import os
import re
import shutil
import socket
import subprocess
import sys
from collections import OrderedDict

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from utils import (  # noqa: E402
    RED, GREEN, BLUE, RESET,
)

YELLOW = "\033[93m"

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.dirname(os.path.abspath(__file__)))))
BUILD_SDK = os.path.join(REPO_ROOT, "build_sdk.sh")
CONFIGURE_AC = os.path.join(REPO_ROOT, "configure.ac")
SDK_MAKEFILE_AM = os.path.join(REPO_ROOT, "mft_sdk", "Makefile.am")
SDK_SPEC_IN = os.path.join(REPO_ROOT, "mstflint-sdk.spec.in")
DEBIAN_SDK = os.path.join(REPO_ROOT, "debian-sdk")

# The snippet directory the feature is specified against. Hardcoded on purpose:
# a test that reads the value out of configure.ac would agree with any change to
# it, including one that breaks ldconfig.
LDSOCONFDIR_DEFAULT = "/etc/ld.so.conf.d"
SONAME = "libmstflint_sdk.so"

# Directories the dynamic linker searches with no configuration at all. The
# whole feature is a no-op if the SDK libdir is one of these, so group E asserts
# it is not. Triplet dirs are the Debian/Ubuntu default set.
DEFAULT_LD_DIRS = frozenset([
    "/lib", "/lib64", "/usr/lib", "/usr/lib64",
    "/lib/x86_64-linux-gnu", "/usr/lib/x86_64-linux-gnu",
    "/lib/aarch64-linux-gnu", "/usr/lib/aarch64-linux-gnu",
])

# Where an installed SDK can be, in probe order. MFT_SDK_SO_DIR (set by the
# SDK-Verify extension) wins when it names a real directory.
SDK_LIBDIR_CANDIDATES = [
    "/usr/lib64/mstflint/sdk",
    "/usr/lib/x86_64-linux-gnu/mstflint/sdk",
    "/usr/lib/aarch64-linux-gnu/mstflint/sdk",
    "/usr/local/lib/mstflint/sdk",
]

# Binds a real symbol so --as-needed keeps the DT_NEEDED entry, and never calls
# into the SDK: this client exists to prove the loader can FIND the library by
# soname, not to exercise any API. Inline rather than a .c file next to
# packaging_smoke.c -- that one needs a device and sudo, this one must not.
LDSO_CLIENT_C = """\
#include <stdio.h>
#include <mft_sdk/mft_sdk.h>

void* const sdk_symbol = (void*)&mstGetLastErrorString;

int main(void)
{
    printf("resolved %p\\n", sdk_symbol);
    return sdk_symbol ? 0 : 1;
}
"""


def _run(cmd, desc="", verbose=False, cwd=None, env=None):
    """Run a shell command; return (rc, output). Never raises."""
    if verbose and desc:
        print("{}[CMD]{} {}".format(BLUE, RESET, cmd))
    try:
        p = subprocess.Popen(cmd, shell=True, cwd=cwd, env=env,
                             stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out = p.communicate()[0]
        return p.returncode, out.decode("utf-8", errors="replace")
    except Exception as e:  # noqa: BLE001 - a broken command is a test FAIL, not a crash
        return 1, str(e)


def _have(tool):
    return _run("command -v {} >/dev/null 2>&1".format(tool))[0] == 0


def _ldconfig():
    """ldconfig's path. On Debian/Ubuntu it is /usr/sbin/ldconfig, which is not
    on a non-root user's PATH -- a bare `ldconfig -p` there exits 127 and would
    be reported as "the snippet was not applied" on every DEB machine."""
    for c in ("ldconfig", "/sbin/ldconfig", "/usr/sbin/ldconfig"):
        if c.startswith("/"):
            if os.path.isfile(c) and os.access(c, os.X_OK):
                return c
        elif _have(c):
            return c
    return ""


def _read(path):
    try:
        with open(path) as f:
            return f.read()
    except Exception:
        return ""


def _write(path, body, mode=None):
    d = os.path.dirname(path)
    if d and not os.path.isdir(d):
        os.makedirs(d)
    with open(path, "w") as f:
        f.write(body)
    if mode is not None:
        os.chmod(path, mode)
    return path


# Real spec sections only. A generic ^%[a-z]+ terminator would end %files at
# its own first %defattr/%config line, which reads as "the snippet is not
# shipped" -- a passing spec reported as a failure.
_SPEC_SECTIONS = ("package", "description", "prep", "build", "install", "check",
                  "clean", "files", "changelog", "preun", "postun", "pre", "post",
                  "verifyscript", "triggerin", "triggerun")


def _section(text, name):
    """An RPM spec section's body: from %<name> to the next section keyword."""
    m = re.search(r"^%" + name + r"\b[^\n]*\n(.*?)(?=^%(?:"
                  + "|".join(_SPEC_SECTIONS) + r")\b|\Z)",
                  text, re.M | re.S)
    return m.group(1) if m else ""


class LdconfigSuite(object):
    def __init__(self, workdir, verbose):
        self.workdir = workdir
        self.verbose = verbose
        self.results = OrderedDict()
        self.details = {}
        # Group B/C artifacts, built once and reused by their group's checks.
        self.acdir = None
        self.mkfile = None
        # Group E/F discovery, filled by _probe_install().
        self.libdir = None
        self.pkg = None
        self.pkgtype = None
        self.snippet = None
        self.skip_live = ""

    # -- result helpers ----------------------------------------------------
    def _record(self, name, status, detail=""):
        self.results[name] = status
        self.details[name] = detail
        color = {"PASS": GREEN, "FAIL": RED, "SKIP": YELLOW}[status]
        line = "  {:24s}: {}{}{}".format(name, color, status, RESET)
        if detail:
            line += "  ({})".format(detail)
        print(line)
        return status != "FAIL"

    # ======================================================================
    # Group A -- build_sdk.sh flag surface
    # ======================================================================
    def help_flags(self):
        """Both flags must be discoverable from --help, like every other one."""
        rc, out = _run("{} --help".format(BUILD_SDK))
        if rc != 0:
            return self._record("help_flags", "FAIL", "--help exited {}".format(rc))
        missing = [f for f in ("--ldsoconfdir", "--no-ldsoconf") if f not in out]
        if missing:
            return self._record("help_flags", "FAIL",
                                "undocumented: {}".format(",".join(missing)))
        return self._record("help_flags", "PASS", "2 flags documented")

    def configure_argv(self):
        """build_sdk.sh -> ./configure argument mapping, against stubs.

        The real script, a stub autogen.sh/configure/make, and CWD == the stub
        tree: build_sdk.sh runs ./autogen.sh and ./configure relative to CWD, so
        this exercises the actual argument-building code in about a second
        instead of the minutes a real configure costs.
        """
        work = os.path.join(self.workdir, "argv")
        shutil.rmtree(work, ignore_errors=True)
        os.makedirs(work)
        shutil.copy2(BUILD_SDK, os.path.join(work, "build_sdk.sh"))
        os.chmod(os.path.join(work, "build_sdk.sh"), 0o755)
        _write(os.path.join(work, "autogen.sh"), "#!/bin/sh\nexit 0\n", 0o755)
        # Records argv one flag per line, so a value containing spaces cannot
        # smear two flags into one match.
        _write(os.path.join(work, "configure"),
               '#!/bin/sh\nfor a in "$@"; do printf \'%s\\n\' "$a"; done > configure.argv\nexit 0\n',
               0o755)
        _write(os.path.join(work, "Makefile"),
               "sdk:\n\t@true\ninstall-sdk:\n\t@true\n")

        cases = [
            # flags passed to build_sdk.sh, expected ldsoconf argument or None
            ([], None),
            (["--ldsoconfdir", "/opt/sdkv/ld.so.conf.d"],
             "--with-ldsoconfdir=/opt/sdkv/ld.so.conf.d"),
            (["--no-ldsoconf"], "--without-ldsoconfdir"),
        ]
        bad = []
        for flags, want in cases:
            argv_path = os.path.join(work, "configure.argv")
            if os.path.exists(argv_path):
                os.remove(argv_path)
            cmd = "./build_sdk.sh --build-only " + " ".join(flags)
            rc, out = _run(cmd, cmd, self.verbose, cwd=work)
            if rc != 0:
                bad.append("{}: rc={} {}".format(" ".join(flags) or "(default)",
                                                 rc, out.strip()[-80:]))
                continue
            argv = [ln for ln in _read(argv_path).splitlines() if ln]
            got = [a for a in argv if "ldsoconfdir" in a]
            if want is None and got:
                bad.append("(default): unexpected {}".format(got))
            elif want is not None and got != [want]:
                bad.append("{}: got {} want [{}]".format(" ".join(flags), got, want))
        return self._record("configure_argv", "FAIL" if bad else "PASS",
                            "; ".join(bad) or "{} mappings".format(len(cases)))

    # ======================================================================
    # Group B -- configure.ac, extracted verbatim and actually run
    # ======================================================================
    def _build_ac_harness(self):
        """Micro configure.ac wrapping the AC_ARG_WITH block verbatim."""
        text = _read(CONFIGURE_AC)
        start = text.find("AC_MSG_CHECKING(--with-ldsoconfdir argument)")
        if start < 0:
            self._record("ac_block_present", "FAIL",
                         "no --with-ldsoconfdir block in configure.ac")
            return None
        cond = text.find("AM_CONDITIONAL(INSTALL_SDK_LDSOCONF", start)
        if cond < 0:
            self._record("ac_block_present", "FAIL",
                         "no AM_CONDITIONAL(INSTALL_SDK_LDSOCONF) after the block")
            return None
        end = text.find("])", cond)
        if end < 0:
            self._record("ac_block_present", "FAIL", "unterminated AM_CONDITIONAL")
            return None
        block = text[start:end + 2] + "\n"
        self._record("ac_block_present", "PASS",
                     "{} lines extracted".format(len(block.splitlines())))

        work = os.path.join(self.workdir, "ac")
        shutil.rmtree(work, ignore_errors=True)
        os.makedirs(work)
        _write(os.path.join(work, "block.m4"), block)
        # AM_CONDITIONAL is an automake macro; stub it so plain autoconf can run
        # the block, and so its condition -- the part that can regress -- is
        # evaluated verbatim rather than paraphrased here.
        _write(os.path.join(work, "configure.ac"),
               "AC_INIT([ldsoconfcheck],[0])\n"
               "m4_define([AM_CONDITIONAL],[if $2; then $1[_TRUE]=yes; "
               "else $1[_TRUE]=no; fi])\n"
               "AC_ARG_ENABLE([mstflint-sdk],[],[],[enable_mstflint_sdk=yes])\n"
               "m4_include([block.m4])\n"
               "AC_MSG_NOTICE([RESULT|$LDSOCONFDIR|$INSTALL_SDK_LDSOCONF_TRUE|])\n"
               "AC_OUTPUT\n")
        rc, out = _run("autoconf -o configure configure.ac", cwd=work)
        ok = rc == 0 and os.path.isfile(os.path.join(work, "configure"))
        self._record("ac_harness_build", "PASS" if ok else "FAIL",
                     "" if ok else out.strip()[-120:])
        return work if ok else None

    def _ac_run(self, args):
        """Run the micro configure; return (ldsoconfdir, conditional) or None."""
        rc, out = _run("./configure {} 2>&1".format(args), cwd=self.acdir)
        m = re.search(r"RESULT\|([^|]*)\|([^|]*)\|", out)
        if rc != 0 or not m:
            return None
        return m.group(1), m.group(2)

    def configure_matrix(self):
        """Every way the snippet can be turned on, off, or relocated."""
        if self.acdir is None:
            return self._record("configure_matrix", "SKIP", "no autoconf harness")
        cases = [
            # configure args,                     want dir,               want cond
            ("", LDSOCONFDIR_DEFAULT, "yes"),
            ("--with-ldsoconfdir=/opt/sdkv/lsc", "/opt/sdkv/lsc", "yes"),
            # A bare --with-ldsoconfdir sets withval to the literal "yes"; the
            # block normalises it back to the default instead of installing the
            # snippet into a directory called "yes".
            ("--with-ldsoconfdir", LDSOCONFDIR_DEFAULT, "yes"),
            ("--without-ldsoconfdir", "", "no"),
            ("--with-ldsoconfdir=no", "", "no"),
            # The snippet is SDK-only: no SDK, no snippet, whatever the dir says.
            ("--disable-mstflint-sdk", LDSOCONFDIR_DEFAULT, "no"),
        ]
        bad = []
        for args, want_dir, want_cond in cases:
            got = self._ac_run(args)
            if got is None:
                bad.append("{!r}: configure failed".format(args or "(default)"))
            elif got != (want_dir, want_cond):
                bad.append("{!r}: got {} want {}".format(
                    args or "(default)", got, (want_dir, want_cond)))
        return self._record("configure_matrix", "FAIL" if bad else "PASS",
                            "; ".join(bad) or "{} argument combinations".format(len(cases)))

    def prefix_independent(self):
        """The trap the block was written for.

        ldconfig reads only the real /etc, so the snippet directory must not
        follow --prefix or --sysconfdir. Deriving it from $sysconfdir looks
        correct and tests clean on a default build, then silently drops the
        snippet somewhere ldconfig never looks on any relocated one.
        """
        if self.acdir is None:
            return self._record("prefix_independent", "SKIP", "no autoconf harness")
        got = self._ac_run("--prefix=/opt/sdkv --sysconfdir=/opt/sdkv/etc")
        if got is None:
            return self._record("prefix_independent", "FAIL", "configure failed")
        if got[0] != LDSOCONFDIR_DEFAULT:
            return self._record("prefix_independent", "FAIL",
                                "--prefix=/opt/sdkv moved the snippet to {}".format(got[0]))
        return self._record("prefix_independent", "PASS",
                            "{} under --prefix=/opt/sdkv".format(got[0]))

    # ======================================================================
    # Group C -- the Makefile.am recipe, extracted verbatim and actually run
    # ======================================================================
    def _build_mk_harness(self):
        """Micro Makefile wrapping the install/uninstall recipe verbatim."""
        text = _read(SDK_MAKEFILE_AM)
        m = re.search(r"^ldsoconfdir\s*=.*?^endif\s*$", text, re.M | re.S)
        if not m:
            self._record("mk_block_present", "FAIL",
                         "no ldsoconfdir..endif block in mft_sdk/Makefile.am")
            return None
        block = m.group(0)
        if "install-data-local" not in block or "uninstall-local" not in block:
            self._record("mk_block_present", "FAIL",
                         "block has no install-data-local/uninstall-local")
            return None
        self._record("mk_block_present", "PASS",
                     "{} lines extracted".format(len(block.splitlines())))

        work = os.path.join(self.workdir, "mk")
        shutil.rmtree(work, ignore_errors=True)
        os.makedirs(work)
        # Play configure and automake: substitute @LDSOCONFDIR@, drop the
        # conditional wrapper (the condition itself is group B's job), and
        # supply the variables automake would have defined. sdklibdir keeps its
        # real definition from Makefile.am so the recipe is proven to name the
        # PRIVATE directory, not $(libdir).
        sdklib = re.search(r"^sdklibdir\s*=\s*(.+)$", text, re.M)
        if not sdklib:
            self._record("mk_block_present", "FAIL", "no sdklibdir in Makefile.am")
            return None
        body = block.replace("@LDSOCONFDIR@", "/etc/ld.so.conf.d")
        body = re.sub(r"^(if INSTALL_SDK_LDSOCONF|endif)\s*$", "", body, flags=re.M)
        _write(os.path.join(work, "micro.mk"),
               "MKDIR_P = mkdir -p\n"
               "libdir = /usr/lib64\n"
               "sdklibdir = {}\n".format(sdklib.group(1).strip()) + body + "\n")
        return work

    def _mk_install(self, destdir, extra=""):
        rc, out = _run("make -f micro.mk install-data-local DESTDIR={} {}".format(
            destdir, extra), cwd=self.mkfile)
        return rc, out

    def install_recipe(self):
        """install-data-local writes the private libdir into the snippet."""
        if self.mkfile is None:
            return self._record("install_recipe", "SKIP", "no make harness")
        dest = os.path.join(self.mkfile, "d1")
        rc, out = self._mk_install(dest)
        if rc != 0:
            return self._record("install_recipe", "FAIL", out.strip()[-120:])
        path = os.path.join(dest, "etc/ld.so.conf.d/mstflint-sdk.conf")
        if not os.path.isfile(path):
            return self._record("install_recipe", "FAIL",
                                "no snippet at $DESTDIR{}/mstflint-sdk.conf".format(
                                    LDSOCONFDIR_DEFAULT))
        body = _read(path).strip()
        if body != "/usr/lib64/mstflint/sdk":
            return self._record("install_recipe", "FAIL",
                                "snippet says {!r}, want the private libdir".format(body))
        return self._record("install_recipe", "PASS", "mstflint-sdk.conf -> " + body)

    def ldsoconffile_override(self):
        """`make ... ldsoconffile=X.conf` renames the snippet.

        Both packagings depend on this: the RPM passes ldsoconffile=%{name}.conf
        and the DEB passes the Source name, so a privately-named build installs
        beside a distro mstflint-sdk instead of file-conflicting with it.
        """
        if self.mkfile is None:
            return self._record("ldsoconffile_override", "SKIP", "no make harness")
        dest = os.path.join(self.mkfile, "d2")
        rc, out = self._mk_install(dest, "ldsoconffile=mstflint-sdk-local.conf")
        if rc != 0:
            return self._record("ldsoconffile_override", "FAIL", out.strip()[-120:])
        base = os.path.join(dest, "etc/ld.so.conf.d")
        got = sorted(os.listdir(base)) if os.path.isdir(base) else []
        if got != ["mstflint-sdk-local.conf"]:
            return self._record("ldsoconffile_override", "FAIL",
                                "snippet dir holds {}".format(got))
        return self._record("ldsoconffile_override", "PASS", "renamed to " + got[0])

    def uninstall_recipe(self):
        """uninstall-local takes the snippet back out."""
        if self.mkfile is None:
            return self._record("uninstall_recipe", "SKIP", "no make harness")
        dest = os.path.join(self.mkfile, "d3")
        rc, out = self._mk_install(dest)
        if rc != 0:
            return self._record("uninstall_recipe", "FAIL",
                                "install leg failed: " + out.strip()[-100:])
        path = os.path.join(dest, "etc/ld.so.conf.d/mstflint-sdk.conf")
        if not os.path.isfile(path):
            return self._record("uninstall_recipe", "FAIL", "nothing installed to remove")
        rc, out = _run("make -f micro.mk uninstall-local DESTDIR={}".format(dest),
                       cwd=self.mkfile)
        if rc != 0:
            return self._record("uninstall_recipe", "FAIL", out.strip()[-120:])
        if os.path.exists(path):
            return self._record("uninstall_recipe", "FAIL", "snippet survived uninstall")
        return self._record("uninstall_recipe", "PASS", "snippet removed")

    # ======================================================================
    # Group D -- the packaging recipes
    # ======================================================================
    def spec_recipe(self):
        """The RPM half: scriptlets, config marking, and the /etc hardcode."""
        text = _read(SDK_SPEC_IN)
        if not text:
            return self._record("spec_recipe", "FAIL",
                                "cannot read {}".format(SDK_SPEC_IN))
        bad = []
        define = re.search(r"^%define\s+mstflint_sdk_ldsoconf\s+(\S+)", text, re.M)
        if not define:
            bad.append("no %define mstflint_sdk_ldsoconf")
        else:
            path = define.group(1)
            if not path.startswith("/etc/ld.so.conf.d/"):
                bad.append("snippet path {} is not under /etc/ld.so.conf.d".format(path))
            # %{_sysconfdir} follows a relocated %{_prefix}; ldconfig would
            # never read the result.
            if "_sysconfdir" in path:
                bad.append("snippet path uses %{_sysconfdir}")
            if "%{name}" not in path:
                bad.append("snippet is not named after %{name} (renamed builds collide)")
        for sect in ("post", "postun"):
            if "ldconfig" not in _section(text, sect):
                bad.append("%{} does not run ldconfig".format(sect))
        files = _section(text, "files")
        if not re.search(r"%config\(noreplace\)\s+%\{mstflint_sdk_ldsoconf\}", files):
            bad.append("%files does not ship the snippet as %config(noreplace)")
        if not re.search(r"make\s+install-sdk[^\n]*ldsoconffile=%\{name\}\.conf",
                         _section(text, "install")):
            bad.append("%install does not pass ldsoconffile=%{name}.conf")
        return self._record("spec_recipe", "FAIL" if bad else "PASS",
                            "; ".join(bad) or "scriptlets + %config + %{name}.conf")

    def deb_recipe(self):
        """The DEB half: the trigger, and the rename-safe file names."""
        rules = _read(os.path.join(DEBIAN_SDK, "rules"))
        triggers_path = os.path.join(DEBIAN_SDK, "triggers")
        triggers = _read(triggers_path)
        bad = []
        if not rules:
            bad.append("cannot read debian-sdk/rules")
        else:
            if not re.search(r"^DEB_PKG\s*:?=\s*\$\(shell\s+dpkg-parsechangelog\s+-SSource\)",
                             rules, re.M):
                bad.append("rules does not derive DEB_PKG from dpkg-parsechangelog -SSource")
            if not re.search(r"install-sdk[^\n]*ldsoconffile=\$\(DEB_PKG\)\.conf", rules):
                bad.append("rules does not pass ldsoconffile=$(DEB_PKG).conf")
        if not os.path.isfile(triggers_path):
            bad.append("no debian-sdk/triggers")
        elif not re.search(r"^activate-noawait\s+ldconfig\s*$", triggers, re.M):
            bad.append("triggers does not activate-noawait ldconfig")
        # dh_makeshlibs is overridden to nothing, so debhelper adds no ldconfig
        # trigger of its own -- the shipped one is the only one there is.
        if rules and not re.search(r"^override_dh_makeshlibs:", rules, re.M):
            bad.append("dh_makeshlibs is no longer overridden (trigger may now be doubled)")
        # A <package>.triggers name stops working the moment --deb-name renames
        # the binary package; the unprefixed name is what makes rename safe.
        stray = [f for f in (os.listdir(DEBIAN_SDK) if os.path.isdir(DEBIAN_SDK) else [])
                 if f.endswith(".triggers")]
        if stray:
            bad.append("package-prefixed trigger file(s) {} break --deb-name".format(stray))
        return self._record("deb_recipe", "FAIL" if bad else "PASS",
                            "; ".join(bad) or "activate-noawait ldconfig + $(DEB_PKG).conf")

    # ======================================================================
    # Group E -- the installed package
    # ======================================================================
    def _probe_install(self):
        """Find the installed SDK lib, its package, and the shipped snippet."""
        cands = []
        env_dir = os.environ.get("MFT_SDK_SO_DIR")
        if env_dir:
            cands.append(env_dir)
        cands.extend(SDK_LIBDIR_CANDIDATES)
        for d in cands:
            if os.path.isfile(os.path.join(d, SONAME)):
                self.libdir = d
                break
        if self.libdir is None:
            self.skip_live = "no installed mstflint SDK ({} not found in {})".format(
                SONAME, ", ".join(cands[:2]) + ", ...")
            return
        lib = os.path.join(self.libdir, SONAME)
        if _have("rpm"):
            # %{NAME}, not the default NVRA: the snippet is named after the
            # package NAME (%{name}.conf), so an NVRA here would compare
            # mstflint-sdk.conf against mstflint-sdk-4.37.0-1.el10.x86_64.conf.
            rc, out = _run("rpm -qf --qf '%{{NAME}}\\n' {} 2>/dev/null".format(lib))
            if rc == 0 and out.strip() and "not owned" not in out:
                self.pkg, self.pkgtype = out.strip().splitlines()[0], "rpm"
        if self.pkg is None and _have("dpkg"):
            rc, out = _run("dpkg -S {} 2>/dev/null".format(lib))
            if rc == 0 and ":" in out:
                self.pkg, self.pkgtype = out.split(":")[0].strip(), "deb"
        if self.pkg is None:
            self.skip_live = ("{} is installed at {} but owned by no package "
                              "(source install?) -- packaging checks need a package".format(
                                  SONAME, self.libdir))

    def pkg_owns_snippet(self):
        """The package ships the snippet; it is not left to the admin."""
        if self.skip_live:
            return self._record("pkg_owns_snippet", "SKIP", self.skip_live)
        cmd = ("rpm -ql {}" if self.pkgtype == "rpm" else "dpkg -L {}").format(self.pkg)
        rc, out = _run(cmd)
        snips = [ln.strip() for ln in out.splitlines()
                 if ln.strip().startswith(LDSOCONFDIR_DEFAULT + "/")]
        if rc != 0 or not snips:
            return self._record("pkg_owns_snippet", "FAIL",
                                "{} ships nothing under {}".format(self.pkg,
                                                                   LDSOCONFDIR_DEFAULT))
        if len(snips) > 1:
            return self._record("pkg_owns_snippet", "FAIL",
                                "{} ships {} snippets: {}".format(self.pkg, len(snips), snips))
        self.snippet = snips[0]
        want = os.path.join(LDSOCONFDIR_DEFAULT, self.pkg + ".conf")
        if self.snippet != want:
            return self._record("pkg_owns_snippet", "FAIL",
                                "snippet is {} but the package is {} (want {})".format(
                                    self.snippet, self.pkg, want))
        return self._record("pkg_owns_snippet", "PASS",
                            "{} owns {}".format(self.pkg, self.snippet))

    def snippet_is_config(self):
        """Marked config/conffile, so a local edit survives an upgrade."""
        if self.skip_live:
            return self._record("snippet_is_config", "SKIP", self.skip_live)
        if not self.snippet:
            return self._record("snippet_is_config", "SKIP", "no snippet found")
        if self.pkgtype == "rpm":
            rc, out = _run("rpm -q --configfiles {}".format(self.pkg))
            ok = rc == 0 and self.snippet in out.split()
            return self._record("snippet_is_config", "PASS" if ok else "FAIL",
                                "%config(noreplace)" if ok
                                else "not listed by rpm -q --configfiles")
        rc, out = _run("dpkg-query -W -f='${{Conffiles}}' {}".format(self.pkg))
        ok = rc == 0 and self.snippet in out
        return self._record("snippet_is_config", "PASS" if ok else "FAIL",
                            "conffile" if ok else "not a registered conffile")

    def pkg_ldconfig_hook(self):
        """Installing the package must refresh the ld.so cache by itself."""
        if self.skip_live:
            return self._record("pkg_ldconfig_hook", "SKIP", self.skip_live)
        if self.pkgtype == "rpm":
            rc, out = _run("rpm -q --scripts {}".format(self.pkg))
            if rc != 0:
                return self._record("pkg_ldconfig_hook", "FAIL", "rpm -q --scripts failed")
            missing = [s for s in ("postinstall", "postuninstall")
                       if not re.search(r"^" + s + r"[^\n]*\n(?:(?!^\w+ scriptlet).)*?ldconfig",
                                        out, re.M | re.S)]
            return self._record("pkg_ldconfig_hook", "FAIL" if missing else "PASS",
                                "no ldconfig in: {}".format(",".join(missing)) if missing
                                else "%post + %postun run ldconfig")
        rc, out = _run("dpkg-query --control-show {} triggers 2>/dev/null".format(self.pkg))
        if rc != 0 or not out.strip():
            rc, out = _run("cat /var/lib/dpkg/info/{}.triggers 2>/dev/null".format(self.pkg))
        ok = "ldconfig" in out
        return self._record("pkg_ldconfig_hook", "PASS" if ok else "FAIL",
                            "ldconfig trigger registered" if ok
                            else "no ldconfig trigger on {}".format(self.pkg))

    def snippet_content(self):
        """One line, and it names the directory the library is actually in."""
        if self.skip_live:
            return self._record("snippet_content", "SKIP", self.skip_live)
        if not self.snippet:
            return self._record("snippet_content", "SKIP", "no snippet found")
        if not os.path.isfile(self.snippet):
            return self._record("snippet_content", "FAIL",
                                "{} is in the package file list but not on disk".format(
                                    self.snippet))
        lines = [ln.strip() for ln in _read(self.snippet).splitlines()
                 if ln.strip() and not ln.strip().startswith("#")]
        if len(lines) != 1:
            return self._record("snippet_content", "FAIL",
                                "{} directory lines, want exactly 1".format(len(lines)))
        listed = lines[0]
        if os.path.realpath(listed) != os.path.realpath(self.libdir):
            return self._record("snippet_content", "FAIL",
                                "snippet names {} but {} is in {}".format(
                                    listed, SONAME, self.libdir))
        return self._record("snippet_content", "PASS", listed)

    def dir_not_default(self):
        """The snippet is only meaningful if the directory is a private one.

        If the SDK libdir were already searched by default, every other check
        here would pass while proving nothing -- and a regression that dropped
        the snippet would go unnoticed until a machine with a stricter loader.
        """
        if self.skip_live:
            return self._record("dir_not_default", "SKIP", self.skip_live)
        real = os.path.realpath(self.libdir)
        if real in DEFAULT_LD_DIRS:
            return self._record("dir_not_default", "FAIL",
                                "{} is a default loader directory".format(real))
        # Any OTHER snippet naming the same dir would also mask a regression.
        others = []
        for name in sorted(os.listdir(LDSOCONFDIR_DEFAULT)
                           if os.path.isdir(LDSOCONFDIR_DEFAULT) else []):
            path = os.path.join(LDSOCONFDIR_DEFAULT, name)
            if path == self.snippet or not os.path.isfile(path):
                continue
            for ln in _read(path).splitlines():
                if ln.strip() and os.path.realpath(ln.strip()) == real:
                    others.append(name)
        conf = _read("/etc/ld.so.conf")
        for ln in conf.splitlines():
            ln = ln.strip()
            if ln and not ln.startswith(("#", "include")) and os.path.realpath(ln) == real:
                others.append("/etc/ld.so.conf")
        if others:
            return self._record("dir_not_default", "FAIL",
                                "{} is also registered by {}".format(real, ",".join(others)))
        return self._record("dir_not_default", "PASS",
                            "{} is private to the SDK snippet".format(real))

    def ldconfig_cache(self):
        """The cache resolves the soname, and to our copy."""
        if self.skip_live:
            return self._record("ldconfig_cache", "SKIP", self.skip_live)
        ldc = _ldconfig()
        if not ldc:
            return self._record("ldconfig_cache", "SKIP", "no ldconfig on this machine")
        rc, out = _run("{} -p 2>/dev/null".format(ldc))
        if rc != 0:
            return self._record("ldconfig_cache", "FAIL",
                                "{} -p exited {}".format(ldc, rc))
        hits = [ln.split("=>")[-1].strip() for ln in out.splitlines()
                if SONAME in ln and "=>" in ln]
        if not hits:
            return self._record("ldconfig_cache", "FAIL",
                                "{} is not in the ld.so cache (snippet not applied, "
                                "or ldconfig never ran)".format(SONAME))
        want = os.path.realpath(os.path.join(self.libdir, SONAME))
        if want not in [os.path.realpath(h) for h in hits]:
            return self._record("ldconfig_cache", "FAIL",
                                "cache resolves {} to {}, not {}".format(SONAME, hits, want))
        return self._record("ldconfig_cache", "PASS", "{} -> {}".format(SONAME, want))

    # ======================================================================
    # Group F -- the consumer contract
    # ======================================================================
    def soname_resolution(self):
        """A client linked by soname alone, with no rpath and no LD_LIBRARY_PATH.

        This is exactly how DOCA's libdoca_mgmt consumes the SDK, and exactly
        what failed before PR #1855. Everything else in this suite is evidence;
        this is the behaviour.
        """
        if self.skip_live:
            return self._record("soname_resolution", "SKIP", self.skip_live)
        if not _have("gcc"):
            return self._record("soname_resolution", "SKIP", "no gcc on this machine")
        inc = None
        # The .pc is installed to $(libdir)/pkgconfig -- the default search path,
        # not the private SDK dir -- so plain pkg-config finds it. This is how
        # DOCA discovers the SDK, so prefer it and fall back only if absent.
        rc, out = _run("pkg-config --cflags mstflint_sdk 2>/dev/null")
        if rc == 0 and out.strip():
            inc = out.strip()
        else:
            for d in ("/usr/include/mstflint/sdk", "/usr/local/include/mstflint/sdk"):
                if os.path.isfile(os.path.join(d, "mft_sdk", "mft_sdk.h")):
                    inc = "-I" + d
                    break
        if inc is None:
            return self._record("soname_resolution", "SKIP",
                                "SDK headers not found (mft_sdk/mft_sdk.h)")

        work = os.path.join(self.workdir, "client")
        shutil.rmtree(work, ignore_errors=True)
        os.makedirs(work)
        src = _write(os.path.join(work, "ldso_client.c"), LDSO_CLIENT_C)
        binp = os.path.join(work, "ldso_client")
        # -L to link, and deliberately NO -Wl,-rpath: at run time the loader
        # must find the library through the ld.so cache alone.
        cmd = "gcc -O0 -o {} {} {} -L{} -lmstflint_sdk -Wl,--allow-shlib-undefined".format(
            binp, src, inc, self.libdir)
        rc, out = _run(cmd, cmd, self.verbose)
        if rc != 0:
            return self._record("soname_resolution", "FAIL",
                                "link failed: " + out.strip()[-160:])

        rc, out = _run("readelf -d {} 2>/dev/null".format(binp))
        if re.search(r"\((RPATH|RUNPATH)\)", out):
            return self._record("soname_resolution", "FAIL",
                                "the client got an RPATH/RUNPATH -- the check would "
                                "pass without the snippet")
        if SONAME not in out:
            return self._record("soname_resolution", "FAIL",
                                "no DT_NEEDED on {} (linker dropped it)".format(SONAME))

        # env -u: an LD_LIBRARY_PATH inherited from the runner would resolve the
        # library and hide exactly the failure this check is for.
        rc, out = _run("env -u LD_LIBRARY_PATH ldd {} 2>&1".format(binp))
        line = [ln for ln in out.splitlines() if SONAME in ln]
        if not line or "not found" in " ".join(line):
            return self._record("soname_resolution", "FAIL",
                                "ldd: {}".format((line or ["no line for " + SONAME])[0].strip()))
        resolved = line[0].split("=>")[-1].split("(")[0].strip()
        if os.path.realpath(resolved) != os.path.realpath(os.path.join(self.libdir, SONAME)):
            return self._record("soname_resolution", "FAIL",
                                "ldd resolved {} to {}, not the installed copy".format(
                                    SONAME, resolved))
        rc, out = _run("env -u LD_LIBRARY_PATH {}".format(binp))
        if rc != 0:
            return self._record("soname_resolution", "FAIL",
                                "client exited {}: {}".format(rc, out.strip()[-120:]))
        return self._record("soname_resolution", "PASS",
                            "no rpath, no LD_LIBRARY_PATH -> " + resolved)

    # ======================================================================
    def run(self):
        print("{}mstflint SDK ldconfig registration (PR #1855){}".format(BLUE, RESET))
        print("  repo:   {}".format(REPO_ROOT))

        print("\n{}A. build_sdk.sh flag surface{}".format(BLUE, RESET))
        self.help_flags()
        self.configure_argv()

        print("\n{}B. configure.ac --with/--without-ldsoconfdir{}".format(BLUE, RESET))
        if _have("autoconf"):
            self.acdir = self._build_ac_harness()
        else:
            self._record("ac_block_present", "SKIP", "no autoconf on this machine")
            self._record("ac_harness_build", "SKIP", "no autoconf on this machine")
        self.configure_matrix()
        self.prefix_independent()

        print("\n{}C. Makefile.am install recipe{}".format(BLUE, RESET))
        if _have("make"):
            self.mkfile = self._build_mk_harness()
        else:
            self._record("mk_block_present", "SKIP", "no make on this machine")
        self.install_recipe()
        self.ldsoconffile_override()
        self.uninstall_recipe()

        print("\n{}D. packaging recipes{}".format(BLUE, RESET))
        self.spec_recipe()
        self.deb_recipe()

        print("\n{}E. installed package{}".format(BLUE, RESET))
        self._probe_install()
        if self.libdir:
            print("  {:24s}  {} ({})".format("installed:", self.libdir,
                                             self.pkg or "no owning package"))
        self.pkg_owns_snippet()
        self.snippet_is_config()
        self.pkg_ldconfig_hook()
        self.snippet_content()
        self.dir_not_default()
        self.ldconfig_cache()

        print("\n{}F. consumer contract (the libdoca_mgmt case){}".format(BLUE, RESET))
        self.soname_resolution()

        self._summary()
        return 1 if any(s == "FAIL" for s in self.results.values()) else 0

    def _summary(self):
        print("\n" + "=" * 60 + "\nLDCONFIG REGISTRATION TEST SUMMARY\n" + "=" * 60)
        for name, status in self.results.items():
            print("  {}: {}".format(name, status))
        failed = [n for n, s in self.results.items() if s == "FAIL"]
        skipped = [n for n, s in self.results.items() if s == "SKIP"]
        print("  {} passed, {} failed, {} skipped".format(
            len(self.results) - len(failed) - len(skipped), len(failed), len(skipped)))
        print("=" * 60 + "\nOverall: " + (
            "ALL TESTS PASSED" if not failed else "SOME TESTS FAILED") +
            "\n" + "=" * 60)


def print_usage():
    print(__doc__)


def main():
    keep = False
    verbose = False
    so_mode = False
    workdir = None
    args = sys.argv[1:]
    i = 0
    while i < len(args):
        a = args[i]
        if a in ("--help", "-h"):
            print_usage()
            return 0
        elif a == "--keep":
            keep = True
        elif a == "--workdir":
            i += 1
            workdir = args[i] if i < len(args) else None
        elif a == "--so":
            so_mode = True
        elif a == "--verbose":
            verbose = True
        elif a == "-d":
            i += 1  # accepted and ignored: this suite needs no device
        elif a in ("--compare", "--compare-all", "--coverage", "--sdk-only"):
            pass  # accepted and ignored: the extension always appends these
        elif a == "--build":
            print("{}[ERROR] ldconfig tests only support --so{}".format(RED, RESET))
            return 1
        else:
            print("{}[ERROR] unknown argument: {}{}".format(RED, a, RESET))
            return 1
        i += 1

    if not so_mode:
        print("{}[ERROR] ldconfig tests require --so{}".format(RED, RESET))
        return 1
    for path, what in ((BUILD_SDK, "build_sdk.sh"), (CONFIGURE_AC, "configure.ac"),
                       (SDK_MAKEFILE_AM, "mft_sdk/Makefile.am"),
                       (SDK_SPEC_IN, "mstflint-sdk.spec.in")):
        if not os.path.isfile(path):
            print("{}[ERROR] {} not found at {}{}".format(RED, what, path, RESET))
            return 1

    # /data/tmp, never the system temp dir. Host+pid namespaced because the
    # fallback root is $HOME, one NFS export shared by the whole fleet: two
    # machines tested in parallel would otherwise rmtree each other's scratch.
    if workdir is None:
        root = os.environ.get("SDKV_TMP_ROOT", "/data/tmp")
        if not (os.path.isdir(root) and os.access(root, os.W_OK)):
            root = os.path.expanduser("~")
        workdir = os.path.join(root, "sdkv_ldconfig_test_{}_{}".format(
            socket.gethostname().split(".")[0], os.getpid()))
    shutil.rmtree(workdir, ignore_errors=True)
    os.makedirs(workdir)

    try:
        return LdconfigSuite(workdir, verbose).run()
    finally:
        if keep:
            print("\nscratch kept at {}".format(workdir))
        else:
            shutil.rmtree(workdir, ignore_errors=True)


if __name__ == "__main__":
    sys.exit(main())
