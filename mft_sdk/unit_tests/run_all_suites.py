#!/usr/bin/env python3
# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

"""Run every comparison suite against ONE installed SDK and ONE built harness.

Each suite runs the way op-info does: the C column, the C++ column and the
reference CLI are executed and compared field by field. Nothing here builds or
installs -- `make prepare` does that once, and every suite reuses its output.

A single runner names the C, C++ and CLI binaries once, so no suite can be
pointed at the wrong binary and compare against an empty column.

Usage:
    ./run_all_suites.py -d 0000:21:00.0            # all suites
    ./run_all_suites.py -d <bdf> --only mlxreg     # one group
    ./run_all_suites.py -d <bdf> --json out.json   # machine-readable

Exit status: 0 only if every suite passed or was legitimately skipped.
"""

import argparse
import json
import os
import re
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))

# (group, driver relative to HERE). Order is cheapest-first so a broken install
# surfaces on a fast suite rather than after the slow ones.
SUITES = [
    ("mlxreg", "mlxreg/test_register_list.py"),
    ("mlxreg", "mlxreg/test_metadata.py"),
    ("mlxreg", "mlxreg/test_register_access.py"),
    ("mlxreg", "mlxreg/test_error_handling.py"),
    ("mlxreg", "mlxreg/test_full_path.py"),
    ("mlxlink", "mlxlink/test_operational_info.py"),
    ("mlxlink", "mlxlink/test_counters.py"),
    ("mlxlink", "mlxlink/test_fec_histogram.py"),
    ("mlxlink", "mlxlink/test_module_info.py"),
    ("mlxlink", "mlxlink/test_cable_ddm.py"),
]

ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")

# The suites do not share one summary format; each regex below matches a real
# verdict line emitted by at least one driver.
#
#   op_info                         "Summary: 7 fields match, 0 fields differ"
#   counters, module_info           "Match summary: 54 compared, 54 match, 0 differ"
#   register_list                   "Summary: 207 total, 207 common, 0 SDK-only, ..."
#   register_access, per register   "Summary: 40 compared, 39 match, 1 differ"
#   metadata/register_access/...    "Overall: ALL TESTS PASSED"
FIELDS_RE = re.compile(r"Summary:\s*(\d+)\s+fields?\s+match(?:es)?,\s*(\d+)\s+fields?\s+differ", re.I)
MATCH_RE = re.compile(r"Match summary:\s*(\d+)\s+compared,\s*(\d+)\s+match,\s*(\d+)\s+differ", re.I)
REGLIST_RE = re.compile(r"Summary:\s*(\d+)\s+total,\s*(\d+)\s+common,\s*(\d+)\s+SDK-only,\s*(\d+)\s+\S+-only", re.I)
REGTABLE_RE = re.compile(r"^Summary:\s*(\d+)\s+compared,\s*(\d+)\s+match,\s*(\d+)\s+differ", re.M | re.I)
OVERALL_PASS_RE = re.compile(r"^Overall:\s*ALL TESTS PASSED", re.M | re.I)
OVERALL_FAIL_RE = re.compile(r"^Overall:.*(FAIL|FAILED)", re.M | re.I)
# utils.py's per-device FINAL SUMMARY block, which several drivers print INSTEAD
# of an "Overall:" line -- the only verdict cable_ddm and fec_histogram emit.
SUMMARY_RE = re.compile(r"Passed:\s*(\d+)\s*$\s*Failed:\s*(\d+)\s*$\s*Skipped:\s*(\d+)", re.M)

# Device/link state that makes a suite genuinely inapplicable. These are NOT
# failures: the SDK and the CLI agree the data is unavailable.
#
# Keep the phrases anchored: a bare "SKIP" match would hit the "`mst` not
# installed - skipping" banner that every suite prints.
UNAVAILABLE_RE = re.compile(
    r"not supported on this device"
    r"|is valid with active link operation only"
    r"|No plugged cable detected"
    r"|All runners returned an error"
    r"|No module (?:plugged|detected)"
    r"|link is down",
    re.I)

# The marker utils.announce_device_not_answering() prints when a suite FAILED
# because the device answered no register access at all -- device state, so
# name it rather than a bare "driver exited 1".
NOT_ANSWERING_RE = re.compile(r"^DEVICE NOT ANSWERING: \S+: (.*)$", re.M)


def required_env():
    """Fail loudly on a half-configured environment rather than testing nothing."""
    missing = [k for k in ("MFT_SDK_SO_DIR", "MFT_SDK_SO_TEST_BIN", "MFT_SDK_C_SO_TEST_BIN")
               if not os.environ.get(k)]
    if missing:
        sys.exit("error: missing %s\n       run: eval \"$(make print-env)\"" % ", ".join(missing))

    for k in ("MFT_SDK_SO_TEST_BIN", "MFT_SDK_C_SO_TEST_BIN"):
        p = os.environ[k]
        if not os.path.isfile(p):
            sys.exit("error: %s=%s does not exist\n       run: make unified" % (k, p))

    # utils.py defaults to MFT's mlxreg_ext/mlxlink_ext, so on a machine that
    # also carries MFT an unset env would compare the mstflint SDK against the
    # wrong CLI.
    for k, want in (("MFT_SDK_LINK_TOOL", "mstlink"), ("MFT_SDK_REG_TOOL", "mstreg")):
        v = os.environ.get(k, "")
        if not v:
            sys.exit("error: %s is unset; utils.py would fall back to an MFT tool.\n"
                     "       run: eval \"$(make print-env)\"" % k)
        if os.path.basename(v) != want:
            sys.exit("error: %s=%s is not %s.\n"
                     "       The SDK must be compared against mstflint's own CLI, not MFT's."
                     % (k, v, want))
        if not os.path.isfile(v):
            sys.exit("error: %s=%s does not exist; run `make prepare`" % (k, v))


def classify(rc, out):
    """pass / skip / fail. A skip must never masquerade as a pass, and an
    unavailable feature must never masquerade as a failure."""
    out = ANSI_RE.sub("", out)

    # A real difference is a failure regardless of anything else in the output.
    m = FIELDS_RE.search(out)
    if m:
        match, differ = int(m.group(1)), int(m.group(2))
        if differ:
            return "fail", "%d match, %d DIFFER" % (match, differ)
        if match:
            return "pass", "%d fields match, 0 differ" % match

    m = MATCH_RE.search(out)
    if m:
        compared, match, differ = (int(m.group(i)) for i in (1, 2, 3))
        if differ:
            return "fail", "%d compared, %d DIFFER" % (compared, differ)
        if compared:
            return "pass", "%d compared, %d match, 0 differ" % (compared, match)
        # 0 compared means every field was masked out -- the port has nothing to
        # report. Legitimate, but it must read as a skip, never as a pass.
        return "skip", "0 fields comparable (all masked -- link state)"

    m = REGLIST_RE.search(out)
    if m:
        total, common, sdk_only, cli_only = (int(m.group(i)) for i in range(1, 5))
        if sdk_only or cli_only:
            return "fail", "%d SDK-only, %d CLI-only of %d" % (sdk_only, cli_only, total)
        return "pass", "%d registers, all common" % total

    # register_access prints one table summary per register: a register that
    # differs is a real difference even when a later one found the device
    # not answering.
    differ = sum(int(m.group(3)) for m in REGTABLE_RE.finditer(out))
    if differ:
        return "fail", "%d register field(s) DIFFER" % differ

    # After the real-difference checks above, before the generic verdicts.
    if NOT_ANSWERING_RE.search(out) and (rc != 0 or OVERALL_FAIL_RE.search(out)):
        return "fail", "device not answering"

    if OVERALL_FAIL_RE.search(out):
        return "fail", "driver reported FAILED"
    if OVERALL_PASS_RE.search(out):
        return "pass", "ALL TESTS PASSED"

    # FINAL SUMMARY counters and the exit code must be checked before the
    # device-state phrases below: cable_ddm with no cable prints "No plugged
    # cable detected" and "Failed: 1" together, and the failure has to win.
    m = SUMMARY_RE.search(out)
    if m:
        npass, nfail, nskip = (int(m.group(i)) for i in (1, 2, 3))
        if nfail:
            return "fail", "%d passed, %d FAILED, %d skipped" % (npass, nfail, nskip)
        if npass:
            return "pass", "%d device(s) passed, %d skipped" % (npass, nskip)
        if nskip:
            return "skip", "%d device(s) skipped, none comparable" % nskip
    # Exit codes follow BaseTestSuite's RESULT_* (utils.py): 0 PASS, 1 FAIL,
    # 2 SKIP. 2 means "nothing to compare here", not a crash.
    if rc == 2:
        return "skip", "driver reported SKIP (nothing comparable)"
    if rc != 0:
        return "fail", "driver exited %d" % rc

    # No verdict line and a clean exit. Only now is device state allowed to
    # explain what happened.
    if UNAVAILABLE_RE.search(out):
        why = UNAVAILABLE_RE.search(out).group(0)
        return "skip", why[:40].strip()

    if rc == 0:
        return "fail", "exit 0 but no verdict line -- nothing was compared"
    return "fail", "exit %d, no verdict line" % rc


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("-d", "--device", required=True, help="PCI BDF, e.g. 0000:21:00.0")
    ap.add_argument("--only", help="run one group only: mlxreg | mlxlink")
    ap.add_argument("--json", help="write machine-readable results here")
    ap.add_argument("--timeout", type=int, default=900, help="per-suite timeout (s)")
    args = ap.parse_args()

    required_env()

    suites = [s for s in SUITES if not args.only or s[0] == args.only]
    print("=" * 78)
    print("mstflint SDK -- %d comparison suites against ONE installed SDK" % len(suites))
    print("  device   %s" % args.device)
    print("  SDK      %s" % os.environ["MFT_SDK_SO_DIR"])
    print("  C++      %s" % os.environ["MFT_SDK_SO_TEST_BIN"])
    print("  C        %s" % os.environ["MFT_SDK_C_SO_TEST_BIN"])
    print("  ref CLI  %s / %s" % (os.environ["MFT_SDK_LINK_TOOL"], os.environ["MFT_SDK_REG_TOOL"]))
    print("=" * 78)

    results = []
    for group, rel in suites:
        name = os.path.basename(rel)[len("test_"):-len(".py")]
        cmd = [sys.executable, os.path.join(HERE, rel), "--compare", "-d", args.device, "--so"]
        t0 = time.time()
        try:
            p = subprocess.run(cmd, capture_output=True, text=True, timeout=args.timeout)
            out, rc = p.stdout + p.stderr, p.returncode
        except subprocess.TimeoutExpired:
            out, rc = "", 124
        verdict, detail = ("fail", "timeout") if rc == 124 else classify(rc, out)
        dt = time.time() - t0
        mark = {"pass": "PASS", "skip": "SKIP", "fail": "FAIL"}[verdict]
        print("  %-4s %-18s %-34s %5.1fs" % (mark, name, detail, dt))
        results.append({"group": group, "suite": name, "verdict": verdict,
                        "detail": detail, "seconds": round(dt, 1), "output": out})

    npass = sum(1 for r in results if r["verdict"] == "pass")
    nskip = sum(1 for r in results if r["verdict"] == "skip")
    nfail = sum(1 for r in results if r["verdict"] == "fail")
    print("=" * 78)
    print("TOTAL: %d passed, %d skipped, %d failed (of %d)" % (npass, nskip, nfail, len(results)))
    print("=" * 78)

    if args.json:
        with open(args.json, "w") as fh:
            json.dump({"device": args.device, "passed": npass, "skipped": nskip,
                       "failed": nfail, "results": results}, fh, indent=2)
        print("wrote %s" % args.json)

    for r in results:
        if r["verdict"] == "fail":
            print("\n--- %s ---\n%s" % (r["suite"], r["output"][-2000:]))

    return 1 if nfail else 0


if __name__ == "__main__":
    sys.exit(main())
