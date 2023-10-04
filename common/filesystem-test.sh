#!/bin/bash -e

# set -x

ORIG_PWD=$(pwd)

echo $ORIG_PWD

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
  install -d regular-folder
  ln -snf regular-file soft-link-to-file
  ln -snf soft-link-to-file soft-link-to-soft-link-to-file
  ln -snf $(readlink -f regular-file) soft-link-to-file-absolute-path
  ln -snf regular-folder soft-link-to-folder
  ln -snf soft-link-to-folder soft-link-to-soft-link-to-folder
  ln -snf $(readlink -f regular-folder) soft-link-to-folder-absolute-path
  ln -snf "does not exist" dead-soft-link
  ln -nf regular-file hard-link-to-file
  ln -nf regular-file hard-link-to-file-absolute-path
  install /dev/null "file with spaces in the name"
  install -d "folder with spaces in the name"
  install -m 0311 -d folder-0311 # Access: (0311/d-wx--x--x)
  install /dev/null folder-0311/file
  install -d folder-0311/folder

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
common/filesystem-test-bin
