dnl Process this file with autoconf to produce a configure script.

AC_INIT(mstflint, 3.7.1, orenk@mellanox.co.il)

AC_DEFINE_UNQUOTED([PROJECT], ["mstflint"], [Define the project name.])
AC_SUBST([PROJECT])

AC_DEFINE_UNQUOTED([VERSION], ["3.7.1"], [Define the project version.])
AC_SUBST([VERSION])

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([README])
AM_INIT_AUTOMAKE(mstflint, 3.7.1)

dnl Checks for programs
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_CONFIG_HEADERS( config.h )

dnl Checks for headers
AC_CHECK_HEADER(termios.h,[CXXFLAGS="${CXXFLAGS} -DHAVE_TERMIOS_H"])

AC_MSG_CHECKING(--enable-dc argument)
AC_ARG_ENABLE(dc,
		    [  --disable-dc            Disable mstflint "dc" command. Eliminates zlib dependency],
		    [enable_dc=$enableval],
		    [enable_dc="yes"])
AC_MSG_RESULT($enable_dc)
if test "$enable_dc" = "yes"; then
  AC_CHECK_HEADER(zlib.h,,AC_MSG_ERROR([cannot find zlib.h . Use --disable-dc to remove this dependaency]))
  AC_CHECK_LIB(z, uncompress,, AC_MSG_ERROR([cannot find zlib uncompress() function. Use --disable-dc to remove this dependaency]))
fi

AM_CONDITIONAL(ENABLE_DC, [test  "x$enable_dc" = "xyes"])
AC_SUBST(ENABLE_DC)

AC_MSG_CHECKING(--enable-inband argument)
AC_ARG_ENABLE(inband,
		    [  --disable-inband        Disable inabnd access. Prevents FW updtes for Mellanox SwitchX and ConnectIB devices. Eliminates infiniband/mad.h dependency],
		    [enable_inband=$enableval],
		    [enable_inband="yes"])
AC_MSG_RESULT($enable_inband)
if test "x$enable_inband" = "xyes"; then
  AC_CHECK_HEADER(infiniband/mad.h,,AC_MSG_ERROR([cannot find infiniband/mad.h . Use --disable-inband to remove this dependaency]))
fi

AM_CONDITIONAL(ENABLE_INBAND, [test  "x$enable_inband" = "xyes"])

CFLAGS="$CFLAGS -Werror -DMST_UL"
CXXFLAGS="$CXXFLAGS -Werror -DMST_UL"

AC_CONFIG_FILES( mstflint.spec )

AC_OUTPUT( Makefile mft_utils/Makefile mtcr_ul/Makefile dev_mgt/Makefile tools_layouts/Makefile reg_access/Makefile mlxconfig/Makefile \
		mflash/Makefile mlxfwops/Makefile mlxfwops/lib/Makefile cmdparser/Makefile flint/Makefile \
 		small_utils/Makefile mstdump/Makefile mstdump/crd_lib/Makefile mstdump/crd_main/Makefile  mstdump/mstdump_dbs/Makefile )

