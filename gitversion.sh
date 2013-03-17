#!/bin/sh

if git rev-parse --short HEAD > gitversion.tmp
then
    echo "#define TOOLS_SVN_VER \"`tr -d '\n' < gitversion.tmp`\"" > $1 
fi
rm gitversion.tmp
