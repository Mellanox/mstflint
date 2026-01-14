#!/bin/sh

if git rev-parse --short HEAD > gitversion.tmp
then
    echo "#define PACKAGE_GIT_VER \"`tr -d '\n' < gitversion.tmp`\"" > $1 
fi
rm gitversion.tmp
