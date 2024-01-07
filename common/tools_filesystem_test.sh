#!/bin/bash -e

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

# set -x

TEST_BINARY=$1
# echo $TEST_BINARY
ORIG_PWD=$(pwd)
# echo $ORIG_PWD

setup() {
  echo "setup"
  mkdir data
  pushd data

  # a bit of overkill :-)
  #  mkdir data/overkill
  #  for special in $(seq 0 7); do
  #    for owner in $(seq 0 7); do
  #      for group in $(seq 0 7); do
  #        for others in $(seq 0 7); do
  #          install -m $special$owner$group$others /dev/null overkill/file-$special$owner$group$others
  #          install -m $special$owner$group$others -d overkill/folder-$special$owner$group$others
  #        done
  #      done
  #    done
  #  done

  install /dev/null regular-file
  install /dev/null regular-file.extension
  install /dev/null regular-file.another-extension
  install -d regular-folder
  ln -snf regular-file soft-link-to-file
  ln -snf regular-file soft-link-to-file.extension
  ln -snf regular-file soft-link-to-file.another-extension
  ln -snf soft-link-to-file soft-link-to-soft-link-to-file
  ln -snf soft-link-to-file soft-link-to-soft-link-to-file.extension
  ln -snf soft-link-to-file soft-link-to-soft-link-to-file.another-extension
  ln -snf $(readlink -f regular-file) soft-link-to-file-absolute-path
  ln -snf $(readlink -f regular-file) soft-link-to-file-absolute-path.extension
  ln -snf $(readlink -f regular-file) soft-link-to-file-absolute-path.another-extension
  ln -snf regular-folder soft-link-to-folder
  ln -snf soft-link-to-folder soft-link-to-soft-link-to-folder
  ln -snf $(readlink -f regular-folder) soft-link-to-folder-absolute-path
  ln -snf "does not exist" dead-soft-link
  ln -nf regular-file hard-link-to-file
  ln -nf regular-file hard-link-to-file.extension
  ln -nf regular-file hard-link-to-file.another-extension
  ln -nf regular-file hard-link-to-file-absolute-path
  ln -nf regular-file hard-link-to-file-absolute-path.extension
  ln -nf regular-file hard-link-to-file-absolute-path.another-extension
  install /dev/null "file with spaces in the name"
  install /dev/null "file with spaces in the name.with extension"
  install /dev/null "file with spaces in the name.with another extension"
  install -d "folder with spaces in the name"
  install -m 0311 -d folder-0311 # Access: (0311/d-wx--x--x)
  install /dev/null folder-0311/file
  install -d folder-0311/folder
  install -d empty-folder
  install /dev/null a    # corner
  install /dev/null .a   #  cases
  install /dev/null a.   #   for ".", ".." skip
  install /dev/null ..a  #    feature
  install -d folder-with-content
  install /dev/null folder-with-content/file
  install -d folder-with-content/folder

  popd
  echo "setup done"
}

teardown() {
  echo "cleanup"
  cd "$ORIG_PWD"
  if [ -e data ]; then
    chmod -R 777 data
    rm -rf data
  fi
  echo "cleanup done"
}

trap "teardown" EXIT
trap "teardown && exit 1" SIGINT SIGTERM

setup
./common/"$TEST_BINARY"
# ./common/"$TEST_BINARY" --gtest_list_tests
# ./common/"$TEST_BINARY" --gtest_filter="path.*"
# ./common/"$TEST_BINARY" --gtest_filter="path.Construct*"
# ./common/"$TEST_BINARY" --gtest_filter="path.Exten*"
# ./common/"$TEST_BINARY" --gtest_filter="path.IsRelative*"
# ./common/"$TEST_BINARY" --gtest_filter="path.Pare*"
# ./common/"$TEST_BINARY" --gtest_filter="path.Equ*"

# ./common/"$TEST_BINARY" --gtest_filter="directory_iterator.*"
# ./common/"$TEST_BINARY" --gtest_filter="directory_iterator.EmptyFolder" --gtest_repeat=10000
# ./common/"$TEST_BINARY" --gtest_filter="directory_iterator.Loop" --gtest_repeat=10000
# ./common/"$TEST_BINARY" --gtest_filter="directory_iterator.RangeLoop" --gtest_repeat=10000
# ./common/"$TEST_BINARY" --gtest_filter="directory_iterator.ForEachClassic"
# ./common/"$TEST_BINARY" --gtest_filter="directory_iterator.ForEachLambda"
# ./common/"$TEST_BINARY" --gtest_filter="directory_iterator.BackInserter"
