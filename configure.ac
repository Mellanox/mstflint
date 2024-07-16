# Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

dnl Process this file with autoconf to produce a configure script.

AC_INIT(mstflint, 4.29.0, akiselman-org@exchange.nvidia.com)

AC_DEFINE_UNQUOTED([PROJECT], ["mstflint"], [Define the project name.])
AC_SUBST([PROJECT])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([README])
AM_INIT_AUTOMAKE([foreign subdir-objects])

dnl Checks for programs
AC_PROG_CC
AC_PROG_CXX
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT
AC_CONFIG_HEADERS( config.h )

# OPENSSL_VERSION_NUMBER < 0x100020bf
#0x100020bfL = OpenSSL 1.0.2k - 26 Jan 2017
MIN_OPENSSL_VER="1.0.2k"
AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM([[
#include <openssl/ssl.h>
#if OPENSSL_VERSION_NUMBER < 0x100020bf
  ERROR: OPENSSL_VERSION_NUMBER version must be >= 0x100020bf ("OpenSSL 1.0.2k - 26 Jan 2017")
#endif
]])], [OPENSSL_VERSION_VALID=yes], [OPENSSL_VERSION_VALID=no])
OS=$(uname -s)
KERNEL_VER=`uname -r | egrep -E -o '[[0-9]]+\.[[0-9]]+' | head -1`
OFED_VER=`ofed_info -s | egrep -E -o '[[0-9]]+\.[[0-9]]+' | head -1`
OFED_EXIST=`ofed_info -s`
OFED_NOT_EXIST="ofed_info: command not found"
MTCR_CONF_DIR=""
LDL=""
default_en_inband=""
default_en_rdmem="no"
OFED_VERSION_CHK=0
KERNEL_BUILD_CHK=0

if test "x$OFED_EXIST" != "x$OFED_NOT_EXIST"; then
  if test $(echo $OFED_VER 5.6 | tr " " "\n" | sort -V | tail -n 1) == $OFED_VER ; then
      OFED_VERSION_CHK=1
  fi
fi

AM_CONDITIONAL(OFED_BUILD,[test ${OFED_VERSION_CHK} = 1])
AC_SUBST(OFED_BUILD)

#AC_MSG_NOTICE(Kernel: ${KERNEL_VER})

if test ${KERNEL_VER} \> "x5.13" ; then
    KERNEL_BUILD_CHK=1
fi

AM_CONDITIONAL(KERNEL_BUILD,[test ${KERNEL_BUILD_CHK} = 1])
AC_SUBST(KERNEL_BUILD)

LDFLAGS="${LDFLAGS} -L/usr/local/lib -L/usr/local/lib64 -L/usr/lib64"
CXXFLAGS="${CXXFLAGS} -isystem /usr/local/include"
if test "x$OS" = "xFreeBSD"; then
    AC_MSG_NOTICE(FreeBSD Build)
    MTCR_CONF_DIR="mtcr_freebsd"
    CFLAGS="${CFLAGS} -I /usr/local/include"
else
    MTCR_CONF_DIR="mtcr_ul"
    LDL="-ldl"
    default_en_inband="yes"
    if test ${OFED_VERSION_CHK} -eq 1 ; then
        default_en_rdmem="yes"
    fi
fi
AC_SUBST(MTCR_CONF_DIR)
AC_SUBST(LDL)
AC_SUBST(default_en_inband)

AM_CONDITIONAL(ARM64_BUILD, [ echo $build_cpu | grep -iq "aarch64" ])
AM_CONDITIONAL(X86_64_BUILD, [ echo $build_cpu | grep -iq "x86_64" ])

dnl Checks for headers
AC_CHECK_HEADER(termios.h,[CXXFLAGS="${CXXFLAGS} -DHAVE_TERMIOS_H"])
AC_CHECK_HEADER(sys/pci.h,[CXXFLAGS="${CXXFLAGS} -DHAVE_SYS_PCI_H"])
TOOLS_CRYPTO=""
MAD_IFC=""
FW_MGR_TOOLS=""
XZ_UTILS_DIR=""
ADABE_TOOLS=""
ADABE_DBS=""
ADABE_DBS_EXTRA_DIST=""
DPA=""

COMPILER_FPIC="-fPIC"
AC_SUBST(COMPILER_FPIC)

AC_MSG_CHECKING(--enable-dc argument)
AC_ARG_ENABLE(dc,
		    [  --disable-dc            Disable mstflint "dc" command. Eliminates zlib dependency],
		    [enable_dc=$enableval],
		    [enable_dc="yes"])
AC_MSG_RESULT($enable_dc)
if test "$enable_dc" = "yes"; then
  AC_CHECK_HEADER(zlib.h,,AC_MSG_ERROR([cannot find zlib.h . Use --disable-dc to remove this dependency]))
  AC_CHECK_LIB(z, uncompress,, AC_MSG_ERROR([cannot find zlib uncompress() function. Use --disable-dc to remove this dependency]))
fi

# FWMANAGER
AC_MSG_CHECKING(--enable-fw-mgr argument)
AC_ARG_ENABLE(fw-mgr,
             [  --enable-fw-mgr         Enable compiling mstfwmanager tool and features],
             [enable_fw_mgr="yes"],
             [enable_fw_mgr="no"])
AC_MSG_RESULT($enable_fw_mgr)
if test "x$enable_fw_mgr" = "xyes"; then
    AC_CHECK_HEADER(curl/curl.h,,AC_MSG_ERROR([cannot find curl/curl.h . this header is needed for compiling fw manager tool]))
    AC_CHECK_HEADER(zlib.h,,AC_MSG_ERROR([cannot find zlib.h . this header is needed for compiling fw manager tool]))
    AC_CHECK_LIB(z, uncompress,, AC_MSG_ERROR([cannot find zlib uncompress() function.]))
    AC_CHECK_HEADER(lzma.h,,AC_MSG_ERROR([Cannot find lzma.h.]))
    CURL_INC_DIR=/usr/include/curl/
fi

# mlxdpa
AC_MSG_CHECKING(--enable-dpa argument)
AC_ARG_ENABLE(dpa,
             [  --enable-dpa            Enable compiling mstdpa tool (x86_64/aarch64 Linux only, no FreeBSD support],
             [enable_dpa="yes"],
             [enable_dpa="no"])
AC_MSG_RESULT($enable_dpa)

# Adabe
AC_MSG_CHECKING(--enable-adb-generic-tools argument)
AC_ARG_ENABLE(adb-generic-tools,
             [  --enable-adb-generic-tools        Enable compiling the following tools which depends on ADABE: mstreg and mstlink],
             [enable_adb_generic_tools="yes"],
             [enable_adb_generic_tools="no"])
AC_MSG_RESULT($enable_adb_generic_tools)
if test "x$enable_adb_generic_tools" = "xyes"; then
    AC_LANG_PUSH([C++])
        AC_CHECK_LIB([expat], XML_ParserCreate_MM,
                [AC_CHECK_HEADERS(expat.h, have_expat=true, have_expat=false)],
                have_expat=false)
        if ! $have_expat; then
        AC_MSG_ERROR([Expat library is missing, please install expat xml parser to continue: expat-devel.]
                [http://expat.sourceforge.net/])
        fi
    AC_LANG_POP([C++])
fi

AC_SUBST(CURL_INC_DIR)

AM_CONDITIONAL(ENABLE_FWMGR, [test "x$enable_fw_mgr" = "xyes" ])
AC_SUBST(ENABLE_FWMGR)

AC_SUBST(ENABLE_FWMGR)
# XML2
AC_MSG_CHECKING(--enable-xml2 argument)
AC_ARG_ENABLE(xml2,
            [  --enable-xml2           Enable mstflint libxml2 dependent features],
            [enable_xml2="yes"],
            [enable_xml2="no"])
AC_MSG_RESULT($enable_xml2)
if test [ "x$enable_xml2" = "xyes" ] || [ test "x$enable_fw_mgr" = "xyes" ]; then
    # XML2 checks
    AC_LANG_PUSH([C++])
        if test "x$OS" = "xFreeBSD"; then
            CXXFLAGS="${CXXFLAGS} -isystem /usr/local/include/libxml2"
        else
            CXXFLAGS="${CXXFLAGS} -isystem /usr/include/libxml2"
        fi
        AC_CHECK_HEADER([libxml2/libxml/xpath.h],[],[AC_MSG_ERROR([libxml2: xpath.h is not found in the system PATH. make sure libxml2 headers are installed.])])
        AC_CHECK_LIB(xml2, xmlDocDumpFormatMemoryEnc,, AC_MSG_ERROR([cannot find xml2 xmlDocDumpFormatMemoryEnc() function. Try re-installing the library...]))
    AC_LANG_POP([C++])
fi

AM_CONDITIONAL(DISABLE_XML2, [test  "x$enable_xml2" = "xno"])
AC_SUBST(DISABLE_XML2)

AM_CONDITIONAL(ENABLE_DC, [test  "x$enable_dc" = "xyes"])
AC_SUBST(ENABLE_DC)

AC_MSG_CHECKING(--enable-inband argument)
AC_ARG_ENABLE(inband,
		    [  --disable-inband        Disable inband access. Prevents FW update for Mellanox SwitchX and ConnectIB devices. Eliminates infiniband/mad.h dependency],
		    [enable_inband=$enableval],
		    [enable_inband=$default_en_inband])
AC_MSG_RESULT($enable_inband)
if test "x$enable_inband" = "xyes"; then
  AC_CHECK_HEADER(infiniband/mad.h,,AC_MSG_ERROR([cannot find infiniband/mad.h . Use --disable-inband to remove this dependency]))
  MAD_IFC="mad_ifc"
else
  CXXFLAGS="$CXXFLAGS -DNO_INBAND"
  CFLAGS="$CFLAGS -DNO_INBAND"
fi
AC_SUBST(MAD_IFC)

AM_CONDITIONAL(ENABLE_INBAND, [test  "x$enable_inband" = "xyes"])

AC_MSG_CHECKING(--enable-rdmem argument)
AC_ARG_ENABLE(rdmem,
		    [  --enable-rdmem        Enable resource-dump memory mode. OFED libmlx5 and libibverbs dependency],
		    [enable_rdmem=$enableval],
		    [enable_rdmem=$default_en_rdmem])
AC_MSG_RESULT($enable_rdmem)
if test "x$enable_rdmem" = "xyes"; then
  AC_CHECK_HEADERS(infiniband/mlx5dv.h infiniband/verbs.h,,AC_MSG_ERROR([cannot find infiniband/mlx5dv.h or infiniband/verbs.h . Use --disable-rdmem to remove this dependency]))
else
  CXXFLAGS="$CXXFLAGS -DNO_RDMEM"
  CFLAGS="$CFLAGS -DNO_RDMEM"
fi

AM_CONDITIONAL(ENABLE_RDMEM, [test  "x$enable_rdmem" = "xyes"])

AC_MSG_CHECKING(--enable-cs argument)
AC_ARG_ENABLE(cs,
            [  --enable-cs             Enable mstflint "checksum" command, dependent of openssl library],
            [enable_cs="yes"],
            [enable_cs="no"])
AC_MSG_RESULT($enable_cs)
if test "x$enable_cs" = "xyes"; then
  AC_CHECK_HEADER(openssl/md5.h,,AC_MSG_ERROR([cannot find openssl/md5.h . remove --enable-cs to remove this dependency or install openssl]))
  TOOLS_CRYPTO="tools_crypto"
fi

AC_MSG_CHECKING(openssl argument)
AC_ARG_ENABLE(openssl,
            [  --disable-openssl       Disable functionalities that depend on the OpenSSL library],
            [enable_openssl=$enableval],
            [enable_openssl="yes"])
AC_MSG_RESULT($enable_openssl)
if test "x$enable_openssl" = "xyes"; then
  # check version >= 1.1.1 (not implemented)
  AC_CHECK_HEADER(openssl/sha.h,,AC_MSG_ERROR([cannot find openssl/sha.h . remove --enable-openssl to remove this dependency or install openssl]))
  AC_CHECK_HEADER(openssl/rsa.h,,AC_MSG_ERROR([cannot find openssl/rsa.h . remove --enable-openssl to remove this dependency or install openssl]))
  AC_CHECK_HEADER(openssl/pem.h,,AC_MSG_ERROR([cannot find openssl/pem.h . remove --enable-openssl to remove this dependency or install openssl]))
  AC_CHECK_HEADER(openssl/bio.h,,AC_MSG_ERROR([cannot find openssl/bio.h . remove --enable-openssl to remove this dependency or install openssl]))
  AC_CHECK_HEADER(openssl/md5.h,,AC_MSG_ERROR([cannot find openssl/md5.h . remove --enable-openssl to remove this dependency or install openssl]))
  TOOLS_CRYPTO="tools_crypto mlxsign_lib"
fi

AC_MSG_CHECKING(--enable-all-static argument)
AC_ARG_ENABLE([all_static],
    AS_HELP_STRING([--enable-all-static], [Enable creating none dynamic executables]),
    [enable_all_static="yes"],
    [enable_all_static="no"])
AC_MSG_RESULT($enable_all_static)

AS_IF([test "x$enable_all_static" = "xyes"], [
  if test "x$enable_dc" = "xyes"; then
    AC_MSG_ERROR([cannot enable all static with enable dc . add --disable-dc to remove dependency with dynamic zlib])
  fi
  if test "x$enable_openssl" = "xyes"; then
    AC_MSG_ERROR([cannot enable all static with enable openssl . add --disable-openssl to remove dependency with dynamic openssl])
  fi
  if test "x$enable_inband" = "xyes"; then
    AC_MSG_ERROR([cannot enable all static with enable inband . add --disable-inband to remove dependency with dynamic inband])
  fi
  LDFLAGS="$LDFLAGS -all-static"
  CFLAGS="$CFLAGS -DSQLITE_OMIT_LOAD_EXTENSION=0 -DIBVSMAD_DLOPEN"
])

AC_SUBST(TOOLS_CRYPTO)
AM_CONDITIONAL(ENABLE_OPENSSL, [test "x$enable_openssl" = "xyes" ])
AM_CONDITIONAL(ENABLE_CS, [test  "x$enable_cs" = "xyes" || test "x$enable_openssl" = "xyes" ])

AC_ARG_ENABLE([static_libstdcpp],
    AS_HELP_STRING([--enable-static-libstdcpp], [Enable link static to libstdc++]))

AS_IF([test "x$enable_static_libstdcpp" = "xyes" -o "x$enable_all_static" = "xyes" ], [
  CXXFLAGS="$CXXFLAGS -static-libstdc++ -static-libgcc"
])

AC_ARG_ENABLE([dynamic_ld],
    AS_HELP_STRING([--enable-dynamic-ld], [Enable dynamic link to ld64.so]))

AS_IF([test "x$enable_dynamic_ld" = "xyes"], [
  LDFLAGS="$LDFLAGS -Wl,--dynamic-linker=/lib64/ld64.so.2"
])

AC_CHECK_HEADERS(iniparser.h, INIPARSER_SYSTEM_AVAILABLE="yes", INIPARSER_SYSTEM_AVAILABLE="no")

if test "$INIPARSER_SYSTEM_AVAILABLE" = "yes"; then
  AC_SEARCH_LIBS([iniparser_load], [iniparser], [INIPARSER_SYSTEM_AVAILABLE="yes"],[
    INIPARSER_SYSTEM_AVAILABLE="no"
  ])
fi

if test "$INIPARSER_SYSTEM_AVAILABLE" = "no"; then
    INIPARSER_CFLAGS='-I$(top_srcdir)/ext_libs/iniParser'
    AC_SUBST(INIPARSER_CFLAGS)
    INIPARSER_LIBS='$(top_builddir)/ext_libs/iniParser/libiniparser.la'
    AC_SUBST(INIPARSER_LIBS)
fi

AM_CONDITIONAL([USE_LOCAL_INIPARSER], [test "$INIPARSER_SYSTEM_AVAILABLE" = no])
AS_IF([test "x$INIPARSER_SYSTEM_AVAILABLE" = "xyes" ], [
    CXXFLAGS="$CXXFLAGS -DHAVE_INI_PARSER"
])


AC_SEARCH_LIBS([JSON], [jsoncpp], [JSON_SYSTEM_AVAILABLE="yes"],[
    JSON_SYSTEM_AVAILABLE="no"
    JSON_CFLAGS='-I$(top_srcdir)/ext_libs/json'
    AC_SUBST(JSON_CFLAGS)
    JSON_LIBS='$(top_builddir)/ext_libs/json/libjson.la'
    AC_SUBST(JSON_LIBS)
])
AM_CONDITIONAL([USE_LOCAL_JSON], [test "$JSON_SYSTEM_AVAILABLE" = no])

AC_SEARCH_LIBS([mupCreateVar], [muparser], [MUPARSER_SYSTEM_AVAILABLE="yes"],[
    MUPARSER_SYSTEM_AVAILABLE="no"
    MUPARSER_CFLAGS='-I$(top_srcdir)/ext_libs/muparser'
    AC_SUBST(MUPARSER_CFLAGS)
    MUPARSER_LIBS='$(top_builddir)/ext_libs/muparser/libmuparser.la'

    AC_SUBST(MUPARSER_LIBS)
])
AM_CONDITIONAL([USE_LOCAL_MUPARSER], [test "$MUPARSER_SYSTEM_AVAILABLE" = no])

AC_SEARCH_LIBS([sqlite3_initialize], [sqlite3], [SQLITE_SYSTEM_AVAILABLE="yes"],[
    SQLITE_SYSTEM_AVAILABLE="no"
    SQLITE_CFLAGS='-I$(top_srcdir)/ext_libs/sqlite'
    AC_SUBST(SQLITE_CFLAGS)
    SQLITE_LIBS='$(top_builddir)/ext_libs/sqlite/libsqlite3.la'
    AC_SUBST(SQLITE_LIBS)
])
AM_CONDITIONAL([USE_LOCAL_SQLITE], [test "$SQLITE_SYSTEM_AVAILABLE" = no])


CFLAGS="$CFLAGS -DMST_UL"
CXXFLAGS="$CXXFLAGS -DMST_UL"


CCVER=`${CC} --version | grep ${CC} | grep -E -o "( )[[4-9]]\.[[0-9]]\.[[0-9]]" | head -1`
AC_MSG_NOTICE(Compiler: ${CC}; version: ${CCVER};)
if test ${CCVER} \> 5.0.0 ; then
    CXXFLAGS="$CXXFLAGS -std=c++14"
    CFLAGS="$CFLAGS -fgnu89-inline"
elif test ${CCVER} \> 4.7.2 ; then
    CXXFLAGS="$CXXFLAGS -std=c++11"
fi

AM_CFLAGS="-Wall"
AM_CXXFLAGS="-Wall"

AC_CONFIG_FILES( mstflint.spec )

# We save and restore CFLAGS, after adding Wall and Werror
# because AX_CHECK_COMPILE_FLAG doesn't work properly without it

# C related ignores
OLD_CFLAGS="$CFLAGS"
CFLAGS="$CFLAGS -Wall -Werror"
AX_CHECK_COMPILE_FLAG([-Wno-format-overflow], [CFLAGS="$CFLAGS -Wno-format-overflow"], [], [])
AX_CHECK_COMPILE_FLAG([-Wno-implicit-fallthrough], [CFLAGS="$CFLAGS -Wno-implicit-fallthrough"], [], [])
AX_CHECK_COMPILE_FLAG([-Wno-cast-function-type], [CFLAGS="$CFLAGS -Wno-cast-function-type"], [], [])
CFLAGS="$OLD_CFLAGS"

# C++ related ignores
OLD_CXXFLAGS="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -Wall -Werror"
AC_LANG_PUSH([C++])
AX_CHECK_COMPILE_FLAG([-Wno-implicit-fallthrough], [CXXFLAGS="$CXXFLAGS -Wno-implicit-fallthrough"], [], [])
AX_CHECK_COMPILE_FLAG([-Wno-format-overflow], [CXXFLAGS="$CXXFLAGS -Wno-format-overflow"], [], [])
AX_CHECK_COMPILE_FLAG([-Wno-cast-function-type], [CXXFLAGS="$CXXFLAGS -Wno-cast-function-type"], [], [])
AX_CHECK_COMPILE_FLAG([-Wno-class-memaccess], [CXXFLAGS="$CXXFLAGS -Wno-class-memaccess"], [], [])
AC_LANG_POP([C++])
CXXFLAGS="$OLD_CXXFLAGS"

TOOLS_BUILD_TIME=`date  +"%b %d %Y\, %H:%M:%S"`
if test "x$SOURCE_DATE_EPOCH" != "x"; then
    TOOLS_BUILD_TIME=`LC_ALL=C date -u -d @$SOURCE_DATE_EPOCH +"%b %d %Y\, %H:%M:%S"`
fi
AC_SUBST(TOOLS_BUILD_TIME)

AC_ARG_VAR(MSTFLINT_VERSION_STR, The MSTFLINT version)
if test x"$MSTFLINT_VERSION_STR" == x; then
    MSTFLINT_VERSION_STR="$PACKAGE_STRING"
fi

AC_SUBST(MSTFLINT_VERSION_STR)
AC_DEFINE([MSTFLINT_VERSION_STR], [], [The MSTFLINT version])
AC_DEFINE_UNQUOTED(MSTFLINT_VERSION_STR, "$MSTFLINT_VERSION_STR")


AS_IF([test "x$enable_cs" = "xyes" || test "x$enable_openssl" = "xyes"], [
        AC_CONFIG_FILES(tools_crypto/Makefile)
    ])


AS_IF([test "x$enable_openssl" = "xyes"], [
    AS_IF(test x"$OPENSSL_VERSION_VALID" = "xyes",
        [AC_CONFIG_FILES(mlxsign_lib/Makefile)],
        [AC_MSG_ERROR([Required OpenSSL version >= $MIN_OPENSSL_VER (or use --disable-openssl)])])
])

if [ test "x$enable_openssl" = "xno" ] && \
    [ test "x$enable_fw_mgr" = "xyes" ] ; then
    AC_MSG_ERROR([--enable-fw-mgr cannot be used with --disabled-openssl.])
fi

AS_IF([test "x$enable_fw_mgr" = "xyes"], [
        AC_CONFIG_FILES(mlxfwupdate/Makefile)
        AC_CONFIG_FILES(ext_libs/iniParser/Makefile)
        AC_CONFIG_FILES(mlxarchive/Makefile)
        FW_MGR_TOOLS="mlxfwupdate mlxarchive"
    ])

AC_SUBST(FW_MGR_TOOLS)

AS_IF([test "x$enable_dpa" = "xyes"], [
    AC_CONFIG_FILES(mlxdpa/Makefile)
    DPA="mlxdpa"
])
AM_CONDITIONAL(ENABLE_DPA, [test "x$enable_dpa" = "xyes" ])

AC_SUBST(DPA)

AS_IF([test "x$enable_adb_generic_tools" = "xyes"], [
        AC_CONFIG_FILES(adb_parser/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/hca/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/hca/ext/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/switch/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/switch/ext/Makefile)
        AC_CONFIG_FILES(mlxreg/Makefile)
        AC_CONFIG_FILES(mlxreg/mlxreg_lib/Makefile)
        AC_CONFIG_FILES(mlxlink/Makefile)
        AC_CONFIG_FILES(mlxlink/modules/Makefile)
        AC_CONFIG_FILES(mlxlink/modules/printutil/Makefile)
        ADABE_TOOLS="adb_parser mlxreg mlxlink"
        ADABE_DBS="adb"
        ADABE_DBS_EXTRA_DIST="adb/prm/hca/ext/*.adb adb/prm/switch/ext/*.adb"
    ])

AS_IF([test "x$enable_fw_mgr" = "xyes" || test "x$enable_adb_generic_tools" = "xyes"], [
        AC_CONFIG_FILES(xz_utils/Makefile)
        XZ_UTILS_DIR="xz_utils"
    ])

AC_SUBST(ADABE_TOOLS)
AC_SUBST(ADABE_DBS)
AC_SUBST(ADABE_DBS_EXTRA_DIST)
AC_SUBST(XZ_UTILS_DIR)

if test "x$OS" = "xFreeBSD"; then
    AC_MSG_NOTICE(FreeBSD MTCR)
    AC_CONFIG_FILES(mtcr_freebsd/Makefile)
else
    AC_MSG_NOTICE(Linux MTCR)
    AC_CONFIG_FILES(mtcr_ul/Makefile)
fi

AM_CONDITIONAL(LINUX_BUILD, [test  "x$OS" = "xLinux"])
AC_SUBST(LINUX_BUILD)
AC_SUBST(LINUX_KERNEL_INCLUDE)

# Certain older compilers may not fully support std::regex.
# Signatuire is: the code compiles without issues, then it
# crashes during runtime with:
# terminate called after throwing an instance of 'std::regex_error'
#  what():  regex_error
# For those we resort to using GNU C regex as a fallback.
AC_MSG_CHECKING([for std::regex compatibility])
AC_LANG_PUSH([C++])
AC_RUN_IFELSE([
    AC_LANG_PROGRAM(
        [[#include <regex>
        ]],
        [[std::regex e("[a-z]");]]
    )
],[
    AC_MSG_RESULT([yes])
],[
    AC_MSG_RESULT([no])
    AC_MSG_NOTICE([std::regex support appears to be incomplete; falling back to GNU C regex.])
    AC_DEFINE([USE_STDLIB_REGEX], [1], [Whether to use GNU C regex])
],[
    AC_MSG_RESULT([yes])
    AC_MSG_WARN([Assuming the cross-compiler has complete support for std::regex functionality. VERIFY BEFORE USING!!!])
])
AC_LANG_POP([C++])

# we assume that project root may have a tools_git_sha
TOOLS_GIT_SHA=$(cd $(dirname "$0"); ./eval_git_sha.sh)
AC_SUBST([TOOLS_GIT_SHA])
AC_MSG_NOTICE(TOOLS_GIT_SHA $TOOLS_GIT_SHA)

AC_CONFIG_FILES([debian/mstflint.install])

AC_OUTPUT( \
    Makefile \
    cmdif/Makefile \
    cmdparser/Makefile \
    common/Makefile \
    dev_mgt/Makefile \
    ext_libs/Makefile \
    ext_libs/json/Makefile \
    ext_libs/minixz/Makefile \
    ext_libs/muparser/Makefile \
    ext_libs/sqlite/Makefile \
    flint/Makefile \
    fw_comps_mgr/Makefile \
    libmfa/Makefile \
    mad_ifc/Makefile \
    mflash/Makefile \
    mft_utils/Makefile \
    mlxconfig/Makefile \
    mlxconfig/mlxconfig_dbs/Makefile \
    mlxfwops/Makefile \
    mlxfwops/lib/Makefile \
    mstdump/Makefile \
    mstdump/crd_lib/Makefile \
    mstdump/crd_main/Makefile \
    mstdump/mstdump_dbs/Makefile \
    mtcr_py/Makefile \
    mvpd/Makefile \
    pldmlib/Makefile \
    reg_access/Makefile \
    resourcetools/Makefile \
    resourcetools/resourcedump_lib/Makefile \
    resourcetools/resourcedump_lib/src/Makefile \
    resourcetools/resourcedump_lib/src/commands/Makefile \
    resourcetools/resourcedump_lib/src/common/Makefile \
    resourcetools/resourcedump_lib/src/fetchers/Makefile \
    resourcetools/resourcedump_lib/src/filters/Makefile \
    resourcetools/resourcedump_lib/src/sdk/Makefile \
    small_utils/Makefile \
    small_utils/mlxfwresetlib/Makefile \
    tools_layouts/Makefile \
    tools_res_mgmt/Makefile \
    tracers/Makefile \
    tracers/fwtrace/Makefile \
 )
