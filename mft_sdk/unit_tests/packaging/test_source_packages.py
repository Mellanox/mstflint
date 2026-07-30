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
Packaging test for the mstflint SDK build_sdk.sh source-package flags:
--rpm-source/--rpm-release and --deb-source/--deb-version.

UBS resolves a binary package to its source package (RPM SOURCERPM tag / DEB
Source field). build_sdk.sh used to emit binary packages only, so the SDK binary
referenced a .src.rpm that was never produced and resolution broke.

Asserts the four acceptance artifacts, for --rpm-name/--deb-name
mstflint-sdk-local, version 4.37.0, release 1.60.g6523381:
    mstflint-sdk-local-4.37.0-1.60.g6523381.<dist>.<arch>.rpm
    mstflint-sdk-local-4.37.0-1.60.g6523381.src.rpm          (no dist tag)
    mstflint-sdk-local_4.37.0-1.60.g6523381_<arch>.deb
    mstflint-sdk-local_4.37.0-1.60.g6523381.dsc + .orig.tar.* + .debian.tar.*

mstflint-SDK-ONLY suite, and the first fully OFFLINE one: no device, no sudo, no
installed package, no package cache. It drives build_sdk.sh in a scratch dir and
inspects the output, so it is a build-host suite rather than a per-machine one.

Steps run in three groups. The static ones are instant. The stubbed ones put a
fake rpmbuild/dpkg-buildpackage on PATH that records its argv and fabricates the
artifacts -- seconds instead of minutes, and the only DEB coverage available on
an RPM host, where dpkg tooling is absent. The real-build group compiles for
several minutes and is skipped by --no-build.

Usage:
    ./test_source_packages.py --so
    ./test_source_packages.py --so --no-build
    ./test_source_packages.py --so --keep --workdir /data/tmp/srcpkg
    ./test_source_packages.py --help

Env:
    SDKV_TMP_ROOT          scratch root (default: /data/tmp); never the system
                           temp dir, which cannot hold an SDK rpmbuild
"""

from __future__ import print_function
import os
import platform
import re
import shutil
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
SDK_SPEC_IN = os.path.join(REPO_ROOT, "mstflint-sdk.spec.in")

# The values UBS passes; the acceptance criteria are written against these.
TEST_NAME = "mstflint-sdk-local"
TEST_RELEASE = "1.60.g6523381"


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


def _arch():
    return platform.machine()


def _deb_arch():
    """Debian arch name, which is not uname -m (amd64 vs x86_64, arm64 vs aarch64)."""
    rc, out = _run("dpkg --print-architecture 2>/dev/null")
    return out.strip() if rc == 0 and out.strip() else _arch()


def _missing_build_deps(out):
    """The unsatisfied build dependencies named in a failed build, or ''.

    A lab machine without the BuildRequires/Build-Depends installed is an
    environment gap, not a build_sdk.sh defect, so it must SKIP rather than FAIL.
    """
    m = re.search(r"unmet build dependencies:\s*([^;\n]+)", out)
    if m:
        return m.group(1).strip()
    needed = re.findall(r"^\s*(\S+) is needed by", out, re.M)
    return ", ".join(sorted(set(needed))) if needed else ""


def _have(tool):
    return _run("command -v {}".format(tool))[0] == 0


def _no_output(d):
    """True when a build produced nothing. The output dir is created before the
    build runs, so 'exists' does not mean 'built'."""
    return not os.path.isdir(d) or not os.listdir(d)


def _host_dist():
    """The build host's rpm dist tag ('.el10'), or '' where none is defined."""
    rc, out = _run("rpm --eval '%{?dist}'")
    return out.strip() if rc == 0 else ""


def _sdk_version():
    """Project version from configure.ac, mirroring build_sdk.sh's sdk_version()."""
    rc, out = _run(
        "sed -nE 's/^AC_INIT\\(mstflint,[[:space:]]*([0-9.]+).*/\\1/p' {} | head -1"
        .format(os.path.join(REPO_ROOT, "configure.ac")))
    return out.strip() or "4.37.0"


RPMBUILD_STUB = r'''#!/bin/bash
# Stub rpmbuild: log the argv, then fabricate the artifact the real one would
# produce so build_sdk.sh's collection step behaves normally.
echo "$*" >> "$RPMBUILD_LOG"
top=""; name="mstflint-sdk"; version="0"; release="1"; dist=".elX"; mode=""
prev=""
for a in "$@"; do
    if [[ "$prev" == "--define" ]]; then
        case "$a" in
            "_topdir "*) top="${a#_topdir }" ;;
            "name "*)    name="${a#name }" ;;
            "version "*) version="${a#version }" ;;
            "release "*) release="${a#release }" ;;
            "dist "*)    dist="" ;;
        esac
    fi
    case "$a" in -bs) mode=bs ;; -bb) mode=bb ;; -ba) mode=ba ;; esac
    prev="$a"
done
[[ -n "$top" ]] || exit 0
if [[ "$mode" == "bs" || "$mode" == "ba" ]]; then
    mkdir -p "$top/SRPMS"
    : > "$top/SRPMS/${name}-${version}-${release}${dist}.src.rpm"
fi
if [[ "$mode" == "bb" || "$mode" == "ba" ]]; then
    mkdir -p "$top/RPMS/$(uname -m)"
    : > "$top/RPMS/$(uname -m)/${name}-${version}-${release}${dist}.$(uname -m).rpm"
fi
exit 0
'''

DPKG_STUB = r'''#!/bin/bash
# Stub dpkg-buildpackage: runs with cwd = the staged source tree. Records the
# build flag, source format, changelog headline and what the parent dir and the
# orig tarball contain, then fabricates the output files.
{
  echo "args=$*"
  echo "format=$(cat debian/source/format 2>/dev/null)"
  echo "changelog=$(head -1 debian/changelog 2>/dev/null)"
  echo "control=$(sed -nE 's/^Source: (.*)/\1/p' debian/control 2>/dev/null | head -1)"
  echo "parent=$(ls -1 .. 2>/dev/null | paste -sd, -)"
  orig=$(ls -1 ../*.orig.tar.* 2>/dev/null | head -1)
  if [[ -n "$orig" ]]; then
      echo "origtop=$(tar tzf "$orig" 2>/dev/null | cut -d/ -f2 | sort -u | grep -v '^$' | paste -sd, -)"
  else
      echo "origtop="
  fi
} >> "$DPKG_LOG"
src=$(sed -nE '1s/^([^ ]+) .*/\1/p' debian/changelog)
ver=$(sed -nE '1s/^[^ ]+ \(([^)]*)\).*/\1/p' debian/changelog)
arch=$(dpkg --print-architecture 2>/dev/null || uname -m)
: > "../${src}_${ver}_${arch}.deb"
case "$*" in
    *-F*|*-S*)
        : > "../${src}_${ver}.dsc"
        : > "../${src}_${ver}.debian.tar.xz"
        ;;
esac
exit 0
'''


def _make_stub_bin(workdir, subdir):
    """Create a PATH-prefix dir holding stub build tools; return its path."""
    binroot = os.path.join(workdir, subdir)
    shutil.rmtree(binroot, ignore_errors=True)
    os.makedirs(binroot)
    for tool, body in (("rpmbuild", RPMBUILD_STUB),
                       ("dpkg-buildpackage", DPKG_STUB)):
        path = os.path.join(binroot, tool)
        with open(path, "w") as f:
            f.write(body)
        os.chmod(path, 0o755)
    return binroot


def _define_of(argline, macro):
    """Value of `--define '<macro> <value>'` in a recorded rpmbuild argv."""
    m = re.search(r"--define\s+{}\s+(\S+)".format(re.escape(macro)), argline)
    return m.group(1) if m else None


def _parse_log(path):
    rec = {}
    if os.path.exists(path):
        with open(path) as f:
            for ln in f:
                if "=" in ln:
                    k, _, v = ln.strip().partition("=")
                    rec.setdefault(k, []).append(v)
    return rec


class SourcePackageSuite(object):
    def __init__(self, workdir, do_build, verbose):
        self.workdir = workdir
        self.do_build = do_build
        self.verbose = verbose
        self.results = OrderedDict()
        self.version = _sdk_version()
        self.dist = _host_dist()
        self.rpm_out = os.path.join(workdir, "rpm")
        self.deb_out = os.path.join(workdir, "deb")
        self.binary_rpm = None
        self.source_rpm = None

    # -- result helpers ----------------------------------------------------
    def _record(self, name, status, detail=""):
        self.results[name] = status
        color = {"PASS": GREEN, "FAIL": RED, "SKIP": YELLOW}[status]
        line = "  {:28s}: {}{}{}".format(name, color, status, RESET)
        if detail:
            line += "  ({})".format(detail)
        print(line)
        return status != "FAIL"

    # -- static checks -----------------------------------------------------
    def flags_present(self):
        """Every new flag is documented in --help, so UBS can discover them."""
        rc, out = _run("{} --help".format(BUILD_SDK))
        if rc != 0:
            return self._record("flags_present", "FAIL", "--help exited {}".format(rc))
        missing = [f for f in ("--rpm-source", "--rpm-release",
                               "--deb-source", "--deb-version") if f not in out]
        if missing:
            return self._record("flags_present", "FAIL",
                                "undocumented: {}".format(",".join(missing)))
        return self._record("flags_present", "PASS", "4 flags documented")

    def spec_release_dist(self):
        """The spec's Release must carry %{?dist} so the binary is per-distro.

        The SRPM drops it again via --define "dist %{nil}". Note this only works
        because the spec has no BuildArch: tag -- with one, rpm expands the
        Release tag twice and the dist suffix is doubled.
        """
        with open(SDK_SPEC_IN) as f:
            spec = f.read()
        m = re.search(r"^Release:\s*(.+?)\s*$", spec, re.M)
        if not m:
            return self._record("spec_release_dist", "FAIL", "no Release: tag")
        if m.group(1) != "%{release}%{?dist}":
            return self._record("spec_release_dist", "FAIL",
                                "Release: {}".format(m.group(1)))
        if re.search(r"^BuildArch:", spec, re.M):
            return self._record("spec_release_dist", "FAIL",
                                "BuildArch: present - dist tag will be doubled")
        return self._record("spec_release_dist", "PASS", "%{release}%{?dist}, no BuildArch")

    def dist_not_doubled(self):
        """Prove on a real build that this spec shape yields exactly one dist tag.

        A BuildArch: tag makes rpm expand Release twice; this asserts the real
        spec's shape (guards + ExclusiveArch, no BuildArch) does not.
        """
        if not _have("rpmbuild"):
            return self._record("dist_not_doubled", "SKIP", "rpmbuild not installed")
        if not self.dist:
            return self._record("dist_not_doubled", "SKIP", "host defines no dist tag")
        top = os.path.join(self.workdir, "distprobe")
        for sub in ("SOURCES", "SPECS", "BUILD", "BUILDROOT", "RPMS", "SRPMS"):
            os.makedirs(os.path.join(top, sub))
        spec = os.path.join(top, "SPECS", "probe.spec")
        with open(spec, "w") as f:
            f.write("%{!?release: %define release 1}\n"
                    "%define debug_package %{nil}\n"
                    "Name: distprobe\nVersion: 1.0\nRelease: %{release}%{?dist}\n"
                    "Summary: t\nLicense: MIT\n"
                    "ExclusiveArch: i386 i486 i586 i686 x86_64 ia64 ppc ppc64 "
                    "ppc64le arm64 aarch64 s390x\n"
                    "%description\nt\n"
                    "%install\nmkdir -p %{buildroot}/usr/share/distprobe\n"
                    "echo hi > %{buildroot}/usr/share/distprobe/f\n"
                    "%files\n/usr/share/distprobe\n")
        _run("rpmbuild --define '_topdir {}' --define 'release 9.gABC' -bb {} 2>&1"
             .format(top, spec), timeout=300)
        built = []
        for root, _, files in os.walk(os.path.join(top, "RPMS")):
            built += files
        if not built:
            return self._record("dist_not_doubled", "SKIP", "probe build produced nothing")
        doubled = [f for f in built if f.count(self.dist) > 1]
        if doubled:
            return self._record("dist_not_doubled", "FAIL",
                                "dist doubled: {}".format(doubled[0]))
        return self._record("dist_not_doubled", "PASS",
                            "{} carries one {}".format(built[0], self.dist))

    def no_trailing_test_exit(self):
        """A `[[ ... ]] && cmd` as a function's last line silently breaks set -e.

        The test is false, the function returns 1, and set -e aborts a build that
        actually succeeded. Mid-function the same pattern is fine and is the
        file's established style.
        """
        with open(BUILD_SDK) as f:
            lines = f.read().splitlines()
        offenders = []
        for i, line in enumerate(lines):
            if line.strip() != "}":
                continue
            for j in range(i - 1, max(-1, i - 4), -1):
                prev = lines[j].strip()
                if not prev or prev.startswith("#"):
                    continue
                if re.match(r"^\[\[ .* \]\] &&", prev):
                    offenders.append("{}:{}".format(j + 1, prev[:50]))
                break
        if offenders:
            return self._record("no_trailing_test_exit", "FAIL", "; ".join(offenders))
        return self._record("no_trailing_test_exit", "PASS",
                            "no function ends in a bare [[ ]] &&")

    def deb_tree_untouched(self):
        """build_sdk.sh must edit only its throwaway copy of debian-sdk/.

        Checked after every --deb invocation has run.
        """
        fmt = os.path.join(REPO_ROOT, "debian-sdk", "source", "format")
        with open(fmt) as f:
            content = f.read().strip()
        if content != "3.0 (native)":
            return self._record("deb_tree_untouched", "FAIL",
                                "source/format is now {!r}".format(content))
        rc, out = _run("cd {} && git status --porcelain debian-sdk/".format(REPO_ROOT))
        if rc == 0 and out.strip():
            return self._record("deb_tree_untouched", "FAIL",
                                "debian-sdk/ modified: {}".format(out.strip()[:80]))
        return self._record("deb_tree_untouched", "PASS", "3.0 (native) preserved")

    # -- stubbed behaviour -------------------------------------------------
    def rpm_invocations(self):
        """Drive build_sdk.sh against a stub rpmbuild and inspect the calls.

        Costs milliseconds, so it can assert what a real build cannot cheaply
        re-run: that --rpm alone makes one -bb call and no -bs call, that
        --rpm-source adds the -bs call before the expensive -bb, that only the
        -bs call suppresses the dist tag, and that --rpm-source implies --rpm.
        """
        binroot = _make_stub_bin(self.workdir, "rpmstub")
        log = os.path.join(binroot, "rpmbuild.log")
        outdir = os.path.join(self.workdir, "stubout")

        def calls_for(flags):
            if os.path.exists(log):
                os.remove(log)
            shutil.rmtree(outdir, ignore_errors=True)
            rc, out = _run(
                "cd {} && PATH={}:$PATH RPMBUILD_LOG={} TMPDIR={} "
                "./build_sdk.sh {} --rpm-name {} --rpm-release {} --rpm-output {} 2>&1"
                .format(REPO_ROOT, binroot, log, self.workdir, flags,
                        TEST_NAME, TEST_RELEASE, outdir),
                timeout=600)
            lines = []
            if os.path.exists(log):
                with open(log) as f:
                    lines = [ln.strip() for ln in f if ln.strip()]
            produced = sorted(os.listdir(outdir)) if os.path.isdir(outdir) else []
            return rc, out, lines, produced

        rc, out, lines, produced = calls_for("--rpm")
        if rc != 0:
            return self._record("rpm_invocations", "FAIL", "plain --rpm exited {}".format(rc))
        if len(lines) != 1 or " -bb " not in lines[0] + " ":
            return self._record("rpm_invocations", "FAIL",
                                "plain --rpm made {} call(s)".format(len(lines)))
        if any(f.endswith(".src.rpm") for f in produced):
            return self._record("rpm_invocations", "FAIL",
                                "plain --rpm emitted a source package")

        # --rpm-source alone must imply --rpm.
        rc, out, lines, produced = calls_for("--rpm-source")
        if rc != 0:
            return self._record("rpm_invocations", "FAIL",
                                "--rpm-source alone exited {}".format(rc))
        if len(lines) != 2:
            return self._record("rpm_invocations", "FAIL",
                                "--rpm-source made {} call(s), want 2".format(len(lines)))
        if " -bs " not in lines[0] + " ":
            return self._record("rpm_invocations", "FAIL",
                                "-bs must run before -bb; got {}".format(lines[0][:70]))
        if " -bb " not in lines[1] + " ":
            return self._record("rpm_invocations", "FAIL", "second call is not -bb")
        if "--define dist %{nil}" not in lines[0]:
            return self._record("rpm_invocations", "FAIL", "-bs does not suppress dist")
        if "--define dist" in lines[1]:
            return self._record("rpm_invocations", "FAIL", "-bb must keep the host dist")
        if "--nodeps" not in lines[0]:
            return self._record("rpm_invocations", "FAIL", "-bs missing --nodeps")
        for call in lines:
            if _define_of(call, "release") != TEST_RELEASE:
                return self._record("rpm_invocations", "FAIL",
                                    "release {!r}".format(_define_of(call, "release")))
            if _define_of(call, "name") != TEST_NAME:
                return self._record("rpm_invocations", "FAIL", "name not forwarded")
        # Both artifacts must reach --rpm-output.
        want = {"{}-{}-{}.src.rpm".format(TEST_NAME, self.version, TEST_RELEASE),
                "{}-{}-{}.elX.{}.rpm".format(TEST_NAME, self.version, TEST_RELEASE, _arch())}
        if set(produced) != want:
            return self._record("rpm_invocations", "FAIL",
                                "collected {}, want {}".format(produced, sorted(want)))
        return self._record("rpm_invocations", "PASS",
                            "-bs(no dist) then -bb; both collected")

    def deb_invocations(self):
        """Drive the DEB leg against a stub dpkg-buildpackage.

        dpkg tooling is absent from RPM build hosts, so this is the only DEB
        coverage there. Asserts the build flag, the quilt switch, the changelog
        and control rewrites, the orig tarball, and that --deb-source implies
        --deb.
        """
        binroot = _make_stub_bin(self.workdir, "debstub")
        log = os.path.join(binroot, "dpkg.log")
        outdir = os.path.join(self.workdir, "debstubout")
        full = "{}-{}".format(self.version, TEST_RELEASE)

        def run_deb(flags):
            if os.path.exists(log):
                os.remove(log)
            shutil.rmtree(outdir, ignore_errors=True)
            rc, out = _run(
                "cd {} && PATH={}:$PATH DPKG_LOG={} TMPDIR={} "
                "./build_sdk.sh {} --deb-name {} --deb-version {} --deb-output {} 2>&1"
                .format(REPO_ROOT, binroot, log, self.workdir, flags,
                        TEST_NAME, full, outdir),
                timeout=1800)
            produced = sorted(os.listdir(outdir)) if os.path.isdir(outdir) else []
            return rc, out, _parse_log(log), produced

        rc, out, rec, produced = run_deb("--deb")
        if rc != 0:
            return self._record("deb_invocations", "FAIL",
                                "plain --deb exited {}".format(rc))
        if rec.get("args", [""])[0].split()[0] != "-b":
            return self._record("deb_invocations", "FAIL",
                                "plain --deb passed {!r}".format(rec.get("args")))
        if rec.get("format", [""])[0] != "3.0 (native)":
            return self._record("deb_invocations", "FAIL",
                                "plain --deb changed the source format")
        if any(f.endswith(".dsc") for f in produced):
            return self._record("deb_invocations", "FAIL",
                                "plain --deb emitted a source package")

        # --deb-source alone must imply --deb.
        rc, out, rec, produced = run_deb("--deb-source")
        if rc != 0:
            return self._record("deb_invocations", "FAIL",
                                "--deb-source alone exited {}".format(rc))
        if rec.get("args", [""])[0].split()[0] != "-F":
            return self._record("deb_invocations", "FAIL",
                                "--deb-source passed {!r}, want -F".format(rec.get("args")))
        if rec.get("format", [""])[0] != "3.0 (quilt)":
            return self._record("deb_invocations", "FAIL",
                                "source format {!r}, want quilt".format(rec.get("format")))
        if rec.get("control", [""])[0] != TEST_NAME:
            return self._record("deb_invocations", "FAIL",
                                "control Source: {!r}".format(rec.get("control")))
        if not rec.get("changelog", [""])[0].startswith("{} ({})".format(TEST_NAME, full)):
            return self._record("deb_invocations", "FAIL",
                                "changelog {!r}".format(rec.get("changelog")))
        if "debian" in rec.get("origtop", [""])[0].split(","):
            return self._record("deb_invocations", "FAIL",
                                "orig tarball contains debian/, corrupting the quilt diff")
        want = ["{}_{}.debian.tar.xz".format(TEST_NAME, full),
                "{}_{}.dsc".format(TEST_NAME, full),
                "{}_{}.orig.tar.gz".format(TEST_NAME, self.version),
                "{}_{}_{}.deb".format(TEST_NAME, full, _deb_arch())]
        missing = [w for w in want if w not in produced]
        if missing:
            return self._record("deb_invocations", "FAIL",
                                "missing {}; got {}".format(missing, produced))
        return self._record("deb_invocations", "PASS",
                            "-b/-F, quilt, all 4 deb artifacts collected")

    # -- real build --------------------------------------------------------
    def rpm_build(self):
        if not self.do_build:
            return self._record("rpm_build", "SKIP", "--no-build")
        if not _have("rpmbuild"):
            return self._record("rpm_build", "SKIP", "rpmbuild not installed")
        os.makedirs(self.rpm_out)
        cmd = ("cd {} && TMPDIR={} ./build_sdk.sh --rpm --rpm-source "
               "--rpm-name {} --rpm-release {} --rpm-output {}"
               .format(REPO_ROOT, self.workdir, TEST_NAME, TEST_RELEASE, self.rpm_out))
        print("  {}[CMD]{} {}".format(BLUE, RESET, cmd))
        rc, out = _run(cmd, timeout=3600)
        if rc != 0:
            missing = _missing_build_deps(out)
            if missing:
                return self._record("rpm_build", "SKIP",
                                    "machine lacks build deps: {}".format(missing[:90]))
            tail = "; ".join(out.strip().splitlines()[-3:])[:160]
            return self._record("rpm_build", "FAIL", "rc={} {}".format(rc, tail))
        return self._record("rpm_build", "PASS", "binary + source")

    def rpm_artifacts(self):
        """Both artifacts land with exactly the names the acceptance criteria give."""
        if _no_output(self.rpm_out):
            return self._record("rpm_artifacts", "SKIP", "no rpm build")
        want_bin = "{}-{}-{}{}.{}.rpm".format(
            TEST_NAME, self.version, TEST_RELEASE, self.dist, _arch())
        want_src = "{}-{}-{}.src.rpm".format(TEST_NAME, self.version, TEST_RELEASE)
        present = sorted(os.listdir(self.rpm_out))
        missing = [w for w in (want_bin, want_src) if w not in present]
        if missing:
            return self._record("rpm_artifacts", "FAIL",
                                "missing {}; got {}".format(missing, present))
        self.binary_rpm = os.path.join(self.rpm_out, want_bin)
        self.source_rpm = os.path.join(self.rpm_out, want_src)
        return self._record("rpm_artifacts", "PASS", "{} + {}".format(want_bin, want_src))

    def rpm_identity(self):
        """Binary and source agree on Name/Version; Release differs by the dist tag."""
        if not self.source_rpm:
            return self._record("rpm_identity", "SKIP", "no rpm artifacts")
        fmt = "%{NAME}|%{VERSION}|%{RELEASE}"
        rc_b, bin_hdr = _run("rpm -qp --qf '{}' {}".format(fmt, self.binary_rpm))
        rc_s, src_hdr = _run("rpm -qp --qf '{}' {}".format(fmt, self.source_rpm))
        if rc_b != 0 or rc_s != 0:
            return self._record("rpm_identity", "FAIL", "rpm -qp failed")
        bn, bv, br = bin_hdr.strip().split("|")
        sn, sv, sr = src_hdr.strip().split("|")
        if (bn, bv) != (sn, sv) or bn != TEST_NAME:
            return self._record("rpm_identity", "FAIL",
                                "binary {}-{} vs source {}-{}".format(bn, bv, sn, sv))
        if sr != TEST_RELEASE:
            return self._record("rpm_identity", "FAIL", "srpm release {}".format(sr))
        if br != TEST_RELEASE + self.dist:
            return self._record("rpm_identity", "FAIL", "binary release {}".format(br))
        return self._record("rpm_identity", "PASS",
                            "{} bin={} src={}".format(bn, br, sr))

    def srpm_no_dist(self):
        """The source-repo contract: one SRPM per name, with no .elN/.al8 suffix."""
        if not self.source_rpm:
            return self._record("srpm_no_dist", "SKIP", "no rpm artifacts")
        if not self.dist:
            return self._record("srpm_no_dist", "SKIP", "host defines no dist tag")
        rc, rel = _run("rpm -qp --qf '%{{RELEASE}}' {}".format(self.source_rpm))
        if self.dist in rel.strip():
            return self._record("srpm_no_dist", "FAIL",
                                "srpm release {} carries {}".format(rel.strip(), self.dist))
        if self.dist not in os.path.basename(self.binary_rpm):
            return self._record("srpm_no_dist", "FAIL", "binary lost its dist tag")
        return self._record("srpm_no_dist", "PASS",
                            "src={} bin carries {}".format(rel.strip(), self.dist))

    def srpm_contents(self):
        """The SRPM must carry the spec and the matching source tarball."""
        if not self.source_rpm:
            return self._record("srpm_contents", "SKIP", "no rpm artifacts")
        rc, out = _run("rpm -qlp {}".format(self.source_rpm))
        if rc != 0:
            return self._record("srpm_contents", "FAIL", "rpm -qlp failed")
        files = out.split()
        want_tar = "mstflint-{}.tar.gz".format(self.version)
        if want_tar not in files or not any(f.endswith(".spec") for f in files):
            return self._record("srpm_contents", "FAIL", "got {}".format(files))
        return self._record("srpm_contents", "PASS", " + ".join(sorted(files)))

    def deb_build(self):
        if not self.do_build:
            return self._record("deb_build", "SKIP", "--no-build")
        if not _have("dpkg-buildpackage"):
            return self._record("deb_build", "SKIP", "dpkg-buildpackage not installed")
        os.makedirs(self.deb_out)
        cmd = ("cd {} && TMPDIR={} ./build_sdk.sh --deb --deb-source "
               "--deb-name {} --deb-version {}-{} --deb-output {}"
               .format(REPO_ROOT, self.workdir, TEST_NAME, self.version,
                       TEST_RELEASE, self.deb_out))
        print("  {}[CMD]{} {}".format(BLUE, RESET, cmd))
        rc, out = _run(cmd, timeout=3600)
        if rc != 0:
            missing = _missing_build_deps(out)
            if missing:
                return self._record("deb_build", "SKIP",
                                    "machine lacks build deps: {}".format(missing[:90]))
            tail = "; ".join(out.strip().splitlines()[-3:])[:160]
            return self._record("deb_build", "FAIL", "rc={} {}".format(rc, tail))
        return self._record("deb_build", "PASS", "binary + source")

    def deb_artifacts(self):
        """.deb, .dsc, .orig.tar.* and .debian.tar.* must all reach --deb-output."""
        if _no_output(self.deb_out):
            return self._record("deb_artifacts", "SKIP", "no deb build")
        present = sorted(os.listdir(self.deb_out))
        full = "{}-{}".format(self.version, TEST_RELEASE)
        missing = []
        if not any(f.startswith("{}_{}_".format(TEST_NAME, full)) and f.endswith(".deb")
                   for f in present):
            missing.append("{}_{}_<arch>.deb".format(TEST_NAME, full))
        for pat, label in (("{}_{}.dsc".format(TEST_NAME, full), None),
                           ("{}_{}.orig.tar.".format(TEST_NAME, self.version), "orig"),
                           ("{}_{}.debian.tar.".format(TEST_NAME, full), "debian")):
            if not any(f.startswith(pat) for f in present):
                missing.append(pat + ("*" if label else ""))
        if missing:
            return self._record("deb_artifacts", "FAIL",
                                "missing {}; got {}".format(missing, present))
        return self._record("deb_artifacts", "PASS", "{} files".format(len(present)))

    def _dsc(self):
        """Path of the produced .dsc, or None."""
        if not os.path.isdir(self.deb_out):
            return None
        for f in sorted(os.listdir(self.deb_out)):
            if f.endswith(".dsc"):
                return os.path.join(self.deb_out, f)
        return None

    def deb_source_identity(self):
        """The .dsc Format/Source/Version must match the binary package."""
        dsc = self._dsc()
        if not dsc:
            return self._record("deb_source_identity", "SKIP", "no .dsc")
        with open(dsc) as f:
            body = f.read()
        want = "{}-{}".format(self.version, TEST_RELEASE)
        fields = {}
        for key in ("Format", "Source", "Version"):
            m = re.search(r"^{}:\s*(.+?)\s*$".format(key), body, re.M)
            fields[key] = m.group(1) if m else None
        if fields["Format"] != "3.0 (quilt)":
            return self._record("deb_source_identity", "FAIL",
                                "Format: {}".format(fields["Format"]))
        if fields["Source"] != TEST_NAME:
            return self._record("deb_source_identity", "FAIL",
                                "Source: {}".format(fields["Source"]))
        if fields["Version"] != want:
            return self._record("deb_source_identity", "FAIL",
                                "Version: {}".format(fields["Version"]))
        return self._record("deb_source_identity", "PASS",
                            "{} {} {}".format(fields["Format"], TEST_NAME, want))

    def deb_dsc_checksums(self):
        """Every file the .dsc lists must exist with the recorded size and hash.

        A .dsc whose checksums do not match its tarballs is accepted by a
        filename check but rejected by apt and by dpkg-source -x.
        """
        dsc = self._dsc()
        if not dsc:
            return self._record("deb_dsc_checksums", "SKIP", "no .dsc")
        import hashlib
        with open(dsc) as f:
            body = f.read()
        algos = [("Checksums-Sha256", hashlib.sha256),
                 ("Checksums-Sha1", hashlib.sha1),
                 ("Files", hashlib.md5)]
        checked = 0
        for field, fn in algos:
            m = re.search(r"^{}:\n((?:[ \t].*\n)+)".format(field), body, re.M)
            if not m:
                continue
            for line in m.group(1).strip().splitlines():
                digest, size, name = line.split()
                path = os.path.join(self.deb_out, name)
                if not os.path.isfile(path):
                    return self._record("deb_dsc_checksums", "FAIL",
                                        "{} lists missing file {}".format(field, name))
                with open(path, "rb") as fh:
                    actual = fn(fh.read()).hexdigest()
                if actual != digest:
                    return self._record("deb_dsc_checksums", "FAIL",
                                        "{} mismatch on {}".format(field, name))
                if str(os.path.getsize(path)) != size:
                    return self._record("deb_dsc_checksums", "FAIL",
                                        "{} size mismatch on {}".format(field, name))
                checked += 1
        if not checked:
            return self._record("deb_dsc_checksums", "FAIL", "no checksum fields in .dsc")
        return self._record("deb_dsc_checksums", "PASS", "{} entries verified".format(checked))

    def deb_tarball_split(self):
        """The upstream/packaging split must be clean.

        .debian.tar.* holds only debian/, and the orig tarball holds none of it;
        otherwise the quilt diff is corrupt even though both files exist.
        """
        if _no_output(self.deb_out):
            return self._record("deb_tarball_split", "SKIP", "no deb build")
        names = os.listdir(self.deb_out)
        deb_tar = next((f for f in names if ".debian.tar." in f), None)
        orig_tar = next((f for f in names if ".orig.tar." in f), None)
        if not deb_tar or not orig_tar:
            return self._record("deb_tarball_split", "SKIP", "tarballs not produced")
        rc, out = _run("tar tf {} | cut -d/ -f1 | sort -u"
                       .format(os.path.join(self.deb_out, deb_tar)))
        tops = [t for t in out.split() if t]
        if rc != 0 or tops != ["debian"]:
            return self._record("deb_tarball_split", "FAIL",
                                "{} top-level: {}".format(deb_tar, tops))
        rc, out = _run("tar tf {} | cut -d/ -f2 | sort -u"
                       .format(os.path.join(self.deb_out, orig_tar)))
        if "debian" in out.split():
            return self._record("deb_tarball_split", "FAIL",
                                "{} contains debian/".format(orig_tar))
        return self._record("deb_tarball_split", "PASS",
                            "debian/ only in {}".format(deb_tar))

    def deb_orig_clean(self):
        """The orig tarball must not carry packaging output from an earlier run.

        --deb-output defaults to the repo root, so without excludes the previous
        run's .deb/.dsc/.debian.tar.xz get staged into the next run's upstream
        tarball and shipped as if they were source.
        """
        if _no_output(self.deb_out):
            return self._record("deb_orig_clean", "SKIP", "no deb build")
        orig = next((f for f in os.listdir(self.deb_out) if ".orig.tar." in f), None)
        if not orig:
            return self._record("deb_orig_clean", "SKIP", "no orig tarball")
        rc, out = _run("tar tf {}".format(os.path.join(self.deb_out, orig)))
        if rc != 0:
            return self._record("deb_orig_clean", "FAIL", "cannot list orig tarball")
        bad = [m for m in out.split()
               if re.search(r"\.(deb|dsc|changes|buildinfo|rpm)$", m)
               or re.search(r"\.tar\.(gz|xz|bz2)$", m)]
        if bad:
            return self._record("deb_orig_clean", "FAIL",
                                "{} packaging artifact(s), e.g. {}".format(len(bad), bad[0]))
        return self._record("deb_orig_clean", "PASS", "no packaging artifacts")

    def deb_source_roundtrip(self):
        """dpkg-source -x must reassemble the source package into a usable tree.

        This is the operation a source repo's consumers actually perform, and it
        re-verifies the checksums as a side effect.
        """
        dsc = self._dsc()
        if not dsc:
            return self._record("deb_source_roundtrip", "SKIP", "no .dsc")
        if not _have("dpkg-source"):
            return self._record("deb_source_roundtrip", "SKIP", "dpkg-source not installed")
        xdir = os.path.join(self.workdir, "xtract")
        shutil.rmtree(xdir, ignore_errors=True)
        os.makedirs(xdir)
        rc, out = _run("cd {} && dpkg-source -x {} 2>&1".format(xdir, dsc), timeout=600)
        if rc != 0:
            return self._record("deb_source_roundtrip", "FAIL",
                                out.strip().splitlines()[-1][:120] if out.strip() else "rc={}".format(rc))
        trees = [d for d in os.listdir(xdir) if os.path.isdir(os.path.join(xdir, d))]
        if len(trees) != 1:
            return self._record("deb_source_roundtrip", "FAIL",
                                "extracted {} trees".format(len(trees)))
        tree = os.path.join(xdir, trees[0])
        for rel in ("debian/rules", "debian/control", "build_sdk.sh", "configure.ac"):
            if not os.path.isfile(os.path.join(tree, rel)):
                return self._record("deb_source_roundtrip", "FAIL",
                                    "extracted tree missing {}".format(rel))
        with open(os.path.join(tree, "debian", "changelog")) as f:
            head = f.readline().strip()
        want = "{} ({}-{})".format(TEST_NAME, self.version, TEST_RELEASE)
        if not head.startswith(want):
            return self._record("deb_source_roundtrip", "FAIL",
                                "changelog {!r}".format(head))
        return self._record("deb_source_roundtrip", "PASS", "extracts to {}".format(trees[0]))

    def deb_binary_metadata(self):
        """The .deb control fields must match the source package identity."""
        if _no_output(self.deb_out):
            return self._record("deb_binary_metadata", "SKIP", "no deb build")
        debs = [f for f in os.listdir(self.deb_out) if f.endswith(".deb")]
        if not debs:
            return self._record("deb_binary_metadata", "SKIP", "no .deb")
        if not _have("dpkg-deb"):
            return self._record("deb_binary_metadata", "SKIP", "dpkg-deb not installed")
        path = os.path.join(self.deb_out, debs[0])
        rc, out = _run("dpkg-deb -f {} Package Version".format(path))
        if rc != 0:
            return self._record("deb_binary_metadata", "FAIL", "dpkg-deb -f failed")
        got = dict(l.split(": ", 1) for l in out.strip().splitlines() if ": " in l)
        want = "{}-{}".format(self.version, TEST_RELEASE)
        if got.get("Package") != TEST_NAME or got.get("Version") != want:
            return self._record("deb_binary_metadata", "FAIL",
                                "{} {}".format(got.get("Package"), got.get("Version")))
        rc, out = _run("dpkg-deb -c {}".format(path))
        if "libmstflint_sdk.so" not in out:
            return self._record("deb_binary_metadata", "FAIL", "no libmstflint_sdk.so in payload")
        return self._record("deb_binary_metadata", "PASS",
                            "{} {} + payload".format(got["Package"], got["Version"]))

    # -- driver ------------------------------------------------------------
    def run(self):
        print("=" * 70)
        print("SOURCE PACKAGE TESTS  version={} dist={} arch={}".format(
            self.version, self.dist or "(none)", _arch()))
        print("workdir={}  build={}".format(self.workdir, self.do_build))
        print("=" * 70)
        steps = [
            self.flags_present, self.spec_release_dist, self.dist_not_doubled,
            self.no_trailing_test_exit,
            self.rpm_invocations, self.deb_invocations,
            self.rpm_build, self.rpm_artifacts, self.rpm_identity,
            self.srpm_no_dist, self.srpm_contents,
            self.deb_build, self.deb_artifacts, self.deb_source_identity,
            self.deb_dsc_checksums, self.deb_tarball_split, self.deb_orig_clean,
            self.deb_source_roundtrip, self.deb_binary_metadata,
            self.deb_tree_untouched,
        ]
        try:
            for step in steps:
                step()
        finally:
            self._summary()
        return 0 if all(s != "FAIL" for s in self.results.values()) else 1

    def _summary(self):
        print("\n" + "=" * 60 + "\nSOURCE PACKAGE TEST SUMMARY\n" + "=" * 60)
        for name, status in self.results.items():
            print("  {}: {}".format(name, status))
        failed = [n for n, s in self.results.items() if s == "FAIL"]
        print("=" * 60 + "\nOverall: " + (
            "ALL TESTS PASSED" if not failed else "SOME TESTS FAILED") +
            "\n" + "=" * 60)


def print_usage():
    print(__doc__)


def main():
    do_build = True
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
        elif a == "--no-build":
            do_build = False
        elif a == "--keep":
            keep = True
        elif a == "--workdir":
            i += 1
            workdir = args[i] if i < len(args) else None
        elif a == "--so":
            so_mode = True
        elif a == "-d":
            i += 1  # accepted and ignored: this suite needs no device
        elif a in ("--compare", "--compare-all", "--coverage", "--sdk-only"):
            pass  # accepted and ignored: the extension always appends these
        elif a == "--verbose":
            verbose = True
        elif a == "--build":
            print("{}[ERROR] source-package tests only support --so{}".format(RED, RESET))
            return 1
        else:
            print("{}[ERROR] unknown argument: {}{}".format(RED, a, RESET))
            return 1
        i += 1

    if not so_mode:
        print("{}[ERROR] source-package tests require --so{}".format(RED, RESET))
        return 1
    if not os.path.isfile(BUILD_SDK):
        print("{}[ERROR] build_sdk.sh not found at {}{}".format(RED, BUILD_SDK, RESET))
        return 1

    # /data/tmp, never the system temp dir: an SDK rpmbuild does not fit in /tmp.
    # Test writability, not just existence -- /data/tmp is root-owned on some hosts.
    if workdir is None:
        root = os.environ.get("SDKV_TMP_ROOT", "/data/tmp")
        if not (os.path.isdir(root) and os.access(root, os.W_OK)):
            root = os.path.expanduser("~")
        workdir = os.path.join(root, "sdkv_source_pkg_test")
    if os.path.isdir(workdir):
        shutil.rmtree(workdir)
    os.makedirs(workdir)

    try:
        return SourcePackageSuite(workdir, do_build, verbose).run()
    finally:
        if keep:
            print("[INFO] kept workdir: {}".format(workdir))
        else:
            shutil.rmtree(workdir, ignore_errors=True)


if __name__ == "__main__":
    sys.exit(main())
