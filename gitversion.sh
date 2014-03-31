#!/bin/sh

if git rev-parse --short HEAD > gitversion.tmp
then
    echo "#define TOOLS_GIT_SHA \"`tr -d '\n' < gitversion.tmp`\"" > $1 
fi
rm gitversion.tmp
