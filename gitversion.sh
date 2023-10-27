#!/bin/bash

OUTPUT_FILE=${1:?Error: Filename parameter is missing.}

unset git_sha
if git rev-parse --is-inside-work-tree > /dev/null 2>&1; then
  git_sha=$(git rev-parse --short HEAD)
else
  if [ -f "$OUTPUT_FILE" ]; then
    # we assume it was created while we were inside the repository
    exit 0
  else
    git_sha="N/A"
  fi
fi

if [ -z "$git_sha" ]; then
  echo "an unexpected error occurred"
  exit 1
fi

cat > "$OUTPUT_FILE" <<EOL
#ifndef TOOLS_GIT_SHA_H
#define TOOLS_GIT_SHA_H
#define TOOLS_GIT_SHA "$git_sha"
#endif
EOL
