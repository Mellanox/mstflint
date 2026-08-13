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
LIBDIR=""
INCLUDEDIR=""
DATADIR=""
DESTDIR=""
JOBS="$(nproc 2>/dev/null || echo 4)"
ENABLE_NVML=0
NVML_INCLUDE_DIR=""
ENABLE_VFIO=0
DO_CONFIGURE=1
INSTALL=1
BUILD_DEB=0
DEB_OUTPUT=""
DEB_NAME=""
DEB_VERSION=""
BUILD_DEB_SRC=0
BUILD_RPM=0
RPM_OUTPUT=""
RPM_NAME=""
RPM_RELEASE=""
BUILD_RPM_SRC=0
LDSOCONFDIR=""

usage() {
    cat <<'EOF'
Usage: ./build_sdk.sh [options]

Build and install only the mstflint SDK (libmstflint_sdk.so) and its
dependencies, skipping the rest of the mstflint tool suite.

Options:
  --prefix DIR             Install prefix (passed to configure; default: autotools default)
  --libdir DIR             Library install dir (overrides <prefix>/lib[64]);
                           the SDK .so lands in DIR/mstflint/sdk, the .pc in DIR/pkgconfig
  --includedir DIR         Header install dir (overrides <prefix>/include);
                           SDK headers land in DIR/mstflint/sdk/mft_sdk
  --datadir DIR            Data install dir (overrides <prefix>/share);
                           PRM databases land under DIR/mstflint
  --destdir DIR            Staged install root (DESTDIR for `make install-sdk`)
  --with-nvml              Enable NVML support in the SDK
  --with-nvml-include-dir DIR
                           Path to nvml.h (implies --with-nvml)
  --with-vfio              Enable VFIO device access in the SDK
  --ldsoconfdir DIR        Directory for the ld.so.conf.d snippet that registers
                           the SDK library dir with ldconfig (default: /etc/ld.so.conf.d)
  --no-ldsoconf            Do not install the ld.so.conf.d snippet
  -j, --jobs N             Parallel build jobs (default: nproc)
  --no-configure           Skip autogen/configure; reuse the existing configuration
  --build-only             Build the SDK but do not install it
  --rpm                    Build a standalone mstflint-sdk .rpm (uses mstflint-sdk.spec)
  --rpm-name NAME          Override the RPM package Name (default: mstflint-sdk);
                           only changes package identity, not install paths
  --rpm-release R          RPM Release (default: 1); the binary also gets %{?dist}
  --rpm-source             Also build the .src.rpm, without a dist tag
  --rpm-output DIR         Directory to place the built .rpm (default: repo root)
  --deb                    Build a standalone mstflint-sdk .deb (uses debian-sdk/)
  --deb-name NAME          Override the .deb package name (default: mstflint-sdk);
                           only changes package identity, not install paths
  --deb-version V          Debian version (default: from debian-sdk/changelog)
  --deb-source             Also build the .dsc + .orig.tar.xz + .debian.tar.*
  --deb-output DIR         Directory to place the built .deb (default: repo root)
  -h, --help               Show this help

Examples:
  ./build_sdk.sh --destdir /tmp/mstflint-sdk-stage
  ./build_sdk.sh --prefix /usr --with-nvml
  ./build_sdk.sh --prefix /opt/doca --libdir /opt/doca/lib64
  ./build_sdk.sh --rpm --prefix /opt/doca --rpm-output /tmp/rpms
  ./build_sdk.sh --rpm --rpm-name acme-mstflint-sdk
  ./build_sdk.sh --deb --deb-output /tmp/debs
  ./build_sdk.sh --deb --deb-name acme-mstflint-sdk
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
        --exclude='*.tar.xz' --exclude=./configure~ --exclude=config.status \
        --exclude=config.log --exclude=autom4te.cache \
        -C "$SCRIPT_DIR" . 2>/dev/null
    cp "$spec" "$top/SPECS/mstflint-sdk.spec"

    # Forward install-dir overrides as RPM path macros. The spec's %configure
    # expands to --prefix=%{_prefix} --libdir=%{_libdir} etc., so redefining
    # these macros changes both the configure invocation and the %files paths
    # (mstflint_sdk_libdir/incdir/datadir are all derived from them). _prefix
    # cascades to _exec_prefix/_libdir/_includedir/_datadir unless individually
    # overridden below.
    local dir_defines=()
    # Override the package Name (the spec guards its default with %{!?name}),
    # so a client can ship under a private name that won't clash with a
    # distro-provided mstflint-sdk. Install paths are unaffected.
    [[ -n "$RPM_NAME" ]]   && dir_defines+=(--define "name $RPM_NAME")
    [[ -n "$RPM_RELEASE" ]] && dir_defines+=(--define "release $RPM_RELEASE")
    [[ -n "$PREFIX" ]]     && dir_defines+=(--define "_prefix $PREFIX")
    [[ -n "$LIBDIR" ]]     && dir_defines+=(--define "_libdir $LIBDIR")
    [[ -n "$INCLUDEDIR" ]] && dir_defines+=(--define "_includedir $INCLUDEDIR")
    [[ -n "$DATADIR" ]]    && dir_defines+=(--define "_datadir $DATADIR")

    # SRPM first (cheap) so a failure here does not discard the built binary.
    if [[ "$BUILD_RPM_SRC" -eq 1 ]]; then
        echo ">> rpmbuild -bs"
        rpmbuild --define "_topdir $top" --define "_tmppath $top/tmp" \
                 --define "version $version" "${dir_defines[@]}" \
                 --define "dist %{nil}" --nodeps \
                 -bs "$top/SPECS/mstflint-sdk.spec"
    fi

    echo ">> rpmbuild -bb"
    rpmbuild --define "_topdir $top" --define "_tmppath $top/tmp" \
             --define "version $version" "${dir_defines[@]}" \
             -bb "$top/SPECS/mstflint-sdk.spec"

    echo ">> collecting .rpm into $out"
    find "$top/RPMS" "$top/SRPMS" -name '*.rpm' -exec mv {} "$out"/ \;
    rm -rf "$top"
    echo ">> SDK .rpm build complete:"
    ls -1 "$out"/"${RPM_NAME:-mstflint-sdk}"-*.rpm
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

    # The staged tree is named <source>-<upstream>, which is also the orig
    # tarball's single top-level directory -- so resolve both before staging.
    local work src name ver upstream
    name="${DEB_NAME:-mstflint-sdk}"
    ver="${DEB_VERSION:-$(sed -nE '1s/^[^ ]+ \(([^)]*)\).*/\1/p' "$SCRIPT_DIR/debian-sdk/changelog")}"
    upstream="${ver%-*}"       # drop the Debian revision
    upstream="${upstream#*:}"  # and the epoch
    work="$(mktemp -d)"
    src="$work/$name-$upstream"
    mkdir -p "$src"

    echo ">> staging isolated source tree as $name-$upstream"
    # ibdump/ stays: automake traces AC_CONFIG_FILES(ibdump/Makefile) statically,
    # so excluding it silently breaks autogen.sh.
    tar -c \
        --exclude=.git --exclude='*.o' --exclude='*.lo' --exclude='*.la' \
        --exclude='*.a' --exclude=.libs --exclude=.deps \
        --exclude=./debian --exclude='*.tar.gz' --exclude=./configure~ \
        --exclude=config.status --exclude=config.log --exclude=autom4te.cache \
        --exclude='*.deb' --exclude='*.dsc' --exclude='*.tar.xz' \
        --exclude='*.changes' --exclude='*.buildinfo' --exclude='*.rpm' \
        --exclude="./$name-$upstream" \
        -C "$SCRIPT_DIR" . | tar -x -C "$src"
    cp -r "$SCRIPT_DIR/debian-sdk" "$src/debian"
    cp "$SCRIPT_DIR/debian/mstflint.install.in" "$src/debian/"

    # Rename the binary/source package in the isolated debian/ copy so a client
    # can ship under a private name without clashing with a distro mstflint-sdk.
    # The name lives in control (Source:/Package:), the changelog source stanza,
    # and the dh staging path in rules (override_dh_auto_install installs into
    # debian/<package>/, which dh_builddeb then packages -- so it MUST track the
    # package name). Install paths are unaffected. The checked-in debian-sdk/ is
    # never touched; only this throwaway copy is edited.
    if [[ -n "$DEB_NAME" ]]; then
        echo ">> renaming .deb package to $DEB_NAME"
        sed -i "s/^Source: mstflint-sdk$/Source: $DEB_NAME/;s/^Package: mstflint-sdk$/Package: $DEB_NAME/" \
            "$src/debian/control"
        sed -i "1s/^mstflint-sdk (/$DEB_NAME (/" "$src/debian/changelog"
        sed -i "s#debian/mstflint-sdk#debian/$DEB_NAME#g" "$src/debian/rules"
    fi

    if [[ -n "$DEB_VERSION" ]]; then
        echo ">> setting .deb version to $DEB_VERSION"
        sed -i "1s#([^)]*)#($DEB_VERSION)#" "$src/debian/changelog"
    fi

    # Forward install-dir overrides into the isolated tree's debian/rules so a
    # relocated package (e.g. --prefix /opt/...) actually installs there. dh's
    # dh_auto_configure otherwise defaults to /usr, ignoring these; unlike the
    # RPM path there is no macro to redefine, so append the flags to the
    # override_dh_auto_configure configure invocation.
    local configure_extra=""
    [[ -n "$PREFIX" ]]     && configure_extra+=" --prefix=$PREFIX"
    [[ -n "$LIBDIR" ]]     && configure_extra+=" --libdir=$LIBDIR"
    [[ -n "$INCLUDEDIR" ]] && configure_extra+=" --includedir=$INCLUDEDIR"
    [[ -n "$DATADIR" ]]    && configure_extra+=" --datadir=$DATADIR"
    if [[ -n "$configure_extra" ]]; then
        echo ">> forwarding install dirs to debian/rules:$configure_extra"
        sed -i "s#--enable-adb-generic-tools --enable-mstflint-sdk#--enable-adb-generic-tools --enable-mstflint-sdk$configure_extra#" \
            "$src/debian/rules"
    fi

    local flags=(-b)
    if [[ "$BUILD_DEB_SRC" -eq 1 ]]; then
        # debian-sdk/ is native, which has no .orig/.debian split; quilt needs an orig tarball.
        echo "3.0 (quilt)" > "$src/debian/source/format"
        # Archive the directory BY NAME: "-C $src ." would store every member as
        # ./<path>, leaving the tarball with no top-level directory (a tarbomb).
        tar cJf "$work/${name}_${upstream}.orig.tar.xz" \
            --anchored --exclude="$name-$upstream/debian" \
            -C "$work" "$name-$upstream"
        flags=(-F)
    fi

    echo ">> dpkg-buildpackage ${flags[*]} -uc -us"
    ( cd "$src" && dpkg-buildpackage "${flags[@]}" -uc -us )

    echo ">> collecting .deb into $out"
    mv "$work"/*.deb "$out"/
    [[ "$BUILD_DEB_SRC" -eq 1 ]] && mv "$work"/*.dsc "$work"/*.tar.* "$out"/
    rm -rf "$work"
    echo ">> SDK .deb build complete:"
    ls -1 "$out"/"${DEB_NAME:-mstflint-sdk}"_*
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --prefix)              PREFIX="$2"; shift 2 ;;
        --libdir)              LIBDIR="$2"; shift 2 ;;
        --includedir)          INCLUDEDIR="$2"; shift 2 ;;
        --datadir)             DATADIR="$2"; shift 2 ;;
        --destdir)             DESTDIR="$2"; shift 2 ;;
        --with-nvml)           ENABLE_NVML=1; shift ;;
        --with-nvml-include-dir) ENABLE_NVML=1; NVML_INCLUDE_DIR="$2"; shift 2 ;;
        --with-vfio)           ENABLE_VFIO=1; shift ;;
        --ldsoconfdir)         LDSOCONFDIR="$2"; shift 2 ;;
        --no-ldsoconf)         LDSOCONFDIR="no"; shift ;;
        -j|--jobs)             JOBS="$2"; shift 2 ;;
        --no-configure)        DO_CONFIGURE=0; shift ;;
        --build-only)          INSTALL=0; shift ;;
        --rpm)                 BUILD_RPM=1; shift ;;
        --rpm-name)            RPM_NAME="$2"; shift 2 ;;
        --rpm-release)         RPM_RELEASE="$2"; shift 2 ;;
        --rpm-source)          BUILD_RPM=1; BUILD_RPM_SRC=1; shift ;;
        --rpm-output)          RPM_OUTPUT="$2"; shift 2 ;;
        --deb)                 BUILD_DEB=1; shift ;;
        --deb-name)            DEB_NAME="$2"; shift 2 ;;
        --deb-version)         DEB_VERSION="$2"; shift 2 ;;
        --deb-source)          BUILD_DEB=1; BUILD_DEB_SRC=1; shift ;;
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
    [[ -n "$PREFIX" ]]     && CONFIGURE_FLAGS+=(--prefix="$PREFIX")
    [[ -n "$LIBDIR" ]]     && CONFIGURE_FLAGS+=(--libdir="$LIBDIR")
    [[ -n "$INCLUDEDIR" ]] && CONFIGURE_FLAGS+=(--includedir="$INCLUDEDIR")
    [[ -n "$DATADIR" ]]    && CONFIGURE_FLAGS+=(--datadir="$DATADIR")
    if [[ "$ENABLE_NVML" -eq 1 ]]; then
        CONFIGURE_FLAGS+=(--enable-nvml)
        [[ -n "$NVML_INCLUDE_DIR" ]] && CONFIGURE_FLAGS+=(--with-nvml-include-dir="$NVML_INCLUDE_DIR")
    fi
    [[ "$ENABLE_VFIO" -eq 1 ]] && CONFIGURE_FLAGS+=(--enable-vfio)
    # --without-ldsoconfdir drops the ld.so.conf.d snippet entirely; anything
    # else is taken as the directory to install it into.
    if [[ "$LDSOCONFDIR" == "no" ]]; then
        CONFIGURE_FLAGS+=(--without-ldsoconfdir)
    elif [[ -n "$LDSOCONFDIR" ]]; then
        CONFIGURE_FLAGS+=(--with-ldsoconfdir="$LDSOCONFDIR")
    fi

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
