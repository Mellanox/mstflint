#!/bin/sh -e

OUT=${1:?Error: filename is missing.}

git_sha=$(git rev-parse --short HEAD) || git_sha="undefined"

cat > "$OUT" <<EOL
#ifndef TOOLS_GIT_SHA_H
#define TOOLS_GIT_SHA_H
#define TOOLS_GIT_SHA "$git_sha"
#endif
EOL
