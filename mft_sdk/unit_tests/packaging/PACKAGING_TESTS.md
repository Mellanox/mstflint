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
