#!/bin/bash

# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Prints the full release version for the base version given as $1 (the
# AC_INIT version). On a release tag that is 4.35.0-1.14; commits after
# the tag keep the distance and hash (4.35.0-1.14-47-gabc1234) so they
# cannot pose as the tagged drop. The suffix exists only as a git tag
# (v<base>-<release>), so it comes from git in a checkout, or from
# RELEASE_VERSION_FILENAME, which "git archive" fills in through export-subst.
# Falls back to the base version so an empty suffix is never printed.
# Both sources use the same git-describe match so a checkout and an archive
# of the same commit report the same version.

CDPATH= cd -- "$(dirname -- "$0")" > /dev/null || exit 1

BASE_VERSION=$1
RELEASE_VERSION_FILENAME=tools_release_version

VERSION=
# Only this tree's own git metadata counts, not that of an enclosing repository.
if [ -e .git ]; then
  VERSION=$(git describe --tags --match 'v[0-9]*' 2>/dev/null) || VERSION=
fi
if [ -z "$VERSION" ] && [ -f "$RELEASE_VERSION_FILENAME" ]; then
  VERSION=$(head -n 1 "$RELEASE_VERSION_FILENAME") || VERSION=
fi
VERSION=${VERSION#v}

# The value ends up in C and Python string literals and in sed replacements.
case "$VERSION" in
  *[!A-Za-z0-9._-]*) VERSION=$BASE_VERSION ;;
  "${BASE_VERSION}"-?*) ;;
  *) VERSION=$BASE_VERSION ;;
esac

printf '%s\n' "$VERSION"
