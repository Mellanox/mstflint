#/bin/bash
set -x
set -e

# go to root of repository
cd $(dirname "${BASH_SOURCE[0]}")
cd $(git rev-parse --show-toplevel --show-prefix)

# build from source
./autogen.sh
./configure
make V=1
make install
