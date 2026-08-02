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
configure.ac warns when the compiler's major version is below 9, because from
January 2027 mstflint is built as C++17 (PR #1832). This checks it fires on
exactly the right versions.

Three ways that check can be silently wrong: `-dumpversion` prints "4.8.5"
before GCC 7 and a bare "8" after; a lexical compare would call "13" < "9" and
warn on most of the fleet; and `test "" -lt 9` is a shell error on a compiler
that does not answer -dumpversion at all.

So the block is extracted verbatim from configure.ac into a micro configure.ac,
autoconf'd, and run against stub compilers -- the real post-m4 shell, about a
second per version instead of minutes for a full ./configure. Offline: no
device, no sudo, no installed package.

Usage: ./test_configure_compiler_warning.py --so
"""

from __future__ import print_function
import os
import re
import shutil
import subprocess
import sys

MIN_MAJOR = 9
WARN = "minimal supported GCC version will be {}".format(MIN_MAJOR)
CONFIGURE_AC = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.dirname(os.path.abspath(__file__))))), "configure.ac")

# What `CC -dumpversion` prints. Expected outcome is derived from the rule
# (major < 9), never written per row, so the table cannot drift from it.
VERSIONS = ["4.8.5", "6.3.0", "7", "8", "8.5.0", "9", "9.3.0", "10", "13", "16", "20"]

# Compilers that answer nothing useful: none may warn, none may error.
HOSTILE = ["", "   ", "apple-clang-15", "gcc\n8"]

GREEN, RED, RESET = "\033[92m", "\033[91m", "\033[0m"
fails = []


def check(name, ok, detail=""):
    print("  {:24s}: {}{}{}{}".format(name, GREEN if ok else RED,
                                      "PASS" if ok else "FAIL", RESET,
                                      "  ({})".format(detail) if detail else ""))
    if not ok:
        fails.append(name)


def run(cmd, cwd=None):
    p = subprocess.Popen(cmd, shell=True, cwd=cwd,
                         stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    out = p.communicate()[0].decode("utf-8", errors="replace")
    return p.returncode, out


def build_harness(workdir):
    """Micro configure.ac wrapping the block verbatim; returns the built script."""
    block = re.search(r"^CC_MAJOR_VER=.*?\n(?:.*\n)*?.*?\]\)\]\)\s*?\n",
                      open(CONFIGURE_AC).read(), re.M)
    check("block_present", bool(block), CONFIGURE_AC)
    if not block:
        return None
    os.makedirs(workdir)
    open(os.path.join(workdir, "block.m4"), "w").write(block.group(0))
    open(os.path.join(workdir, "configure.ac"), "w").write(
        "AC_INIT([warncheck],[0])\n"
        "AC_ARG_VAR([CC],[C compiler])\n"
        'test -n "${CC}" || CC=cc\n'
        "m4_include([block.m4])\n"
        "AC_OUTPUT\n")
    rc, out = run("autoconf -o configure configure.ac", cwd=workdir)
    ok = rc == 0 and os.path.isfile(os.path.join(workdir, "configure"))
    check("harness_build", ok, out.strip()[:100])
    return workdir if ok else None


def stub(workdir, name, prints):
    """A fake compiler. Scans every argument, not just $1: by this point in
    configure AC_PROG_CC has appended the standard flag, so CC is
    `gcc -std=gnu11` and -dumpversion arrives second."""
    path = os.path.join(workdir, name)
    # Concatenated, not .format()'d: the shell body is full of braces.
    open(path, "w").write(
        "#!/bin/sh\n"
        'for a in "$@"; do\n'
        '  [ "$a" = "-dumpversion" ] && { printf \'%s\\n\' \''
        + prints.replace("'", "'\\''") + "'; exit 0; }\n"
        "done\nexit 0\n")
    os.chmod(path, 0o755)
    return path


def warns_with(harness, cc):
    rc, out = run("./configure CC={}".format(cc), cwd=harness)
    return (WARN in out), rc


def main():
    args = sys.argv[1:]
    if "--help" in args or "-h" in args:
        print(__doc__)
        return 0
    if "--so" not in args:
        print("{}[ERROR] this suite requires --so{}".format(RED, RESET))
        return 1

    root = os.environ.get("SDKV_TMP_ROOT", "/data/tmp")
    if not (os.path.isdir(root) and os.access(root, os.W_OK)):
        root = os.path.expanduser("~")
    work = os.path.join(root, "sdkv_configure_warning_test")
    shutil.rmtree(work, ignore_errors=True)

    cc = os.environ.get("CC") or "gcc"
    rc, out = run("{} -dumpversion 2>/dev/null".format(cc))
    host = out.strip().split(".")[0] if rc == 0 else ""
    print("configure warning: threshold GCC {}, host {} reports {!r}".format(
        MIN_MAJOR, cc, host))

    try:
        harness = build_harness(os.path.join(work, "h"))
        if not harness:
            return 1

        bad = []
        for v in VERSIONS:
            want = int(v.split(".")[0]) < MIN_MAJOR
            got, rc = warns_with(harness, stub(harness, "cc_" + v.replace(".", "_"), v))
            if got != want or rc != 0:
                bad.append("{}: warn={} want={} rc={}".format(v, int(got), int(want), rc))
        check("version_matrix", not bad,
              "; ".join(bad) or "{} versions, boundary at {}".format(len(VERSIONS), MIN_MAJOR))

        bad = []
        for i, v in enumerate(HOSTILE + [None]):
            # None = a CC that is not on the machine at all
            path = os.path.join(harness, "missing") if v is None \
                else stub(harness, "cc_odd{}".format(i), v)
            got, rc = warns_with(harness, path)
            if got or rc != 0:
                bad.append("{!r}: warn={} rc={}".format(v, int(got), rc))
        check("odd_compilers", not bad,
              "; ".join(bad) or "{} quiet, rc=0".format(len(HOSTILE) + 1))

        if host.isdigit():
            got, rc = warns_with(harness, cc)
            want = int(host) < MIN_MAJOR
            check("host_compiler", got == want and rc == 0,
                  "{} major {} -> {}".format(cc, host, "warns" if got else "quiet"))
    finally:
        shutil.rmtree(work, ignore_errors=True)

    print("Overall: " + ("ALL TESTS PASSED" if not fails
                         else "FAILED: " + ", ".join(fails)))
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main())
