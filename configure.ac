# Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

AC_INIT(mstflint, 4.35.0, akiselman-org@exchange.nvidia.com)

AC_DEFINE_UNQUOTED([PROJECT], ["mstflint"], [Firmware Burning and Diagnostics Tools for NVIDIA network devices.])
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
AC_CONFIG_HEADERS(config.h)

PKG_PROG_PKG_CONFIG
if test -z "$PKG_CONFIG"; then
  AC_MSG_ERROR([pkg-config could not be found.])
fi

# OPENSSL_VERSION_NUMBER < 0x100020bf
#0x100020bfL = openssl 1.0.2k - 26 Jan 2017
MIN_OPENSSL_VER="1.0.2k"
AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM([[
#include <openssl/ssl.h>
#if OPENSSL_VERSION_NUMBER < 0x100020bf
  ERROR: OPENSSL_VERSION_NUMBER version must be >= 0x100020bf ("openssl 1.0.2k - 26 Jan 2017")
#endif
]])], [OPENSSL_VERSION_VALID=yes], [OPENSSL_VERSION_VALID=no])
OS=$(uname -s)
KERNEL_VER=`uname -r | egrep -E -o '[[0-9]]+\.[[0-9]]+' | head -1`
OFED_VER=`ofed_info -s | egrep -E -o '[[0-9]]+\.[[0-9]]+' | head -1`
OFED_EXIST=`ofed_info -s`
OFED_NOT_EXIST="ofed_info: command not found"
MTCR_CONF_DIR=""
LDL=""
LDFLAGS="$LDFLAGS -lstdc++"
default_en_inband=""
default_en_rdmem="no"
default_en_nvml="no"
default_en_vfio="no"
default_en_i2c="no"
OFED_VERSION_CHK=0
KERNEL_BUILD_CHK=0

if test "x$OFED_EXIST" != "x$OFED_NOT_EXIST"; then
    if test $(echo $OFED_VER 5.6 | tr " " "\n" | sort -V | tail -n 1) == $OFED_VER ; then
        OFED_VERSION_CHK=1
    fi
fi

AM_CONDITIONAL(OFED_BUILD,[test ${OFED_VERSION_CHK} = 1])
AC_SUBST(OFED_BUILD)

if test ${KERNEL_VER} \> "x5.13" ; then
    KERNEL_BUILD_CHK=1
fi

AM_CONDITIONAL(KERNEL_BUILD,[test ${KERNEL_BUILD_CHK} = 1])
AC_SUBST(KERNEL_BUILD)

if test "x$OS" = "xFreeBSD"; then
    AC_MSG_NOTICE(FreeBSD Build)
    MTCR_CONF_DIR="mtcr_freebsd"
else
    MTCR_CONF_DIR="mtcr_ul"
    LDL="-ldl"
    default_en_inband="yes"
    if test ${OFED_VERSION_CHK} -eq 1 ; then
        default_en_rdmem="yes"
    fi
fi


AC_SUBST(MTCR_CONF_DIR)
AC_SUBST(VFIO_DRIVER_DIR)
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
    AS_HELP_STRING([--enable-dc], [enables the "dc" command in mstflint, requires zlib [default=enabled]]),
    [enable_dc="$enableval"],
    [enable_dc="yes"]
)
AC_MSG_RESULT($enable_dc)
if test "$enable_dc" = "yes"; then
    # zlib
    AC_ARG_WITH([zlib], AS_HELP_STRING([--with-zlib=PATH], [use zlib from the specified PATH]),
        [
            zlib_dir="$withval"
            AC_MSG_NOTICE([Using zlib from $zlib_dir])
            libz_CFLAGS="-I$zlib_dir/include"
            libz_LIBS="-L$zlib_dir/lib -lz"
        ],
        [
            AC_MSG_NOTICE([Looking for zlib headers and libraries])
            PKG_CHECK_MODULES([libz], [zlib], [],
                [
                    AC_MSG_NOTICE([Looking for zlib headers and libraries manually])
                    AC_CHECK_HEADERS([zlib.h], [], [AC_MSG_ERROR([missed zlib headers])])
                    AC_CHECK_LIB([z], [uncompress], [], [AC_MSG_ERROR([zlib not found])])
                    libz_CFLAGS=""
                    libz_LIBS="-lz"
                ]
            )
        ]
    )
    AC_MSG_NOTICE([zlib CFLAGS:'$libz_CFLAGS' LIBS:'$libz_LIBS'])
    AC_SUBST(libz_CFLAGS)
    AC_SUBST(libz_LIBS)
fi

# mstfwmanager
AC_MSG_CHECKING(--enable-fw-mgr argument)
AC_ARG_ENABLE(fw-mgr,
    AS_HELP_STRING([--enable-fw-mgr], [enable compilation of the mstfwmanager tool, requires curl/zlib/lzma/libxml2 [default=disabled]]),
    [enable_fw_mgr="$enableval"],
    [enable_fw_mgr="no"]
)
AC_MSG_RESULT($enable_fw_mgr)

if test "x$enable_fw_mgr" = "xyes"; then
    # libxml2
    AC_ARG_WITH([libxml2], AS_HELP_STRING([--with-libxml2=PATH], [use libxml2 from the specified PATH]),
        [
            libxml2_dir="$withval"
            AC_MSG_NOTICE([Using libxml2 from $libxml2_dir])
            libxml2_CFLAGS="-I$libxml2_dir/include"
            libxml2_LIBS="-L$libxml2_dir/lib -lz"
        ],
        [
            AC_MSG_NOTICE([Looking for libxml2 headers and libraries])
            PKG_CHECK_MODULES([libxml2], [libxml-2.0], [],
                [
                    AC_MSG_NOTICE([Looking for libxml2 headers and libraries manually])
                    CPPFLAGS_ORIG="$CPPFLAGS"
                    CPPFLAGS="$CPPFLAGS -I/usr/include/libxml2"
                    AC_CHECK_HEADERS([libxml/parser.h],
                        [libxml2_CFLAGS="-I/usr/include/libxml2"],
                        [AC_MSG_ERROR([missed libxml2 headers])]
                    )
                    CPPFLAGS="$CPPFLAGS_ORIG"
                    AC_CHECK_LIB([xml2], [xmlInitParser], [], [AC_MSG_ERROR([libxml2 not found])])
                    libxml2_LIBS="-lxml2"
                ]
            )
        ]
    )
    AC_MSG_NOTICE([libxml2 CFLAGS:'$libxml2_CFLAGS' LIBS:'$libxml2_LIBS'])
    AC_SUBST(libxml2_CFLAGS)
    AC_SUBST(libxml2_LIBS)
    # curl
    AC_ARG_WITH([libcurl], AS_HELP_STRING([--with-libcurl=PATH], [use libcurl from the specified PATH]),
        [
            libcurl_dir="$withval"
            AC_MSG_NOTICE([Using libcurl from $libcurl_dir])
            libcurl_CFLAGS="-I$libcurl_dir/include"
            libcurl_LIBS="-L$libcurl_dir/lib -lcurl"
        ],
        [
            AC_MSG_NOTICE([Looking for libcurl headers and libraries])
            PKG_CHECK_MODULES([libcurl], [libcurl], [],
                [
                    AC_MSG_NOTICE([Looking for libcurl headers and libraries manually])
                    AC_CHECK_HEADERS([curl/curl.h], [], [AC_MSG_ERROR([missed libcurl headers])])
                    AC_CHECK_LIB([curl], [curl_easy_init], [], [AC_MSG_ERROR([libcurl not found])])
                    libcurl_CFLAGS=""
                    libcurl_LIBS="-lcurl"
                ]
            )
        ]
    )
    AC_MSG_NOTICE([libcurl CFLAGS:'$libcurl_CFLAGS' LIBS:'$libcurl_LIBS'])
    AC_SUBST(libcurl_CFLAGS)
    AC_SUBST(libcurl_LIBS)
    # zlib
    AC_ARG_WITH([zlib], AS_HELP_STRING([--with-zlib=PATH], [use zlib from the specified PATH]),
        [
            zlib_dir="$withval"
            AC_MSG_NOTICE([Using zlib from $zlib_dir])
            libz_CFLAGS="-I$zlib_dir/include"
            libz_LIBS="-L$zlib_dir/lib -lz"
        ],
        [
            AC_MSG_NOTICE([Looking for zlib headers and libraries])
            PKG_CHECK_MODULES([libz], [zlib], [],
                [
                    AC_MSG_NOTICE([Looking for zlib headers and libraries manually])
                    AC_CHECK_HEADERS([zlib.h], [], [AC_MSG_ERROR([missed zlib headers])])
                    AC_CHECK_LIB([z], [uncompress], [], [AC_MSG_ERROR([zlib not found])])
                    libz_CFLAGS=""
                    libz_LIBS="-lz"
                ]
            )
        ]
    )
    AC_MSG_NOTICE([zlib CFLAGS:'$libz_CFLAGS' LIBS:'$libz_LIBS'])
    AC_SUBST(libz_CFLAGS)
    AC_SUBST(libz_LIBS)
fi

if test "x$enable_fw_mgr" = "xyes" || test "x$enable_adb_generic_tools" = "xyes"; then
    AC_ARG_WITH([liblzma], AS_HELP_STRING([--with-liblzma=PATH], [use liblzma from the specified PATH]),
        [
            liblzma_dir="$withval"
            AC_MSG_NOTICE([Using liblzma from $liblzma_dir])
            liblzma_CFLAGS="-I$liblzma_dir/include"
            liblzma_LIBS="-L$liblzma_dir/lib -llzma"
        ],
        [
            AC_MSG_NOTICE([Looking for liblzma headers and libraries])
            PKG_CHECK_MODULES([liblzma], [liblzma], [liblzma_pkg_config="yes"],
                [
                    AC_MSG_NOTICE([Looking for liblzma headers and libraries manually])
                    AC_CHECK_HEADERS([lzma.h], [], [AC_MSG_ERROR([missed liblzma headers])])
                    AC_CHECK_LIB([lzma], [lzma_easy_encoder], [], [AC_MSG_ERROR([liblzma not found])])
                    liblzma_CFLAGS=""
                    liblzma_LIBS="-llzma"
                ]
            )
        ]
    )
    AC_MSG_NOTICE([liblzma CFLAGS:'$liblzma_CFLAGS' LIBS:'$liblzma_LIBS'])
    AC_SUBST(liblzma_CFLAGS)
    AC_SUBST(liblzma_LIBS)
fi



# mlxdpa
AC_MSG_CHECKING(--enable-dpa argument)
AC_ARG_ENABLE(dpa,
    AS_HELP_STRING([--enable-dpa], [enable compilation of the mstdpa tool (requires openssl, Linux x86_64/aarch64 only) [default=disabled]]),
    [enable_dpa="$enableval"],
    [enable_dpa="no"]
)
AC_MSG_RESULT($enable_dpa)

# adabe tools
AC_MSG_CHECKING(--enable-adb-generic-tools argument)
AC_ARG_ENABLE(adb-generic-tools,
    AS_HELP_STRING([--enable-adb-generic-tools], [enable compilation of tools dependent on ADABE (mstreg/mstlink), requires expat [default=disabled]]),
    [enable_adb_generic_tools="$enableval"],
    [enable_adb_generic_tools="no"]
)
AC_MSG_RESULT($enable_adb_generic_tools)
if test "x$enable_adb_generic_tools" = "xyes"; then
    # expat
    AC_ARG_WITH([expat], AS_HELP_STRING([--with-expat=PATH], [use expat from the specified PATH]),
        [
            expat_dir="$withval"
            AC_MSG_NOTICE([Using expat from $expat_dir])
            expat_CFLAGS="-I$expat_dir/include"
            expat_LIBS="-L$expat_dir/lib -lz"
        ],
        [
            AC_MSG_NOTICE([Looking for expat headers and libraries])
            PKG_CHECK_MODULES([expat], [expat], [],
                [
                    AC_MSG_NOTICE([Looking for expat headers and libraries manually])
                    AC_CHECK_HEADERS([expat.h],
                        [AC_MSG_ERROR([missed expat headers])]
                    )
                    AC_CHECK_LIB([expat], [xmlInitParser], [], [AC_MSG_ERROR([expat not found])])
                    expat_LIBS="-lexpat"
                ]
            )
        ]
    )
    AC_MSG_NOTICE([expat CFLAGS:'$expat_CFLAGS' LIBS:'$expat_LIBS'])
    AC_SUBST(expat_CFLAGS)
    AC_SUBST(expat_LIBS)
fi
AM_CONDITIONAL(ENABLE_FWMGR, [test "x$enable_fw_mgr" = "xyes" ])
AC_SUBST(ENABLE_FWMGR)

# xml features
AC_MSG_CHECKING(--enable-xml2 argument)
AC_ARG_ENABLE(xml2,
    AS_HELP_STRING([--enable-xml2], [enable features dependent on libxml2, requires libxml2 [default=disabled]]),
    [enable_xml2="$enableval"],
    [enable_xml2="no"]
)
AC_MSG_RESULT($enable_xml2)
if test [ "x$enable_xml2" = "xyes" ] || [ test "x$enable_fw_mgr" = "xyes" ]; then
    # libxml2
    AC_ARG_WITH([libxml2], AS_HELP_STRING([--with-libxml2=PATH], [use libxml2 from the specified PATH]),
        [
            libxml2_dir="$withval"
            AC_MSG_NOTICE([Using libxml2 from $libxml2_dir])
            libxml2_CFLAGS="-I$libxml2_dir/include"
            libxml2_LIBS="-L$libxml2_dir/lib -lz"
        ],
        [
            AC_MSG_NOTICE([Looking for libxml2 headers and libraries])
            PKG_CHECK_MODULES([libxml2], [libxml-2.0], [],
                [
                    AC_MSG_NOTICE([Looking for libxml2 headers and libraries manually])
                    CPPFLAGS_ORIG="$CPPFLAGS"
                    CPPFLAGS="$CPPFLAGS -I/usr/include/libxml2"
                    AC_CHECK_HEADERS([libxml/parser.h],
                        [libxml2_CFLAGS="-I/usr/include/libxml2"],
                        [AC_MSG_ERROR([missed libxml2 headers])]
                    )
                    CPPFLAGS="$CPPFLAGS_ORIG"
                    AC_CHECK_LIB([xml2], [xmlInitParser], [], [AC_MSG_ERROR([libxml2 not found])])
                    libxml2_LIBS="-lxml2"
                ]
            )
        ]
    )
    AC_MSG_NOTICE([libxml2 CFLAGS:'$libxml2_CFLAGS' LIBS:'$libxml2_LIBS'])
    AC_SUBST(libxml2_CFLAGS)
    AC_SUBST(libxml2_LIBS)
fi

AM_CONDITIONAL(DISABLE_XML2, [test "x$enable_xml2" = "xno"])
AC_SUBST(DISABLE_XML2)

AM_CONDITIONAL(ENABLE_DC, [test "x$enable_dc" = "xyes"])
AC_SUBST(ENABLE_DC)

AC_MSG_CHECKING(--enable-inband argument)
AC_ARG_ENABLE(inband,
    AS_HELP_STRING([--enable-inband], [enable inband access (Linux only), requires libibmad]),
    [enable_inband="$enableval"],
    [enable_inband="$default_en_inband"]
)
AC_MSG_RESULT($enable_inband)
if test "x$enable_inband" = "xyes"; then
    AC_CHECK_HEADER(infiniband/mad.h, [],
        AC_MSG_ERROR([cannot find infiniband/mad.h (--disable-inband to remove this dependency).])
    )
    MAD_IFC="mad_ifc"
else
    CXXFLAGS="$CXXFLAGS -DNO_INBAND"
    CFLAGS="$CFLAGS -DNO_INBAND"
fi
AC_SUBST(MAD_IFC)
AM_CONDITIONAL(ENABLE_INBAND, [ test "x$enable_inband" = "xyes" ])

# Enable NVML:

AC_MSG_CHECKING(--enable-nvml argument)
AC_ARG_ENABLE(nvml,
    AS_HELP_STRING([--enable-nvml], [enable GPU device access using NVML library (Linux only), requires libnvidia-ml.so]),
    [enable_nvml="$enableval"],
    [enable_nvml="$default_en_nvml"]
)
AC_MSG_RESULT($enable_nvml)

if test "$enable_nvml" = "yes"; then
    AC_ARG_WITH([nvml-include-dir], AS_HELP_STRING([--with-nvml-include-dir=DIR], [use nvml from the specified DIR]),
        [
            nvml_dir="$withval"
            AC_MSG_NOTICE([Using nvml from $nvml_dir])
            CXXFLAGS="$CXXFLAGS -I$nvml_dir"
            CFLAGS="$CFLAGS -I$nvml_dir"
        ],
        [
            AC_MSG_NOTICE([Looking for nvml headers])
            PKG_CHECK_MODULES([nvml], [nvidia-ml], [],
                [
                    AC_MSG_NOTICE([Looking for nvml headers and libraries in default include paths])
                    AC_CHECK_HEADERS([nvml.h], [], [AC_MSG_ERROR([cannot find nvml.h in default include paths, please check you nvidia driver installation or use --with-nvml-include-dir=DIR to specify the correct directory path of nvml.h.])])
                    AC_CHECK_LIB([nvidia-ml], [nvmlInit_v2], [
                    NVML_LIBS="-lnvidia-ml"
                    AC_SUBST([NVML_LIBS])
                ], [
                    # Fallback for systems where only .so.1 exists without the .so symlink
                    # We use the -l:filename syntax which is supported by GNU ld
                    AC_MSG_CHECKING([for nvmlInit_v2 in -l:libnvidia-ml.so.1])
                    save_LIBS="$LIBS"
                    LIBS="-l:libnvidia-ml.so.1 $save_LIBS"
                    AC_LINK_IFELSE(
                        [AC_LANG_PROGRAM([[#include <nvml.h>]], [[nvmlInit_v2();]])],
                        [
                            AC_MSG_RESULT([yes])
                            NVML_LIBS="-l:libnvidia-ml.so.1"
                            AC_SUBST([NVML_LIBS])
                        ],
                        [
                            AC_MSG_RESULT([no])
                            AC_MSG_ERROR([Could not find libnvidia-ml.so or libnvidia-ml.so.1. please check you nvidia driver installation or use --with-nvml-include-dir=DIR to specify the correct directory path of nvml.h.])
                        ])
                ])

                # Restore LIBS
                LIBS="$save_LIBS"
                ]
            )
        ]
    )
    CXXFLAGS="$CXXFLAGS -DENABLE_NVML"
    CFLAGS="$CFLAGS -DENABLE_NVML"
fi

AM_CONDITIONAL(ENABLE_NVML, [ test "x$enable_nvml" = "xyes" ])

# Enable Cables:

AC_MSG_CHECKING(--enable-cables argument)
AC_ARG_ENABLE(cables,
    AS_HELP_STRING([--enable-cables], [enable cable access (Linux only)]),
    [enable_cables="$enableval"],
    [enable_cables="$default_en_cables"]
)
AC_MSG_RESULT($enable_cables)
if test "x$enable_cables" = "xyes"; then
    CXXFLAGS="$CXXFLAGS -DCABLES_SUPPORT"
    CFLAGS="$CFLAGS -DCABLES_SUPPORT"
fi

AM_CONDITIONAL(ENABLE_CABLES, [ test "x$enable_cables" = "xyes" ])

AS_IF([test "x$enable_cables" = "xyes"],
    [
        AC_CONFIG_FILES(cable_access/Makefile)
        CABLE_ACCESS_DIR="cable_access"
    ]
)

# Enable VFIO:

AC_MSG_CHECKING(--enable-vfio argument)
AC_ARG_ENABLE(vfio,
    AS_HELP_STRING([--enable-vfio], [enable VFIO driver access (Linux only), requires VFIO driver]),
    [enable_vfio="$enableval"],
    [enable_vfio="$default_en_vfio"]
)
AC_MSG_RESULT($enable_vfio)
if test "x$enable_vfio" = "xyes"; then
    CXXFLAGS="$CXXFLAGS -DENABLE_VFIO"
    CFLAGS="$CFLAGS -DENABLE_VFIO"
fi

AM_CONDITIONAL(ENABLE_VFIO, [ test "x$enable_vfio" = "xyes" ])

# Set VFIO_DRIVER_DIR based on enable_vfio flag
if test "x$enable_vfio" = "xyes"; then
    if test "x$OS" != "xFreeBSD"; then
        VFIO_DRIVER_DIR="vfio_driver_access"
    fi
else
    VFIO_DRIVER_DIR=""
fi
##

AC_MSG_CHECKING(--enable-rdmem argument)
AC_ARG_ENABLE(rdmem,
    AS_HELP_STRING([--enable-rdmem], [enable resource-dump memory mode (Linux only), requires rdma-core.]),
    [enable_rdmem="$enableval"],
    [enable_rdmem="$default_en_rdmem"]
)
AC_MSG_RESULT($enable_rdmem)
if test "x$enable_rdmem" = "xyes"; then
    AC_CHECK_HEADERS(infiniband/mlx5dv.h infiniband/verbs.h, [],
    AC_MSG_ERROR([cannot find infiniband/mlx5dv.h or infiniband/verbs.h (--disable-rdmem to remove this dependency).]))
else
    CXXFLAGS="$CXXFLAGS -DNO_RDMEM"
    CFLAGS="$CFLAGS -DNO_RDMEM"
fi
AM_CONDITIONAL(ENABLE_RDMEM, [ test "x$enable_rdmem" = "xyes" ])

# Enable I2C:
AC_MSG_CHECKING(--enable-i2c argument)
AC_ARG_ENABLE(i2c,
    AS_HELP_STRING([--enable-i2c], [enable i2c interface (supported in Linux only)]),
    [enable_i2c="$enableval"],
    [enable_i2c="$default_en_i2c"]
)
AC_MSG_RESULT($enable_i2c)
if test "x$enable_i2c" = "xyes"; then
    CXXFLAGS="$CXXFLAGS -DENABLE_MST_DEV_I2C"
    CFLAGS="$CFLAGS -DENABLE_MST_DEV_I2C"
fi
AM_CONDITIONAL(ENABLE_MST_DEV_I2C, [ test "x$enable_i2c" = "xyes" ])
##

AC_MSG_CHECKING(--enable-cs argument)
AC_ARG_ENABLE(cs,
    AS_HELP_STRING([--enable-cs], [Enable the "checksum" command in mstflint, requires openssl [defailt=disabled]]),
    [enable_cs="$enableval"],
    [enable_cs="no"]
)
AC_MSG_RESULT($enable_cs)
if test "x$enable_cs" = "xyes"; then
    AC_CHECK_HEADER(openssl/md5.h,,AC_MSG_ERROR([cannot find openssl/md5.h . remove --enable-cs to remove this dependency or install openssl]))
    TOOLS_CRYPTO="tools_crypto"
fi

AC_MSG_CHECKING(openssl argument)
AC_ARG_ENABLE(openssl,
    AS_HELP_STRING([--enable-openssl], [disable features dependent on the openssl library.]),
    [enable_openssl="$enableval"],
    [enable_openssl="yes"]
)
AC_MSG_RESULT($enable_openssl)
if test "x$enable_openssl" = "xyes"; then
    # openssl
    AC_ARG_WITH([openssl], AS_HELP_STRING([--with-openssl=PATH], [use openssl from the specified PATH]),
        [
            openssl_dir="$withval"
            AC_MSG_NOTICE([Using openssl from $openssl_dir])
            openssl_CFLAGS="-I$openssl_dir/include"
            openssl_LIBS="-L$openssl_dir/lib -lssl -lcrypto"
        ],
        [
            AC_MSG_NOTICE([Looking for openssl headers and libraries])
            PKG_CHECK_MODULES([openssl], [openssl], [],
                [
                    AC_MSG_NOTICE([Looking for openssl headers and libraries manually])
                    AC_CHECK_HEADERS([openssl/ssl.h], [],[AC_MSG_ERROR([missed openssl headers])])
                    AC_CHECK_LIB([ssl], [OPENSSL_init_ssl], [], [AC_MSG_ERROR([libssl not found])])
                    AC_CHECK_LIB([crypto], [OPENSSL_init], [], [AC_MSG_RESULT([libcrypto not found])])
                    openssl_CFLAGS="-I/usr/include/openssl"
                    openssl_LIBS="-lssl -lcrypto"
                ]
            )
        ]
    )
    AC_MSG_NOTICE([openssl CFLAGS:'$openssl_CFLAGS' LIBS:'$openssl_LIBS'])
    AC_SUBST(openssl_CFLAGS)
    AC_SUBST(openssl_LIBS)
    TOOLS_CRYPTO="tools_crypto mlxsign_lib"
fi

AC_MSG_CHECKING(--enable-all-static argument)
AC_ARG_ENABLE([all_static],
    AS_HELP_STRING([--enable-all-static], [Enable the creation of static executables [default=disabled]]),
    [enable_all_static="$enableval"],
    [enable_all_static="no"]
)
AC_MSG_RESULT($enable_all_static)

AS_IF([test "x$enable_all_static" = "xyes"], 
    [
        if test "x$enable_dc" = "xyes"; then
            AC_MSG_ERROR([The '--enable-all-static' flag can only be used in conjunction with '--disable-dc'.])
        fi
        if test "x$enable_openssl" = "xyes"; then
            AC_MSG_ERROR([The '--enable-all-static' flag can only be used in conjunction with '--disable-openss'.])
        fi
        if test "x$enable_inband" = "xyes"; then
            AC_MSG_ERROR([The '--enable-all-static' flag can only be used in conjunction with '--disable-inband'.])
        fi
        CFLAGS="$CFLAGS -DSQLITE_OMIT_LOAD_EXTENSION=0 -DIBVSMAD_DLOPEN"
    ]
)

AC_SUBST(TOOLS_CRYPTO)
AM_CONDITIONAL(ENABLE_OPENSSL, [test "x$enable_openssl" = "xyes"])
AM_CONDITIONAL(ENABLE_CS, [test  "x$enable_cs" = "xyes" || test "x$enable_openssl" = "xyes"])

AC_CHECK_HEADERS(iniparser.h, INIPARSER_SYSTEM_AVAILABLE="yes", INIPARSER_SYSTEM_AVAILABLE="no")
if test "$INIPARSER_SYSTEM_AVAILABLE" = "yes"; then
    AC_SEARCH_LIBS([iniparser_load], [iniparser],
        [INIPARSER_SYSTEM_AVAILABLE="yes"],
        [INIPARSER_SYSTEM_AVAILABLE="no"]
    )
fi

if test "$INIPARSER_SYSTEM_AVAILABLE" = "no"; then
    INIPARSER_CFLAGS='-I$(top_srcdir)/ext_libs/iniParser'
    AC_SUBST(INIPARSER_CFLAGS)
    INIPARSER_LIBS='$(top_builddir)/ext_libs/iniParser/libiniparser.la'
    AC_SUBST(INIPARSER_LIBS)
fi

AM_CONDITIONAL([USE_LOCAL_INIPARSER], [test "$INIPARSER_SYSTEM_AVAILABLE" = no])
AS_IF([test "x$INIPARSER_SYSTEM_AVAILABLE" = "xyes" ], [
    CXXFLAGS="$CXXFLAGS -DHAVE_INI_PARSER"])

AC_SEARCH_LIBS([JSON], [jsoncpp], [JSON_SYSTEM_AVAILABLE="yes"],[
    JSON_SYSTEM_AVAILABLE="no"
    JSON_CFLAGS='-I$(top_srcdir)/ext_libs/json'
    AC_SUBST(JSON_CFLAGS)
    JSON_LIBS='$(top_builddir)/ext_libs/json/libjson.la'
    AC_SUBST(JSON_LIBS)])
AM_CONDITIONAL([USE_LOCAL_JSON], [test "$JSON_SYSTEM_AVAILABLE" = no])

AC_SEARCH_LIBS([mupCreateVar], [muparser], [MUPARSER_SYSTEM_AVAILABLE="yes"],[
    MUPARSER_SYSTEM_AVAILABLE="no"
    MUPARSER_CFLAGS='-I$(top_srcdir)/ext_libs/muparser'
    AC_SUBST(MUPARSER_CFLAGS)
    MUPARSER_LIBS='$(top_builddir)/ext_libs/muparser/libmuparser.la'
    AC_SUBST(MUPARSER_LIBS)])
AM_CONDITIONAL([USE_LOCAL_MUPARSER], [test "$MUPARSER_SYSTEM_AVAILABLE" = no])

AC_SEARCH_LIBS([sqlite3_initialize], [sqlite3], [SQLITE_SYSTEM_AVAILABLE="yes"],[
    SQLITE_SYSTEM_AVAILABLE="no"
    SQLITE_CFLAGS='-I$(top_srcdir)/ext_libs/sqlite'
    AC_SUBST(SQLITE_CFLAGS)
    SQLITE_LIBS='$(top_builddir)/ext_libs/sqlite/libsqlite3.la'
    AC_SUBST(SQLITE_LIBS)])
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

AC_CONFIG_FILES(mstflint.spec)

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

AS_IF([test "x$enable_cs" = "xyes" || test "x$enable_openssl" = "xyes"],
    [AC_CONFIG_FILES(tools_crypto/Makefile)]
)

AM_CONDITIONAL(ENABLE_NVFWRESET, [test "x$OS" != "xFreeBSD" && test "x$enable_nvfwreset" = "xyes" ])

if test "x$OS" != "xFreeBSD"; then
    AC_MSG_CHECKING(--enable-nvfwreset argument)
    AC_ARG_ENABLE(nvfwreset,
        AS_HELP_STRING([--enable-nvfwreset], [enable compilation of the nvfwreset tool [default=disabled]]),
        [enable_nvfwreset="$enableval"],
        [enable_nvfwreset="no"]
    )
    AC_MSG_RESULT($enable_nvfwreset)
    AS_IF([test "x$enable_nvfwreset" = "xyes"], [
        AC_CONFIG_FILES(nvfwreset/Makefile)
        NVFWRESET_DIR="nvfwreset"
    ])
    AC_SUBST(enable_nvfwreset)
    AC_SUBST(NVFWRESET_DIR)
else
    enable_nvfwreset="no"
    NVFWRESET_DIR=""
    AC_SUBST(enable_nvfwreset)
    AC_SUBST(NVFWRESET_DIR)
fi

AS_IF([test "x$enable_openssl" = "xyes"],
    [
        AS_IF(test x"$OPENSSL_VERSION_VALID" = "xyes",
           [AC_CONFIG_FILES(mlxsign_lib/Makefile)],
           [AC_MSG_ERROR([Required openssl version >= $MIN_OPENSSL_VER (or use --disable-openssl)])]
        )
    ]
)

if [ test "x$enable_openssl" = "xno" ] && \
    [ test "x$enable_fw_mgr" = "xyes" ] ; then
    AC_MSG_ERROR([--enable-fw-mgr cannot be used with --disabled-openssl.])
fi

AS_IF([test "x$enable_fw_mgr" = "xyes"], 
    [
        AC_CONFIG_FILES(mlxfwupdate/Makefile)
        AC_CONFIG_FILES(ext_libs/iniParser/Makefile)
        AC_CONFIG_FILES(mlxarchive/Makefile)
        FW_MGR_TOOLS="mlxfwupdate mlxarchive"
    ]
)

AC_SUBST(FW_MGR_TOOLS)

AS_IF([test "x$enable_dpa" = "xyes"], 
    [
        AC_CONFIG_FILES(mlxdpa/Makefile)
        DPA="mlxdpa"
    ]
)
AM_CONDITIONAL(ENABLE_DPA, [test "x$enable_dpa" = "xyes" ])

AC_SUBST(DPA)

if [ test "x$enable_openssl" = "xno" ] && \
    [ test "x$enable_dpa" = "xyes" ] ; then
    AC_MSG_ERROR([--enable-dpa cannot be used with --disabled-openssl.])
fi

AS_IF([test "x$enable_adb_generic_tools" = "xyes"], [
        AC_CONFIG_FILES(adb_parser/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/hca/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/hca/ext/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/switch/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/switch/ext/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/gpu/Makefile)
        AC_CONFIG_FILES(tools_layouts/adb/prm/gpu/ext/Makefile)
        AC_CONFIG_FILES(mlxreg/Makefile)
        AC_CONFIG_FILES(mlxreg/scripts/Makefile)
        AC_CONFIG_FILES(mlxreg/mlxreg_lib/Makefile)
        AC_CONFIG_FILES(mlxlink/Makefile)
        AC_CONFIG_FILES(mlxlink/modules/Makefile)
        AC_CONFIG_FILES(mlxlink/modules/printutil/Makefile)
        ADABE_TOOLS="adb_parser mlxreg mlxlink"
        ADABE_DBS="adb"
        ADABE_DBS_EXTRA_DIST="adb/prm/hca/ext/*.adb adb/prm/switch/ext/*.adb adb/prm/gpu/ext/*.adb"])

AM_CONDITIONAL([ADB_GENERIC_TOOLS_ENABLED], [test "x$enable_adb_generic_tools" = "xyes"])

AS_IF([test "x$enable_fw_mgr" = "xyes" || test "x$enable_adb_generic_tools" = "xyes"],
    [
        AC_CONFIG_FILES(xz_utils/Makefile)
        XZ_UTILS_DIR="xz_utils"
    ]
)

AS_IF([test "x$enable_nvml" = "xyes"],
    [
        AC_CONFIG_FILES(nvml_lib/Makefile)
        NVML_DIR="nvml_lib"
    ]
)

AC_SUBST(ADABE_TOOLS)
AC_SUBST(ADABE_DBS)
AC_SUBST(ADABE_DBS_EXTRA_DIST)
AC_SUBST(XZ_UTILS_DIR)
AC_SUBST(NVML_DIR)
AC_SUBST(CABLE_ACCESS_DIR)

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
    pci_library/Makefile \
    ext_libs/Makefile \
    ext_libs/json/Makefile \
    ext_libs/mini-yaml/Makefile \
    ext_libs/sole/Makefile \
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
    mlxtokengenerator/Makefile \
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
    mst_utils/Makefile \
    small_utils/mlxfwresetlib/Makefile \
    tools_layouts/Makefile \
    tools_res_mgmt/Makefile \
    tracers/Makefile \
    tracers/fwtrace/Makefile \
    vfio_driver_access/Makefile \
    mft_core/Makefile \
    mft_core/mft_core_utils/Makefile \
    mft_core/mft_core_utils/logger/Makefile \
    mft_core/mft_core_utils/operating_system_api/Makefile \
    mft_core/mft_core_utils/mft_exceptions/Makefile \
 )
