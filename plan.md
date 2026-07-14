# Plan: make SDK package install directories customizable

## Goal

Let a user of `build_sdk.sh` control **where** the mstflint SDK artifacts install,
for both the plain (`--destdir`) path and the `--rpm` path. Before this change,
`build_sdk.sh` only forwarded `--prefix`, and it dropped even that when `--rpm`
was given — so `./build_sdk.sh --prefix ... --rpm` silently ignored the prefix
and always produced an RPM that installs to `/usr`.

Chosen approach (per review decision): **build-time configdir** — install paths
are baked into the build/RPM at configure time via standard autotools directory
variables. (Not a relocatable `Prefix:` RPM.)

## Background — how the SDK paths are derived

All SDK install locations come from autotools directory variables, so they all
respond to `--prefix` and can be individually overridden:

| Artifact                | Make variable                                   | Config var     |
|-------------------------|-------------------------------------------------|----------------|
| `libmstflint_sdk.so`    | `sdklibdir = $(libdir)/mstflint/sdk`            | `--libdir`     |
| headers                 | `sdkincludedir = $(includedir)/mstflint/sdk/mft_sdk` | `--includedir` |
| `mstflint_sdk.pc`       | `pkgconfigdir = $(libdir)/pkgconfig`            | `--libdir`     |
| PRM databases           | `pkgdatadir` (under `$(datadir)`)               | `--datadir`    |

Source of truth: `mft_sdk/Makefile.am` (lines ~61, ~119, ~136),
`mft_sdk/mstflint_sdk.pc.in` (uses `@libdir@`/`@includedir@`).

In the RPM, `mstflint-sdk.spec` builds with the `%configure` macro, which already
expands to `--prefix=%{_prefix} --libdir=%{_libdir} --includedir=%{_includedir}
--datadir=%{_datadir} ...`, and the `%files` paths (`mstflint_sdk_libdir` etc.)
are defined from those same macros. So **the spec needs no structural change** —
redefining the RPM path macros at `rpmbuild` time changes both the configure
invocation and the packaged file list consistently. `_prefix` cascades to
`_exec_prefix`/`_libdir`/`_includedir`/`_datadir` unless individually overridden.

## Changes made (applied to working tree, NOT committed)

Only `build_sdk.sh` was edited. `mstflint-sdk.spec` / `.spec.in` were intentionally
left unchanged (already parametrized via macros).

1. New CLI flags: `--libdir DIR`, `--includedir DIR`, `--datadir DIR`
   (added vars `LIBDIR`/`INCLUDEDIR`/`DATADIR`, arg parsing, and usage/help text).
2. Plain path: forwards the new flags to `./configure` as
   `--libdir=` / `--includedir=` / `--datadir=` alongside the existing `--prefix=`.
3. RPM path (`build_rpm()`): forwards them to `rpmbuild` as path-macro defines —
   `--define "_prefix ..."`, `--define "_libdir ..."`, `--define "_includedir ..."`,
   `--define "_datadir ..."` (only for flags the user actually passed). This is
   what fixes the prior bug where `--prefix` was ignored under `--rpm`.

## How to use after the change

```bash
# Plain staged install with a custom prefix + libdir
./build_sdk.sh --prefix /opt/doca --libdir /opt/doca/lib64 --destdir /tmp/stage

# RPM whose contents install under /opt/doca instead of /usr
./build_sdk.sh --rpm --prefix /opt/doca --rpm-output /tmp/rpms
```

## Verification checklist (for the reviewing/executing agent)

1. `bash -n build_sdk.sh` — passes (already confirmed).
2. Plain path dir forwarding (no full build needed):
   run with `--no-configure` removed and inspect the echoed
   `>> ./configure ...` line to confirm `--libdir/--includedir/--datadir` appear.
3. RPM path, if `rpmbuild` is available:
   `./build_sdk.sh --rpm --prefix /opt/doca --rpm-output /tmp/rpms`
   then `rpm -qlp /tmp/rpms/mstflint-sdk-*.rpm` and confirm paths are rooted at
   `/opt/doca` (e.g. `/opt/doca/lib64/mstflint/sdk/libmstflint_sdk.so`,
   `/opt/doca/lib64/pkgconfig/mstflint_sdk.pc`,
   `/opt/doca/include/mstflint/sdk/mft_sdk/...`, PRM dbs under
   `/opt/doca/share/mstflint`). Also confirm the `.pc` file's `libdir=`/`includedir=`
   lines reflect the override.
4. Sanity: a plain `./build_sdk.sh --rpm` (no dir flags) still produces the
   default `/usr`-rooted RPM — the defines are only added when flags are given.

## Follow-up: custom RPM package name (`--rpm-name`)

A client wanted to ship the SDK under a private package name to avoid clashing
with a distro-provided `mstflint-sdk` in the RPM database.

The spec already supports this: line 1 is `%{!?name: %define name mstflint-sdk}`
and `Name: %{name}`, so defining `name` at rpmbuild time overrides it. Crucially
the install paths are hardcoded to `mstflint` (e.g. `%{_libdir}/mstflint/sdk`),
NOT `%{name}`, so renaming changes package identity only — files stay put.

Changes in `build_sdk.sh` (RPM path only):
- New flag `--rpm-name NAME` (var `RPM_NAME`), forwarded as `--define "name NAME"`.
- Fixed the trailing success `ls`, which hardcoded `mstflint-sdk-*.rpm`, to use
  `${RPM_NAME:-mstflint-sdk}-*.rpm` so the rename doesn't break the final listing.

Verified: `./build_sdk.sh --rpm --rpm-name acme-mstflint-sdk --prefix /opt/doca
--libdir /opt/doca/lib64` produced `acme-mstflint-sdk-4.37.0-1.x86_64.rpm`
(`rpm -qip` Name = `acme-mstflint-sdk`) with library still at
`/opt/doca/lib64/mstflint/sdk/libmstflint_sdk.so`.

### DEB rename (`--deb-name`)

Extended the same idea to the `.deb` path. The Debian name is less centralized
than RPM's `%{name}` — it appears in three places that must stay consistent:
- `debian/control`: `Source:` and `Package:`
- `debian/changelog`: the source stanza on line 1 (dpkg errors if it disagrees
  with `control`'s `Source:`)
- `debian/rules`: `override_dh_auto_install` stages into `debian/mstflint-sdk`;
  `dh_builddeb` packages `debian/<binary-package>/`, so this path MUST equal the
  package name or the resulting .deb is empty/fails.

`build_deb()` already stages an isolated copy of `debian-sdk/` into
`$work/mstflint-sdk/debian`, so the rename is done by `sed` on that throwaway
copy (checked-in `debian-sdk/` stays generic):
- New flag `--deb-name NAME` (var `DEB_NAME`).
- `sed` rewrites `Source:`/`Package:` in control, the changelog line-1 source
  token, and the `debian/mstflint-sdk` staging path in rules.
- Fixed the trailing success `ls` (`mstflint-sdk_*.deb` -> `${DEB_NAME:-mstflint-sdk}_*.deb`).

Install paths are unaffected (they use `mstflint`, not `mstflint-sdk`).

Verification: `dpkg-buildpackage` is NOT installed on the build host, so a real
.deb was not produced. The rename `sed` commands were run against copies of the
real `debian-sdk/{control,changelog,rules}` and confirmed to rewrite all three
name sites with no leftover bare `mstflint-sdk` source tokens. A full
`--deb --deb-name ...` build should be run on a Debian/Ubuntu host to confirm
end-to-end (check `dpkg-deb -I` Package field and `dpkg-deb -c` file paths).

## Runtime PRM-database path safety (important)

The SDK opens its PRM databases at runtime via `PrmAdbDB::getDefaultDBName()`
(`tools_layouts/prm_adb_db.cpp:119`). `MST_UL` is defined unconditionally
(`configure.ac:746`), so it uses a COMPILE-TIME absolute path:
`DATA_PATH "/prm_dbs/<type>/ext/<file>"`, where `DATA_PATH` is set in
`tools_layouts/Makefile.am:41` to `$(pkgdatadir)/sdk` (= `$(datadir)/mstflint/sdk`).

Do the name/prefix/dir customizations break this? No, in the normal case:
- `DATA_PATH` (baked into the .so) and the install location of the PRM files
  (`make install-sdk` -> `$(pkgdatadir)/sdk/prm_dbs`) BOTH derive from the same
  `$(datadir)` in the SAME configure run, so they move together and cannot drift.
- Package NAME (`--rpm-name`/`--deb-name`) does not affect `pkgdatadir` at all
  (that uses autotools PACKAGE = `mstflint`, not the package Name), so renaming
  changes nothing here.
- `--libdir`/`--includedir` do not affect `DATA_PATH` (only `datadir`/`prefix` do).

Verified empirically on the `/opt/doca` RPM: `strings` on `libmstflint_sdk.so`
shows `DATA_PATH` = `/opt/doca/share/mstflint/sdk` and the `.adb` files install
to `/opt/doca/share/mstflint/sdk/prm_dbs/...` — exact match.

Caveat: `DATA_PATH` is absolute with NO runtime fallback (no getenv / no
relative-to-.so lookup) in the MST_UL branch. So the flow breaks ONLY if the
package is deployed to a prefix different from the one it was built for
(RPM relocation, or manually moving files). Build-time configdir keeps
build-prefix == install-prefix, so it's safe. `--destdir` staging is fine
(DESTDIR only prepends at install time; the baked prefix is the final one).

## Notes / caveats

- Overriding only `--prefix` uses the distro default libdir suffix (`lib` vs
  `lib64`); pass `--libdir` explicitly if a specific suffix is required.
- This is build-time customization: each distinct path layout is a separate
  build. Relocating an already-built RPM (`rpm --prefix`) is out of scope and
  would need `Prefix:` tags in the spec (the alternative that was not chosen).
- `--deb` path (`build_deb()` / `debian-sdk/`) was not touched; if per-dir
  customization is later wanted there too, it needs its own follow-up.
