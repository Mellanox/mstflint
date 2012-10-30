#!/bin/sh

if git rev-parse --short HEAD > gitversion.tmp
then
    echo "#define TOOLS_SVN_VER \"`tr -d '\n' < gitversion.tmp`\"" > gitversion.h
fi
rm gitversion.tmp
