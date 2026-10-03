#!/bin/bash
# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# Build the mstflint SDK unit-test harness and install it alongside the
# installed SDK. Companion to build_sdk.sh -- run that one first, since the
# harness links against the library it installs.
#
# Separate from build_sdk.sh on purpose: that script builds and packages the
# SHIPPED SDK, and mstflint-sdk.spec.in mirrors its configure flags, so it has
# to stay a faithful description of what ends up in a package. This harness is
# test-only code that is never packaged.
#
# All the real logic lives in mft_sdk/unit_tests/Makefile. This is the stable
# entry point, so a caller never has to know where the harness builds, which
# binaries a target produces, or where they are installed.

set -euo pipefail

TESTS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/mft_sdk/unit_tests"

JOBS="$(nproc 2>/dev/null || echo 4)"
TARGET=""
RULE=install-tests
MAKE_VARS=()

usage() {
    cat <<'EOF'
Usage: ./build_sdk_tests.sh [options] [VAR=value ...]

Build the mstflint SDK unit-test harness and install it next to the installed
SDK. Run ./build_sdk.sh first: the harness links against the installed library.

Options:
  --target NAME      Harness target to build (default: the Makefile's own --
                     "unified", every gtest suite in one binary; "op_info" is
                     the narrower pair the MARS op-info case runs)
  --installdir DIR   Where to install the binaries
                     (default: <sdk libdir>/tests, where the suites look)
  --build-only       Build the harness but do not install it
  -j, --jobs N       Parallel build jobs (default: nproc)
  -h, --help         Show this help

Any VAR=value is forwarded to make verbatim, e.g.
GTEST_TARBALL=/path/googletest.tar to unpack a local googletest instead of
fetching it from github.

Examples:
  ./build_sdk_tests.sh
  ./build_sdk_tests.sh --target op_info -j 32
  ./build_sdk_tests.sh --installdir /tmp/stage/tests --build-only
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --target)      TARGET="$2"; MAKE_VARS+=(TEST_TARGET="$2"); shift 2 ;;
        --installdir)  MAKE_VARS+=(TESTS_INSTALLDIR="$2"); shift 2 ;;
        --build-only)  RULE=""; shift ;;
        -j|--jobs)     JOBS="$2"; shift 2 ;;
        -h|--help)     usage; exit 0 ;;
        # Anything else that looks like a make variable goes straight through,
        # so a knob added to the Makefile is usable here without a code change.
        *=*)           MAKE_VARS+=("$1"); shift ;;
        *) echo "error: unknown option: $1" >&2; usage >&2; exit 1 ;;
    esac
done

# --build-only still has to name what to build; fall back to the default goal.
[[ -n "$RULE" ]] || RULE="${TARGET:-all}"

echo ">> make -C $TESTS_DIR -j$JOBS $RULE ${MAKE_VARS[*]}"
make -C "$TESTS_DIR" -j"$JOBS" "$RULE" "${MAKE_VARS[@]}"

echo ">> SDK test harness complete."
