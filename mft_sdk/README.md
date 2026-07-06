# mstflint SDK (`libmstflint_sdk.so`)

The mstflint SDK is a self-contained shared library exposing a C API (the
`mst*` functions) for device discovery, HCA capability queries, PRM register
access, CR-space access, I2C access and telemetry — the mstflint counterpart of
MFT's `libmft_sdk.so`.

The library is self-contained: all mstflint dependencies (including `mtcr`) are
linked in statically, so at runtime it needs only standard system libraries
(`libstdc++`, `liblzma`, `libexpat`, `libc`, ...).

## Standalone build

The SDK can be built and installed on its own, without building the rest of the
mstflint tool suite (flint, mlxconfig, mstdump, ...).

The simplest way is the wrapper script from the repository root:

```sh
./build_sdk.sh --destdir /tmp/mstflint-sdk-stage
```

Useful options (`./build_sdk.sh --help` for the full list):

| Option | Meaning |
| --- | --- |
| `--prefix DIR` | install prefix passed to `configure` |
| `--destdir DIR` | staged install root (`DESTDIR`) |
| `--with-nvml` / `--with-nvml-include-dir DIR` | enable NVML-backed GPU discovery |
| `--with-vfio` | enable VFIO device access |
| `-j N` | parallel build jobs |
| `--build-only` | build but do not install |
| `--no-configure` | reuse the existing configuration |

## Using the make targets directly

If the tree is already configured with `--enable-mstflint-sdk` (which requires
`--enable-adb-generic-tools`):

```sh
./configure --enable-adb-generic-tools --enable-mstflint-sdk
make sdk           # build only the SDK and the subdirs it links against
make install-sdk   # install the SDK library, headers and PRM databases
```

## Installed layout

```
$(libdir)/mstflint/sdk/libmstflint_sdk.so             # stripped, redistributable
$(includedir)/mstflint/sdk/mft_sdk/*.h                # public SDK headers
$(datadir)/mstflint/prm_dbs/{hca,gpu,switch}/ext/*.adb   # PRM databases opened at runtime
```

## Using the SDK

Headers are included via the `mft_sdk/` prefix (consistent with MFT). Add the
SDK include directory to the compiler's search path:

```c
#include <mft_sdk/mft_sdk.h>
```

```sh
gcc app.c -I$(prefix)/include/mstflint/sdk -L$(prefix)/lib/mstflint/sdk -lmstflint_sdk
```
