This directory holds two suites:

| Script | Covers | Needs |
|---|---|---|
| `test_build_flags.py` | install-dir relocation + package rename, against real installed packages | device, sudo, package cache |
| `test_source_packages.py` | source-package emission (`--rpm-source`/`--deb-source`) and release stamping | nothing — fully offline |

`test_source_packages.py` is documented at the end of this file.

---

# Packaging tests — build_sdk.sh custom install dirs & package names

Validates the mstflint `build_sdk.sh` packaging-customization flags
(`--prefix/--libdir/--includedir/--datadir`, `--rpm-name/--deb-name`,
mstflint commit `6f27c0e5`) against real installed packages.

**mstflint-SDK-only suite.** It installs/uninstalls mstflint-sdk package
variants, so in the SDK-Verify extension it is gated off for the MFT product
and always dispatched LAST — it is the only suite allowed to change the
installed package mid-run. It restores the default package when it finishes
(also on failure).

## Variants

| `--variant` | Flags baked into the cached package | Flavors |
|---|---|---|
| `paths_only` | `--prefix /opt/sdkv --libdir /opt/sdkv/lib64x --includedir /opt/sdkv/inc --datadir /opt/sdkv/dat` | RPM only¹ |
| `name_only` | `--rpm-name/--deb-name sdkv-mstflint-sdk` | RPM + DEB |
| `both` | paths + name combined | RPM only¹ |

¹ `build_sdk.sh` has no per-dir customization on the DEB path (upstream
follow-up); the test SKIPs those variants on DEB machines.

## Steps per variant

clean_slate (wipe **all** MFT-SDK/mstflint-SDK packages+dirs, verified) →
install → package_identity → install_layout (incl. `.pc`) →
no_default_paths (relocated variants: default paths must be ABSENT) →
data_path_consistency (PRM db root baked into the `.so` == variant datadir) →
compile_smoke (`packaging_smoke.c` vs the variant headers — the only honest
`.h` coverage; nothing in `--so` mode compiles otherwise) →
runtime_smoke (MGIR read on a live device — proves the relocated DATA_PATH
resolves at runtime) →
harness_discovery (installed gtest harness through the variant libdir, with a
WRONGLIB `ldd` gate) →
cli_compare (compare mode only: sibling `mlxreg/test_register_access.py` with
`MFT_SDK_SO_DIR` pointed at the variant — functional equivalence vs
`mlxreg_ext`; SKIPped under `--sdk-only`) →
coexist_or_conflict (`both`: renamed+relocated must coexist with the default
package; `name_only`: must be *refused* on file conflicts — same paths;
`paths_only`: SKIP, same identity) →
restore_default.

## The fixed-location problem (headers/libs)

Existing `--so` tests find the SDK via `MFT_SDK_SO_DIR` / `MFT_SDK_SO_TEST_BIN`
(utils.py) — this suite points them at the variant dirs and creates the
`libmft_sdk.so.1` compat symlink inside the variant libdir. Default paths are
asserted absent, so no stale copy can be silently tested. Headers are covered
by the compile step.

## Running by hand

```bash
cd <mstflint-repo>
MSTFLINT_PKG_CACHE=<cache-root> python3 mft_sdk/unit_tests/packaging/test_build_flags.py \
    --variant paths_only --compare -d 21:00.0 --so [--sdk-only] [--verbose]
```

Needs: passwordless sudo, gcc, the package cache (`MSTFLINT_PKG_CACHE`,
required) with `variants/manifest.json` + variant packages (produced by the
extension's Build & Run), and the seeded harness binary
(`MFT_SDK_SO_TEST_BIN`, default `/usr/lib64/mft_sdk/tests/mft_sdk_mstflint_so_test`).

---

# Source-package tests — build_sdk.sh `--rpm-source` / `--deb-source`

Validates that `build_sdk.sh` emits source packages alongside the binaries, so
UBS can resolve a binary to its source (RPM `SOURCERPM` tag / DEB `Source`
field). Before these flags existed the SDK binary referenced a
`mstflint-sdk-local-*.src.rpm` that was never produced.

**Fully offline.** No device, no sudo, no installed package, no package cache.
It drives `build_sdk.sh` in a scratch dir and inspects the output, which makes it
a build-host suite rather than a per-machine one.

## Flags under test

| Flag | Effect |
|---|---|
| `--rpm-release R` | `--define "release R"`; the binary also picks up `%{?dist}` from the spec |
| `--rpm-source` | extra `rpmbuild -bs` with `--define "dist %{nil}"` (implies `--rpm`) |
| `--deb-version V` | rewrites the staged `debian/changelog` version |
| `--deb-source` | `dpkg-buildpackage -F` + quilt format + orig tarball (implies `--deb`) |

## Steps

`flags_present → spec_release_dist → dist_not_doubled → no_trailing_test_exit →
rpm_invocations → deb_invocations → rpm_build → rpm_artifacts → rpm_identity →
srpm_no_dist → srpm_contents → deb_build → deb_artifacts →
deb_source_identity → deb_tree_untouched`

- **Static** (`flags_present`, `spec_release_dist`, `no_trailing_test_exit`) — instant.
- **Stubbed** (`rpm_invocations`, `deb_invocations`) — a fake `rpmbuild` /
  `dpkg-buildpackage` on `PATH` records its argv and fabricates artifacts.
  Seconds, and the only DEB coverage available on an RPM host where dpkg is absent.
- **Real build** (`dist_not_doubled` and everything from `rpm_build` on) — an
  actual compile, several minutes. `--no-build` skips the expensive group.

## Non-obvious things these catch

- **`BuildArch:` doubles the dist tag.** With a `BuildArch:` tag, rpm expands the
  `Release:` tag twice, so `%{release}%{?dist}` yields `1.60.gABC.el10.el10`.
  `mstflint-sdk.spec.in` has no `BuildArch` (it uses `ExclusiveArch`), so it is
  safe — but `spec_release_dist` fails if anyone adds one, and
  `dist_not_doubled` proves the property on a real build.
- **The `-bs` call must run before `-bb`**, so a source-packaging failure cannot
  discard an already-built binary.
- **Only `-bs` may pass `--define "dist %{nil}"`.** If `-bb` got it too, the
  binary would lose its per-distro suffix and collide across distros.
- **The orig tarball must exclude `debian/`**, or the generated
  `.debian.tar.*` diff is corrupted.
- **A trailing `[[ ... ]] && cmd` silently breaks `set -e`.** As a function's
  last line it makes the function return 1 when the test is false. Mid-function
  the same pattern is fine and is this file's established style.
- **`debian-sdk/` must stay `3.0 (native)`** in the tree; the quilt switch
  applies only to the throwaway staged copy.

## Running by hand

```bash
cd <mstflint-repo>
python3 mft_sdk/unit_tests/packaging/test_source_packages.py --so             # full
python3 mft_sdk/unit_tests/packaging/test_source_packages.py --so --no-build  # fast
```

Scratch defaults to `$SDKV_TMP_ROOT` or `/data/tmp` — never the system temp dir,
which cannot hold an SDK rpmbuild.
