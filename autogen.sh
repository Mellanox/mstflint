#! /bin/sh

# create config dir if not exist
test -d config || mkdir config

sh gitversion.sh ./common/gitversion.h

set -x
aclocal -I config
libtoolize --force --copy
autoheader
automake --foreign --add-missing --copy
autoconf
