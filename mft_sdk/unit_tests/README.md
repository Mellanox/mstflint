# mstflint SDK unit tests

Validation suites for `libmstflint_sdk.so` (see `../README.md`). The Python
scripts compare the SDK's output — via an installed gtest harness binary —
field-by-field against the reference CLI tools; the C++ sources are the gtest
suites themselves.

## Layout

| Path | Content |
|---|---|
| `utils.py` | Shared infra: device discovery, command runner, runner bases, CLI, KNOWN_MISSING |
| `mlxlink/` | 5 compare suites (operational info, counters, FEC histogram, cable DDM, module info) + gtest sources |
| `mlxreg/` | 5 compare suites (register list/access/metadata/full path/error handling) + gtest sources |
| `discovery/`, `hca_caps/`, `telemetry/`, `segfault/` | gtest-only suites (run via the installed harness with `--gtest_filter`) |
| `packaging/` | `build_sdk.sh` packaging-flags validation (variants, relocation, coexistence) |
| `test_utils.*`, `mft_sdk_test_main.cpp`, `mlxreg/mlxreg_fields.h` | gtest harness sources (shared `main()`, field-name parsing contract) |

## Running

Tests run against **installed packages** (`--so` mode); building test binaries
from this tree is not supported yet — the gtest sources are compiled into the
harness by the MFT build for now.

```bash
cd <mstflint-repo>
MFT_SDK_SO_DIR=/usr/lib64/mstflint/sdk \
MFT_SDK_SO_TEST_BIN=/usr/lib64/mft_sdk/tests/mft_sdk_mstflint_so_test \
MFT_SDK_KNOWN_MISSING=<comma-list> \
python3 mft_sdk/unit_tests/mlxreg/test_register_access.py --compare -d <BDF> --so
```

Env knobs (all consumed by `utils.py`):

- `MFT_SDK_SO_DIR` — SDK lib dir (forwarded through sudo as `LD_LIBRARY_PATH`).
- `MFT_SDK_SO_TEST_BIN` — installed gtest harness binary.
- `MFT_SDK_KNOWN_MISSING` — comma list of register/field names the reference
  CLI knows but this SDK does not yet (underscores stand for spaces); such
  rows count as expected differences, everything else stays strict.
- `MFT_SDK_REG_TOOL` — reference reg CLI for the mlxreg compare (default
  `mlxreg_ext`; e.g. `mstreg`).
- `MSTFLINT_PKG_CACHE` — package cache root (required by `packaging/` only).

## Provenance / sync

The Python suites, field mirrors and gtest sources are synced from the MFT
repo (`user/mft_sdk/unit_tests/`), which is the upstream for shared files;
only `utils.py` intentionally diverges (no build machinery here). The
`packaging/` suite is owned by this repo.
