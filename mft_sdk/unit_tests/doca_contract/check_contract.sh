#!/usr/bin/env bash
# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# Assert the integration contract DOCA's libs/doca_mgmt depends on.
#
# Run it after any change to the SDK's public API, its header layout, its
# packaging paths or its pkg-config metadata. Everything checked here is
# invisible to the rest of the test suite: the other binaries resolve the SDK
# from hardcoded -I/-L paths and bake in an rpath, so they keep passing through
# regressions that break DOCA at link or load time.
#
# Usage:
#   check_contract.sh [--probe <binary>] [--symbols <file>] [--fwctl <name>]
#
# Environment:
#   PKG_CONFIG                pkg-config binary (default: pkg-config)
#   SDK_PKG                   module name       (default: mstflint_sdk)
#   DOCA_CONTRACT_SKIP_LDCONFIG=1
#         Skip the ldconfig check. Only for a staged/DESTDIR tree that is not
#         installed yet -- never for validating a real install.
#
# Exit: 0 all checks passed, 1 otherwise.

set -u

PKG_CONFIG="${PKG_CONFIG:-pkg-config}"
SDK_PKG="${SDK_PKG:-mstflint_sdk}"
# /sbin is not on a non-root user's PATH on Debian, so resolving ldconfig by
# bare name turns check [5] into a false negative there.
LDCONFIG="${LDCONFIG:-$(command -v ldconfig || echo /sbin/ldconfig)}"
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROBE=""
SYMBOLS="$HERE/doca_symbols.txt"
FWCTL="fwctl0"

while [ $# -gt 0 ]; do
    case "$1" in
        --probe)   PROBE="$2";   shift 2 ;;
        --symbols) SYMBOLS="$2"; shift 2 ;;
        --fwctl)   FWCTL="$2";   shift 2 ;;
        -h|--help) sed -n '3,25p' "${BASH_SOURCE[0]}"; exit 0 ;;
        *) echo "unknown argument: $1" >&2; exit 2 ;;
    esac
done

rc=0
pass() { printf '  \033[32mPASS\033[0m  %s\n' "$1"; }
fail() { printf '  \033[31mFAIL\033[0m  %s\n' "$1"; rc=1; }
skip() { printf '  \033[33mSKIP\033[0m  %s\n' "$1"; }
note() { printf '        %s\n' "$1"; }

echo "=============================================================="
echo "DOCA integration contract -- mstflint SDK"
echo "=============================================================="

# --- 1. discovery: the pkg-config module DOCA resolves ----------------------
# DOCA does dependency('mstflint_sdk', required: true). No fallback, no
# hardcoded path: if this module is missing or misnamed, libdoca_mgmt.so does
# not build at all.
echo
echo "[1] pkg-config module '$SDK_PKG'"
if "$PKG_CONFIG" --exists "$SDK_PKG" 2>/dev/null; then
    pass "module found (version $("$PKG_CONFIG" --modversion "$SDK_PKG"))"
    SDK_INCDIR="$("$PKG_CONFIG" --variable=includedir "$SDK_PKG")"
    SDK_LIBDIR="$("$PKG_CONFIG" --variable=libdir "$SDK_PKG")"
    note "includedir = $SDK_INCDIR"
    note "libdir     = $SDK_LIBDIR"
else
    fail "module '$SDK_PKG' not found by $PKG_CONFIG"
    note "DOCA's meson dependency('$SDK_PKG', required: true) would fail here."
    note "For a relocated install, point PKG_CONFIG_PATH at its pkgconfig dir."
    echo
    echo "Cannot continue without the module. FAILED"
    exit 1
fi

# --- 2. the load-bearing header nesting -------------------------------------
# DOCA writes #include <mft_sdk/mft_sdk.h> and gets only -I$includedir from the
# .pc, so the headers must sit one level down in mft_sdk/. Flattening the
# install to $includedir/*.h breaks every DOCA source file.
echo
echo "[2] header spelling <mft_sdk/mft_sdk.h>"
if [ -f "$SDK_INCDIR/mft_sdk/mft_sdk.h" ]; then
    pass "$SDK_INCDIR/mft_sdk/mft_sdk.h"
else
    fail "not found at \$includedir/mft_sdk/mft_sdk.h"
    if [ -f "$SDK_INCDIR/mft_sdk.h" ]; then
        note "found a FLAT $SDK_INCDIR/mft_sdk.h instead -- the mft_sdk/"
        note "subdirectory level is required; see mft_sdk/Makefile.am."
    fi
fi

# --- 3. the library itself --------------------------------------------------
echo
echo "[3] libmstflint_sdk.so"
SDK_SO="$SDK_LIBDIR/libmstflint_sdk.so"
if [ -f "$SDK_SO" ]; then
    pass "$SDK_SO"
else
    fail "not found at $SDK_SO"
    echo
    echo "Cannot check symbols without the library. FAILED"
    exit 1
fi

# --- 4. the 23 symbols ------------------------------------------------------
# A missing symbol surfaces as an "undefined reference" while linking doca-dms,
# a package that never mentions mstflint.
echo
echo "[4] DOCA-consumed mst* symbols"
if [ ! -f "$SYMBOLS" ]; then
    fail "symbol list not found: $SYMBOLS"
else
    exported="$(nm -D --defined-only "$SDK_SO" 2>/dev/null | awk '{print $NF}')"
    total=0; missing=0
    while read -r sym; do
        case "$sym" in ''|\#*) continue ;; esac
        total=$((total + 1))
        if ! printf '%s\n' "$exported" | grep -qx "$sym"; then
            fail "missing symbol: $sym"
            missing=$((missing + 1))
        fi
    done < "$SYMBOLS"
    if [ "$missing" -eq 0 ]; then
        pass "all $total symbols exported"
    else
        note "$missing of $total missing -- this breaks the doca-dms build."
    fi
fi

# --- 5. runtime discoverability (no-rpath consumers) ------------------------
# DOCA sets rpath empty for all its libraries, and libmstflint_sdk.so lives in
# a private directory no loader searches by default. Without the ld.so.conf.d
# snippet, ldd libdoca_mgmt.so reports "libmstflint_sdk.so => not found".
echo
echo "[5] ldconfig registration"
if [ "${DOCA_CONTRACT_SKIP_LDCONFIG:-0}" = "1" ]; then
    skip "DOCA_CONTRACT_SKIP_LDCONFIG=1"
elif "$LDCONFIG" -p 2>/dev/null | grep -q 'libmstflint_sdk\.so'; then
    pass "$("$LDCONFIG" -p | grep -m1 'libmstflint_sdk\.so' | sed 's/^[[:space:]]*//')"
else
    fail "libmstflint_sdk.so is not registered with ldconfig"
    note "A consumer without an rpath cannot load it. Check that the package"
    note "shipped /etc/ld.so.conf.d/<name>.conf and that ldconfig has run."
fi

# --- 6/7. linkage shape and load, via the probe -----------------------------
echo
echo "[6] probe linkage shape (DT_NEEDED, no RPATH/RUNPATH)"
if [ -z "$PROBE" ]; then
    skip "no --probe binary given (build it with: make doca-contract)"
elif [ ! -x "$PROBE" ]; then
    fail "probe not executable: $PROBE"
else
    dyn="$(readelf -d "$PROBE" 2>/dev/null)"
    if printf '%s\n' "$dyn" | grep -q 'NEEDED.*libmstflint_sdk\.so'; then
        pass "DT_NEEDED: libmstflint_sdk.so"
    else
        fail "no DT_NEEDED on libmstflint_sdk.so"
    fi
    if printf '%s\n' "$dyn" | grep -qE '\((RPATH|RUNPATH)\)'; then
        fail "probe carries an RPATH/RUNPATH -- it must not"
        note "$(printf '%s\n' "$dyn" | grep -E '\((RPATH|RUNPATH)\)' | sed 's/^[[:space:]]*//')"
        note "With an rpath this probe would mask exactly the ldconfig"
        note "regression it exists to catch. DOCA links with rpath empty."
    else
        pass "no RPATH/RUNPATH (matches libdoca_mgmt.so)"
    fi

    echo
    echo "[7] probe loads and enters the SDK"
    out="$("$PROBE" "$FWCTL" 2>&1)"; prc=$?
    if [ "$prc" -eq 0 ]; then
        pass "$(printf '%s\n' "$out" | grep '^RESULT:' || echo 'ran')"
    else
        fail "probe exited $prc"
        printf '%s\n' "$out" | sed 's/^/        /'
        case "$out" in
            *'cannot open shared object file'*)
                note "This is the DOCA failure mode: the loader cannot find the"
                note "SDK without an rpath. Check [5] above." ;;
        esac
    fi
fi

echo
echo "=============================================================="
if [ "$rc" -eq 0 ]; then
    echo "DOCA contract: PASSED"
else
    echo "DOCA contract: FAILED"
fi
echo "=============================================================="
exit "$rc"
