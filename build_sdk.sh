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
BUILD_DEB=0
DEB_OUTPUT=""
BUILD_RPM=0
RPM_OUTPUT=""

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
  --rpm                    Build a standalone mstflint-sdk .rpm (uses mstflint-sdk.spec)
  --rpm-output DIR         Directory to place the built .rpm (default: repo root)
  --deb                    Build a standalone mstflint-sdk .deb (uses debian-sdk/)
  --deb-output DIR         Directory to place the built .deb (default: repo root)
  -h, --help               Show this help

Examples:
  ./build_sdk.sh --destdir /tmp/mstflint-sdk-stage
  ./build_sdk.sh --prefix /usr --with-nvml
  ./build_sdk.sh --rpm --rpm-output /tmp/rpms
  ./build_sdk.sh --deb --deb-output /tmp/debs
EOF
}

# Project version (from configure.ac AC_INIT), used to name the source tarball
# the SDK spec expects.
sdk_version() {
    local v
    v="$(sed -nE 's/^AC_INIT\(mstflint,[[:space:]]*([0-9.]+).*/\1/p' "$SCRIPT_DIR/configure.ac" | head -1)"
    echo "${v:-4.37.0}"
}

# Build a standalone mstflint-sdk .rpm from a clean source tarball, in a private
# rpm topdir. Mirrors the SDK spec's build (configure --enable-mstflint-sdk,
# make sdk, make install-sdk).
build_rpm() {
    command -v rpmbuild >/dev/null 2>&1 || {
        echo "error: rpmbuild not found; RPM build tools are required for --rpm" >&2
        exit 1
    }
    local spec="$SCRIPT_DIR/mstflint-sdk.spec"
    [[ -f "$spec" ]] || spec="$SCRIPT_DIR/mstflint-sdk.spec.in"
    [[ -f "$spec" ]] || { echo "error: mstflint-sdk.spec(.in) not found" >&2; exit 1; }

    local version out top
    version="$(sdk_version)"
    out="${RPM_OUTPUT:-$SCRIPT_DIR}"; mkdir -p "$out"; out="$(cd "$out" && pwd)"
    top="$(mktemp -d)"
    mkdir -p "$top"/{SOURCES,SPECS,BUILD,BUILDROOT,RPMS,SRPMS,tmp}

    echo ">> creating source tarball mstflint-$version.tar.gz"
    tar czf "$top/SOURCES/mstflint-$version.tar.gz" \
        --transform "s,^\./,mstflint-$version/," \
        --exclude=.git --exclude='*.o' --exclude='*.lo' --exclude='*.la' \
        --exclude='*.a' --exclude=.libs --exclude=.deps --exclude='*.tar.gz' \
        --exclude=./configure~ --exclude=config.status --exclude=config.log \
        --exclude=autom4te.cache \
        -C "$SCRIPT_DIR" . 2>/dev/null
    cp "$spec" "$top/SPECS/mstflint-sdk.spec"

    echo ">> rpmbuild -bb"
    rpmbuild --define "_topdir $top" --define "_tmppath $top/tmp" \
             --define "version $version" -bb "$top/SPECS/mstflint-sdk.spec"

    echo ">> collecting .rpm into $out"
    find "$top/RPMS" -name '*.rpm' -exec mv {} "$out"/ \;
    rm -rf "$top"
    echo ">> SDK .rpm build complete:"
    ls -1 "$out"/mstflint-sdk-*.rpm
}

# Build a standalone mstflint-sdk .deb in an isolated copy of the source tree,
# using the dedicated debian-sdk/ packaging. The real debian/ tree is never
# touched.
build_deb() {
    command -v dpkg-buildpackage >/dev/null 2>&1 || {
        echo "error: dpkg-buildpackage not found; Debian build tools are required for --deb" >&2
        exit 1
    }
    [[ -d "$SCRIPT_DIR/debian-sdk" ]] || {
        echo "error: debian-sdk/ not found" >&2
        exit 1
    }
    local out="${DEB_OUTPUT:-$SCRIPT_DIR}"
    mkdir -p "$out"
    out="$(cd "$out" && pwd)"

    local work src
    work="$(mktemp -d)"
    src="$work/mstflint-sdk"
    mkdir -p "$src"

    echo ">> staging isolated source tree"
    tar -c \
        --exclude=.git --exclude='*.o' --exclude='*.lo' --exclude='*.la' \
        --exclude='*.a' --exclude=.libs --exclude=.deps \
        --exclude=./debian --exclude='*.tar.gz' --exclude=./configure~ \
        -C "$SCRIPT_DIR" . | tar -x -C "$src"
    cp -r "$SCRIPT_DIR/debian-sdk" "$src/debian"

    echo ">> dpkg-buildpackage -b -uc -us"
    ( cd "$src" && dpkg-buildpackage -b -uc -us )

    echo ">> collecting .deb into $out"
    mv "$work"/*.deb "$out"/
    rm -rf "$work"
    echo ">> SDK .deb build complete:"
    ls -1 "$out"/mstflint-sdk_*.deb
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
        --rpm)                 BUILD_RPM=1; shift ;;
        --rpm-output)          RPM_OUTPUT="$2"; shift 2 ;;
        --deb)                 BUILD_DEB=1; shift ;;
        --deb-output)          DEB_OUTPUT="$2"; shift 2 ;;
        -h|--help)             usage; exit 0 ;;
        *) echo "error: unknown option: $1" >&2; usage >&2; exit 1 ;;
    esac
done

cd "$SCRIPT_DIR"

if [[ "$BUILD_RPM" -eq 1 || "$BUILD_DEB" -eq 1 ]]; then
    [[ "$BUILD_RPM" -eq 1 ]] && build_rpm
    [[ "$BUILD_DEB" -eq 1 ]] && build_deb
    exit 0
fi

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
