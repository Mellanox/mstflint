#!/bin/bash
# Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# Standalone build/install helper for the mstflint SDK (libmstflint_sdk.so).
#
# Configures the tree for an SDK-only build and drives the `sdk` / `install-sdk`
# make targets, so only the SDK library, its headers and the PRM databases it
# needs are built and installed -- not the full mstflint tool suite.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

PREFIX=""
DESTDIR=""
JOBS="$(nproc 2>/dev/null || echo 4)"
ENABLE_NVML=0
NVML_INCLUDE_DIR=""
ENABLE_VFIO=0
DO_CONFIGURE=1
INSTALL=1

usage() {
    cat <<'EOF'
Usage: ./build_sdk.sh [options]

Build and install only the mstflint SDK (libmstflint_sdk.so) and its
dependencies, skipping the rest of the mstflint tool suite.

Options:
  --prefix DIR             Install prefix (passed to configure; default: autotools default)
  --destdir DIR            Staged install root (DESTDIR for `make install-sdk`)
  --with-nvml              Enable NVML support in the SDK
  --with-nvml-include-dir DIR
                           Path to nvml.h (implies --with-nvml)
  --with-vfio              Enable VFIO device access in the SDK
  -j, --jobs N             Parallel build jobs (default: nproc)
  --no-configure           Skip autogen/configure; reuse the existing configuration
  --build-only             Build the SDK but do not install it
  -h, --help               Show this help

Examples:
  ./build_sdk.sh --destdir /tmp/mstflint-sdk-stage
  ./build_sdk.sh --prefix /usr --with-nvml
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --prefix)              PREFIX="$2"; shift 2 ;;
        --destdir)             DESTDIR="$2"; shift 2 ;;
        --with-nvml)           ENABLE_NVML=1; shift ;;
        --with-nvml-include-dir) ENABLE_NVML=1; NVML_INCLUDE_DIR="$2"; shift 2 ;;
        --with-vfio)           ENABLE_VFIO=1; shift ;;
        -j|--jobs)             JOBS="$2"; shift 2 ;;
        --no-configure)        DO_CONFIGURE=0; shift ;;
        --build-only)          INSTALL=0; shift ;;
        -h|--help)             usage; exit 0 ;;
        *) echo "error: unknown option: $1" >&2; usage >&2; exit 1 ;;
    esac
done

cd "$SCRIPT_DIR"

if [[ "$DO_CONFIGURE" -eq 1 ]]; then
    CONFIGURE_FLAGS=(--enable-adb-generic-tools --enable-mstflint-sdk)
    [[ -n "$PREFIX" ]] && CONFIGURE_FLAGS+=(--prefix="$PREFIX")
    if [[ "$ENABLE_NVML" -eq 1 ]]; then
        CONFIGURE_FLAGS+=(--enable-nvml)
        [[ -n "$NVML_INCLUDE_DIR" ]] && CONFIGURE_FLAGS+=(--with-nvml-include-dir="$NVML_INCLUDE_DIR")
    fi
    [[ "$ENABLE_VFIO" -eq 1 ]] && CONFIGURE_FLAGS+=(--enable-vfio)

    echo ">> ./autogen.sh"
    ./autogen.sh
    echo ">> ./configure ${CONFIGURE_FLAGS[*]}"
    ./configure "${CONFIGURE_FLAGS[@]}"
fi

echo ">> make -j${JOBS} sdk"
make -j"${JOBS}" sdk

if [[ "$INSTALL" -eq 1 ]]; then
    INSTALL_ARGS=()
    [[ -n "$DESTDIR" ]] && INSTALL_ARGS+=(DESTDIR="$DESTDIR")
    echo ">> make install-sdk ${INSTALL_ARGS[*]}"
    make install-sdk "${INSTALL_ARGS[@]}"
fi

echo ">> SDK build complete."
