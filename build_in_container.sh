#/bin/bash
set -x
set -e 
cd $(dirname "${BASH_SOURCE[0]}")
REPO_ROOT=$(git rev-parse --show-toplevel --show-prefix)

docker build -t mstflint:builder .
docker run -it --rm -v $REPO_ROOT:/sources mstflint:builder /sources/build.sh