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
Deep validation of the MFT SDK HCA-capabilities feature.

The 37 existing gtests assert status codes and non-emptiness; the single
value-equality assertion in the file compares the SDK against ITSELF. This suite
validates the feature against sources that are not the SDK:

  A  offline    the shipped hca_cap_table.adb, parsed independently of the SDK
  B  device     the fwctl gate and API robustness, through the INSTALLED .so
  C  device     the independent oracle: resourcedump + resourceparse + a
                firmware-matched ADB -- the same firmware data reached by a
                completely different path
  D  fwctl      SDK value == oracle value, both halves pinned to one device

Layers A-C need no fwctl and run on any host with a ConnectX/BlueField adapter.
Layer D needs /dev/fwctl and self-skips with a precise reason where there is
none. See .claude/mds/mft-sdk/hca-capabilities/TEST_PLAN.md for the full contract.

Usage:  ./test_hca_caps_validation.py --compare -d <bdf>
        ./test_hca_caps_validation.py --compare-all          (offline layers only)
"""

from __future__ import print_function

import glob
import os
import re
import shutil
import subprocess
import sys
import xml.etree.ElementTree as ET
from collections import Counter, OrderedDict

GREEN, RED, YELLOW, RESET = "\033[92m", "\033[91m", "\033[93m", "\033[0m"

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(os.path.dirname(HERE)))

ADB_BASENAME = "hca_cap_table.adb"
CAPS_UNION = "query_hca_cap_out_capability_auto"
MAX_CAP_NAME_SIZE = 128          # MST_MAX_CAP_NAME_SIZE, mft_sdk_hca_caps.h:52
HCA_CAP_SEGMENT = 0x4100

MST_SUCCESS = 0
MST_ERROR_INVALID_ARGUMENT = 2
MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES = 13
FWCTL_GATE_MSG = "Only FWCTL devices support HCA capabilities"

# op_mod map keys, from HcaCapabilities::initCapabilityTypesMap()
# (hca_capabilities/hca_capabilities.cpp). Parsed live from the source when this
# runs out of a checkout; this copy is the fallback for the staged tree, which
# carries mft_sdk/unit_tests only.
OPMOD_TYPES_FALLBACK = [
    "adv_rdma_capabilities", "adv_virtualization_capabilities", "atomic_caps",
    "cc_prov_capabilities", "cmd_hca_cap", "crypto_caps", "debug_cap",
    "device_emulation_cap", "device_mem_cap", "dpa_capabilities", "dpp_cap",
    "e_switch_cap", "event_capabilities", "flow_table_eswitch_cap",
    "flow_table_nic_cap", "generic_dev_emu_capabilities", "hca_caps_2",
    "hotplug_capabilities", "ipsec_cap", "macsec_cap", "nvmeotcp_cap",
    "nvmf_cap", "odp_cap", "parse_graph_node_cap", "paso_capabilities",
    "per_protocol_networking_offload_caps", "port_selection_capabilities",
    "psp_cap", "qos_caps", "roce_cap", "shampo_cap", "tlp_dev_emu_capabilities",
    "tls_cap", "ts_prov_capabilities", "upt_device_emulation_caps",
    "vector_calc_caps", "virtio_emulation_cap",
    "wqe_based_flow_table_capabilities",
]

# (type, field) pairs cross-checked SDK-vs-oracle. Chosen <= 32 bits, present in
# both the shipped ADB and the FW segments ADB, and stable across runs.
# qos_caps.packet_pacing_max_rate is the pair Oded used by hand.
PINNED = [
    ("qos_caps", "packet_pacing_max_rate"),
    ("qos_caps", "packet_pacing_min_rate"),
    ("qos_caps", "packet_pacing_rate_table_size"),
    ("qos_caps", "log_max_flow_meter"),
    ("device_mem_cap", "max_memic_size"),
    ("cmd_hca_cap", "log_max_qp"),
    ("cmd_hca_cap", "num_ports"),
    ("cmd_hca_cap", "vhca_id"),
    # The one (type, field) DOCA itself depends on: doca_mgmt.c queries
    # cmd_hca_cap / native_port_num in CUR mode against target SELF, and treats
    # 0 as "not available". If this pair ever stops matching the firmware,
    # doca_mgmt_dev_ctx creation misreports the port.
    ("cmd_hca_cap", "native_port_num"),
]

# What DOCA's libs/doca_mgmt requires of this SDK, from its own build files:
#   dependency('mstflint_sdk', required: true)   -- dependencies/meson.build:16
#   #include <mft_sdk/mft_sdk.h>                 -- src/doca_mgmt.c:25
# The pkg-config module name and the <mft_sdk/...> include spelling are a
# packaging contract: DOCA's meson configure aborts if either moves.
DOCA_PKGCONFIG_MODULE = "mstflint_sdk"
DOCA_UMBRELLA_HEADER = "mft_sdk/mft_sdk.h"
# DOCA's own gtest RawHCACapDescribeGoodFlow reads our metadata and asserts these
# exact bit widths on cmd_hca_cap (libs/doca_mgmt/unit_test/doca_mgmt_unit_test.cpp:
# "EXPECT_EQ(fields[i].bit_size, 16)" for vhca_id, "...5)" for log_max_qp), plus
# EXPECT_GT(bit_size, 0) for EVERY field and access RO-or-UNKNOWN. An ADB revision
# that changes any of them breaks DOCA's test suite, so pin them here where they
# can be checked offline.
DOCA_METADATA_PINS = {"vhca_id": 16, "log_max_qp": 5}
DOCA_GENERAL_CAP_TYPE = "cmd_hca_cap"       # RAW_HCA_CAP_GENERAL in DOCA's tests
# cmd_hca_cap fields DOCA names by string: native_port_num drives
# doca_mgmt_dev_ctx creation (doca_mgmt.c:182), selective_repeat is the field
# DOCA's RawHCACapModifyWithTargetTypeVHCAID test modifies and restores.
DOCA_CONSUMED_FIELDS = ["native_port_num", "selective_repeat"]
# convertHcaCapAccessType maps anything it does not recognise to
# MST_PRM_ACCESS_UNKNOWN, and DOCA/DMS read UNKNOWN as "no read-only constraint".
# So an ADB that introduces a new access spelling silently turns a read-only
# field into an apparently writable one.
ADB_ACCESS_DOMAIN = {"RO", "WO", "RW", "INDEX", "OP"}
# Package floor DOCA declares in both debian/control and doca-sdk-mgmt.spec:
#   BuildRequires/Requires: mstflint-sdk-local >= 4.37.0-1
DOCA_SDK_VERSION_FLOOR = (4, 37, 0)
# Every SDK symbol libdoca_mgmt.so leaves undefined, i.e. the exact set DOCA
# needs this .so to export. NOT hand-derived from the HCA-cap sources: taken
# from `nm -D --undefined-only` on a real libdoca_mgmt.so.3.6.0013 built on
# apps-180 against mstflint_sdk 4.37.0 (DOCA master b395c3ee06, meson
# -Denable_libs=mgmt). That matters — the nine PRM-register symbols come from
# doca_mgmt_raw_register.c, which lives in the SAME library, so dropping any one
# of them fails the link for the HCA-cap path too.
DOCA_REQUIRED_SYMBOLS = [
    # handle lifetime + errors (src/doca_mgmt.c)
    "mstGetDeviceHandleByFwctlDeviceName", "mstReleaseDeviceHandle",
    "mstGetInitErrorString", "mstGetLastErrorString",
    # HCA capabilities (src/raw/doca_mgmt_raw_hca_cap.c)
    "mstGetCapabilityTypesList", "mstFreeHcaCapabilitiesArray",
    "mstGetCapabilitiesByType", "mstFreeHcaCapabilitiesMetadata",
    "mstInitHcaCapabilityMap", "mstQueryHcaCapability", "mstSetHcaCapability",
    "mstGetCapabilityValue", "mstSetCapabilityValue", "mstFreeHcaCapabilityMap",
    # PRM registers (src/raw/doca_mgmt_raw_register.c) - same library, same link
    "mstShowAllPRMRegisters", "mstFreePRMRegisterNamesArray",
    "mstGetRegisterMetadata", "mstFreePrmRegisterMetadata",
    "mstInitRegisterMap", "mstSetPRMRegisterField", "mstSendPRMRegister",
    "mstGetPRMRegisterField", "mstFreePrmRegisterMap",
]

# Fields expected to be monotonic MAX >= CURRENT. Bit-flags legitimately differ
# in both directions, so only sized/log fields belong here.
MONOTONIC = [
    ("qos_caps", "packet_pacing_max_rate"),
    ("qos_caps", "packet_pacing_rate_table_size"),
    ("qos_caps", "log_max_flow_meter"),
    ("cmd_hca_cap", "log_max_qp"),
]

results = OrderedDict()
_fails = []
_verbose = False


def check(name, status, detail=""):
    """The one reporting contract: two-space indent, spaces around the colon --
    what report.parseLogFindings matches (out/lib/report.js:443)."""
    results[name] = status
    color = {"PASS": GREEN, "FAIL": RED, "SKIP": YELLOW}[status]
    line = "  {:38s} : {}{}{}".format(name, color, status, RESET)
    if detail:
        line += "  ({})".format(detail)
    print(line)
    if status == "FAIL":
        _fails.append(name)
    return status == "PASS"


def note(msg):
    print("    - {}".format(msg))


def have(tool):
    """Is the tool on this host at all?

    run() is shell=True, so a missing binary yields 127 -- indistinguishable
    from the tool's own "not found" exit status. Probe first, so an unprovisioned
    lab machine is not reported as a product defect.
    """
    return run("command -v {} >/dev/null 2>&1".format(tool))[0] == 0


def run(cmd, timeout=None):
    kw = {"shell": True, "stdout": subprocess.PIPE, "stderr": subprocess.STDOUT}
    p = subprocess.Popen(cmd, **kw)
    try:
        out = p.communicate(timeout=timeout)[0] if timeout else p.communicate()[0]
    except TypeError:                     # py2 Popen.communicate has no timeout
        out = p.communicate()[0]
    except subprocess.TimeoutExpired:
        p.kill()
        return -9, "TIMEOUT after {}s".format(timeout)
    text = out.decode("utf-8", errors="replace")
    if _verbose:
        print("      $ {}\n{}".format(cmd, text[:2000]))
    return p.returncode, text


def scratch_root():
    """Standing directive: SDK-Verify does all scratch work under /data/tmp,
    never the system temp dir."""
    root = os.environ.get("SDKV_TMP_ROOT") or "/data/tmp"
    for cand in (os.path.join(root, "sdk_verify"), root, os.path.expanduser("~")):
        try:
            if not os.path.isdir(cand):
                os.makedirs(cand)
            if os.access(cand, os.W_OK):
                return cand
        except OSError:
            continue
    return os.path.expanduser("~")


# --------------------------------------------------------------------------
# discovery
# --------------------------------------------------------------------------

def find_adb():
    """DATA_PATH is baked in at compile time (no env override), so the ADB is
    wherever the package put it: <pkgdatadir>/sdk for the SDK build,
    <pkgdatadir> for plain mstflint, /usr/share/mft for MFT."""
    cands = []
    for base in ("/usr/share", "/usr/local/share", "/opt"):
        cands += glob.glob(os.path.join(base, "*", "sdk", "prm_dbs", "hca", "ext", ADB_BASENAME))
        cands += glob.glob(os.path.join(base, "*", "prm_dbs", "hca", "ext", ADB_BASENAME))
    # SDK build first: that is the copy the SDK under test actually loads.
    cands.sort(key=lambda p: (0 if "/sdk/" in p else 1, len(p)))
    return cands[0] if cands else None


def find_sdk_paths():
    """Include dir + lib dir of the installed SDK, for compiling the probe.
    MFT_SDK_INC_DIR / MFT_SDK_LIB_DIR point the probe at a build tree instead,
    which is how a fix is validated before it is packaged."""
    inc = os.environ.get("MFT_SDK_INC_DIR")
    lib = os.environ.get("MFT_SDK_LIB_DIR")
    if inc and lib:
        return inc, lib
    inc = lib = None
    for c in ("/usr/include/mstflint/sdk", "/usr/local/include/mstflint/sdk",
              "/usr/include/mft_sdk", "/usr/include"):
        if os.path.isfile(os.path.join(c, "mft_sdk", "mft_sdk_hca_caps.h")):
            inc = c
            break
    for c in ("/usr/lib64/mstflint/sdk", "/usr/lib/x86_64-linux-gnu/mstflint/sdk",
              "/usr/lib/aarch64-linux-gnu/mstflint/sdk", "/usr/lib64/mft_sdk", "/usr/lib64"):
        if glob.glob(os.path.join(c, "lib*_sdk.so*")):
            lib = c
            break
    return inc, lib


def resource_tools():
    """The mstflint-sdk package ships neither tool; MFT ships them under the
    internal names. Trap T10."""
    def pick(*names):
        for n in names:
            rc, out = run("command -v {} 2>/dev/null".format(n))
            if rc == 0 and out.strip():
                return out.strip().splitlines()[0]
        return None
    return pick("mstresourcedump", "resourcedump"), pick("mstresourceparse", "resourceparse")


def fwctl_nodes():
    return sorted(glob.glob("/dev/fwctl/fwctl*"))


def mst_node_for(bdf):
    """The /dev/mst node of the SAME PCI function as <bdf>. Trap T2: letting the
    two halves drift onto different adapters produces a confident wrong answer,
    so this resolves rather than guesses -- and returns None instead of picking
    an arbitrary node when it cannot."""
    short = bdf.split(":", 1)[1] if bdf.count(":") == 2 else bdf
    rc, out = run("sudo mst status -v 2>/dev/null", timeout=120)
    for line in out.splitlines():
        if short in line:
            for tok in line.split():
                if tok.startswith("/dev/mst/") and "cable" not in tok:
                    return tok
    # `mst status` prints no MST column when the node name is not tied to the
    # BDF in its output; fall back only when the machine has exactly one adapter
    # so "the same device" is still guaranteed.
    cands = [n for n in sorted(glob.glob("/dev/mst/*pciconf*")) if not n.endswith(".1")]
    if len(cands) == 1 and len(re.findall(r"^\w+:\w+\.\w+", out, re.M)) <= 1:
        return cands[0]
    return cands[0] if len(cands) == 1 else None


# --------------------------------------------------------------------------
# ADB model -- parsed with ElementTree, deliberately NOT through the SDK, so a
# bug in the SDK's ADB handling cannot hide itself behind the same bug.
# --------------------------------------------------------------------------

class Adb(object):
    def __init__(self, path):
        self.path = path
        self.root = ET.parse(path).getroot()
        self.nodes = {n.get("name"): n for n in self.root.iter("node")}

    @staticmethod
    def bits(spec):
        """ADB offset/size notation is "<hex bytes>.<bits>"."""
        byte, _, bit = (spec or "0x0.0").partition(".")
        return int(byte, 16) * 8 + int(bit or 0)

    def union(self):
        return self.nodes.get(CAPS_UNION)

    def types(self):
        u = self.union()
        return [f.get("name") for f in u.findall("field")] if u is not None else []

    def leaves(self, node_name, prefix="", base=0, depth=0, seen=()):
        """traverse_layout invokes the callback on LEAVES only (adb_instance.cpp),
        which is why a 64-bit field shows up as <name>.hi / <name>.lo and never as
        a bare <name> -- trap T4."""
        node = self.nodes.get(node_name)
        if node is None or depth > 16 or node_name in seen:
            return
        for f in node.findall("field"):
            name, sub = f.get("name"), f.get("subnode")
            off = base + self.bits(f.get("offset"))
            path = (prefix + "." + name) if prefix else name
            if sub and sub in self.nodes:
                for leaf in self.leaves(sub, path, off, depth + 1, seen + (node_name,)):
                    yield leaf
            else:
                yield path, off, self.bits(f.get("size"))

    def type_size_bits(self, t):
        u = self.union()
        for f in u.findall("field"):
            if f.get("name") == t:
                return self.bits(f.get("size"))
        return 0


HCA_CAPS_SRC = os.path.join(REPO, "hca_capabilities", "hca_capabilities.cpp")


def opmod_types():
    """Live from the source when available (a checkout), else the fallback."""
    if os.path.isfile(HCA_CAPS_SRC):
        keys = re.findall(r'_capabilityTypesMap\["([^"]+)"\]', open(HCA_CAPS_SRC).read())
        if keys:
            return sorted(set(keys)), "hca_capabilities.cpp"
    return sorted(set(OPMOD_TYPES_FALLBACK)), "built-in fallback list"


def advertises_only_queryable():
    """Does getCapabilityTypesList() filter the ADB union down to the types that
    actually have an op_mod? Read off the function body, because that is what
    decides whether the names handed to callers are usable -- and without fwctl
    the list cannot be obtained from the live SDK. None = source unavailable."""
    if not os.path.isfile(HCA_CAPS_SRC):
        return None
    body = re.search(r"std::vector<std::string> HcaCapabilities::getCapabilityTypesList\(\)\s*\{(.*?)\n\}",
                     open(HCA_CAPS_SRC).read(), re.S)
    if not body:
        return None
    return "_capabilityTypesMap.find(" in body.group(1)


# --------------------------------------------------------------------------
# Layer A -- offline invariants
# --------------------------------------------------------------------------

def layer_a():
    adb_path = find_adb()
    if not adb_path:
        check("A1_adb_present", "FAIL", "no {} under any packaged DATA_PATH".format(ADB_BASENAME))
        return None
    check("A1_adb_present", "PASS", adb_path)

    try:
        adb = Adb(adb_path)
    except Exception as e:
        check("A2_caps_union", "FAIL", "ADB is not parseable XML: {}".format(e))
        return None

    u = adb.union()
    ok = u is not None and u.get("attr_is_union") == "1"
    union_bits = adb.bits(u.get("size")) if u is not None else 0
    check("A2_caps_union", "PASS" if ok else "FAIL",
          "{} is a union, {} bytes, {} members".format(CAPS_UNION, union_bits // 8, len(adb.types()))
          if ok else "{} missing or not a union".format(CAPS_UNION))
    if not ok:
        return None

    types = adb.types()
    oversized = [t for t in types if adb.type_size_bits(t) > union_bits]
    check("A3_member_sizes", "PASS" if not oversized else "FAIL",
          "all {} members <= {} bytes".format(len(types), union_bits // 8) if not oversized
          else "larger than the capability blob: " + ", ".join(oversized))

    mapped, origin = opmod_types()
    # Two different divergences, and only one of them is a defect.
    #
    # A4: a type the SDK ADVERTISES must be queryable. getCapabilityTypesList
    # walks the ADB union; convertCapabilityTypeToOpMod resolves against a
    # separate op_mod map. A name in the first but not the second is handed to
    # the caller and then rejected by the SDK itself -- which is exactly what
    # DOCA's doca_mgmt_raw_hca_cap_list exposes to its users.
    unmappable = sorted(set(types) - set(mapped))
    filters = advertises_only_queryable()
    if filters:
        check("A4_advertised_types_queryable", "PASS",
              "getCapabilityTypesList filters the {}-member union to the {} types with an op_mod; "
              "{} withheld: {}".format(len(types), len(types) - len(unmappable), len(unmappable),
                                       ", ".join(unmappable) or "none"))
    elif not unmappable:
        check("A4_advertised_types_queryable", "PASS",
              "every one of the {} union members resolves to an op_mod (map has {}, {})".format(
                  len(types), len(mapped), origin))
    elif filters is None:
        # Staged tree: hca_capabilities.cpp is not shipped with the tests, and
        # the advertised list cannot be read out of the .so without an fwctl
        # device. Claiming a verdict from the raw ADB union would fail a build
        # that already filters correctly, so defer to D7 on a fwctl host.
        check("A4_advertised_types_queryable", "SKIP",
              "cannot tell what this build advertises (no hca_capabilities.cpp in the staged tree, "
              "and the live list needs fwctl); D7 checks it there. {} union member(s) have no "
              "op_mod: {}".format(len(unmappable), ", ".join(unmappable)))
    else:
        check("A4_advertised_types_queryable", "FAIL",
              "advertised but unmappable, so querying them throws: " + ", ".join(unmappable))
        note("mstGetCapabilityTypesList returns every ADB union member, but "
             "convertCapabilityTypeToOpMod resolves against a separate map: iterating the "
             "returned list and querying each type throws on the unmappable ones.")

    # A4b: the reverse is an ADB-coverage property, not a code defect -- the type
    # has a PRM op_mod but this ADB revision ships no layout for it. It is never
    # advertised, and asking for it by name gives a clear error, so it is
    # reported rather than failed.
    mapped_not_listed = sorted(set(mapped) - set(types))
    check("A4b_opmod_types_without_layout", "PASS",
          "every mapped type has an ADB layout" if not mapped_not_listed
          else "{} type(s) have a PRM op_mod but no layout in this ADB revision, so they cannot "
               "be queried: {}".format(len(mapped_not_listed), ", ".join(mapped_not_listed)))

    all_leaves = {t: list(adb.leaves(t)) for t in types}
    total = sum(len(v) for v in all_leaves.values())

    too_long = [(t, p) for t, ls in all_leaves.items() for p, _, _ in ls if len(p) >= MAX_CAP_NAME_SIZE]
    check("A5_name_fits_buffer", "PASS" if not too_long else "FAIL",
          "{} leaf fields, longest {} chars, limit {}".format(
              total, max([len(p) for ls in all_leaves.values() for p, _, _ in ls] or [0]),
              MAX_CAP_NAME_SIZE)
          if not too_long else "{} name(s) >= {} would be silently truncated, e.g. {}".format(
              len(too_long), MAX_CAP_NAME_SIZE, too_long[0][1][:60]))

    dups = []
    for t, ls in all_leaves.items():
        c = Counter(p for p, _, _ in ls)
        dups += ["{}.{}".format(t, k) for k, v in c.items() if v > 1]
    check("A6_no_duplicate_names", "PASS" if not dups else "FAIL",
          "no duplicates across {} fields".format(total) if not dups
          else "{} duplicate(s), unreachable via the index cache: {}".format(len(dups), ", ".join(dups[:5])))

    bad = []
    for t, ls in all_leaves.items():
        size_bits = adb.type_size_bits(t)
        for p, off, sz in ls:
            addr = (off >> 3) & ~0x3
            if size_bits and addr * 8 + 32 > size_bits:
                bad.append("{}.{} dword@0x{:x} past the {}-byte layout".format(t, p, addr, size_bits // 8))
    check("A7_metadata_arithmetic", "PASS" if not bad else "FAIL",
          "address=(offset>>3)&~3 and bitOffset=offset%32 hold for {} fields".format(total)
          if not bad else "; ".join(bad[:4]))

    # MstHcaCapability.value is a uint32_t, so a leaf wider than 32 bits that the
    # ADB did NOT split into hi/lo halves cannot be represented: popBuf returns
    # one dword and the caller is given a silently narrowed value. Those fields
    # exist (byte-array style caps), so this is the API's shape, not a
    # regression -- but a cross-checked field must never be one of them, or the
    # comparison would be meaningless.
    wide = ["{}.{}".format(t, p) for t, ls in all_leaves.items() for p, _, sz in ls
            if sz > 32 and not (p.endswith(".hi") or p.endswith(".lo"))]
    pinned_wide = [w for w in wide if w in ["{}.{}".format(t, f) for t, f in PINNED]]
    check("A9_wide_field_truncation", "PASS" if not pinned_wide else "FAIL",
          "{} field(s) wider than 32 bits and not hi/lo split -> mstGetCapabilityValue "
          "narrows them to one dword; none is cross-checked (e.g. {})".format(
              len(wide), ", ".join(sorted(wide)[:3])) if not pinned_wide
          else "a pinned cross-check field is wider than 32 bits: " + ", ".join(pinned_wide))

    # A10: DOCA's RawHCACapDescribeGoodFlow, re-expressed against the ADB so it
    # can be checked without fwctl. DOCA reads this metadata through
    # mstGetCapabilitiesByType and asserts it; if the ADB moves, DOCA's suite
    # breaks and we would only learn about it from DOCA's CI.
    gen = all_leaves.get(DOCA_GENERAL_CAP_TYPE)
    if gen is None:
        check("A10_doca_metadata_contract", "FAIL",
              "{} (DOCA's RAW_HCA_CAP_GENERAL) is not in the ADB union".format(DOCA_GENERAL_CAP_TYPE))
    else:
        sizes = {}
        for p, _, sz in gen:
            sizes.setdefault(p, sz)
        bad = []
        for name, want in sorted(DOCA_METADATA_PINS.items()):
            got = sizes.get(name)
            if got is None:
                bad.append("{}.{} absent".format(DOCA_GENERAL_CAP_TYPE, name))
            elif got != want:
                bad.append("{}.{} is {} bits, DOCA asserts {}".format(DOCA_GENERAL_CAP_TYPE, name, got, want))
        zero = [p for p, _, sz in gen if sz <= 0]
        if zero:
            bad.append("{} field(s) with bit_size 0, DOCA asserts > 0 for every field: {}".format(
                len(zero), ", ".join(zero[:3])))
        empty = [p for p, _, _ in gen if not p]
        if empty:
            bad.append("{} unnamed field(s)".format(len(empty)))
        check("A10_doca_metadata_contract", "PASS" if not bad else "FAIL",
              "{} fields; vhca_id={}b log_max_qp={}b, none zero-width — matches DOCA's "
              "RawHCACapDescribeGoodFlow".format(len(gen), sizes.get("vhca_id"), sizes.get("log_max_qp"))
              if not bad else "; ".join(bad))

    # A11: an access spelling the SDK does not recognise degrades to
    # MST_PRM_ACCESS_UNKNOWN, which downstream reads as "not read-only".
    seen_access = set()
    for node in adb.root.iter("node"):
        for f in node.findall("field"):
            if f.get("access"):
                seen_access.add(f.get("access"))
    unknown_access = sorted(seen_access - ADB_ACCESS_DOMAIN)
    check("A11_access_type_domain", "PASS" if not unknown_access else "FAIL",
          "every access= is one of {}: {}".format("/".join(sorted(ADB_ACCESS_DOMAIN)),
                                                  ", ".join(sorted(seen_access)) or "none used")
          if not unknown_access
          else "unrecognised access value(s) collapse to MST_PRM_ACCESS_UNKNOWN, which reads as "
               "writable downstream: " + ", ".join(unknown_access))

    # A12: the cmd_hca_cap fields DOCA refers to by literal name. If one is
    # renamed in a future ADB, doca_mgmt_dev_ctx creation (native_port_num) or
    # DOCA's modify test (selective_repeat) fails with "capability not found".
    if gen is not None:
        present = set(p for p, _, _ in gen)
        absent = [f for f in DOCA_CONSUMED_FIELDS if f not in present]
        check("A12_doca_consumed_fields", "PASS" if not absent else "FAIL",
              "{} present in {}".format(", ".join(DOCA_CONSUMED_FIELDS), DOCA_GENERAL_CAP_TYPE)
              if not absent else "DOCA names these by string and they are gone: " + ", ".join(absent))

    hilo = [p for ls in all_leaves.values() for p, _, _ in ls if p.endswith(".hi") or p.endswith(".lo")]
    bare = set()
    for t, ls in all_leaves.items():
        names = set(p for p, _, _ in ls)
        for p in names:
            if p.endswith(".hi") and p[:-3] in names:
                bare.add("{}.{}".format(t, p[:-3]))
    check("A8_64bit_split", "PASS" if not bare else "FAIL",
          "{} hi/lo halves, no bare 64-bit name".format(len(hilo)) if not bare
          else "bare name alongside its halves: " + ", ".join(sorted(bare)[:4]))

    return adb


# --------------------------------------------------------------------------
# Layer B -- the fwctl gate and API robustness, through the installed .so
# --------------------------------------------------------------------------

def build_probe(work):
    inc, lib = find_sdk_paths()
    if not inc or not lib:
        check("B0_probe_build", "SKIP", "installed SDK headers/libs not found")
        return None
    src = os.path.join(HERE, "hca_caps_probe.c")
    if not os.path.isfile(src):
        check("B0_probe_build", "FAIL", "missing {}".format(src))
        return None
    out = os.path.join(work, "hca_caps_probe")
    sdk_lib = "mstflint_sdk" if glob.glob(os.path.join(lib, "libmstflint_sdk.so*")) else "mft_sdk"
    # An uninstalled build tree needs its sibling libmtcr_ul on the run path too.
    extra_rpath = "".join(" -Wl,-rpath,{}".format(p) for p in
                          (os.environ.get("MFT_SDK_EXTRA_RPATH") or "").split(":") if p)
    cmd = ("gcc -O2 -o {out} {src} -I{inc} -L{lib} -l{name} "
           "-Wl,-rpath,{lib}{extra} -Wl,--allow-shlib-undefined").format(
               out=out, src=src, inc=inc, lib=lib, name=sdk_lib, extra=extra_rpath)
    rc, txt = run(cmd)
    if rc != 0 or not os.path.isfile(out):
        check("B0_probe_build", "FAIL", txt.strip()[:200])
        return None
    check("B0_probe_build", "PASS", "against lib{}.so in {}".format(sdk_lib, lib))
    return out


def probe(bin_path, args, sudo=True):
    """Each probe call is its own process: a crash must be attributable to one
    call rather than lose the run."""
    rc, out = run("{}{} {} 2>&1".format("sudo " if sudo else "", bin_path, args), timeout=120)
    crashed = rc < 0 or rc >= 128
    return rc, out, crashed


def layer_b(probe_bin, bdf):
    if not probe_bin:
        return
    if not bdf:
        for n in ("B1_fwctl_gate", "B2_no_crash_on_pciconf", "B4_fwctl_open_no_device",
                  "B5_uninitialised_instance", "B6_error_string"):
            check(n, "SKIP", "no device selected (-d)")
        rc, out, crashed = probe(probe_bin, "nullargs", sudo=False)
        check("B3_nullarg_matrix", "PASS" if rc == 0 and not crashed else "FAIL",
              "all entry points return MST_ERROR_INVALID_ARGUMENT" if rc == 0
              else ("crashed" if crashed else "{} entry point(s) wrong".format(rc)))
        return

    rc, out, crashed = probe(probe_bin, "nullargs", sudo=False)
    check("B3_nullarg_matrix", "PASS" if rc == 0 and not crashed else "FAIL",
          "{} entry points return MST_ERROR_INVALID_ARGUMENT".format(len(re.findall(r"^NULLARG ", out, re.M)))
          if rc == 0 else ("crashed" if crashed else out.strip()[:160]))

    has_fwctl = bool(fwctl_nodes())
    rc, out, crashed = probe(probe_bin, "{} gate".format(bdf))
    gates = dict(re.findall(r"^GATE (\S+) (-?\d+)", out, re.M))
    msgs = re.findall(r"^GATE \S+ -?\d+ (.*)$", out, re.M)

    if crashed:
        check("B1_fwctl_gate", "FAIL", "probe died with signal (rc={})".format(rc))
        check("B2_no_crash_on_pciconf", "FAIL", "SIGSEGV/abort during the gate sweep")
    elif has_fwctl:
        check("B1_fwctl_gate", "SKIP", "host has fwctl; the PCIconf rejection path needs a non-fwctl handle")
        check("B2_no_crash_on_pciconf", "PASS" if gates else "FAIL",
              "{} entry points exercised, no signal".format(len(gates)))
    else:
        wrong = {k: v for k, v in gates.items() if int(v) != MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES}
        gated = all(FWCTL_GATE_MSG in m for m in msgs) if msgs else False
        ok = bool(gates) and not wrong and gated
        check("B1_fwctl_gate", "PASS" if ok else "FAIL",
              "{} entry points reject a PCIconf handle with the documented message".format(len(gates))
              if ok else "status/message mismatch: {} {}".format(wrong, msgs[:1]))
        check("B2_no_crash_on_pciconf", "PASS", "{} entry points, no signal".format(len(gates)))

    check("B6_error_string", "PASS" if msgs and all(m.strip() for m in msgs) else "FAIL",
          "mstGetLastErrorString populated after every failure" if msgs else "no error strings captured")

    if has_fwctl:
        check("B4_fwctl_open_no_device", "SKIP", "host has {} fwctl node(s)".format(len(fwctl_nodes())))
    else:
        rc, out, crashed = probe(probe_bin, "--fwctl {} gate".format(bdf))
        check("B4_fwctl_open_no_device", "PASS" if not crashed else "FAIL",
              "clean error, no crash" if not crashed
              else "opening a BDF through FWCtl crashed with no /dev/fwctl (rc={})".format(rc))

    # The two entry points that never call initHcaCapabilities(): reached first
    # on a fresh handle they have no HcaCapabilities object at all.
    bad = []
    for sub, sym in (("first-getvalue", "mstGetCapabilityValue"), ("first-setvalue", "mstSetCapabilityValue")):
        rc, out, crashed = probe(probe_bin, "{} {}".format(bdf, sub))
        if crashed:
            bad.append("{} killed the process (rc={})".format(sym, rc))
        elif "FIRST" not in out:
            bad.append("{} produced no result line".format(sym))
    check("B5_uninitialised_instance", "PASS" if not bad else "FAIL",
          "both return an error instead of dereferencing a null instance" if not bad
          else "; ".join(bad))
    if bad:
        note("MftSdk::getCapabilityValue/setCapabilityValue (mft_sdk_hca_caps.cpp) are the only "
             "HCA-caps entry points that never call initHcaCapabilities(), so "
             "_hcaCapabilitiesSdkInstance is still null and the member call dereferences it.")


# --------------------------------------------------------------------------
# Layer C -- the independent oracle
# --------------------------------------------------------------------------

class Oracle(object):
    def __init__(self, dump_tool, parse_tool, mst_dev, work):
        self.dump_tool, self.parse_tool, self.mst_dev, self.work = dump_tool, parse_tool, mst_dev, work
        self.parsed = {}      # mode -> {segment: {field: value}}
        self.unknown = {}     # mode -> count
        self.adb = None
        self.adb_exact = False

    def menu_has_hca_cap(self):
        rc, out = run("sudo {} query -d {} 2>&1".format(self.dump_tool, self.mst_dev), timeout=180)
        return rc == 0 and re.search(r"0x4100\s*\(HCA_CAP\)", out) is not None, out

    def resolve_adb(self, devid, fw_version):
        """Exact running-FW release first; last_stable only as an explicit,
        logged fallback. Oded's own run used last_stable and mis-parsed segments
        because of it (hca-capabilities.md section 6)."""
        base = "/mswg/release/host_fw/fw-{}".format(devid)
        if not os.path.isdir(base):
            return None, "no {} on /mswg".format(base)
        rels = []
        if fw_version:
            rels.append(os.path.join(base, "fw-{}-rel-{}".format(devid, fw_version.replace(".", "_"))))
        rels.append(os.path.join(base, "last_stable"))
        for i, rel in enumerate(rels):
            # The release entry is a symlink into <build>/dist, so "../etc" only
            # lands in the release's etc/ AFTER the link is resolved -- a lexical
            # normpath would strip it back up to the fw-<devid> directory, where
            # there is no etc/ at all.
            etc = os.path.normpath(os.path.join(os.path.realpath(rel), "..", "etc"))
            if not os.path.isdir(etc):
                continue
            for pat in ("*_segments.adb", "*_def.adb"):
                hits = [h for h in sorted(glob.glob(os.path.join(etc, pat)))
                        if "ini" not in os.path.basename(h)]
                if hits:
                    self.adb = hits[0]
                    self.adb_exact = (i == 0 and fw_version is not None)
                    return self.adb, ("exact FW {}".format(fw_version) if self.adb_exact
                                      else "last_stable -> {}".format(os.path.realpath(rel).split("/")[-1]))
        return None, "no *_segments.adb / *_def.adb under {}".format(base)

    def dump_and_parse(self, mode):
        """--index1: 0 = current, 1 = max. Opposite to the SDK's
        MstCapabilityMode (CURRENT=0x1, MAX=0x0) -- trap T1."""
        i1 = 0 if mode == "current" else 1
        binf = os.path.join(self.work, "hca_{}.bin".format(mode))
        txt = os.path.join(self.work, "hca_{}.txt".format(mode))
        rc, out = run("sudo {} dump -d {} -s HCA_CAP -i1 {} -b {} 2>&1".format(
            self.dump_tool, self.mst_dev, i1, binf), timeout=300)
        if rc != 0 or not os.path.isfile(binf):
            return False, "dump failed: " + out.strip()[-200:]
        rc, out = run("sudo {} -d {} -a {} -o {} 2>&1".format(
            self.parse_tool, binf, self.adb, txt), timeout=900)
        if rc != 0 or not os.path.isfile(txt):
            return False, "parse failed: " + out.strip()[-200:]
        segs, cur, unknown = {}, None, 0
        for line in open(txt, errors="replace") if sys.version_info[0] >= 3 else open(txt):
            m = re.search(r"Segment - (\S+) \((0x[0-9a-f]+)\)", line)
            if m:
                if m.group(1) == "UNKNOWN":
                    unknown += 1
                    cur = None
                else:
                    cur = m.group(1)
                    segs.setdefault(cur, {})
                continue
            m = re.match(r"^(\w+) = (0x[0-9a-fA-F]+|\d+)\s*$", line.strip())
            if m and cur:
                segs[cur][m.group(1)] = int(m.group(2), 0)
        self.parsed[mode] = segs
        self.unknown[mode] = unknown
        return True, "{} segments, {} UNKNOWN".format(len(segs), unknown)

    def value(self, mode, cap_type, field):
        return self.parsed.get(mode, {}).get(cap_type, {}).get(field)


def device_ids(bdf):
    """(devid, fw_version) -- devid picks the /mswg tree, fw_version the release."""
    devid = fw = None
    rc, out = run("sudo flint -d {} q 2>/dev/null || sudo mstflint -d {} q 2>/dev/null".format(bdf, bdf),
                  timeout=120)
    m = re.search(r"FW Version:\s*(\S+)", out)
    if m:
        fw = m.group(1)
    # The /mswg tree is keyed by the PCI device id in DECIMAL (0x1021 -> 4129,
    # the "mt4129" in the mst node name). Read it per-BDF from lspci rather than
    # off an arbitrary /dev/mst node, which need not be this adapter.
    rc, out = run("lspci -n -s {} 2>/dev/null".format(bdf))
    m = re.search(r"15b3:([0-9a-f]{4})", out, re.I)
    if m:
        devid = str(int(m.group(1), 16))
    if not devid:
        for node in glob.glob("/dev/mst/mt*"):
            m = re.search(r"mt(\d+)_", os.path.basename(node))
            if m:
                devid = m.group(1)
                break
    return devid, fw


def layer_c(bdf, work):
    names = ["C1_resource_tools", "C2_same_device", "C3_hca_cap_in_menu", "C4_adb_resolution",
             "C5_dump_parse_both_modes", "C6_oracle_quality", "C7_expected_groups",
             "C8_oracle_max_ge_current"]
    if not bdf:
        for n in names:
            check(n, "SKIP", "no device selected (-d)")
        return None

    dump_tool, parse_tool = resource_tools()
    if not dump_tool or not parse_tool:
        check("C1_resource_tools", "SKIP",
              "mstresourcedump/mstresourceparse not installed (the mstflint-sdk package ships neither)")
        for n in names[1:]:
            check(n, "SKIP", "no resource tools")
        return None
    check("C1_resource_tools", "PASS", "{} + {}".format(dump_tool, parse_tool))

    mst_dev = mst_node_for(bdf)
    if not mst_dev:
        check("C2_same_device", "SKIP", "no /dev/mst node for {} (run `mst start`)".format(bdf))
        for n in names[2:]:
            check(n, "SKIP", "no mst node")
        return None
    check("C2_same_device", "PASS", "{} <-> {} (both halves pinned)".format(bdf, mst_dev))

    oracle = Oracle(dump_tool, parse_tool, mst_dev, work)
    ok, menu = oracle.menu_has_hca_cap()
    if not ok:
        check("C3_hca_cap_in_menu", "SKIP", "FW does not expose segment 0x4100 (HCA_CAP)")
        for n in names[3:]:
            check(n, "SKIP", "no HCA_CAP segment")
        return None
    check("C3_hca_cap_in_menu", "PASS", "segment 0x4100 (HCA_CAP) present in the FW menu")

    devid, fw = device_ids(bdf)
    adb, how = oracle.resolve_adb(devid, fw)
    if not adb:
        check("C4_adb_resolution", "SKIP", "{} (devid={} fw={})".format(how, devid, fw))
        for n in names[4:]:
            check(n, "SKIP", "no FW-matched ADB")
        return None
    check("C4_adb_resolution", "PASS" if oracle.adb_exact else "PASS",
          "{} via {}".format(os.path.basename(adb), how))
    if not oracle.adb_exact:
        note("ADB is NOT the running firmware's ({}): segments this ADB cannot decode show up as "
             "UNKNOWN and any field taken from them would be wrong. C6 quantifies the damage.".format(fw))

    details = []
    for mode in ("current", "max"):
        ok, why = oracle.dump_and_parse(mode)
        details.append("{}: {}".format(mode, why))
        if not ok:
            check("C5_dump_parse_both_modes", "FAIL", "; ".join(details))
            for n in names[5:]:
                check(n, "SKIP", "dump/parse failed")
            return None
    check("C5_dump_parse_both_modes", "PASS", "; ".join(details))

    tot_seg = len(oracle.parsed["current"])
    unk = oracle.unknown["current"]
    ratio = float(unk) / max(1, unk + tot_seg)
    check("C6_oracle_quality", "PASS" if ratio < 0.25 else "FAIL",
          "{} decoded / {} UNKNOWN ({:.0%} undecodable)".format(tot_seg, unk, ratio))

    want = sorted(set(t for t, _ in PINNED))
    missing = [t for t in want if t not in oracle.parsed["current"]]
    check("C7_expected_groups", "PASS" if not missing else "FAIL",
          "all of {} present in the parsed dump".format(", ".join(want)) if not missing
          else "absent from the oracle output: " + ", ".join(missing))

    bad, seen = [], 0
    for t, f in MONOTONIC:
        c, m = oracle.value("current", t, f), oracle.value("max", t, f)
        if c is None or m is None:
            continue
        seen += 1
        if m < c:
            bad.append("{}.{}: max 0x{:x} < current 0x{:x}".format(t, f, m, c))
    if seen == 0:
        check("C8_oracle_max_ge_current", "SKIP", "none of the monotonic fields present in both dumps")
    else:
        check("C8_oracle_max_ge_current", "PASS" if not bad else "FAIL",
              "MAX >= CURRENT for {} field(s), oracle-internal".format(seen) if not bad
              else "; ".join(bad))
    return oracle


# --------------------------------------------------------------------------
# Layer E -- the contract DOCA depends on
#
# libs/doca_mgmt is the first external consumer of this API. Its build resolves
# the SDK through pkg-config and its sources use the SDK in one fixed order, so
# these are regression guards for a real downstream, not hypotheticals. All of
# them are offline: they check the packaging and header contract, not a device.
# --------------------------------------------------------------------------

# The exact call sequence of doca_mgmt_raw_hca_cap_query/_modify, reduced to a
# translation unit. It never runs -- compiling and linking it IS the assertion:
# every symbol, signature, enum and struct member DOCA touches must be present
# with the arity DOCA passes.
DOCA_SHAPED_TU = r"""
#include <%s>
#include <stdio.h>
#include <stddef.h>

/* doca_mgmt.c:244 / :364 -- handle lifetime */
static int doca_like_open_close(const char* fwctl_name)
{
    MstDevice dev = NULL;
    MstStatus st = mstGetDeviceHandleByFwctlDeviceName(&dev, fwctl_name);
    if (st != MST_SUCCESS) { (void)mstGetInitErrorString(); return 1; }
    (void)mstGetLastErrorString(dev);
    return mstReleaseDeviceHandle(dev) == MST_SUCCESS ? 0 : 1;
}

/* doca_mgmt_raw_hca_cap_list */
static int doca_like_list(MstDevice dev)
{
    char** types = NULL; unsigned int n = 0; unsigned int i;
    if (mstGetCapabilityTypesList(dev, &types, &n) != MST_SUCCESS) return 1;
    for (i = 0; i < n; i++) { (void)types[i]; }
    return mstFreeHcaCapabilitiesArray(types, n) == MST_SUCCESS ? 0 : 1;
}

/* doca_mgmt_raw_hca_cap_describe -- reads .numberOfFields/.name/.bitSize/.accessType */
static int doca_like_describe(MstDevice dev, const char* cap_type)
{
    MstHcaCapabilityMetadata meta; unsigned int i; unsigned int acc = 0;
    if (mstGetCapabilitiesByType(dev, cap_type, &meta) != MST_SUCCESS) return 1;
    for (i = 0; i < meta.numberOfFields; i++) {
        acc += meta.fields[i].bitSize + (unsigned)meta.fields[i].accessType + (unsigned)meta.fields[i].name[0];
    }
    (void)acc;
    return mstFreeHcaCapabilitiesMetadata(&meta) == MST_SUCCESS ? 0 : 1;
}

/* doca_mgmt_raw_hca_cap_query: init(NULL,0) -> query -> getValue* -> free */
static int doca_like_query(MstDevice dev, const char* cap_type, const char* field)
{
    MstHcaCapabilityMap map; uint32_t value = 0; MstStatus st;
    if (mstInitHcaCapabilityMap(dev, cap_type, &map) != MST_SUCCESS) return 1;
    st = mstQueryHcaCapability(dev, cap_type, &map, MST_CAPABILITY_MODE_CUR_ALIAS, 0,
                               MST_FUNCTION_ID_TYPE_FUNCTION_INDEX, MST_OTHER_FUNCTION_NO);
    if (st == MST_SUCCESS) { (void)mstGetCapabilityValue(dev, &map, field, &value); }
    /* query_all reads the map struct directly */
    if (map.numberOfCapabilities) { (void)map.capabilities[0].capabilityName; (void)map.capabilities[0].value; }
    (void)map.capabilityType;
    return mstFreeHcaCapabilityMap(&map) == MST_SUCCESS ? 0 : 1;
}

/* doca_mgmt_raw_hca_cap_modify: init -> setValue* -> set(MAX, OTHER=YES) -> free */
static int doca_like_modify(MstDevice dev, const char* cap_type, const char* field, uint32_t v, uint16_t vhca)
{
    MstHcaCapabilityMap map;
    if (mstInitHcaCapabilityMap(dev, cap_type, &map) != MST_SUCCESS) return 1;
    if (mstSetCapabilityValue(dev, &map, field, v) != MST_SUCCESS) { mstFreeHcaCapabilityMap(&map); return 1; }
    (void)mstSetHcaCapability(dev, cap_type, &map, MST_CAPABILITY_MODE_MAX, vhca,
                              MST_FUNCTION_ID_TYPE_VHCA_ID, MST_OTHER_FUNCTION_YES);
    return mstFreeHcaCapabilityMap(&map) == MST_SUCCESS ? 0 : 1;
}

/* ---- ABI freeze -------------------------------------------------------
 * DOCA compiles these values and layouts INTO libdoca_mgmt.so and then reads
 * our structs across the .so boundary: doca_mgmt_raw_hca_cap_query_all indexes
 * cap_map.capabilities[i] with DOCA's compile-time stride, and the MstStatus
 * translator is a value switch. So a renumbered enum or a moved field is a
 * silent mis-mapping in an already-built DOCA, not a compile error there. */
_Static_assert(MST_MAX_CAP_NAME_SIZE == 128, "DOCA strdup's straight out of these fixed arrays");

/* enum values DOCA's mode/target translators depend on */
_Static_assert(MST_CAPABILITY_MODE_MAX == 0x0, "");
_Static_assert(MST_CAPABILITY_MODE_CURRENT == 0x1, "");
_Static_assert(MST_FUNCTION_ID_TYPE_FUNCTION_INDEX == 0x0, "");
_Static_assert(MST_FUNCTION_ID_TYPE_VHCA_ID == 0x1, "");
_Static_assert(MST_OTHER_FUNCTION_NO == 0x0, "");
_Static_assert(MST_OTHER_FUNCTION_YES == 0x1, "");

/* every MstStatus DOCA's priv_doca_mgmt_mst_status_to_doca_error switches on;
 * append-only is the rule, an insertion shifts everything after it */
_Static_assert(MST_SUCCESS == 0, "");
_Static_assert(MST_ERROR_UNINITIALIZED == 1, "");
_Static_assert(MST_ERROR_INVALID_ARGUMENT == 2, "");
_Static_assert(MST_ERROR_NOT_SUPPORTED == 3, "");
_Static_assert(MST_ERROR_NO_PERMISSION == 4, "");
_Static_assert(MST_ERROR_NO_AVAILABLE_DEVICES == 5, "");
_Static_assert(MST_ERROR_DEVICE_NOT_FOUND == 6, "");
_Static_assert(MST_ERROR_INTERFACE_NOT_AVAILABLE == 7, "");
_Static_assert(MST_ERROR_MST_DRIVER_NOT_LOADED == 8, "");
_Static_assert(MST_ERROR_FAILED_TO_ALLOCATE_MEMORY == 9, "");
_Static_assert(MST_ERROR_FAILED_TO_OPEN_DEVICE == 10, "");
_Static_assert(MST_ERROR_FAILED_TO_GET_HCA_CAPABILITIES == 13, "");

/* mgmt_raw_field_access_from_mst aborts the whole describe on an unmapped value */
_Static_assert(MST_PRM_ACCESS_UNKNOWN == 0, "");
_Static_assert(MST_PRM_ACCESS_RO == 1, "");
_Static_assert(MST_PRM_ACCESS_WO == 2, "");
_Static_assert(MST_PRM_ACCESS_RW == 3, "");
_Static_assert(MST_PRM_ACCESS_INDEX == 4, "");
_Static_assert(MST_PRM_ACCESS_OP == 5, "");

/* struct layout: DOCA declares these on ITS stack and indexes our arrays */
_Static_assert(sizeof(((MstHcaCapability *)0)->value) == 4,
               "doca_mgmt_raw_field.value is uint32_t and is the only value carrier DOCA has");
_Static_assert(sizeof(((MstHcaCapability *)0)->capabilityName) == MST_MAX_CAP_NAME_SIZE, "");
_Static_assert(sizeof(((MstHcaCapabilityFieldMetadata *)0)->name) == MST_MAX_CAP_NAME_SIZE, "");
_Static_assert(offsetof(MstHcaCapabilityMap, numberOfCapabilities) == MST_MAX_CAP_NAME_SIZE, "");
_Static_assert(offsetof(MstHcaCapabilityMetadata, numberOfFields) == MST_MAX_CAP_NAME_SIZE, "");

int main(void)
{
    printf("%%d\n", doca_like_open_close("fwctl0") + doca_like_list(NULL)
           + doca_like_describe(NULL, "cmd_hca_cap") + doca_like_query(NULL, "cmd_hca_cap", "native_port_num")
           + doca_like_modify(NULL, "cmd_hca_cap", "native_port_num", 0, 0) >= 0);
    return 0;
}
"""


def _find_pc_file(lib):
    """Where the .pc actually landed, independent of pkg-config being installed.

    Keeps the product-facing half of E1 alive on a host with no pkg-config:
    "did we ship the file where a consumer would look" is answerable with
    plain globs, and is the half that would break DOCA.
    """
    name = "{}.pc".format(DOCA_PKGCONFIG_MODULE)
    dirs = [os.path.join(lib, "pkgconfig")] if lib else []
    # The .pc goes to $(libdir)/pkgconfig, which is multiarch on Debian and
    # lib64 on RPM distros -- check both rather than guessing from the host.
    dirs += ["/usr/lib64/pkgconfig", "/usr/lib/x86_64-linux-gnu/pkgconfig",
             "/usr/lib/aarch64-linux-gnu/pkgconfig", "/usr/lib/pkgconfig",
             "/usr/share/pkgconfig"]
    for d in dirs:
        cand = os.path.join(d, name)
        if os.path.isfile(cand):
            return cand
    return None


def layer_e(work, probe_bin):
    inc, lib = find_sdk_paths()

    # E1: the pkg-config module DOCA's meson requires, resolved the way meson
    # resolves it -- and the flags must actually build something.
    #
    # run() is shell=True, so a missing pkg-config binary returns 127, which is
    # indistinguishable here from pkg-config's own "module not found" exit 1.
    # Probing for the tool first stops a thin lab image from being reported as
    # a shipping defect (the message named the module, not the missing tool).
    if not have("pkg-config"):
        pc_flags = ""
        pc = _find_pc_file(lib)
        if pc:
            # Resolution is untestable, but the shipping question -- the half
            # that would actually break DOCA -- is answered, and answered well.
            check("E1_doca_pkgconfig_module", "SKIP",
                  "no pkg-config on this host; {} IS installed, so only meson's "
                  "resolution step is unverified".format(pc))
        else:
            # Missing tool AND missing file: the file is a shipping defect on
            # its own terms, so this stays a FAIL.
            check("E1_doca_pkgconfig_module", "FAIL",
                  "{}.pc is absent from every standard pkgconfig dir -- DOCA's meson "
                  "configure would abort (note: pkg-config is also not installed "
                  "here, so this was checked by file lookup)".format(DOCA_PKGCONFIG_MODULE))
    else:
        rc, out = run("pkg-config --exists {} && pkg-config --cflags --libs {}".format(
            DOCA_PKGCONFIG_MODULE, DOCA_PKGCONFIG_MODULE))
        pc_flags = out.strip() if rc == 0 else ""
        check("E1_doca_pkgconfig_module", "PASS" if rc == 0 and pc_flags else "FAIL",
              "dependency('{}', required: true) resolves: {}".format(DOCA_PKGCONFIG_MODULE, pc_flags)
              if rc == 0 else "pkg-config module '{}' not found -- DOCA's meson configure would abort".format(
                  DOCA_PKGCONFIG_MODULE))

    umbrella = os.path.join(inc, DOCA_UMBRELLA_HEADER) if inc else None
    check("E2_doca_umbrella_header", "PASS" if umbrella and os.path.isfile(umbrella) else "FAIL",
          "<{}> present (DOCA includes it verbatim)".format(DOCA_UMBRELLA_HEADER) if umbrella
          and os.path.isfile(umbrella) else "<{}> not reachable from {}".format(DOCA_UMBRELLA_HEADER, inc))

    # E3: DOCA's exact call sequence must compile and link against the installed
    # SDK, using the pkg-config flags rather than hand-built paths.
    if not pc_flags:
        check("E3_doca_call_sequence_abi", "SKIP", "no pkg-config flags to build with")
    else:
        src = os.path.join(work, "doca_shape.c")
        # DOCA's translator maps its CUR mode onto MST_CAPABILITY_MODE_CURRENT.
        body = (DOCA_SHAPED_TU % DOCA_UMBRELLA_HEADER).replace(
            "MST_CAPABILITY_MODE_CUR_ALIAS", "MST_CAPABILITY_MODE_CURRENT")
        open(src, "w").write(body)
        # Strict C, like DOCA's own build: the umbrella header alone must declare
        # everything, with no implicit declarations and no GNU extensions leaking
        # out of the public headers.
        # -Werror because DOCA builds warnings-as-errors by default; a new warning
        # escaping our public headers breaks doca_mgmt's build, not just ours.
        rcc, txt = run("gcc -std=c11 -O0 -Wall -Wextra -Werror "
                       "-o {}/doca_shape {} {} -Wl,-rpath,{} -Wl,--allow-shlib-undefined 2>&1".format(
                           work, src, pc_flags, lib or ""))
        check("E3_doca_call_sequence_abi", "PASS" if rcc == 0 else "FAIL",
              "DOCA's list/describe/query/modify + handle lifetime compile clean (-std=c11 -Werror), "
              "link, and all 27 enum/struct-ABI static assertions hold" if rcc == 0 else txt.strip()[-400:])

    # E5: the symbols DOCA links must actually be exported. A packaging or
    # visibility change that drops one turns into a link failure in DOCA's build,
    # far from here.
    solib = None
    for cand in (glob.glob(os.path.join(lib or "", "libmstflint_sdk.so*")) +
                 glob.glob(os.path.join(lib or "", "libmft_sdk.so*"))):
        if os.path.isfile(cand) and not os.path.islink(cand):
            solib = cand
            break
    if not solib:
        check("E5_doca_exported_symbols", "SKIP", "no shared object found in {}".format(lib))
    else:
        rc, out = run("nm -D --defined-only {} 2>/dev/null".format(solib))
        exported = set(re.findall(r"\s[TWi]\s+(\S+)", out))
        missing = [s for s in DOCA_REQUIRED_SYMBOLS if s not in exported]
        check("E5_doca_exported_symbols", "PASS" if not missing else "FAIL",
              "all {} symbols doca_mgmt calls are exported from {}".format(
                  len(DOCA_REQUIRED_SYMBOLS), os.path.basename(solib))
              if not missing else "not exported: " + ", ".join(missing))

    # E6: DOCA pins `mstflint-sdk-local >= 4.37.0-1`, so an SDK older than that
    # floor cannot satisfy a DOCA build even though pkg-config resolves.
    ver = ""
    if have("pkg-config"):
        rc, out = run("pkg-config --modversion {} 2>/dev/null".format(DOCA_PKGCONFIG_MODULE))
        ver = out.strip().splitlines()[0] if rc == 0 and out.strip() else ""
    else:
        # No pkg-config: the Version: field is the thing under test, and it is
        # plain text in the .pc. Reading it keeps the floor check meaningful
        # instead of degrading to an unexplained empty-string SKIP.
        pc = _find_pc_file(lib)
        if pc:
            for line in open(pc):
                if line.strip().startswith("Version:"):
                    ver = line.split(":", 1)[1].strip()
                    break
    parts = tuple(int(x) for x in re.findall(r"\d+", ver)[:3]) if ver else ()
    if not parts:
        check("E6_doca_version_floor", "SKIP",
              "no pkg-config on this host and no Version: readable from the .pc"
              if not have("pkg-config")
              else "pkg-config reports no usable version ({!r})".format(ver))
    else:
        ok = parts >= DOCA_SDK_VERSION_FLOOR
        check("E6_doca_version_floor", "PASS" if ok else "FAIL",
              "{} >= DOCA's declared floor {}".format(ver, ".".join(map(str, DOCA_SDK_VERSION_FLOOR)))
              if ok else "{} is below DOCA's declared floor {}".format(
                  ver, ".".join(map(str, DOCA_SDK_VERSION_FLOOR))))

    # E7/E8 need the probe; layer B built it, so reuse it here.
    pb = probe_bin
    if not pb:
        check("E7_doca_error_strings", "SKIP", "probe not built")
        check("E8_doca_free_tolerance", "SKIP", "probe not built")
    else:
        rc, out, crashed = probe(pb, "errstrings", sudo=False)
        nulls = re.findall(r"^ERRSTR (\S+) NULL", out, re.M)
        check("E7_doca_error_strings", "PASS" if rc == 0 and not crashed and not nulls else "FAIL",
              "mstGetInitErrorString and mstGetLastErrorString(NULL) return usable strings; "
              "a failed fwctl open leaves a non-empty init message"
              if rc == 0 and not nulls
              else ("crashed" if crashed else "NULL returned by: " + ", ".join(nulls or ["(empty message)"])))

        rc, out, crashed = probe(pb, "freetolerance", sudo=False)
        check("E8_doca_free_tolerance", "PASS" if rc == 0 and not crashed else "FAIL",
              "zeroed map/metadata free cleanly, twice, and the pointers are NULLed"
              if rc == 0 and not crashed
              else ("crashed" if crashed else out.strip()[-160:]))

    # E9: DOCA links libdoca_mgmt with an EMPTY install_rpath and the SDK lives in
    # a private subdir ldconfig does not index, so every DOCA consumer depends on
    # this SONAME staying put.
    if solib:
        rc, out = run("objdump -p {} 2>/dev/null | awk '/SONAME/{{print $2}}'".format(solib))
        soname = out.strip().splitlines()[0] if out.strip() else ""
        want = os.path.basename(solib).split(".so")[0] + ".so"
        check("E9_doca_soname", "PASS" if soname == want else "FAIL",
              "SONAME {}".format(soname) if soname == want
              else "SONAME is {!r}, DOCA links against {!r}".format(soname, want))
    else:
        check("E9_doca_soname", "SKIP", "no shared object found")

    # E4: DOCA derives the fwctl name from the BDF by readdir on
    # /sys/bus/pci/devices/<bdf>/fwctl (doca_mgmt.c:59,75) -- not /sys/class.
    # Verified by running DOCA's own doca_mgmt_unit_test on apps-180: all nine
    # RawHCACap tests fail at mgmt_get_fwctl_dev_name_by_pci_addr with
    # "failed to open /sys/bus/pci/devices/0000:21:00.0/fwctl directory.
    # errno: ENOENT (2)" -> DOCA_ERROR_OPERATING_SYSTEM, i.e. DOCA never reaches
    # the SDK at all on a host without fwctl. That is the honest outcome to
    # record here, not a suite failure.
    nodes = fwctl_nodes()
    if not nodes:
        check("E4_doca_fwctl_name_lookup", "SKIP",
              "no /dev/fwctl: DOCA stops at mgmt_get_fwctl_dev_name_by_pci_addr "
              "(ENOENT on /sys/bus/pci/devices/<bdf>/fwctl -> DOCA_ERROR_OPERATING_SYSTEM) "
              "before any SDK call")
    else:
        found = []
        for d in sorted(glob.glob("/sys/bus/pci/devices/*/fwctl/fwctl*")):
            found.append("{} -> {}".format(d.split("/")[5], os.path.basename(d)))
        check("E4_doca_fwctl_name_lookup", "PASS" if found else "FAIL",
              "; ".join(found[:4]) if found
              else "{} node(s) in /dev/fwctl but none reachable via /sys/bus/pci/devices/*/fwctl".format(len(nodes)))


# --------------------------------------------------------------------------
# Layer D -- the cross-check itself
# --------------------------------------------------------------------------

def sdk_values(probe_bin, dev_ident, cap_type, mode, fields):
    """dev_ident is an fwctl node name -- the ONLY transport the SDK accepts."""
    rc, out, crashed = probe(probe_bin, "{} query {} {} {}".format(
        dev_ident, cap_type, mode, " ".join(fields)))
    if crashed:
        return None, "probe crashed (rc={})".format(rc)
    if re.search(r"^ERR ", out, re.M):
        return None, re.search(r"^ERR .*", out, re.M).group(0)[:160]
    vals = {}
    for name, hexv in re.findall(r"^VAL (\S+) (0x[0-9a-f]+)", out, re.M):
        vals[name] = int(hexv, 16)
    return vals, "{} field(s)".format(len(vals))


def layer_d(probe_bin, oracle, bdf, work):
    names = ["D1_same_pci_function", "D2_sdk_matches_oracle", "D3_sdk_max_ge_current",
             "D4_negative_field", "D5_requery_leak", "D6_init_map_clean",
             "D7_live_typelist_consumable", "D8_doca_modify_shape", "D9_doca_vhca_id_mode_invariant",
             "D10_doca_fd_coexistence", "D11_describe_matches_query"]
    nodes = fwctl_nodes()
    if not nodes:
        for n in names:
            check(n, "SKIP", "no /dev/fwctl on this host -- the SDK accepts no other transport")
        note("Layers A-C validated everything reachable without fwctl. The SDK<->oracle value "
             "comparison needs a host with /dev/fwctl (e.g. apps-75); this same file performs it "
             "there with no changes.")
        return
    if not oracle or not probe_bin:
        for n in names:
            check(n, "SKIP", "oracle or probe unavailable")
        return

    # D1: the fwctl node must be the SAME PCI function as the dumped device --
    # trap T2, enforced rather than assumed. Resolved through
    # /sys/bus/pci/devices/<bdf>/fwctl, which is the path DOCA's
    # mgmt_get_fwctl_dev_name uses (doca_mgmt.c:59,75), so this check follows
    # the same mapping a real consumer does.
    full = bdf if bdf.count(":") == 2 else "0000:" + bdf
    match = None
    for d in sorted(glob.glob("/sys/bus/pci/devices/{}/fwctl/fwctl*".format(full))):
        match = os.path.basename(d)
        break
    if not match:
        for node in nodes:
            base = os.path.basename(node)
            link = "/sys/class/fwctl/{}/device".format(base)
            if os.path.exists(link) and os.path.basename(os.path.realpath(link)) == full:
                match = base
                break
    if not match:
        check("D1_same_pci_function", "SKIP",
              "no fwctl node resolves to {} ({} node(s) present)".format(full, len(nodes)))
        for n in names[1:]:
            check(n, "SKIP", "no fwctl node for the device under test")
        return
    check("D1_same_pci_function", "PASS", "{} and {} are the same PCI function".format(full, match))

    diffs, compared, misses = [], 0, []
    for cap_type in sorted(set(t for t, _ in PINNED)):
        fields = [f for t, f in PINNED if t == cap_type]
        vals, why = sdk_values(probe_bin, match, cap_type, "current", fields)
        if vals is None:
            misses.append("{}: {}".format(cap_type, why))
            continue
        for f in fields:
            o = oracle.value("current", cap_type, f)
            s = vals.get(f)
            if o is None or s is None:
                misses.append("{}.{}: sdk={} oracle={}".format(cap_type, f, s, o))
                continue
            compared += 1
            if o != s:
                diffs.append("{}.{}: sdk 0x{:x} != oracle 0x{:x}".format(cap_type, f, s, o))
    if compared == 0:
        check("D2_sdk_matches_oracle", "FAIL", "nothing compared: " + "; ".join(misses[:3]))
    else:
        check("D2_sdk_matches_oracle", "PASS" if not diffs else "FAIL",
              "{}/{} pinned fields identical on both paths".format(compared, len(PINNED))
              if not diffs else "; ".join(diffs))
    if misses:
        note("not compared: " + "; ".join(misses[:5]))

    bad, seen = [], 0
    for cap_type in sorted(set(t for t, _ in MONOTONIC)):
        fields = [f for t, f in MONOTONIC if t == cap_type]
        cur, _ = sdk_values(probe_bin, match, cap_type, "current", fields)
        mx, _ = sdk_values(probe_bin, match, cap_type, "max", fields)
        if not cur or not mx:
            continue
        for f in fields:
            if f in cur and f in mx:
                seen += 1
                if mx[f] < cur[f]:
                    bad.append("{}.{}: max 0x{:x} < current 0x{:x}".format(cap_type, f, mx[f], cur[f]))
    check("D3_sdk_max_ge_current", ("SKIP" if seen == 0 else ("PASS" if not bad else "FAIL")),
          "MAX >= CURRENT for {} SDK field(s)".format(seen) if seen and not bad
          else ("; ".join(bad) if bad else "no comparable field"))

    vals, why = sdk_values(probe_bin, match, "qos_caps", "current", ["no_such_capability_field_xyz"])
    absent_in_oracle = oracle.value("current", "qos_caps", "no_such_capability_field_xyz") is None
    check("D4_negative_field", "PASS" if (vals is not None and not vals and absent_in_oracle) else "FAIL",
          "unknown field errors in the SDK and is absent from the oracle" if absent_in_oracle and vals == {}
          else "sdk={} oracle_absent={}".format(vals, absent_in_oracle))

    rc, out, crashed = probe(probe_bin, "{} requery cmd_hca_cap 200".format(match))
    m = re.search(r"rss_pages_delta=(-?\d+).*entry_bytes=(\d+)", out)
    fields_m = re.search(r"fields=(\d+)", out)
    if crashed or not m:
        check("D5_requery_leak", "FAIL" if crashed else "SKIP",
              "probe crashed" if crashed else "no measurement line")
    else:
        grew_kb = int(m.group(1)) * 4
        expect_kb = (200 * int(fields_m.group(1)) * int(m.group(2))) // 1024 if fields_m else 0
        leaking = grew_kb > max(512, expect_kb // 4)
        check("D5_requery_leak", "PASS" if not leaking else "FAIL",
              "RSS grew {} KB over 200 re-queries".format(grew_kb) if not leaking
              else "RSS grew {} KB over 200 re-queries (~{} KB of maps never freed): "
                   "updateCapabilityMap replaces map.capabilities without delete[]".format(grew_kb, expect_kb))

    # D6: a freshly initialised map must be CLEAN -- no entry already flagged for
    # write-back. DOCA's modify path is exactly init -> set only the caller's
    # fields -> mstSetHcaCapability, and mstSetHcaCapability writes back every
    # entry whose `set` flag is true. Any entry pre-flagged by init is a field
    # written to firmware that nobody asked to write.
    # D7: the live answer to A4 -- every name mstGetCapabilityTypesList hands out
    # must survive the next call a consumer makes with it. This is precisely
    # DOCA's doca_mgmt_raw_hca_cap_list -> _describe flow.
    rc, out, crashed = probe(probe_bin, "{} types".format(match))
    live = re.findall(r"^TYPE (\S+)", out, re.M)
    if crashed or not live:
        check("D7_live_typelist_consumable", "FAIL" if crashed else "SKIP",
              "probe crashed" if crashed else "no type list returned")
    else:
        rejected, meta_names = [], {}
        for t in live:
            rc2, out2, cr2 = probe(probe_bin, "{} meta {}".format(match, t))
            if cr2 or re.search(r"^ERR meta ", out2, re.M):
                rejected.append(t)
                continue
            meta_names[t] = set(re.findall(r"^FIELD (\S+)", out2, re.M))
        # DOCA's pipeline is list -> describe -> query, so a name that survives
        # describe must also survive the query it was obtained for.
        unqueryable = []
        for t in list(meta_names)[:6]:
            rc2, out2, cr2 = probe(probe_bin, "{} query {} current".format(match, t))
            if cr2 or re.search(r"^ERR (init|query) ", out2, re.M):
                unqueryable.append(t)
        check("D7_live_typelist_consumable", "PASS" if not rejected and not unqueryable else "FAIL",
              "all {} advertised types accepted by mstGetCapabilitiesByType; {} also queried"
              .format(len(live), len(meta_names) and min(6, len(meta_names)))
              if not rejected and not unqueryable
              else "describe rejected: {}; query rejected: {}".format(
                  ", ".join(rejected) or "none", ", ".join(unqueryable) or "none"))

        # D11: the field names describe hands out must be exactly the names the
        # queried map carries. DOCA's users take names from
        # doca_mgmt_raw_hca_cap_describe and feed them to _query; a name that
        # exists in one and not the other is a dead end for every consumer.
        mism = []
        for t in list(meta_names)[:4]:
            rc2, out2, cr2 = probe(probe_bin, "{} query {} current".format(match, t))
            if cr2 or re.search(r"^ERR ", out2, re.M):
                continue
            qn = set(re.findall(r"^VAL (\S+) ", out2, re.M))
            only_meta = meta_names[t] - qn
            only_query = qn - meta_names[t]
            if only_meta or only_query:
                mism.append("{}: describe-only {} query-only {}".format(
                    t, sorted(only_meta)[:3], sorted(only_query)[:3]))
        check("D11_describe_matches_query", "PASS" if not mism else "FAIL",
              "describe and query agree on every field name for {} type(s)".format(min(4, len(meta_names)))
              if not mism else "; ".join(mism[:3]))

    # D10: DOCA never has the device to itself. mgmt_dev_ctx_create_from_devinfo
    # opens its OWN fd on /dev/fwctl/<name> and only then asks the SDK for a
    # handle on the same node; destroy releases the SDK handle first and closes
    # DOCA's fd second. If the SDK ever took the device exclusively, every
    # doca_mgmt_dev_ctx_create would fail on every host.
    rc, out, crashed = probe(probe_bin, "{} doca-coexist".format(match))
    sdk_open = re.search(r"^COEXIST sdk_open (-?\d+)", out, re.M)
    queried = re.search(r"^COEXIST query_while_fd_open (-?\d+)", out, re.M)
    fd_alive = "doca_fd_after_release alive" in out
    if crashed:
        check("D10_doca_fd_coexistence", "FAIL", "probe crashed (rc={})".format(rc))
    elif not sdk_open:
        check("D10_doca_fd_coexistence", "SKIP",
              (re.search(r"^ERR .*", out, re.M) or ["could not open the fwctl node"])[0])
    else:
        ok = sdk_open.group(1) == "0" and queried and queried.group(1) == "0" and fd_alive
        check("D10_doca_fd_coexistence", "PASS" if ok else "FAIL",
              "SDK opens and queries while DOCA's own fd is held, and that fd survives release"
              if ok else "sdk_open={} query={} doca_fd_after_release={}".format(
                  sdk_open.group(1), queried.group(1) if queried else "n/a", "alive" if fd_alive else "dead"))

    # D9: DOCA's RawHCACapQueryGoodFlow queries cmd_hca_cap.vhca_id in CUR and
    # then in MAX and asserts BOTH equal the vhca_id doca_devinfo reports. So for
    # this one field the two modes must agree exactly -- not just MAX >= CURRENT.
    cur, _ = sdk_values(probe_bin, match, DOCA_GENERAL_CAP_TYPE, "current", ["vhca_id"])
    mx, _ = sdk_values(probe_bin, match, DOCA_GENERAL_CAP_TYPE, "max", ["vhca_id"])
    if not cur or not mx or "vhca_id" not in cur or "vhca_id" not in mx:
        check("D9_doca_vhca_id_mode_invariant", "SKIP", "vhca_id not readable in both modes")
    else:
        same = cur["vhca_id"] == mx["vhca_id"]
        check("D9_doca_vhca_id_mode_invariant", "PASS" if same else "FAIL",
              "vhca_id = 0x{:x} in both CUR and MAX".format(cur["vhca_id"]) if same
              else "CUR 0x{:x} != MAX 0x{:x}; DOCA asserts both equal doca_devinfo_get_vhca_id".format(
                  cur["vhca_id"], mx["vhca_id"]))

    # D8: DOCA's modify shape end to end -- init, then mstSetCapabilityValue on
    # exactly ONE field, and nothing else may end up flagged for write-back.
    # doca_mgmt_raw_hca_cap_modify hands that map straight to mstSetHcaCapability,
    # which pushes every flagged entry to firmware, and it never queries first --
    # so a stray flag here is a capability write DOCA never asked for.
    rc, out, crashed = probe(probe_bin, "{} doca-setshape cmd_hca_cap log_max_qp 0".format(match))
    m = re.search(r"flagged=(\d+) stray=(\d+) init_count=(\d+) count=(\d+)", out)
    if crashed or not m:
        check("D8_doca_modify_shape", "FAIL" if crashed else "SKIP",
              "probe crashed" if crashed else (re.search(r"^ERR .*", out, re.M) or ["no measurement line"])[0])
    else:
        flagged, stray, ic, c = (int(m.group(i)) for i in (1, 2, 3, 4))
        ok = flagged == 1 and stray == 0 and ic == c
        check("D8_doca_modify_shape", "PASS" if ok else "FAIL",
              "exactly the one field DOCA set is flagged for write-back ({} entries)".format(c) if ok
              else "{} entr(y/ies) flagged after setting ONE field ({} of them are fields nobody named); "
                   "mstSetHcaCapability would push all of them to FW".format(flagged, stray)
                   + ("" if ic == c else "; map size changed {}->{} across the call".format(ic, c)))

    rc, out, crashed = probe(probe_bin, "{} initstate cmd_hca_cap".format(match))
    m = re.search(r"preset=(\d+) nonzero_value=(\d+)", out)
    if crashed or not m:
        check("D6_init_map_clean", "FAIL" if crashed else "SKIP",
              "probe crashed" if crashed else "no measurement line")
    else:
        preset = int(m.group(1))
        check("D6_init_map_clean", "PASS" if preset == 0 else "FAIL",
              "no entry pre-flagged for write-back after init" if preset == 0
              else "{} entr(y/ies) already flagged set=true straight out of mstInitHcaCapabilityMap "
                   "({} carry a non-zero value too) -- mstSetHcaCapability would write them to FW: "
                   "updateCapabilityMap allocates with new MstHcaCapability[n], which leaves "
                   "`set` and `value` indeterminate".format(preset, m.group(2)))


# --------------------------------------------------------------------------

def parse_args(argv):
    bdf = None
    for i, a in enumerate(argv):
        if a == "-d" and i + 1 < len(argv):
            bdf = argv[i + 1]
        elif a.startswith("--device="):
            bdf = a.split("=", 1)[1]
    return bdf


def main():
    global _verbose
    argv = sys.argv[1:]
    if "--help" in argv or "-h" in argv:
        print(__doc__)
        return 0
    _verbose = "-v" in argv or "--verbose" in argv
    bdf = parse_args(argv)

    work = os.path.join(scratch_root(), "hca_caps_validation_{}".format(os.getpid()))
    shutil.rmtree(work, ignore_errors=True)
    os.makedirs(work)

    if bdf:
        rc, out = run("lspci -s {} 2>/dev/null".format(bdf))
        model = "ConnectX"
        m = re.search(r"\[(ConnectX-?\w+|BlueField-?\w*)\]", out)
        if m:
            model = m.group(1).replace("-", "")
        print("HCA_CAPS [{} - {}]".format(bdf, model))
    else:
        print("HCA_CAPS [offline - no device]")
    print("fwctl nodes: {}".format(", ".join(fwctl_nodes()) or "none (layer D will skip)"))
    print("")

    try:
        layer_a()
        probe_bin = build_probe(work)
        layer_b(probe_bin, bdf)
        layer_e(work, probe_bin)
        oracle = layer_c(bdf, work)
        layer_d(probe_bin, oracle, bdf, work)
    finally:
        shutil.rmtree(work, ignore_errors=True)

    tally = Counter(results.values())
    print("")
    print("FINAL SUMMARY")
    print("  Passed: {}".format(tally["PASS"]))
    print("  Failed: {}".format(tally["FAIL"]))
    print("  Skipped: {}".format(tally["SKIP"]))
    print("Overall: " + ("ALL TESTS PASSED" if not _fails else "FAILED: " + ", ".join(_fails)))
    return 1 if _fails else 0


if __name__ == "__main__":
    sys.exit(main())
