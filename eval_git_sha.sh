#!/bin/bash

# Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

GIT_SHA_FILENAME=tools_git_sha

unset GIT_SHA

# Check if the current directory is inside a Git repository.
if git rev-parse --is-inside-work-tree > /dev/null 2>&1; then
  # If inside a Git repository, retrieve commit hash.
  GIT_SHA=$(git rev-parse --short HEAD)
else
  # If not in a Git repository, check if GIT_SHA_FILENAME exists.
  if [ -f "$GIT_SHA_FILENAME" ]; then
    # If the file exists, assume it contains the commit hash.
    GIT_SHA=$(<"$GIT_SHA_FILENAME")
  else
    GIT_SHA="N/A"
  fi
fi

if [ -z "$GIT_SHA" ]; then
  echo "an unexpected error occurred"
  exit 1
fi

# Calling code expects evaluated commit hash in STDOUT. In addition we
# refresh the content of GIT_SHA_FILENAME to ensure it is up to date.
echo $GIT_SHA | tee "$GIT_SHA_FILENAME"
