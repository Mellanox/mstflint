# Copyright (c) 2023-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

# Makefile.am -- Process this file with automake to produce Makefile.in
#
# mstflint builds from this ONE non-recursive Makefile, the way MFT builds its
# user/ tree: every library, program, script and data file is declared below,
# named by its path, and every dependency between them is an explicit
# prerequisite (the .la files in _LIBADD / _LDADD / _DEPENDENCIES). make sees
# the whole dependency graph at once and builds everything whose inputs are
# ready in parallel. There are no per-directory Makefiles and no SUBDIRS walk.
#
#   prologue   global lists, initialized empty; every section appends with +=
#   sections   one "########### <dir> ###########" per source directory, in
#              the old SUBDIRS order, guarded by the condition that used to put
#              the directory into SUBDIRS
#   epilogue   install hooks and the standalone SDK goals
#
# Conventions:
#   * a target in <dir> is named by path:   bin_PROGRAMS += <dir>/<prog>
#     and its variables use automake's canonical name: <dir>_<prog>_SOURCES ...
#   * <DIR>_CPPFLAGS / _CFLAGS / _CXXFLAGS hold what used to be the directory's
#     AM_CPPFLAGS / AM_CFLAGS / AM_CXXFLAGS. Each target uses them unless it
#     sets its own, exactly as automake did per directory.
#   * <DIR>_CPPFLAGS starts with -I<dir> (build and source tree) and
#     -I$(top_builddir): the include path automake used to give every
#     subdirectory implicitly. The global AM_*FLAGS stay unset on purpose.
#   * a library that is linked through a variable automake cannot see (a
#     configure substitution, a hand-written .so rule) gets an explicit
#     prerequisite, so no build order depends on luck.
#
# Build one thing:  make flint/mstflint     (not `make -C flint`)
# Build the SDK:    make sdk / make install-sdk

# Every target carries its own include path (see above), so automake's default
# (-I. -I$(srcdir), i.e. the top directory only) is switched off.
DEFAULT_INCLUDES =

bin_PROGRAMS =
noinst_PROGRAMS =
bin_SCRIPTS =
noinst_SCRIPTS =
pkglib_LTLIBRARIES =
noinst_LTLIBRARIES =
noinst_LIBRARIES =
noinst_HEADERS =
BUILT_SOURCES =
CLEANFILES =
INSTALL_DATA_HOOKS =
UNINSTALL_HOOKS =

# The bundled jsoncpp as a prerequisite. Link lines use $(JSON_LIBS) from
# configure, which automake cannot turn into a dependency.
if USE_LOCAL_JSON
JSON_LA = ext_libs/json/libjson.la
endif

man_MANS = man/mstflint.1 man/mstconfig.1 man/mstmcra.1 man/mstmread.1 man/mstmwrite.1 man/mstmtserver.1 man/mstregdump.1 man/mstvpd.1 man/mstprivhost.1 man/mstarchive.1 man/mstreg.1 man/mstfwtrace.1 man/mstlink.1 man/mstcongestion.1 man/mstfwmanager.1 man/mstfwreset.1 man/mstresourcedump.1 man/mstflintlogger.1 man/mstserver.1 man/mstremote.1

EXTRA_DIST = \
	mstflint.spec \
	mstflint-sdk.spec \
	tools_git_sha \
	debian \
	$(man_MANS)

########### nvml_lib ###########
if ENABLE_NVML
NVML_LIB_CPPFLAGS = \
    -I$(top_builddir)/nvml_lib \
    -I$(top_srcdir)/nvml_lib \
    -I$(top_builddir) \
    -I$(top_srcdir)/nvml_lib \
    -I$(top_srcdir) \
    -I$(top_srcdir)/mft_core/mft_core_utils

NVML_LIB_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)
NVML_LIB_CFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES += nvml_lib/libnvml_device.la

nvml_lib_libnvml_device_la_SOURCES = \
    nvml_lib/nvml_device.cpp \
    nvml_lib/nvml_exception.cpp \
    nvml_lib/nvml_lib_wrapper.cpp \
    nvml_lib/nvml_c_wrapper.cpp

nvml_lib_libnvml_device_la_LDFLAGS = -static

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
nvml_lib_libnvml_device_la_CPPFLAGS = $(NVML_LIB_CPPFLAGS)
nvml_lib_libnvml_device_la_CFLAGS = $(NVML_LIB_CFLAGS)
nvml_lib_libnvml_device_la_CXXFLAGS = $(NVML_LIB_CXXFLAGS)
endif

########### ext_libs ###########

# spdlog (header-only, v1.15.0) backs the NVIDIA Tools logger in
# mft_core/mft_core_utils/nvtoolslogger/. It has no build step of its own -
# consumers just add -isystem $(top_srcdir)/ext_libs/spdlog/include - so it
# only needs to be distributed.
EXTRA_DIST += ext_libs/spdlog/include ext_libs/spdlog/LICENSE

# Header-only vendored libraries consumed by mst_server/ (Crow HTTP server and
# standalone Asio, which Crow builds on). They have no build step of their own -
# consumers just add -I<dir>/include - so they only need to be distributed.
#
# Both licences require the licence text to travel with the code, and asio's
# headers name LICENSE_1_0.txt as an accompanying file, so ship them alongside.
EXTRA_DIST += ext_libs/crow/include ext_libs/crow/LICENSE ext_libs/asio/include ext_libs/asio/LICENSE_1_0.txt

########### ext_libs/minixz ###########
EXT_LIBS_MINIXZ_CPPFLAGS = \
    -I$(top_builddir)/ext_libs/minixz \
    -I$(top_srcdir)/ext_libs/minixz \
    -I$(top_builddir) \
    -I$(top_builddir)/ext_libs/minixz
EXT_LIBS_MINIXZ_CPPFLAGS += -DXZ_DEC_ANY_CHECK -W -g -MP -MD ${COMPILER_FPIC}
noinst_LTLIBRARIES += ext_libs/minixz/libminixz.la
ext_libs_minixz_libminixz_la_SOURCES = ext_libs/minixz/xz_crc32.c ext_libs/minixz/xz_dec_bcj.c ext_libs/minixz/xz_dec_lzma2.c ext_libs/minixz/xz_dec_stream.c ext_libs/minixz/xz_config.h ext_libs/minixz/xz.h ext_libs/minixz/xz_lzma2.h ext_libs/minixz/xz_private.h ext_libs/minixz/xz_stream.h

#libminixz_la_DEPENDENCIES =  xz_crc32.c  xz_dec_bcj.c  xz_dec_lzma2.c  xz_dec_stream.c xz_config.h   xz.h xz_lzma2.h    xz_private.h  xz_stream.h
#libminixz_la_LIBADD =

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
ext_libs_minixz_libminixz_la_CPPFLAGS = $(EXT_LIBS_MINIXZ_CPPFLAGS)

########### ext_libs/mini-yaml ###########
EXT_LIBS_MINI_YAML_CPPFLAGS = \
    -I$(top_builddir)/ext_libs/mini-yaml \
    -I$(top_srcdir)/ext_libs/mini-yaml \
    -I$(top_builddir) \
    -W \
    -g \
    -MP \
    -MD \
    ${COMPILER_FPIC} \
    -Wno-unused-parameter
noinst_LTLIBRARIES += ext_libs/mini-yaml/libmini_yaml.la
ext_libs_mini_yaml_libmini_yaml_la_SOURCES = ext_libs/mini-yaml/yaml/Yaml.cpp ext_libs/mini-yaml/yaml/Yaml.hpp

ext_libs_mini_yaml_libmini_yaml_la_DEPENDENCIES =
ext_libs_mini_yaml_libmini_yaml_la_LIBADD =

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
ext_libs_mini_yaml_libmini_yaml_la_CPPFLAGS = $(EXT_LIBS_MINI_YAML_CPPFLAGS)

########### ext_libs/sole ###########
EXT_LIBS_SOLE_CPPFLAGS = \
    -I$(top_builddir)/ext_libs/sole \
    -I$(top_srcdir)/ext_libs/sole \
    -I$(top_builddir) \
    -W \
    -g \
    -MP \
    -MD \
    ${COMPILER_FPIC}
noinst_LTLIBRARIES += ext_libs/sole/libsole.la
ext_libs_sole_libsole_la_SOURCES = ext_libs/sole/sole.cpp ext_libs/sole/sole.hpp

ext_libs_sole_libsole_la_DEPENDENCIES =
ext_libs_sole_libsole_la_LIBADD =

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
ext_libs_sole_libsole_la_CPPFLAGS = $(EXT_LIBS_SOLE_CPPFLAGS)

########### ext_libs/iniParser ###########
if ENABLE_FWMGR
if USE_LOCAL_INIPARSER
EXT_LIBS_INIPARSER_CPPFLAGS = \
    -I$(top_builddir)/ext_libs/iniParser \
    -I$(top_srcdir)/ext_libs/iniParser \
    -I$(top_builddir) \
    -I$(top_builddir)/ext_libs/iniParser \
    -I$(top_builddir) \
    -I$(top_builddir)/${MTCR_CONFIG_DIR} \
    -I$(top_builddir)/common

EXT_LIBS_INIPARSER_CFLAGS = -W -g -MP -MD ${COMPILER_FPIC}

noinst_LTLIBRARIES += ext_libs/iniParser/libiniparser.la

ext_libs_iniParser_libiniparser_la_SOURCES = \
    ext_libs/iniParser/iniparser.c \
    ext_libs/iniParser/iniparser.h \
    ext_libs/iniParser/dictionary.c \
    ext_libs/iniParser/dictionary.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
ext_libs_iniParser_libiniparser_la_CPPFLAGS = $(EXT_LIBS_INIPARSER_CPPFLAGS)
ext_libs_iniParser_libiniparser_la_CFLAGS = $(EXT_LIBS_INIPARSER_CFLAGS)
endif
endif

########### ext_libs/json ###########
if USE_LOCAL_JSON
EXT_LIBS_JSON_CPPFLAGS = \
    -I$(top_builddir)/ext_libs/json \
    -I$(top_srcdir)/ext_libs/json \
    -I$(top_builddir) \
    -W \
    -Werror \
    -g \
    -MP \
    -MD \
    ${COMPILER_FPIC} \
    -Wno-missing-field-initializers \
    -Wno-unused-parameter
noinst_LTLIBRARIES += ext_libs/json/libjson.la
ext_libs_json_libjson_la_SOURCES = ext_libs/json/json_reader.cpp ext_libs/json/json_value.cpp ext_libs/json/json_tool.h ext_libs/json/json_writer.cpp ext_libs/json/json/*.h

ext_libs_json_libjson_la_DEPENDENCIES =
ext_libs_json_libjson_la_LIBADD =

EXTRA_DIST += ext_libs/json/*.inl

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
ext_libs_json_libjson_la_CPPFLAGS = $(EXT_LIBS_JSON_CPPFLAGS)
endif

########### ext_libs/muparser ###########
if USE_LOCAL_MUPARSER
EXT_LIBS_MUPARSER_CFLAGS = -w -g -MP -MD ${COMPILER_FPIC}
EXT_LIBS_MUPARSER_CXXFLAGS = -w -g -MP -MD ${COMPILER_FPIC}

noinst_LTLIBRARIES += ext_libs/muparser/libmuparser.la

ext_libs_muparser_libmuparser_la_SOURCES = \
    ext_libs/muparser/muParser.cpp \
    ext_libs/muparser/muParser.h \
    ext_libs/muparser/muParserBase.cpp \
    ext_libs/muparser/muParserBase.h \
    ext_libs/muparser/muParserBytecode.cpp \
    ext_libs/muparser/muParserBytecode.h \
    ext_libs/muparser/muParserCallback.cpp \
    ext_libs/muparser/muParserCallback.h \
    ext_libs/muparser/muParserDef.h \
    ext_libs/muparser/muParserError.cpp \
    ext_libs/muparser/muParserError.h \
    ext_libs/muparser/muParserFixes.h \
    ext_libs/muparser/muParserInt.cpp \
    ext_libs/muparser/muParserInt.h \
    ext_libs/muparser/muParserTemplateMagic.h \
    ext_libs/muparser/muParserToken.h \
    ext_libs/muparser/muParserTokenReader.cpp \
    ext_libs/muparser/muParserTokenReader.h

EXT_LIBS_MUPARSER_CPPFLAGS = -I$(top_builddir)/ext_libs/muparser -I$(top_srcdir)/ext_libs/muparser -I$(top_builddir)
# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
ext_libs_muparser_libmuparser_la_CPPFLAGS = $(EXT_LIBS_MUPARSER_CPPFLAGS)
ext_libs_muparser_libmuparser_la_CFLAGS = $(EXT_LIBS_MUPARSER_CFLAGS)
ext_libs_muparser_libmuparser_la_CXXFLAGS = $(EXT_LIBS_MUPARSER_CXXFLAGS)
endif

########### ext_libs/sqlite ###########
if USE_LOCAL_SQLITE
EXT_LIBS_SQLITE_CFLAGS = -fno-strict-aliasing -g -MP -MD -DSQLITE_THREADSAFE=0 ${COMPILER_FPIC}

noinst_LTLIBRARIES += ext_libs/sqlite/libsqlite3.la
noinst_HEADERS += ext_libs/sqlite/sqlite3.h

ext_libs_sqlite_libsqlite3_la_SOURCES = \
    ext_libs/sqlite/sqlite3.c \
    ext_libs/sqlite/sqlite3.h

EXT_LIBS_SQLITE_CPPFLAGS = -I$(top_builddir)/ext_libs/sqlite -I$(top_srcdir)/ext_libs/sqlite -I$(top_builddir)
# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
ext_libs_sqlite_libsqlite3_la_CPPFLAGS = $(EXT_LIBS_SQLITE_CPPFLAGS)
ext_libs_sqlite_libsqlite3_la_CFLAGS = $(EXT_LIBS_SQLITE_CFLAGS)
endif

########### mst_server/client ###########
if ENABLE_MTCR_REMOTE
MST_SERVER_CXXFLAGS = \
     $(COMPILER_FPIC) $(CXX17_STD) \
    -I$(top_srcdir) $(JSON_CFLAGS) $(openssl_CFLAGS) $(mst_remote_curl_CFLAGS) \
    -UVERSION

# jsoncpp is NOT added to LIBADD below. libmst_http_client.la is a convenience
# archive, so LIBADD'ing libjson.la would absorb json_writer.o into it - and
# libmtcr_ul already links libnvtoolslogger.la, which absorbs the same objects
# through libmft_log_config.la. Two archives carrying them makes the final link
# fail with "multiple definition of Json::...". The headers still come in via
# $(JSON_CFLAGS); the symbols resolve from the logger's copy.
# The tree is pinned to C++14 by configure (see the CXX_STD note there) and
# automake emits $(CXXFLAGS) after every per-target _CXXFLAGS, so a -std in
# those would lose. Appending here is what actually makes C++17 win, and it is
# scoped to this directory - the only place allowed to use it until mstflint
# takes C++17 as its baseline.

noinst_LTLIBRARIES += mst_server/client/libmst_http_client.la

mst_server_client_libmst_http_client_la_SOURCES = \
    mst_server/client/MstHttpClient.cpp \
    mst_server/client/MstKnownHosts.cpp \
    mst_server/client/mst_http_client_c_api.cpp \
    mst_server/client/MstCurlClient.h \
    mst_server/client/MstHttpClient.h \
    mst_server/client/MstKnownHosts.h \
    mst_server/client/mst_http_client_c_api.h
mst_server_client_libmst_http_client_la_CXXFLAGS = $(MST_SERVER_CXXFLAGS)
mst_server_client_libmst_http_client_la_LIBADD = \
    $(openssl_LIBS) \
    $(mst_remote_curl_LIBS) \
    $(FILESYSTEM_LIBS) \
    -lpthread \
    -lstdc++

MST_SERVER_CLIENT_CPPFLAGS = -I$(top_builddir)/mst_server/client -I$(top_srcdir)/mst_server/client -I$(top_builddir)
# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mst_server_client_libmst_http_client_la_CPPFLAGS = $(MST_SERVER_CLIENT_CPPFLAGS)
# The tree builds at -std=c++14 via CXXFLAGS, which automake puts last on the
# compile line; this directory needs C++17, so raise it for its objects only.
MST_SERVER_CLIENT_CXX17_OBJECTS = $(mst_server_client_libmst_http_client_la_OBJECTS)
$(MST_SERVER_CLIENT_CXX17_OBJECTS): CXXFLAGS += $(CXX17_STD)
endif

########### common ###########
noinst_LTLIBRARIES += common/libcommon.la

COMMON_CPPFLAGS = \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/common \
    -I$(top_builddir) \
    $(JSON_CFLAGS) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul

common_libcommon_la_SOURCES = \
    common/bit_slice.h \
    common/compatibility.h \
    common/tools_algorithm.h \
    common/tools_endianness.h \
    common/tools_filesystem.cpp \
    common/tools_filesystem.h \
    common/tools_json.cpp \
    common/tools_json.h \
    common/tools_regex.cpp \
    common/tools_regex.h \
    common/tools_time.h \
    common/tools_utils.h \
    common/tools_utils.h \
    common/tools_version.h \
    common/tools_string.h \
    common/tools_string.cpp

commonincludedir = $(includedir)/mstflint/common/
commoninclude_HEADERS = common/compatibility.h common/tools_endianness.h

update_prefix = sed -e 's,[@]MST_LIB_DIR[@]${CONF_DISABLE_PATH_UPDATE},$(libdir),g'\
                    -e 's,[@]MST_BIN_DIR[@]${CONF_DISABLE_PATH_UPDATE},$(bindir),g'\
                    -e 's,[@]MFTCONF_PREFIX[@],$(prefix),g'

update_tools_version = sed -e 's,[@]MSTFLINT_VERSION_STR[@],${MSTFLINT_VERSION_STR},g' \
                    -e 's,[@]TOOLS_BUILD_TIME[@],${TOOLS_BUILD_TIME},g' \
                    -e 's,[@]TOOLS_GIT_SHA[@],${TOOLS_GIT_SHA},g'

# tools_version.h is included all over the tree, so it is a BUILT_SOURCE: made
# before anything is compiled. It and tools_version.py are only generated when
# missing. python_wrapper is the launcher every python tool below is a copy of.
# Like the old common/ `all:' rule it is regenerated on every make, so a
# make-time `make prefix=...' reaches the launchers; it is only replaced when
# its content changes, so an unchanged tree stays a no-op build.
BUILT_SOURCES += common/tools_version.h
noinst_SCRIPTS += common/python_wrapper

common/python_wrapper: $(srcdir)/common/python_wrapper.sh FORCE
	@$(MKDIR_P) $(@D)
	@$(update_prefix) < $(srcdir)/common/python_wrapper.sh > $@.tmp && chmod +x $@.tmp && \
	if cmp -s $@.tmp $@; then rm -f $@.tmp; else mv -f $@.tmp $@ && echo "  GEN      $@"; fi

FORCE:
.PHONY: FORCE

common/tools_version.py:
	@$(MKDIR_P) $(@D)
	$(update_tools_version) < $(srcdir)/common/tools_version.py.in > $@

common/tools_version.h:
	@$(MKDIR_P) $(@D)
	$(update_tools_version) < $(srcdir)/common/tools_version.h.in > $@

tools_version_pylibdir = $(libdir)/mstflint/python_tools/
tools_version_pylib_DATA = common/tools_version.py

nvtoolslogger_pylibdir = $(libdir)/mstflint/python_tools/
nvtoolslogger_pylib_DATA = common/nvtoolslogger.py

EXTRA_DIST += common/tools_version.py.in common/python_wrapper.sh

CLEANFILES += common/python_wrapper common/tools_version.py

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
common_libcommon_la_CPPFLAGS = $(COMMON_CPPFLAGS)

########### cmdparser ###########
CMDPARSER_CPPFLAGS = \
    -I$(top_builddir)/cmdparser \
    -I$(top_srcdir)/cmdparser \
    -I$(top_builddir) \
    -I$(top_srcdir)/cmdparser \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common

CMDPARSER_CPPFLAGS += -W -g -MP -MD $(COMPILER_FPIC) $(COMPILER_FPIE)

noinst_LIBRARIES += cmdparser/libcmdparser.a

cmdparser_libcmdparser_a_SOURCES = cmdparser/cmdparser.cpp cmdparser/my_getopt.c cmdparser/cmdparser.h cmdparser/my_getopt.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
cmdparser_libcmdparser_a_CPPFLAGS = $(CMDPARSER_CPPFLAGS)

########### mft_core/mft_core_utils/operating_system_api ###########
MFT_CORE_UTILS_OPERATING_SYSTEM_API_CPPFLAGS = \
    -I$(top_builddir)/mft_core/mft_core_utils/operating_system_api \
    -I$(top_srcdir)/mft_core/mft_core_utils/operating_system_api \
    -I$(top_builddir) \
    -I$(top_builddir)/mft_core/mft_core_utils/operating_system_api \
    -I$(top_srcdir)

MFT_CORE_UTILS_OPERATING_SYSTEM_API_CXXFLAGS = -Wall -W -g -MP -MD -pipe -Werror $(COMPILER_FPIC)

noinst_LTLIBRARIES += mft_core/mft_core_utils/operating_system_api/lib_os_api.la

mft_core_mft_core_utils_operating_system_api_lib_os_api_la_SOURCES = mft_core/mft_core_utils/operating_system_api/OperatingSystemAPI.cpp mft_core/mft_core_utils/operating_system_api/OperatingSystemAPI.h mft_core/mft_core_utils/operating_system_api/OperatingSystemAPIDefs.h mft_core/mft_core_utils/operating_system_api/FactoryOperatingSystemAPI.cpp mft_core/mft_core_utils/operating_system_api/FactoryOperatingSystemAPI.h
mft_core_mft_core_utils_operating_system_api_lib_os_api_la_SOURCES += mft_core/mft_core_utils/operating_system_api/Linux.cpp mft_core/mft_core_utils/operating_system_api/Linux.h

mft_core_mft_core_utils_operating_system_api_lib_os_api_la_DEPENDENCIES =
mft_core_mft_core_utils_operating_system_api_lib_os_api_la_LIBADD = $(LIBSTD_CPP_SO) -lstdc++

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mft_core_mft_core_utils_operating_system_api_lib_os_api_la_CPPFLAGS = $(MFT_CORE_UTILS_OPERATING_SYSTEM_API_CPPFLAGS)
mft_core_mft_core_utils_operating_system_api_lib_os_api_la_CXXFLAGS = $(MFT_CORE_UTILS_OPERATING_SYSTEM_API_CXXFLAGS)

########### mft_core/mft_core_utils/nvtoolslogger ###########
MFT_CORE_UTILS_NVTOOLSLOGGER_CPPFLAGS = \
    -I$(top_builddir)/mft_core/mft_core_utils/nvtoolslogger \
    -I$(top_srcdir)/mft_core/mft_core_utils/nvtoolslogger \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_builddir) \
    -I$(top_srcdir)/mft_core/mft_core_utils \
    $(JSON_CFLAGS)

MFT_CORE_UTILS_NVTOOLSLOGGER_CXXFLAGS = -Wall -W -g -MP -MD -pipe -Werror $(COMPILER_FPIC)

# spdlog is header-only and third party: -isystem keeps -Werror from tripping
# over its headers. It is only needed by NvToolsLogger.cpp.
SPDLOG_CXXFLAGS = -isystem $(top_srcdir)/ext_libs/spdlog/include -DSPDLOG_NO_THREAD_ID

# The bundled jsoncpp is a libtool convenience library, so its objects are
# already folded into .libs/libnvtoolslogger.a and must not be linked twice into
# the .so. A system jsoncpp is a real shared library and still has to be named.
if USE_LOCAL_JSON
NVTOOLSLOGGER_JSON_LIBS = ext_libs/json/libjson.la
NVTOOLSLOGGER_JSON_SO_LIBS =
else
NVTOOLSLOGGER_JSON_LIBS = -ljsoncpp
NVTOOLSLOGGER_JSON_SO_LIBS = -ljsoncpp
endif

noinst_LTLIBRARIES += mft_core/mft_core_utils/nvtoolslogger/libmft_log_config.la mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.la mft_core/mft_core_utils/nvtoolslogger/libmft_log_config_ui.la

mft_core_mft_core_utils_nvtoolslogger_libmft_log_config_la_SOURCES = \
    mft_core/mft_core_utils/nvtoolslogger/log_config.cpp \
    mft_core/mft_core_utils/nvtoolslogger/log_config.h \
    mft_core/mft_core_utils/nvtoolslogger/log_config_defs.h \
    mft_core/mft_core_utils/nvtoolslogger/layers.h
mft_core_mft_core_utils_nvtoolslogger_libmft_log_config_la_LIBADD = $(NVTOOLSLOGGER_JSON_LIBS) -lstdc++

mft_core_mft_core_utils_nvtoolslogger_libnvtoolslogger_la_SOURCES = \
    mft_core/mft_core_utils/nvtoolslogger/NvToolsLogger.cpp \
    mft_core/mft_core_utils/nvtoolslogger/NvToolsLogger.h \
    mft_core/mft_core_utils/nvtoolslogger/nvtoolslogger_c.h
mft_core_mft_core_utils_nvtoolslogger_libnvtoolslogger_la_CXXFLAGS = $(MFT_CORE_UTILS_NVTOOLSLOGGER_CXXFLAGS) $(SPDLOG_CXXFLAGS)
mft_core_mft_core_utils_nvtoolslogger_libnvtoolslogger_la_LDFLAGS = -pthread
# lib_os_api is a build-order dependency only. Embedding it here too would put
# its objects in both libnvtoolslogger.a and libdevice_info.a, and libmtcr_ul links
# both - that is a multiple-definition link failure. Final links get lib_os_api
# from their own dependency on it; the .so rule below names it explicitly.
mft_core_mft_core_utils_nvtoolslogger_libnvtoolslogger_la_DEPENDENCIES = mft_core/mft_core_utils/nvtoolslogger/libmft_log_config.la mft_core/mft_core_utils/operating_system_api/lib_os_api.la
mft_core_mft_core_utils_nvtoolslogger_libnvtoolslogger_la_LIBADD = mft_core/mft_core_utils/nvtoolslogger/libmft_log_config.la -lstdc++

mft_core_mft_core_utils_nvtoolslogger_libmft_log_config_ui_la_SOURCES = \
    mft_core/mft_core_utils/nvtoolslogger/log_config_ui.cpp \
    mft_core/mft_core_utils/nvtoolslogger/log_config_ui.h
mft_core_mft_core_utils_nvtoolslogger_libmft_log_config_ui_la_LIBADD = mft_core/mft_core_utils/nvtoolslogger/libmft_log_config.la -lstdc++

bin_PROGRAMS += mft_core/mft_core_utils/nvtoolslogger/mstflintlogger

mft_core_mft_core_utils_nvtoolslogger_mstflintlogger_SOURCES = mft_core/mft_core_utils/nvtoolslogger/main.cpp
mft_core_mft_core_utils_nvtoolslogger_mstflintlogger_DEPENDENCIES = \
    mft_core/mft_core_utils/nvtoolslogger/libmft_log_config_ui.la \
    mft_core/mft_core_utils/nvtoolslogger/libmft_log_config.la \
    cmdparser/libcmdparser.a
mft_core_mft_core_utils_nvtoolslogger_mstflintlogger_LDADD = $(mft_core_mft_core_utils_nvtoolslogger_mstflintlogger_DEPENDENCIES) $(NVTOOLSLOGGER_JSON_LIBS) -lstdc++
mft_core_mft_core_utils_nvtoolslogger_mstflintlogger_LDFLAGS = -static

# ---------------------------------------------------------------------------
# libnvtoolslogger.so - the same logger exposed as a plain shared object so the
# Python facade can bind the mft_log C ABI through ctypes. Hand-rolled rather
# than a libtool lib_LTLIBRARIES, matching cmtcr.so / ccmdif.so / rreg_access.so
# elsewhere in the tree: one unversioned .so installed next to the module that
# loads it. --whole-archive is required because nothing in the .so references
# mft_log() - the ctypes caller does, at runtime. libtool has folded log_config
# and the bundled jsoncpp into .libs/libnvtoolslogger.a; lib_os_api is named
# separately below because it is only a build-order dependency (see above).

mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.so: mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.la \
		mft_core/mft_core_utils/operating_system_api/lib_os_api.la
	$(CXX) -shared -pthread $(CXXFLAGS) $(LDFLAGS) $(COMPILER_FPIC) -o $@ \
	  -Wl,--whole-archive mft_core/mft_core_utils/nvtoolslogger/.libs/libnvtoolslogger.a \
	    mft_core/mft_core_utils/operating_system_api/.libs/lib_os_api.a \
	  -Wl,--no-whole-archive $(NVTOOLSLOGGER_JSON_SO_LIBS) -lstdc++

CLEANFILES += mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.so

nvtoolslogger_so_pylibdir = $(libdir)/mstflint/python_tools/
nvtoolslogger_so_pylib_DATA = mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.so
dist_nvtoolslogger_so_pylib_DATA = mft_core/mft_core_utils/nvtoolslogger/nvtoolslogger_api.py

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mft_core_mft_core_utils_nvtoolslogger_libmft_log_config_la_CPPFLAGS = $(MFT_CORE_UTILS_NVTOOLSLOGGER_CPPFLAGS)
mft_core_mft_core_utils_nvtoolslogger_libmft_log_config_la_CXXFLAGS = $(MFT_CORE_UTILS_NVTOOLSLOGGER_CXXFLAGS)
mft_core_mft_core_utils_nvtoolslogger_libnvtoolslogger_la_CPPFLAGS = $(MFT_CORE_UTILS_NVTOOLSLOGGER_CPPFLAGS)
mft_core_mft_core_utils_nvtoolslogger_libmft_log_config_ui_la_CPPFLAGS = $(MFT_CORE_UTILS_NVTOOLSLOGGER_CPPFLAGS)
mft_core_mft_core_utils_nvtoolslogger_libmft_log_config_ui_la_CXXFLAGS = $(MFT_CORE_UTILS_NVTOOLSLOGGER_CXXFLAGS)
mft_core_mft_core_utils_nvtoolslogger_mstflintlogger_CPPFLAGS = $(MFT_CORE_UTILS_NVTOOLSLOGGER_CPPFLAGS)
mft_core_mft_core_utils_nvtoolslogger_mstflintlogger_CXXFLAGS = $(MFT_CORE_UTILS_NVTOOLSLOGGER_CXXFLAGS)

########### mft_core/mft_core_utils/logger ###########
MFT_CORE_UTILS_LOGGER_CPPFLAGS = \
    -I$(top_builddir)/mft_core/mft_core_utils/logger \
    -I$(top_srcdir)/mft_core/mft_core_utils/logger \
    -I$(top_builddir) \
    -I$(top_srcdir)

MFT_CORE_UTILS_LOGGER_CXXFLAGS = -Wall -W -g -MP -MD -pipe -Werror $(COMPILER_FPIC)

noinst_LTLIBRARIES += mft_core/mft_core_utils/logger/liblogger.la

mft_core_mft_core_utils_logger_liblogger_la_SOURCES = mft_core/mft_core_utils/logger/Logger.cpp mft_core/mft_core_utils/logger/Logger.h mft_core/mft_core_utils/logger/LoggerDefs.h

mft_core_mft_core_utils_logger_liblogger_la_DEPENDENCIES = mft_core/mft_core_utils/operating_system_api/lib_os_api.la
mft_core_mft_core_utils_logger_liblogger_la_LIBADD = $(LIBSTD_CPP_SO) $(mft_core_mft_core_utils_logger_liblogger_la_DEPENDENCIES) -lstdc++

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mft_core_mft_core_utils_logger_liblogger_la_CPPFLAGS = $(MFT_CORE_UTILS_LOGGER_CPPFLAGS)
mft_core_mft_core_utils_logger_liblogger_la_CXXFLAGS = $(MFT_CORE_UTILS_LOGGER_CXXFLAGS)

########### mft_core/mft_core_utils/mft_exceptions ###########
MFT_CORE_UTILS_MFT_EXCEPTIONS_CPPFLAGS = \
    -I$(top_builddir)/mft_core/mft_core_utils/mft_exceptions \
    -I$(top_srcdir)/mft_core/mft_core_utils/mft_exceptions \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/mft_core/mft_core_utils

MFT_CORE_UTILS_MFT_EXCEPTIONS_CXXFLAGS = -Wall -W -g -MP -MD -pipe -Werror $(COMPILER_FPIC)

noinst_LTLIBRARIES += mft_core/mft_core_utils/mft_exceptions/libmftexceptions.la

mft_core_mft_core_utils_mft_exceptions_libmftexceptions_la_SOURCES = mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h mft_core/mft_core_utils/mft_exceptions/MftGeneralException.cpp mft_core/mft_core_utils/mft_exceptions/DevicePropertyNotFoundException.h

# LOG_AND_THROW_MFT_ERROR logs on the MFT_CORE layer, hence libnvtoolslogger.
mft_core_mft_core_utils_mft_exceptions_libmftexceptions_la_DEPENDENCIES = \
    mft_core/mft_core_utils/operating_system_api/lib_os_api.la \
    mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.la
# Both stay in _DEPENDENCIES for build ordering only. Embedding either here too
# would place its objects in both libmftexceptions.a and the library it came
# from, and a convenience library that pulls in both then ends up with duplicate
# symbols. The logger objects reach every final link through libmtcr_ul anyway.
mft_core_mft_core_utils_mft_exceptions_libmftexceptions_la_LIBADD = $(LIBSTD_CPP_SO)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mft_core_mft_core_utils_mft_exceptions_libmftexceptions_la_CPPFLAGS = $(MFT_CORE_UTILS_MFT_EXCEPTIONS_CPPFLAGS)
mft_core_mft_core_utils_mft_exceptions_libmftexceptions_la_CXXFLAGS = $(MFT_CORE_UTILS_MFT_EXCEPTIONS_CXXFLAGS)

########### mft_core/mft_core_utils/load_shared_library ###########
if ENABLE_MSTFLINT_SDK
if ENABLE_NVML
MFT_CORE_UTILS_LOAD_SHARED_LIBRARY_CPPFLAGS = \
    -I$(top_builddir)/mft_core/mft_core_utils/load_shared_library \
    -I$(top_srcdir)/mft_core/mft_core_utils/load_shared_library \
    -I$(top_builddir) \
    -I$(top_srcdir)/mft_core/mft_core_utils/load_shared_library \
    -I$(top_srcdir) \
    -I$(top_srcdir)/mft_core/mft_core_utils

MFT_CORE_UTILS_LOAD_SHARED_LIBRARY_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES += mft_core/mft_core_utils/load_shared_library/libload_shared_library.la

mft_core_mft_core_utils_load_shared_library_libload_shared_library_la_SOURCES = \
    mft_core/mft_core_utils/load_shared_library/DynamicLinking.h \
    mft_core/mft_core_utils/load_shared_library/FactoryDynamicLinking.cpp \
    mft_core/mft_core_utils/load_shared_library/FactoryDynamicLinking.h \
    mft_core/mft_core_utils/load_shared_library/LinuxDynamicLinking.cpp \
    mft_core/mft_core_utils/load_shared_library/LinuxDynamicLinking.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mft_core_mft_core_utils_load_shared_library_libload_shared_library_la_CPPFLAGS = $(MFT_CORE_UTILS_LOAD_SHARED_LIBRARY_CPPFLAGS)
mft_core_mft_core_utils_load_shared_library_libload_shared_library_la_CXXFLAGS = $(MFT_CORE_UTILS_LOAD_SHARED_LIBRARY_CXXFLAGS)
endif
endif

########### mft_core/device/device_info ###########
MFT_CORE_DEVICE_DEVICE_INFO_CPPFLAGS = \
    -I$(top_builddir)/mft_core/device/device_info \
    -I$(top_srcdir)/mft_core/device/device_info \
    -I$(top_builddir) \
    -I$(top_srcdir)/mft_core/device/device_info \
    -I$(top_srcdir) \
    -I$(top_srcdir)/mft_core/mft_core_utils \
    -I$(top_builddir)/mft_core/device/device_info/generated \
    $(JSON_CFLAGS)

MFT_CORE_DEVICE_DEVICE_INFO_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES += mft_core/device/device_info/libdevice_info.la

mft_core_device_device_info_libdevice_info_la_SOURCES = mft_core/device/device_info/device_properties_api.cpp

noinst_HEADERS += \
    mft_core/device/device_info/device_properties_api.h \
    mft_core/device/device_info/device_hw_ids.h \
    mft_core/device/device_info/device_properties_constants.h

# device_properties_data.h is generated in $(builddir)/generated; depending on
# it here forces automake to run the generator before compiling the .cpp.
nodist_mft_core_device_device_info_libdevice_info_la_SOURCES = mft_core/device/device_info/generated/device_properties_data.h

mft_core_device_device_info_libdevice_info_la_LIBADD = \
    mft_core/mft_core_utils/logger/liblogger.la \
    mft_core/mft_core_utils/mft_exceptions/libmftexceptions.la

noinst_PROGRAMS += mft_core/device/device_info/generate_device_properties
mft_core_device_device_info_generate_device_properties_CPPFLAGS = -I$(top_builddir)/mft_core/device/device_info -I$(top_srcdir)/mft_core/device/device_info -I$(top_builddir) $(JSON_CFLAGS)
mft_core_device_device_info_generate_device_properties_SOURCES = mft_core/device/device_info/generate_device_properties.cpp
mft_core_device_device_info_generate_device_properties_LDADD = $(JSON_LIBS)
mft_core_device_device_info_generate_device_properties_DEPENDENCIES = $(JSON_LIBS)

DEVICE_PROPS_GENERATOR = mft_core/device/device_info/generate_device_properties$(EXEEXT)
DEVICE_PROPS_JSON_DIR = $(srcdir)/mft_core/device/device_info/json
DEVICE_PROPS_GEN_DIR = mft_core/device/device_info/generated
DEVICE_PROPS_GEN_H = $(DEVICE_PROPS_GEN_DIR)/device_properties_data.h
DEVICE_PROPS_GEN_PY = $(DEVICE_PROPS_GEN_DIR)/device_properties_data.py
DEVICE_PROPS_GEN_STAMP = $(DEVICE_PROPS_GEN_DIR)/.device_properties_data.stamp

# Only device_properties_api.cpp includes the generated header, so only its
# object waits for the generator; the rest of the tree compiles meanwhile.
# (The .py is installed data, so `make all` builds it too.)
$(mft_core_device_device_info_libdevice_info_la_OBJECTS): $(DEVICE_PROPS_GEN_H)
CLEANFILES += $(DEVICE_PROPS_GEN_H) $(DEVICE_PROPS_GEN_PY) $(DEVICE_PROPS_GEN_STAMP)

# A single generator invocation produces both files. Drive it through one
# stamp target so the recipe runs exactly once even under `make -j`, avoiding
# the double-run/race a multi-target rule would cause. The recovery rules
# regenerate if an output is removed while the stamp is still present; the
# .py recovery depends on the .h so that, under `make -j`, only one sub-make
# can run the generator when both outputs are missing.
$(DEVICE_PROPS_GEN_H): $(DEVICE_PROPS_GEN_STAMP)
	@if test -f $@; then :; else \
	  rm -f $(DEVICE_PROPS_GEN_STAMP); \
	  $(MAKE) $(AM_MAKEFLAGS) $(DEVICE_PROPS_GEN_STAMP); \
	fi

$(DEVICE_PROPS_GEN_PY): $(DEVICE_PROPS_GEN_H)
	@if test -f $@; then :; else \
	  rm -f $(DEVICE_PROPS_GEN_STAMP); \
	  $(MAKE) $(AM_MAKEFLAGS) $(DEVICE_PROPS_GEN_STAMP); \
	fi

$(DEVICE_PROPS_GEN_STAMP): $(DEVICE_PROPS_GENERATOR) $(wildcard $(DEVICE_PROPS_JSON_DIR)/*.json)
	$(MKDIR_P) $(DEVICE_PROPS_GEN_DIR)
	@touch $@
	./$(DEVICE_PROPS_GENERATOR) $(DEVICE_PROPS_JSON_DIR) $(DEVICE_PROPS_GEN_DIR)
	@touch $(DEVICE_PROPS_GEN_H) $(DEVICE_PROPS_GEN_PY)

EXTRA_DIST += \
    mft_core/device/device_info/device_properties_api.py \
    mft_core/device/device_info/device_properties_constants.py \
    mft_core/device/device_info/unit_test/test_device_id_constants.py \
    mft_core/device/device_info/unit_test/test_device_properties_constants.py \
    mft_core/device/device_info/unit_test/test_device_properties_api.py

# 'make dist' bundles the per-device JSON files without enumerating them here
# (the whole point of option 7 is that the JSON list lives only on disk).

# Python unit tests. `make check` runs them; the drift-guard tests need the
# raw sources, and test_device_properties_api.py imports the module, which in
# turn imports the build-generated device_properties_data module.
TESTS = \
    mft_core/device/device_info/unit_test/test_device_id_constants.py \
    mft_core/device/device_info/unit_test/test_device_properties_constants.py \
    mft_core/device/device_info/unit_test/test_device_properties_api.py

TEST_EXTENSIONS = .py
PY_LOG_COMPILER = $(PYTHON)
AM_TESTS_ENVIRONMENT = \
    PYTHONPATH="$(srcdir)/mft_core/device/device_info:$(builddir)/mft_core/device/device_info/generated:$$PYTHONPATH"; export PYTHONPATH;

# Distribute the Python API alongside other mstflint python tools. The generated
# device_properties_data.py is co-installed so device_properties_api.py can import it.
device_info_pylibdir = $(libdir)/mstflint/python_tools/
dist_device_info_pylib_DATA = mft_core/device/device_info/device_properties_api.py mft_core/device/device_info/device_properties_constants.py
device_info_pylib_DATA = mft_core/device/device_info/generated/device_properties_data.py

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mft_core_device_device_info_libdevice_info_la_CPPFLAGS = $(MFT_CORE_DEVICE_DEVICE_INFO_CPPFLAGS)
mft_core_device_device_info_libdevice_info_la_CXXFLAGS = $(MFT_CORE_DEVICE_DEVICE_INFO_CXXFLAGS)
mft_core_device_device_info_generate_device_properties_CXXFLAGS = $(MFT_CORE_DEVICE_DEVICE_INFO_CXXFLAGS)

########### mft_core/device/nvml ###########
if ENABLE_MSTFLINT_SDK
if ENABLE_NVML
MFT_CORE_DEVICE_NVML_CPPFLAGS = \
    -I$(top_builddir)/mft_core/device/nvml \
    -I$(top_srcdir)/mft_core/device/nvml \
    -I$(top_builddir) \
    -I$(top_srcdir)/mft_core/device/nvml \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_core/mft_core_utils

MFT_CORE_DEVICE_NVML_CPPFLAGS += $(nvml_CFLAGS)

MFT_CORE_DEVICE_NVML_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES += mft_core/device/nvml/libnvml_discovery.la

mft_core_device_nvml_libnvml_discovery_la_SOURCES = \
    mft_core/device/nvml/NvmlDiscoveryLib.cpp \
    mft_core/device/nvml/NvmlDiscoveryLib.h \
    mft_core/device/nvml/NvmlLibWrapper.cpp \
    mft_core/device/nvml/NvmlLibWrapper.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mft_core_device_nvml_libnvml_discovery_la_CPPFLAGS = $(MFT_CORE_DEVICE_NVML_CPPFLAGS)
mft_core_device_nvml_libnvml_discovery_la_CXXFLAGS = $(MFT_CORE_DEVICE_NVML_CXXFLAGS)
endif
endif

########### tools_crypto ###########
if ENABLE_CS
TOOLS_CRYPTO_CPPFLAGS = \
    -I$(top_builddir)/tools_crypto \
    -I$(top_srcdir)/tools_crypto \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    $(COMPILER_FPIC)
TOOLS_CRYPTO_CFLAGS = -MD -pipe -Wall -W -DMST_UL -g $(COMPILER_FPIC)

noinst_LIBRARIES += tools_crypto/libtools_crypto.a
tools_crypto_libtools_crypto_a_SOURCES = tools_crypto/tools_md5.c tools_crypto/tools_md5.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
tools_crypto_libtools_crypto_a_CPPFLAGS = $(TOOLS_CRYPTO_CPPFLAGS)
tools_crypto_libtools_crypto_a_CFLAGS = $(TOOLS_CRYPTO_CFLAGS)
endif

########### mlxsign_lib ###########
if ENABLE_OPENSSL
MLXSIGN_LIB_CPPFLAGS = \
    -I$(top_builddir)/mlxsign_lib \
    -I$(top_srcdir)/mlxsign_lib \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxsign_lib \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common

MLXSIGN_LIB_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)
MLXSIGN_LIB_CXXFLAGS += -DTOOLS_CRYPTO_KEY='$(TOOLS_CRYPTO_KEY)' -DTOOLS_CRYPTO_IV='$(TOOLS_CRYPTO_IV)'

noinst_LTLIBRARIES += mlxsign_lib/libmlxsign.la
mlxsign_lib_libmlxsign_la_SOURCES = \
    mlxsign_lib/mlxsign_lib.cpp \
    mlxsign_lib/mlxsign_lib.h \
    mlxsign_lib/mlxsign_com_def.h \
    mlxsign_lib/mlxsign_signer_interface.h \
    mlxsign_lib/mlxsign_signer_interface.cpp

if ENABLE_OPENSSL
else
MLXSIGN_LIB_CXXFLAGS += -DNO_OPEN_SSL
endif

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxsign_lib_libmlxsign_la_CPPFLAGS = $(MLXSIGN_LIB_CPPFLAGS)
mlxsign_lib_libmlxsign_la_CXXFLAGS = $(MLXSIGN_LIB_CXXFLAGS)
endif

########### tools_layouts ###########
TOOLS_LAYOUTS_CPPFLAGS = \
    -I$(top_builddir)/tools_layouts \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_builddir) \
    -I$(top_srcdir)/${MTCR_CONFIG_DIR} \
    -I$(top_srcdir)/common
TOOLS_LAYOUTS_CFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)
# The SDK ships its PRM databases under a private data root ($(pkgdatadir)/sdk)
# so its package does not clash with the main mstflint package (which owns
# $(pkgdatadir)). getDefaultDBName() resolves databases relative to DATA_PATH,
# so it must point at that same private root when building the SDK.
if ENABLE_MSTFLINT_SDK
TOOLS_LAYOUTS_CXXFLAGS = -DDATA_PATH=\"$(pkgdatadir)/sdk\"
else
TOOLS_LAYOUTS_CXXFLAGS = -DDATA_PATH=\"$(pkgdatadir)\"
endif

noinst_LTLIBRARIES += tools_layouts/libadb_utils.la tools_layouts/libtools_layouts.la tools_layouts/libmlxarchive_layouts.la tools_layouts/libcables_layouts.la

toolslayoutsincludedir = $(includedir)/mstflint/tools_layouts/

toolslayoutsinclude_HEADERS = tools_layouts/icmd_layouts.h tools_layouts/icmd_hca_layouts.h tools_layouts/adb_to_c_utils.h tools_layouts/hca_cap_types_enums.h
tools_layouts_libadb_utils_la_SOURCES = tools_layouts/adb_to_c_utils.c

tools_layouts_libtools_layouts_la_SOURCES = \
    tools_layouts/prm_adb_db.cpp \
    tools_layouts/prm_adb_db.h \
    tools_layouts/adb_to_c_utils.c \
    tools_layouts/adb_to_c_utils.h \
    tools_layouts/cibfw_layouts.c \
    tools_layouts/cibfw_layouts.h \
    tools_layouts/register_access_open_layouts.h \
    tools_layouts/register_access_open_layouts.c \
    tools_layouts/tools_open_layouts.c \
    tools_layouts/tools_open_layouts.h \
    tools_layouts/register_access_sib_layouts.h \
    tools_layouts/register_access_sib_layouts.c \
    tools_layouts/cx4fw_layouts.c \
    tools_layouts/cx4fw_layouts.h \
    tools_layouts/image_layout_layouts.c \
    tools_layouts/image_layout_layouts.h \
    tools_layouts/cx6fw_layouts.c \
    tools_layouts/cx6fw_layouts.h \
    tools_layouts/icmd_layouts.c \
    tools_layouts/icmd_layouts.h \
    tools_layouts/icmd_hca_layouts.c \
    tools_layouts/icmd_hca_layouts.h \
    tools_layouts/reg_access_hca_layouts.c \
    tools_layouts/reg_access_hca_layouts.h \
    tools_layouts/image_info_layouts.c \
    tools_layouts/image_info_layouts.h \
    tools_layouts/reg_access_switch_layouts.c \
    tools_layouts/reg_access_switch_layouts.h \
    tools_layouts/fs5_image_layout_layouts.h \
    tools_layouts/fs5_image_layout_layouts.c \
    tools_layouts/tokens_layout_layouts.c \
    tools_layouts/tokens_layout_layouts.h

tools_layouts_libtools_layouts_la_DEPENDENCIES = tools_layouts/libadb_utils.la
tools_layouts_libmlxarchive_layouts_la_DEPENDENCIES = $(tools_layouts_libtools_layouts_la_DEPENDENCIES)
tools_layouts_libmlxarchive_layouts_la_LIBADD = $(tools_layouts_libtools_layouts_la_LIBADD)
tools_layouts_libmlxarchive_layouts_la_SOURCES = tools_layouts/mlxarchive_layouts.h tools_layouts/mlxarchive_layouts.c

tools_layouts_libcables_layouts_la_SOURCES = tools_layouts/cables_layouts.h tools_layouts/cables_layouts.c
tools_layouts_libcables_layouts_la_DEPENDENCIES = $(tools_layouts_libtools_layouts_la_DEPENDENCIES)
tools_layouts_libcables_layouts_la_LIBADD = $(tools_layouts_libtools_layouts_la_DEPENDENCIES)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
tools_layouts_libadb_utils_la_CPPFLAGS = $(TOOLS_LAYOUTS_CPPFLAGS)
tools_layouts_libadb_utils_la_CFLAGS = $(TOOLS_LAYOUTS_CFLAGS)
tools_layouts_libadb_utils_la_CXXFLAGS = $(TOOLS_LAYOUTS_CXXFLAGS)
tools_layouts_libtools_layouts_la_CPPFLAGS = $(TOOLS_LAYOUTS_CPPFLAGS)
tools_layouts_libtools_layouts_la_CFLAGS = $(TOOLS_LAYOUTS_CFLAGS)
tools_layouts_libtools_layouts_la_CXXFLAGS = $(TOOLS_LAYOUTS_CXXFLAGS)
tools_layouts_libmlxarchive_layouts_la_CPPFLAGS = $(TOOLS_LAYOUTS_CPPFLAGS)
tools_layouts_libmlxarchive_layouts_la_CFLAGS = $(TOOLS_LAYOUTS_CFLAGS)
tools_layouts_libmlxarchive_layouts_la_CXXFLAGS = $(TOOLS_LAYOUTS_CXXFLAGS)
tools_layouts_libcables_layouts_la_CPPFLAGS = $(TOOLS_LAYOUTS_CPPFLAGS)
tools_layouts_libcables_layouts_la_CFLAGS = $(TOOLS_LAYOUTS_CFLAGS)
tools_layouts_libcables_layouts_la_CXXFLAGS = $(TOOLS_LAYOUTS_CXXFLAGS)

########### tools_layouts/adb/prm/hca/ext ###########
if ADB_GENERIC_TOOLS_ENABLED
if ENABLE_MSTFLINT_SDK
prmhcaextdir = $(pkgdatadir)/sdk/prm_dbs/hca/ext
else
prmhcaextdir = $(pkgdatadir)/prm_dbs/hca/ext
endif
prmhcaext_DATA = tools_layouts/adb/prm/hca/ext/register_access_table.adb tools_layouts/adb/prm/hca/ext/hca_cap_table.adb
EXTRA_DIST += tools_layouts/adb/prm/hca/ext/register_access_table.adb tools_layouts/adb/prm/hca/ext/hca_cap_table.adb
endif

########### tools_layouts/adb/prm/switch/ext ###########
if ADB_GENERIC_TOOLS_ENABLED
if ENABLE_MSTFLINT_SDK
prmswitchextdir = $(pkgdatadir)/sdk/prm_dbs/switch/ext
else
prmswitchextdir = $(pkgdatadir)/prm_dbs/switch/ext
endif
prmswitchext_DATA = tools_layouts/adb/prm/switch/ext/register_access_table.adb
EXTRA_DIST += tools_layouts/adb/prm/switch/ext/register_access_table.adb
endif

########### tools_layouts/adb/prm/gpu/ext ###########
if ADB_GENERIC_TOOLS_ENABLED
if ENABLE_MSTFLINT_SDK
prmgpuextdir = $(pkgdatadir)/sdk/prm_dbs/gpu/ext
else
prmgpuextdir = $(pkgdatadir)/prm_dbs/gpu/ext
endif
prmgpuext_DATA = tools_layouts/adb/prm/gpu/ext/register_access_table.adb
EXTRA_DIST += tools_layouts/adb/prm/gpu/ext/register_access_table.adb
endif

########### vfio_driver_access ###########
if BUILD_VFIO_DRIVER
VFIO_DRIVER_ACCESS_CXXFLAGS = \
    -I$(top_srcdir)/vfio_driver_access \
    -I$(top_srcdir) \
    $(JSON_CFLAGS) \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -Wall \
    -W \
    -g \
    -MP \
    -MD \
    -pipe \
    $(COMPILER_FPIC)

noinst_LTLIBRARIES += vfio_driver_access/libvfio_access_driver.la

vfio_driver_access_libvfio_access_driver_la_SOURCES = \
    vfio_driver_access/VFIODriverAccess.cpp \
    vfio_driver_access/VFIODriverAccess.h \
    vfio_driver_access/VFIODriverAccessDefs.h \
    vfio_driver_access/VFIODriverAccessWrapperC.cpp \
    vfio_driver_access/VFIODriverAccessWrapperC.h

vfio_driver_access_libvfio_access_driver_la_DEPENDENCIES = common/libcommon.la
vfio_driver_access_libvfio_access_driver_la_LIBADD = $(vfio_driver_access_libvfio_access_driver_la_DEPENDENCIES)
vfio_driver_access_libvfio_access_driver_la_LDFLAGS = -static

VFIO_DRIVER_ACCESS_CPPFLAGS = -I$(top_builddir)/vfio_driver_access -I$(top_srcdir)/vfio_driver_access -I$(top_builddir)
# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
vfio_driver_access_libvfio_access_driver_la_CPPFLAGS = $(VFIO_DRIVER_ACCESS_CPPFLAGS)
vfio_driver_access_libvfio_access_driver_la_CXXFLAGS = $(VFIO_DRIVER_ACCESS_CXXFLAGS)
endif

########### mtcr_ul ###########
if !MTCR_FREEBSD
MTCR_UL_CPPFLAGS = \
    -I$(top_builddir)/mtcr_ul \
    -I$(top_srcdir)/mtcr_ul \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/common \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/mft_core/mft_core_utils

pkglib_LTLIBRARIES += mtcr_ul/libmtcr_ul.la

mtcr_ul_libmtcr_ul_la_SOURCES = \
    mtcr_ul/mtcr_ul.c \
    mtcr_ul/mtcr_ib.h \
    mtcr_ul/mtcr_int_defs.h \
    mtcr_ul/mtcr_ib_res_mgt.h \
    mtcr_ul/mtcr_ib_res_mgt.c \
    mtcr_ul/mtcr_ul_icmd_cif.c \
    mtcr_ul/mtcr_icmd_cif.h \
    mtcr_ul/mtcr_mem_ops.c \
    mtcr_ul/mtcr_mem_ops.h \
    mtcr_ul/mtcr_ul_com_defs.h \
    mtcr_ul/mtcr_mf.h \
    mtcr_ul/mtcr_ul_com.h \
    mtcr_ul/mtcr_ul_com.c \
    mtcr_ul/mtcr_common.h \
    mtcr_ul/mtcr_common.c \
    mtcr_ul/packets_common.c \
    mtcr_ul/packets_common.h \
    mtcr_ul/packets_layout.c \
    mtcr_ul/packets_layout.h \
    mtcr_ul/fwctrl.c \
    mtcr_ul/fwctrl.h \
    mtcr_ul/fwctrl_ioctl.h \
    mtcr_ul/mtcr_remote.c \
    mtcr_ul/mtcr_remote.h \
    mtcr_ul/mtcr_gpu.c \
    mtcr_ul/mtcr_gpu.h
mtcr_ul_libmtcr_ul_la_CFLAGS = -W -Wall -g -MP -MD -fPIC -DMTCR_API="" -DMST_UL
# The MTCR layer of the central NVIDIA Tools logger. Every tool links
# libmtcr_ul, so this is what puts mft_log() in reach of the whole suite.
# -lstdc++ is already in LDFLAGS below, so the C++ logger adds no new link
# requirement.
mtcr_ul_libmtcr_ul_la_DEPENDENCIES = \
    mft_core/device/device_info/libdevice_info.la \
    mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.la

if ENABLE_INBAND
mtcr_ul_libmtcr_ul_la_SOURCES += mtcr_ul/mtcr_ib_ofed.c
endif

if ENABLE_VFIO
mtcr_ul_libmtcr_ul_la_DEPENDENCIES += vfio_driver_access/libvfio_access_driver.la
endif
# -static in every configuration. Upstream took the unconditional -static as
# its own in PR #1983 (mtcr_ul/Makefile.am), so the base line already carries
# it and what is left here is dropping the two conditional `+= -static' that
# are now redundant. libmtcr_ul ships as a static archive only -- the
# install-exec-hook deletes the shared object -- and every consumer absorbs it,
# the tools via -static and the SDK via MTCR_SDK_WHOLE_ARCHIVE. Built shared,
# it would make libtool relink the SDK at install time with -lmtcr_ul from
# $(pkglibdir): in one Makefile a parallel `make -j install' races that relink
# against the hook (the recursive build always installed mtcr_ul/ first), and
# `make install-sdk' resolves -lmtcr_ul against whatever the build host has.
mtcr_ul_libmtcr_ul_la_LDFLAGS = -static -lstdc++

if ENABLE_NVML
mtcr_ul_libmtcr_ul_la_DEPENDENCIES += $(NVML_DIR)/libnvml_device.la
endif

if ENABLE_CABLES
mtcr_ul_libmtcr_ul_la_SOURCES += mtcr_ul/mtcr_cables.c mtcr_ul/mtcr_cables.h
mtcr_ul_libmtcr_ul_la_DEPENDENCIES += tools_layouts/libcables_layouts.la
endif

# --enable-remote: mtcr_remote.c drives the MST HTTP client, so libmtcr_ul (and
# hence every tool that links it) picks up the client archive, jsoncpp, libcurl
# and libstdc++. Off by default; without it mtcr_remote.c compiles to just the
# never-matching mtcr_remote_is_remote_name() stub.
if ENABLE_MTCR_REMOTE
mtcr_ul_libmtcr_ul_la_DEPENDENCIES += mst_server/client/libmst_http_client.la
endif

mtcr_ul_libmtcr_ul_la_LIBADD = $(mtcr_ul_libmtcr_ul_la_DEPENDENCIES)

# Several links name libtool's archive (.libs/libmtcr_ul.a) directly -- flint's
# _DEPENDENCIES, the python modules, the SDK's whole-archive input. Tie that
# file to the library that produces it so it is always a real prerequisite.
mtcr_ul/.libs/libmtcr_ul.a: mtcr_ul/libmtcr_ul.la
	@test -f $@

mtcr_ul_libraryincludedir = $(includedir)/mstflint
mtcr_ul_libraryinclude_HEADERS = include/mtcr_ul/mtcr.h include/mtcr_ul/mtcr_com_defs.h include/mtcr_ul/mtcr_mf.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mtcr_ul_libmtcr_ul_la_CPPFLAGS = $(MTCR_UL_CPPFLAGS)
endif

########### mtcr_freebsd ###########
if MTCR_FREEBSD
MTCR_FREEBSD_CPPFLAGS = \
    -I$(top_builddir)/mtcr_freebsd \
    -I$(top_srcdir)/mtcr_freebsd \
    -I$(top_builddir) \
    -I$(top_srcdir)/mtcr_freebsd \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mtcr_ul \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/mft_core/mft_core_utils

noinst_LTLIBRARIES += mtcr_freebsd/libmtcr_ul.la

mtcr_freebsd_libmtcr_ul_la_SOURCES = \
    mtcr_ul/mtcr_ib.h \
    mtcr_ul/mtcr_ib_res_mgt.c \
    mtcr_ul/mtcr_ib_res_mgt.h \
    mtcr_ul/mtcr_icmd_cif.h \
    mtcr_ul/mtcr_int_defs.h \
    mtcr_ul/mtcr_mem_ops.c \
    mtcr_ul/mtcr_mem_ops.h \
    mtcr_ul/mtcr_ul_icmd_cif.c \
    mtcr_ul/packets_common.c \
    mtcr_ul/packets_common.h \
    mtcr_ul/packets_layout.c \
    mtcr_ul/packets_layout.h \
    mtcr_ul/mtcr_common.h \
    mtcr_ul/mtcr_common.c \
    mtcr_ul/mtcr_gpu.c \
    mtcr_ul/mtcr_gpu.h \
    mtcr_freebsd/mtcr_mf.h \
    mtcr_freebsd/mtcr_ul.c \
    mtcr_freebsd/mtcr_ul_com_defs.h \
    mtcr_freebsd/mtcr_ul_com_stub.c

mtcr_freebsd_libmtcr_ul_la_CFLAGS = -W -Wall -g -MP -MD -fPIC -DMTCR_API="" -DMST_UL

# This target compiles the shared mtcr_ul/*.c sources, which log on the MTCR
# layer of the central NVIDIA Tools logger, so it needs the same dependency
# the Linux libmtcr_ul has.
if ENABLE_INBAND
mtcr_freebsd_libmtcr_ul_la_SOURCES += mtcr_ul/mtcr_ib_ofed.c
endif

mtcr_freebsd_libmtcr_ul_la_DEPENDENCIES = \
    mft_core/device/device_info/libdevice_info.la \
    mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.la

mtcr_freebsd_libmtcr_ul_la_LIBADD = $(mtcr_freebsd_libmtcr_ul_la_DEPENDENCIES) -lstdc++

mtcr_freebsd/.libs/libmtcr_ul.a: mtcr_freebsd/libmtcr_ul.la
	@test -f $@

mtcr_freebsd_libraryincludedir = $(includedir)/mstflint

mtcr_freebsd_libraryinclude_HEADERS = \
    include/mtcr_ul/mtcr.h \
    include/mtcr_ul/mtcr_com_defs.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mtcr_freebsd_libmtcr_ul_la_CPPFLAGS = $(MTCR_FREEBSD_CPPFLAGS)
endif

########### mtcr_py ###########
mtcr_pylibdir = $(libdir)/mstflint/python_tools/

mtcr_pylib_DATA = mtcr_py/cmtcr.so
dist_mtcr_pylib_DATA = mtcr_py/mtcr.py

# With --enable-vfio, libmtcr_ul.a absorbs vfio_driver_access -> libcommon
# (tools_json.cpp), which references jsoncpp symbols (Json::parseFromStream,
# Json::Value::asString, ...). cmtcr.so must therefore also link jsoncpp,
# otherwise it fails to dlopen at runtime with "undefined symbol: _ZN4Json...".
if ENABLE_VFIO
if USE_LOCAL_JSON
CMTCR_JSON_LIBS = ext_libs/json/.libs/libjson.a
else
CMTCR_JSON_LIBS = -ljsoncpp
endif
else
CMTCR_JSON_LIBS =
endif

mtcr_py/cmtcr.so: $(MTCR_CONF_DIR)/libmtcr_ul.la
	@$(MKDIR_P) $(@D)
	$(CC) -g -Wall -pthread -shared ${CFLAGS} ${LDFLAGS} -o $@ -Wl,--whole-archive ${MTCR_CONF_DIR}/.libs/libmtcr_ul.a -Wl,--no-whole-archive $(CMTCR_JSON_LIBS) $(MST_REMOTE_LINK_LIBS) -lstdc++

CLEANFILES += mtcr_py/cmtcr.so

########### mad_ifc ###########
if ENABLE_INBAND
MAD_IFC_CPPFLAGS = \
    -I$(top_builddir)/mad_ifc \
    -I$(top_srcdir)/mad_ifc \
    -I$(top_builddir) \
    -I$(top_srcdir)/mad_ifc \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/tools_layouts

MAD_IFC_CFLAGS = -W -Wall -g -MP -MD $(COMPILER_FPIC)

noinst_LTLIBRARIES += mad_ifc/libmad_ifc.la

mad_ifc_libmad_ifc_la_SOURCES = mad_ifc/mad_ifc.c mad_ifc/mad_ifc.h
mad_ifc_libmad_ifc_la_DEPENDENCIES = tools_layouts/libtools_layouts.la
mad_ifc_libmad_ifc_la_LIBADD = $(mad_ifc_libmad_ifc_la_DEPENDENCIES)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mad_ifc_libmad_ifc_la_CPPFLAGS = $(MAD_IFC_CPPFLAGS)
mad_ifc_libmad_ifc_la_CFLAGS = $(MAD_IFC_CFLAGS)
endif

########### xz_utils ###########
if BUILD_XZ_UTILS
XZ_UTILS_CPPFLAGS = \
    -I$(top_builddir)/xz_utils \
    -I$(top_srcdir)/xz_utils \
    -I$(top_builddir) \
    -I$(top_srcdir)/xz_utils \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common

XZ_UTILS_CFLAGS = -W -g -MP -MD ${COMPILER_FPIC}

noinst_LTLIBRARIES += xz_utils/libxz_utils.la

xz_utils_libxz_utils_la_SOURCES = \
    xz_utils/xz_utils.c \
    xz_utils/xz_utils.h

xz_utils_libxz_utils_la_DEPENDENCIES =
xz_utils_libxz_utils_la_LIBADD = $(liblzma_LIBS)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
xz_utils_libxz_utils_la_CPPFLAGS = $(XZ_UTILS_CPPFLAGS)
xz_utils_libxz_utils_la_CFLAGS = $(XZ_UTILS_CFLAGS)
endif

########### reg_access ###########
REG_ACCESS_CPPFLAGS = \
    -I$(top_builddir)/reg_access \
    -I$(top_srcdir)/reg_access \
    -I$(top_builddir) \
    -I$(top_srcdir)/reg_access \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/tools_layouts

REG_ACCESS_CFLAGS = -W -Wall -g -MP -MD $(COMPILER_FPIC)
REG_ACCESS_CXXFLAGS = -W -Wall -g -MP -MD $(COMPILER_FPIC)

noinst_LTLIBRARIES += reg_access/libreg_access.la

reg_access_libreg_access_la_SOURCES = \
    reg_access/reg_access.c \
    reg_access/reg_access.h \
    reg_access/reg_access_common.h \
    reg_access/reg_access_macros.h \
    reg_access/mcam_capabilities.cpp \
    reg_access/mcam_capabilities.h

reg_access_libreg_access_la_DEPENDENCIES = tools_layouts/libtools_layouts.la

reg_access_libreg_access_la_LIBADD = $(reg_access_libreg_access_la_DEPENDENCIES)

reg_access_pylibdir = $(libdir)/mstflint/python_tools/

reg_access_pylib_DATA = reg_access/rreg_access.so
dist_reg_access_pylib_DATA = reg_access/regaccess.py reg_access/regaccess_hca_ext_structs.py reg_access/regaccess_switch_ext_structs.py

reg_access/rreg_access.so: reg_access/libreg_access.la tools_layouts/libtools_layouts.la $(MTCR_CONF_DIR)/libmtcr_ul.la
	$(CC) -g -Wall -pthread -shared ${CFLAGS} ${LDFLAGS} $(sort $(patsubst %.lo,%.o,$(reg_access_libreg_access_la_OBJECTS))) -o $@ \
	tools_layouts/.libs/libtools_layouts.a ${MTCR_CONF_DIR}/.libs/libmtcr_ul.a \
	$(MST_REMOTE_LINK_LIBS) -lstdc++

CLEANFILES += reg_access/rreg_access.so

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
reg_access_libreg_access_la_CPPFLAGS = $(REG_ACCESS_CPPFLAGS)
reg_access_libreg_access_la_CFLAGS = $(REG_ACCESS_CFLAGS)
reg_access_libreg_access_la_CXXFLAGS = $(REG_ACCESS_CXXFLAGS)

########### cmdif ###########
CMDIF_CPPFLAGS = \
    -I$(top_builddir)/cmdif \
    -I$(top_srcdir)/cmdif \
    -I$(top_builddir) \
    -I$(top_srcdir)/cmdif \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/tools_layouts

CMDIF_CFLAGS = -W -Wall -g -MP -MD $(COMPILER_FPIC) -DCMDIF_EXPORTS

noinst_LTLIBRARIES += cmdif/libcmdif.la

cmdifincludedir = $(includedir)/mstflint/cmdif/

cmdifinclude_HEADERS = cmdif/icmd_cif_common.h cmdif/icmd_cif_open.h

cmdif_libcmdif_la_SOURCES = cmdif/icmd_cif_common.c cmdif/icmd_cif_common.h cmdif/icmd_cif_open.c cmdif/icmd_cif_open.h

cmdif_pylibdir = $(libdir)/mstflint/python_tools/
cmdif_pylib_DATA = cmdif/ccmdif.so cmdif/cmdif.py
cmdif/ccmdif.so: cmdif/libcmdif.la tools_layouts/libtools_layouts.la $(MTCR_CONF_DIR)/libmtcr_ul.la
	$(CC) -g -Wall -pthread -shared ${CFLAGS} ${LDFLAGS} $(sort $(patsubst %.lo,%.o,$(cmdif_libcmdif_la_OBJECTS))) -o $@ \
	tools_layouts/.libs/libtools_layouts.a ${MTCR_CONF_DIR}/.libs/libmtcr_ul.a \
	$(MST_REMOTE_LINK_LIBS) -lstdc++

CLEANFILES += cmdif/ccmdif.so

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
cmdif_libcmdif_la_CPPFLAGS = $(CMDIF_CPPFLAGS)
cmdif_libcmdif_la_CFLAGS = $(CMDIF_CFLAGS)

########### dev_mgt ###########
DEV_MGT_CPPFLAGS = \
    -I$(top_builddir)/dev_mgt \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_builddir) \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/include/mtcr_ul

DEV_MGT_CFLAGS = -W -Wall -g -MP -MD -Wswitch-enum $(COMPILER_FPIC) -DMTCR_EXPORT

noinst_LTLIBRARIES += dev_mgt/libdev_mgt.la

dev_mgt_libdev_mgt_la_SOURCES = \
    dev_mgt/tools_dev_types.c \
    dev_mgt/tools_dev_types.h \
    dev_mgt/therm_fw.c \
    dev_mgt/therm_fw.h

dev_mgt_pylibdir = $(libdir)/mstflint/python_tools/

dev_mgt_pylib_DATA = dev_mgt/c_dev_mgt.so
dist_dev_mgt_pylib_DATA = dev_mgt/dev_mgt.py

dev_mgt/c_dev_mgt.so: dev_mgt/libdev_mgt.la reg_access/libreg_access.la tools_layouts/libtools_layouts.la \
		$(MTCR_CONF_DIR)/libmtcr_ul.la
	$(CC) -g -Wall -pthread -shared ${CFLAGS} ${LDFLAGS} \
	$(patsubst %.lo,%.o,$(filter %-tools_dev_types.lo,$(dev_mgt_libdev_mgt_la_OBJECTS))) -o $@ \
	reg_access/.libs/libreg_access.a \
	tools_layouts/.libs/libtools_layouts.a \
	${MTCR_CONF_DIR}/.libs/libmtcr_ul.a \
	$(MST_REMOTE_LINK_LIBS) -lstdc++

CLEANFILES += dev_mgt/c_dev_mgt.so

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
dev_mgt_libdev_mgt_la_CPPFLAGS = $(DEV_MGT_CPPFLAGS)
dev_mgt_libdev_mgt_la_CFLAGS = $(DEV_MGT_CFLAGS)

########### pci_library ###########
PCI_LIBRARY_CXXFLAGS = \
    -I$(top_srcdir)/pci_library \
    -I$(top_srcdir) \
    -I$(top_srcdir)/mft_core/mft_core_utils \
    -Wall \
    -W \
    -g \
    -MP \
    -MD \
    -pipe \
    $(COMPILER_FPIC)

noinst_LTLIBRARIES += pci_library/libpci_library.la

pci_library_libpci_library_la_SOURCES = pci_library/PCILibrary.cpp pci_library/PCILibrary.h

# libnvtoolslogger is a build-order dependency only: PCILibrary logs on the
# COMMON layer, but every consumer of this convenience library already links
# libmtcr_ul, which carries the logger objects. Adding it to LIBADD as well
# would fold a second copy of spdlog into the archive for nothing.
pci_library_libpci_library_la_DEPENDENCIES = \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la \
    mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.la
pci_library_libpci_library_la_LIBADD = \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la
pci_library_libpci_library_la_LDFLAGS = -static

PCI_LIBRARY_CPPFLAGS = -I$(top_builddir)/pci_library -I$(top_srcdir)/pci_library -I$(top_builddir)
# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
pci_library_libpci_library_la_CPPFLAGS = $(PCI_LIBRARY_CPPFLAGS)
pci_library_libpci_library_la_CXXFLAGS = $(PCI_LIBRARY_CXXFLAGS)

########### mft_utils ###########
MFT_UTILS_CPPFLAGS = \
    -I$(top_builddir)/mft_utils \
    -I$(top_srcdir)/mft_utils \
    -I$(top_builddir) \
    -I$(top_builddir)/mft_utils \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    $(COMPILER_FPIC)

MFT_UTILS_CFLAGS = -MD -pipe -Wall -W $(COMPILER_FPIC)

MFT_UTILS_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_HEADERS += mft_utils/mft_sig_handler.h mft_utils/errmsg.h mft_utils/hex64.h

noinst_LTLIBRARIES += mft_utils/libmftutils.la

mft_utils_libmftutils_la_SOURCES = mft_utils/mft_sig_handler.c mft_utils/errmsg.cpp mft_utils/calc_hw_crc.c mft_utils/mlarge_buffer.cpp mft_utils/mft_utils.cpp mft_utils/hex64.cpp mft_utils/crc16.h mft_utils/crc16.cpp

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mft_utils_libmftutils_la_CPPFLAGS = $(MFT_UTILS_CPPFLAGS)
mft_utils_libmftutils_la_CFLAGS = $(MFT_UTILS_CFLAGS)
mft_utils_libmftutils_la_CXXFLAGS = $(MFT_UTILS_CXXFLAGS)

########### cable_access ###########
if ENABLE_CABLES
noinst_LTLIBRARIES += cable_access/libcable_access.la

cable_access_libcable_access_la_SOURCES = cable_access/cdb_cable_access.cpp cable_access/cdb_cable_access.h cable_access/cdb_cable_commander.cpp cable_access/cdb_cable_commander.h cable_access/cable_access.cpp cable_access/cable_access.h
cable_access_libcable_access_la_CXXFLAGS = -W -Wall -g -MP -MD -fPIC -DMTCR_API="" -DMST_UL -I$(top_srcdir)/${MTCR_CONF_DIR} -I$(top_srcdir)/common -I$(top_srcdir) -I$(top_srcdir)/include/${MTCR_CONF_DIR}/
cable_access_libcable_access_la_LDFLAGS = -lstdc++ -static
cable_access_libcable_access_la_DEPENDENCIES = ${MTCR_CONF_DIR}/libmtcr_ul.la reg_access/libreg_access.la dev_mgt/libdev_mgt.la tools_layouts/libcables_layouts.la
cable_access_libcable_access_la_LIBADD = $(cable_access_libcable_access_la_DEPENDENCIES)

CABLE_ACCESS_CPPFLAGS = -I$(top_builddir)/cable_access -I$(top_srcdir)/cable_access -I$(top_builddir)
# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
cable_access_libcable_access_la_CPPFLAGS = $(CABLE_ACCESS_CPPFLAGS)
endif

########### tools_res_mgmt ###########
TOOLS_RES_MGMT_CPPFLAGS = \
    -I$(top_builddir)/tools_res_mgmt \
    -I$(top_srcdir)/tools_res_mgmt \
    -I$(top_builddir) \
    -I$(top_srcdir)/tools_res_mgmt \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/include/mtcr_ul

TOOLS_RES_MGMT_CFLAGS = -W -Wall -g -MP -MD $(COMPILER_FPIC)

noinst_LTLIBRARIES += tools_res_mgmt/libtools_res_mgmt.la

tools_res_mgmt_libtools_res_mgmt_la_SOURCES = tools_res_mgmt/tools_res_mgmt.c tools_res_mgmt/tools_res_mgmt.h tools_res_mgmt/tools_time.c tools_res_mgmt/tools_time.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
tools_res_mgmt_libtools_res_mgmt_la_CPPFLAGS = $(TOOLS_RES_MGMT_CPPFLAGS)
tools_res_mgmt_libtools_res_mgmt_la_CFLAGS = $(TOOLS_RES_MGMT_CFLAGS)

########### mvpd ###########
MVPD_CPPFLAGS = \
    -I$(top_builddir)/mvpd \
    -I$(top_srcdir)/mvpd \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/dev_mgt

MVPD_CFLAGS = -W -Wall -g -MP -MD $(COMPILER_FPIC)

noinst_LTLIBRARIES += mvpd/libmvpd.la

mvpd_libmvpd_la_SOURCES = mvpd/mvpd.c mvpd/mvpd.h

mvpd_libmvpd_la_DEPENDENCIES = ${MTCR_CONF_DIR}/libmtcr_ul.la
mvpd_libmvpd_la_LIBADD = $(mvpd_libmvpd_la_DEPENDENCIES)

noinst_HEADERS += mvpd/mvpd.h

mvpd/rmvpd.so: mvpd/libmvpd.la $(MTCR_CONF_DIR)/libmtcr_ul.la
	$(CC) -g -Wall -pthread -shared ${CFLAGS} $(sort $(patsubst %.lo,%.o,$(mvpd_libmvpd_la_OBJECTS))) -o $@ \
	 ${MTCR_CONF_DIR}/.libs/libmtcr_ul.a $(MST_REMOTE_LINK_LIBS)

CLEANFILES += mvpd/rmvpd.so

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mvpd_libmvpd_la_CPPFLAGS = $(MVPD_CPPFLAGS)
mvpd_libmvpd_la_CFLAGS = $(MVPD_CFLAGS)

########### mflash ###########
MFLASH_CPPFLAGS = \
    -I$(top_builddir)/mflash \
    -I$(top_srcdir)/mflash \
    -I$(top_builddir) \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir) \
    -I$(top_srcdir)/cmdif \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/reg_access \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/tools_res_mgmt \
    -I$(top_srcdir)/mft_core/mft_core_utils

MFLASH_CPPFLAGS += $(COMPILER_FPIC)

MFLASH_CFLAGS = -MD -pipe -Wall -W -DMST_UL -g ${MFLASH_INBAND_FLAG} $(COMPILER_FPIC)

noinst_LTLIBRARIES += mflash/libmflash.la

mflash_libmflash_la_SOURCES = \
    mflash/mflash.c \
    mflash/mflash.h \
    mflash/mflash_gw.c \
    mflash/mflash_gw.h \
    mflash/mflash_new_gw.c \
    mflash/mflash_new_gw.h \
    mflash/mflash_dev_capability.c \
    mflash/mflash_dev_capability.h \
    mflash/mflash_pack_layer.c \
    mflash/mflash_pack_layer.h \
    mflash/mflash_access_layer.c \
    mflash/mflash_access_layer.h \
    mflash/mflash_common_structs.h \
    mflash/mflash_types.h \
    mflash/flash_int_defs.h

noinst_HEADERS += mflash/mflash.h mflash/mflash_gw.h mflash/mflash_new_gw.h mflash/mflash_types.h mflash/mflash_common_structs.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mflash_libmflash_la_CPPFLAGS = $(MFLASH_CPPFLAGS)
mflash_libmflash_la_CFLAGS = $(MFLASH_CFLAGS)

########### fw_comps_mgr ###########
FW_COMPS_MGR_CPPFLAGS = \
    -I$(top_builddir)/fw_comps_mgr \
    -I$(top_srcdir)/fw_comps_mgr \
    -I$(top_builddir) \
    -I$(top_srcdir)/fw_comps_mgr \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/cmdif \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/reg_access \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/tools_res_mgmt

FW_COMPS_MGR_CFLAGS = -MD -pipe -Wall -W $(COMPILER_FPIC)

FW_COMPS_MGR_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES += fw_comps_mgr/libfw_comps_mgr.la

fw_comps_mgr_libfw_comps_mgr_la_SOURCES = \
    fw_comps_mgr/fw_comps_mgr.cpp \
    fw_comps_mgr/fw_comps_mgr.h \
    fw_comps_mgr/fw_comps_mgr_abstract_access.cpp \
    fw_comps_mgr/fw_comps_mgr_abstract_access.h \
    fw_comps_mgr/fw_comps_mgr_direct_access.cpp \
    fw_comps_mgr/fw_comps_mgr_direct_access.h \
    fw_comps_mgr/fw_comps_mgr_dma_access.cpp \
    fw_comps_mgr/fw_comps_mgr_dma_access.h

if ENABLE_INBAND
else
FW_COMPS_MGR_CXXFLAGS += "-DNO_INBAND"
endif

fw_comps_mgr_libfw_comps_mgr_la_DEPENDENCIES = \
    reg_access/libreg_access.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    tools_res_mgmt/libtools_res_mgmt.la \
    mft_utils/libmftutils.la \
    common/libcommon.la

if ENABLE_INBAND
fw_comps_mgr_libfw_comps_mgr_la_DEPENDENCIES += mad_ifc/libmad_ifc.la
endif

fw_comps_mgr_libfw_comps_mgr_la_LIBADD = $(fw_comps_mgr_libfw_comps_mgr_la_DEPENDENCIES)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
fw_comps_mgr_libfw_comps_mgr_la_CPPFLAGS = $(FW_COMPS_MGR_CPPFLAGS)
fw_comps_mgr_libfw_comps_mgr_la_CFLAGS = $(FW_COMPS_MGR_CFLAGS)
fw_comps_mgr_libfw_comps_mgr_la_CXXFLAGS = $(FW_COMPS_MGR_CXXFLAGS)

########### libmfa ###########
LIBMFA_CPPFLAGS = \
    -I$(top_builddir)/libmfa \
    -I$(top_srcdir)/libmfa \
    -I$(top_builddir) \
    -I$(top_srcdir)/libmfa \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/ext_libs/minixz

LIBMFA_CFLAGS = -MD -pipe -Wall -W -g $(COMPILER_FPIC)

noinst_LTLIBRARIES += libmfa/libmfa.la

libmfa_libmfa_la_SOURCES = \
    libmfa/mfa.c \
    libmfa/mfa.h \
    libmfa/mfa_section.c \
    libmfa/mfa_section.h \
    libmfa/mfaerr.h \
    libmfa/xz_io_ops.c \
    libmfa/xz_io_ops.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
libmfa_libmfa_la_CPPFLAGS = $(LIBMFA_CPPFLAGS)
libmfa_libmfa_la_CFLAGS = $(LIBMFA_CFLAGS)

########### pldm_utils ###########
PLDM_UTILS_CPPFLAGS = \
    -I$(top_builddir)/pldm_utils \
    -I$(top_srcdir)/pldm_utils \
    -I$(top_builddir) \
    -I$(top_builddir)/pldm_utils \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    $(JSON_CFLAGS)

PLDM_UTILS_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES += pldm_utils/libpldm_utils.la

pldm_utils_libpldm_utils_la_SOURCES = \
    pldm_utils/pldm_utils.cpp \
    pldm_utils/pldm_utils.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
pldm_utils_libpldm_utils_la_CPPFLAGS = $(PLDM_UTILS_CPPFLAGS)
pldm_utils_libpldm_utils_la_CXXFLAGS = $(PLDM_UTILS_CXXFLAGS)

########### pldmlib ###########
PLDMLIB_CPPFLAGS = \
    -I$(top_builddir)/pldmlib \
    -I$(top_srcdir)/pldmlib \
    -I$(top_builddir) \
    -I$(top_builddir)/pldmlib \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    $(JSON_CFLAGS)

PLDMLIB_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) -DPLDMLIB_EXPORT

noinst_LTLIBRARIES += pldmlib/libpldm.la

pldmlib_libpldm_la_SOURCES = \
    pldmlib/pldm_buff.cpp \
    pldmlib/pldm_buff.h \
    pldmlib/pldm_record_descriptor.cpp \
    pldmlib/pldm_record_descriptor.h \
    pldmlib/pldm_dev_id_record.cpp \
    pldmlib/pldm_dev_id_record.h \
    pldmlib/pldm_component_image.cpp \
    pldmlib/pldm_component_image.h \
    pldmlib/pldm_pkg_hdr.cpp \
    pldmlib/pldm_pkg_hdr.h \
    pldmlib/pldm_pkg.cpp \
    pldmlib/pldm_pkg.h

pldmlib_libpldm_la_LIBADD = pldm_utils/libpldm_utils.la

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
pldmlib_libpldm_la_CPPFLAGS = $(PLDMLIB_CPPFLAGS)
pldmlib_libpldm_la_CXXFLAGS = $(PLDMLIB_CXXFLAGS)

########### mlxdpa ###########
if ENABLE_DPA
MLXDPA_CPPFLAGS = \
    -I$(top_builddir)/mlxdpa \
    -I$(top_srcdir)/mlxdpa \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxdpa \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONFIG_DIR} \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mft_core/mft_core_utils \
    -I$(top_srcdir)/mlxsign_lib \
    -I$(top_srcdir)/ext_libs/mini-yaml \
    -I$(top_srcdir)/ext_libs/sole \
    $(openssl_CFLAGS)

XML_FLAGS = -DUSE_XML -DLIBXML_STATIC

MLXDPA_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) $(XML_FLAGS)

noinst_LIBRARIES += mlxdpa/libmstdpa.a

mlxdpa_libmstdpa_a_SOURCES = \
    mlxdpa/baseHeader.cpp \
    mlxdpa/baseHeader.h \
    mlxdpa/certcontainerbase.cpp \
    mlxdpa/certcontainerbase.h \
    mlxdpa/certcontainerimp.cpp \
    mlxdpa/certcontainerimp.h \
    mlxdpa/dpaAppStructHeader.cpp \
    mlxdpa/dpaAppStructHeader.h

mlxdpa_libmstdpa_a_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) $(XML_FLAGS)

mlxdpa_libmstdpa_a_DEPENDENCIES = mft_utils/libmftutils.la

mlxdpa_libmstdpa_a_LIBADD = $(mlxdpa_libmstdpa_a_DEPENDENCIES)

bin_PROGRAMS += mlxdpa/mstdpa

mlxdpa_mstdpa_SOURCES = \
    mlxdpa/baseHeader.cpp \
    mlxdpa/baseHeader.h \
    mlxdpa/certcontainerbase.cpp \
    mlxdpa/certcontainerbase.h \
    mlxdpa/certcontainerimp.cpp \
    mlxdpa/certcontainerimp.h \
    mlxdpa/cryptodata.cpp \
    mlxdpa/cryptodata.h \
    mlxdpa/dpaAppRemoval.cpp \
    mlxdpa/dpaAppRemoval.h \
    mlxdpa/dpaAppStructHeader.cpp \
    mlxdpa/dpaAppStructHeader.h \
    mlxdpa/hostelf.cpp \
    mlxdpa/hostelf.h \
    mlxdpa/hostless.cpp \
    mlxdpa/hostless.h \
    mlxdpa/mlxdpa.cpp \
    mlxdpa/mlxdpa.h \
    mlxdpa/mlxdpa_utils.cpp \
    mlxdpa/mlxdpa_utils.h

mlxdpa_mstdpa_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) $(XML_FLAGS)

mlxdpa_mstdpa_LDADD = \
    cmdparser/libcmdparser.a \
    mlxsign_lib/libmlxsign.la \
    mft_utils/libmftutils.la \
    mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.la \
    mft_core/mft_core_utils/operating_system_api/lib_os_api.la \
    tools_layouts/libtools_layouts.la \
    ext_libs/mini-yaml/libmini_yaml.la \
    ext_libs/sole/libsole.la \
    xz_utils/libxz_utils.la \
    ext_libs/minixz/libminixz.la \
    $(liblzma_LIBS)

# these are precompiled
if ARM64_BUILD
mlxdpa_mstdpa_LDADD += $(srcdir)/mlxdpa/dpa_elf/arm64/libdpa_elf
endif
if X86_64_BUILD
mlxdpa_mstdpa_LDADD += $(srcdir)/mlxdpa/dpa_elf/x86_64/libdpa_elf
endif

if ENABLE_OPENSSL
mlxdpa_mstdpa_LDADD += $(openssl_LIBS)
else
mlxdpa_mstdpa_CXXFLAGS += -DNO_OPEN_SSL
endif

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxdpa_libmstdpa_a_CPPFLAGS = $(MLXDPA_CPPFLAGS)
mlxdpa_mstdpa_CPPFLAGS = $(MLXDPA_CPPFLAGS)
endif

########### mlxfwops/lib ###########
MLXFWOPS_LIB_CPPFLAGS = \
    -I$(top_builddir)/mlxfwops/lib \
    -I$(top_srcdir)/mlxfwops/lib \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxfwops/lib \
    -I$(top_srcdir)/mlxfwops/lib/components \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/ext_libs/minixz \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxfwops/uefi_c \
    -I$(top_srcdir)/mtcr_ul \
    -I$(top_srcdir)/tools_layouts

MLXFWOPS_LIB_CPPFLAGS += $(JSON_CFLAGS)

MLXFWOPS_LIB_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) -Wno-implicit-fallthrough

if ENABLE_FWMGR
MLXFWOPS_LIB_CPPFLAGS += -I$(top_srcdir)/libmfa
else
MLXFWOPS_LIB_CXXFLAGS += -DNO_MFA_SUPPORT
endif

if ENABLE_OPENSSL
else
MLXFWOPS_LIB_CXXFLAGS += -DNO_OPEN_SSL
endif

if ENABLE_CS
else
MLXFWOPS_LIB_CXXFLAGS += -DNO_CS_CMD
endif

noinst_LIBRARIES += mlxfwops/lib/libmlxfwops.a

mlxfwops_lib_libmlxfwops_a_SOURCES = \
    mlxfwops/lib/aux_tlv_ops.cpp \
    mlxfwops/lib/aux_tlv_ops.h \
    mlxfwops/lib/bluefiled_signature_manager.cpp \
    mlxfwops/lib/connectx6_signature_manager.cpp \
    mlxfwops/lib/flint_base.cpp \
    mlxfwops/lib/flint_base.h \
    mlxfwops/lib/flint_io.cpp \
    mlxfwops/lib/flint_io.h \
    mlxfwops/lib/fs_checks.cpp \
    mlxfwops/lib/fs_checks.h \
    mlxfwops/lib/fs3_ops.cpp \
    mlxfwops/lib/fs3_ops.h \
    mlxfwops/lib/fs4_ops.cpp \
    mlxfwops/lib/fs4_ops.h \
    mlxfwops/lib/fs5_ops.cpp \
    mlxfwops/lib/fs5_ops.h \
    mlxfwops/lib/fsctrl_ops.cpp \
    mlxfwops/lib/fsctrl_ops.h \
    mlxfwops/lib/fs_pldm.cpp \
    mlxfwops/lib/fs_pldm.h \
    mlxfwops/lib/fw_ops.cpp \
    mlxfwops/lib/fw_ops.h \
    mlxfwops/lib/fw_version.cpp \
    mlxfwops/lib/mlxfwops_com.h \
    mlxfwops/lib/psid_utils.cpp \
    mlxfwops/lib/psid_utils.h \
    mlxfwops/lib/mlxfwops.cpp \
    mlxfwops/lib/mlxfwops.h \
    mlxfwops/lib/security_version_gw.cpp \
    mlxfwops/lib/security_version_gw.h \
    mlxfwops/lib/signature_manager_factory.h \
    mlxfwops/lib/signature_manager.h \
    mlxfwops/lib/components/fs_comps_factory.h \
    mlxfwops/lib/components/fs_cert_ops.cpp \
    mlxfwops/lib/components/fs_cert_ops.h \
    mlxfwops/lib/components/fs_comps_ops.cpp \
    mlxfwops/lib/components/fs_comps_ops.h \
    mlxfwops/lib/components/fs_synce_ops.cpp \
    mlxfwops/lib/components/fs_synce_ops.h

if ENABLE_DPA
MLXFWOPS_LIB_CXXFLAGS += -DENABLE_DPA
mlxfwops_lib_libmlxfwops_a_SOURCES += \
    mlxfwops/lib/components/fs_dpa_app_ops.cpp \
    mlxfwops/lib/components/fs_dpa_app_ops.h
mlxfwops_lib_libmlxfwops_a_DEPENDENCIES = mlxdpa/libmstdpa.a
endif

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxfwops_lib_libmlxfwops_a_CPPFLAGS = $(MLXFWOPS_LIB_CPPFLAGS)
mlxfwops_lib_libmlxfwops_a_CXXFLAGS = $(MLXFWOPS_LIB_CXXFLAGS)

########### mlxconfig ###########

MLXCONFIG_CPPFLAGS = \
    -I$(top_builddir)/mlxconfig \
    -I$(top_srcdir)/mlxconfig \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxconfig \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/cmdif \
    -I$(top_srcdir)/tools_res_mgmt \
    -I$(top_srcdir)/mflash \
    $(libxml2_CFLAGS) \
    $(openssl_CFLAGS)

MLXCONFIG_CPPFLAGS += $(MUPARSER_CFLAGS) $(SQLITE_CFLAGS) $(COMPILER_FPIC)

MLXCONFIG_CXXFLAGS = -pthread -Wall -W -g -MP -MD -pipe $(JSON_CFLAGS) -Wno-deprecated-declarations $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"

bin_PROGRAMS += mlxconfig/mstconfig

if ADB_GENERIC_TOOLS_ENABLED
bin_SCRIPTS += mlxconfig/mstprivhost
mlxconfig/mstprivhost: common/python_wrapper
	@$(MKDIR_P) $(@D)
	cp common/python_wrapper $@

mlxprivhostlibdir = $(libdir)/mstflint/python_tools/mstprivhost
mlxprivhostlib_DATA = mlxconfig/mstprivhost.py
endif

noinst_LTLIBRARIES += mlxconfig/libmlxcfg.la

mlxconfig_libmlxcfg_la_SOURCES = \
    mlxconfig/mlxcfg_status.h \
    mlxconfig/mlxcfg_utils.h \
    mlxconfig/mlxcfg_utils.cpp \
    mlxconfig/mlxcfg_view.h \
    mlxconfig/mlxcfg_expression.h \
    mlxconfig/mlxcfg_expression.cpp \
    mlxconfig/mlxcfg_db_items.h \
    mlxconfig/mlxcfg_db_items.cpp \
    mlxconfig/mlxcfg_db_manager.h \
    mlxconfig/mlxcfg_db_manager.cpp \
    mlxconfig/mlxcfg_param.h \
    mlxconfig/mlxcfg_param.cpp \
    mlxconfig/mlxcfg_tlv.h \
    mlxconfig/mlxcfg_tlv.cpp \
    mlxconfig/mlxcfg_commander.h \
    mlxconfig/mlxcfg_commander.cpp \
    mlxconfig/mlxcfg_generic_commander.h \
    mlxconfig/mlxcfg_generic_commander.cpp \
    mlxconfig/mlxcfg_ui_tokens.h \
    mlxconfig/mlxcfg_ui_tokens.cpp \
    mlxconfig/mlxcfg_configuration.h \
    mlxconfig/mlxcfg_configuration.cpp

mlxconfig_libmlxcfg_la_DEPENDENCIES = \
    mft_utils/libmftutils.la \
    cmdif/libcmdif.la \
    reg_access/libreg_access.la \
    tools_layouts/libtools_layouts.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    dev_mgt/libdev_mgt.la \
    fw_comps_mgr/libfw_comps_mgr.la \
    tools_res_mgmt/libtools_res_mgmt.la \
    $(MUPARSER_LIBS) \
    $(SQLITE_LIBS)

mlxconfig_libmlxcfg_la_LIBADD = $(mlxconfig_libmlxcfg_la_DEPENDENCIES) $(JSON_LIBS) ${LDL}

mlxconfig_mstconfig_DEPENDENCIES = \
    mlxconfig/libmlxcfg.la \
    mlxfwops/lib/libmlxfwops.a \
    pldmlib/libpldm.la \
    libmfa/libmfa.la \
    ext_libs/minixz/libminixz.la \
    mflash/libmflash.la \
    mft_utils/libmftutils.la \
    cmdif/libcmdif.la \
    reg_access/libreg_access.la \
    tools_layouts/libtools_layouts.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    dev_mgt/libdev_mgt.la \
    fw_comps_mgr/libfw_comps_mgr.la \
    tools_res_mgmt/libtools_res_mgmt.la \
    common/libcommon.la \
    $(MUPARSER_LIBS) \
    $(SQLITE_LIBS)

mlxconfig_mstconfig_LDADD = $(mlxconfig_mstconfig_DEPENDENCIES) ${LDL}

mlxconfig_mstconfig_LDFLAGS = -static

if DISABLE_XML2
MLXCONFIG_CXXFLAGS += -DDISABLE_XML2
else
MLXCONFIG_CPPFLAGS += $(libxml2_CFLAGS)
mlxconfig_mstconfig_LDADD += $(libxml2_LIBS)
mlxconfig_libmlxcfg_la_LIBADD += $(libxml2_LIBS)
endif

# The libraries appended to the link lines below come after the explicit
# _DEPENDENCIES lists above, so they are named as prerequisites here as well.
EXTRA_mlxconfig_mstconfig_DEPENDENCIES =
EXTRA_mlxconfig_libmlxcfg_la_DEPENDENCIES =

if ENABLE_INBAND
mlxconfig_mstconfig_LDADD += mad_ifc/libmad_ifc.la
mlxconfig_libmlxcfg_la_LIBADD += mad_ifc/libmad_ifc.la
EXTRA_mlxconfig_mstconfig_DEPENDENCIES += mad_ifc/libmad_ifc.la
EXTRA_mlxconfig_libmlxcfg_la_DEPENDENCIES += mad_ifc/libmad_ifc.la
else
endif

if ENABLE_OPENSSL
MLXCONFIG_CPPFLAGS += $(openssl_CFLAGS)
mlxconfig_mstconfig_DEPENDENCIES += tools_crypto/libtools_crypto.a
mlxconfig_mstconfig_LDADD += mlxsign_lib/libmlxsign.la $(openssl_LIBS)
mlxconfig_libmlxcfg_la_LIBADD += mlxsign_lib/libmlxsign.la $(openssl_LIBS)
EXTRA_mlxconfig_mstconfig_DEPENDENCIES += mlxsign_lib/libmlxsign.la
EXTRA_mlxconfig_libmlxcfg_la_DEPENDENCIES += mlxsign_lib/libmlxsign.la
else
MLXCONFIG_CXXFLAGS += -DNO_OPEN_SSL
endif

if ENABLE_DPA
mlxconfig_mstconfig_DEPENDENCIES += mlxdpa/libmstdpa.a
endif

mlxconfig_mstconfig_SOURCES = mlxconfig/mlxcfg_ui.h mlxconfig/mlxcfg_parser.cpp mlxconfig/mlxcfg_ui.cpp

# get mst device examples and tool name from makefile
MLXCONFIG_CXXFLAGS += -DMLXCFG_NAME=\"mstconfig\"
MLXCONFIG_CXXFLAGS += -DMST_DEV_EXAMPLE=\"04:00.0\" -DMST_DEV_EXAMPLE2=\"05:00.0\"

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxconfig_mstconfig_CPPFLAGS = $(MLXCONFIG_CPPFLAGS)
mlxconfig_mstconfig_CXXFLAGS = $(MLXCONFIG_CXXFLAGS)
mlxconfig_libmlxcfg_la_CPPFLAGS = $(MLXCONFIG_CPPFLAGS)
mlxconfig_libmlxcfg_la_CXXFLAGS = $(MLXCONFIG_CXXFLAGS)

########### mlxconfig/mlxconfig_dbs ###########
mlxconfig_mlxconfig_dbs_docdir = $(pkgdatadir)/mlxconfig_dbs
dist_mlxconfig_mlxconfig_dbs_doc_DATA = mlxconfig/mlxconfig_dbs/mlxconfig_host.db mlxconfig/mlxconfig_dbs/mlxconfig_switch.db

########### nvfwreset ###########
if ENABLE_NVFWRESET
NVFWRESET_CPPFLAGS = \
    -I$(top_builddir)/nvfwreset \
    -I$(top_srcdir)/nvfwreset \
    -I$(top_builddir) \
    -I$(top_srcdir)/nvfwreset \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/mft_core/mft_core_utils \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/cmdparser \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/reg_access \
    -I$(top_srcdir)/pci_library

NVFWRESET_CXXFLAGS = -Wall -W -DMST_UL -g -MP -MD -pipe

bin_PROGRAMS += nvfwreset/nvfwreset

nvfwreset_nvfwreset_SOURCES = \
    nvfwreset/CommonResetPlatform.cpp \
    nvfwreset/CommonResetPlatform.h \
    nvfwreset/DeviceTypeDetector.cpp \
    nvfwreset/DeviceTypeDetector.h \
    nvfwreset/DeviceTypeDetectorDefs.h \
    nvfwreset/HotResetManager.cpp \
    nvfwreset/HotResetManager.h \
    nvfwreset/LinuxResetPlatform.cpp \
    nvfwreset/LinuxResetPlatform.h \
    nvfwreset/NVFWresetMain.cpp \
    nvfwreset/NVFWresetParams.cpp \
    nvfwreset/NVFWresetParams.h \
    nvfwreset/NVFWresetParser.cpp \
    nvfwreset/NVFWresetParser.h \
    nvfwreset/ResetDeviceCapabilities.cpp \
    nvfwreset/ResetDeviceCapabilities.h \
    nvfwreset/ResetFlowExecutor.cpp \
    nvfwreset/ResetFlowExecutor.h \
    nvfwreset/ResetParameterChooser.cpp \
    nvfwreset/ResetParameterChooser.h \
    nvfwreset/ResetParameterDefs.h \
    nvfwreset/ResetPlatformInterface.cpp \
    nvfwreset/ResetPlatformInterface.h

nvfwreset_nvfwreset_DEPENDENCIES = \
    cmdparser/libcmdparser.a \
    mft_utils/libmftutils.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    dev_mgt/libdev_mgt.la \
    pci_library/libpci_library.la \
    reg_access/libreg_access.la \
    common/libcommon.la \
    mft_core/mft_core_utils/logger/liblogger.la \
    mft_core/mft_core_utils/mft_exceptions/libmftexceptions.la \
    mft_core/mft_core_utils/operating_system_api/lib_os_api.la

nvfwreset_nvfwreset_LDADD = $(nvfwreset_nvfwreset_DEPENDENCIES) ${LDL}

nvfwreset_nvfwreset_LDFLAGS = -static

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
nvfwreset_nvfwreset_CPPFLAGS = $(NVFWRESET_CPPFLAGS)
nvfwreset_nvfwreset_CXXFLAGS = $(NVFWRESET_CXXFLAGS)
endif

########### mlxarchive ###########
if ENABLE_FWMGR
MLXARCHIVE_CPPFLAGS = \
    -I$(top_builddir)/mlxarchive \
    -I$(top_srcdir)/mlxarchive \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxarchive \
    -I$(top_srcdir) \
    -I$(top_srcdir)/libmfa \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxfwops/lib \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/tools_layouts

MLXARCHIVE_CPPFLAGS += $(JSON_CFLAGS)

noinst_LTLIBRARIES += mlxarchive/libmstarchive.la

mlxarchive_libmstarchive_la_SOURCES = \
    mlxarchive/mlxarchive_mfa2_utils.h \
    mlxarchive/mlxarchive_mfa2_utils.cpp \
    mlxarchive/mlxarchive_mfa2_common_header.h \
    mlxarchive/mlxarchive_mfa2_common_header.cpp \
    mlxarchive/mlxarchive_mfa2_element.h \
    mlxarchive/mlxarchive_mfa2_element.cpp \
    mlxarchive/mlxarchive_mfa2_extension.h \
    mlxarchive/mlxarchive_mfa2_extension.cpp \
    mlxarchive/mlxarchive_mfa2_descriptor.h \
    mlxarchive/mlxarchive_mfa2_descriptor.cpp \
    mlxarchive/mlxarchive_mfa2_component.h \
    mlxarchive/mlxarchive_mfa2.h \
    mlxarchive/mlxarchive_mfa2.cpp \
    mlxarchive/mlxarchive_mfa2_builder.h \
    mlxarchive/mlxarchive_mfa2_builder.cpp \
    mlxarchive/mlxarchive_mfa2_package_gen.h \
    mlxarchive/mlxarchive_mfa2_package_gen.cpp \
    mlxarchive/mfa2_buff.h \
    mlxarchive/mfa2_buff.cpp

MLXARCHIVE_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

bin_PROGRAMS += mlxarchive/mstarchive

mlxarchive_mstarchive_SOURCES = mlxarchive/mlxarchive.cpp mlxarchive/mlxarchive.h

mlxarchive_mstarchive_CXXFLAGS =

mlxarchive_mstarchive_LDADD = \
    mlxarchive/libmstarchive.la \
    mlxfwops/lib/libmlxfwops.a \
    pldmlib/libpldm.la \
    libmfa/libmfa.la \
    fw_comps_mgr/libfw_comps_mgr.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    mflash/libmflash.la \
    tools_res_mgmt/libtools_res_mgmt.la \
    dev_mgt/libdev_mgt.la \
    cmdif/libcmdif.la \
    mft_utils/libmftutils.la \
    $(JSON_LIBS) \
    cmdparser/libcmdparser.a \
    reg_access/libreg_access.la \
    tools_layouts/libmlxarchive_layouts.la \
    tools_layouts/libtools_layouts.la \
    xz_utils/libxz_utils.la \
    ext_libs/minixz/libminixz.la \
    xz_utils/libxz_utils.la \
    common/libcommon.la \
    $(libcurl_LIBS) \
    $(liblzma_LIBS) \
    -lm \
    ${LDL}

mlxarchive_mstarchive_LDFLAGS = -static

if ENABLE_OPENSSL
mlxarchive_mstarchive_LDADD += mlxsign_lib/libmlxsign.la $(openssl_LIBS)
endif

if ENABLE_CS
mlxarchive_mstarchive_LDADD += tools_crypto/libtools_crypto.a $(openssl_LIBS)
endif

if ENABLE_INBAND
mlxarchive_mstarchive_LDADD += mad_ifc/libmad_ifc.la
endif

if ENABLE_DPA
mlxarchive_mstarchive_CXXFLAGS += -DENABLE_DPA
mlxarchive_mstarchive_LDADD += mlxdpa/libmstdpa.a
endif

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxarchive_libmstarchive_la_CPPFLAGS = $(MLXARCHIVE_CPPFLAGS)
mlxarchive_libmstarchive_la_CXXFLAGS = $(MLXARCHIVE_CXXFLAGS)
mlxarchive_mstarchive_CPPFLAGS = $(MLXARCHIVE_CPPFLAGS)
endif

########### mlxfwupdate ###########
if ENABLE_FWMGR
mlxfwupdate_docdir = $(INSTALL_BASEDIR)/etc/mstflint
dist_mlxfwupdate_doc_DATA = mlxfwupdate/certificate/ca-bundle.crt

MLXFWUPDATE_CPPFLAGS = \
    -I$(top_builddir)/mlxfwupdate \
    -I$(top_srcdir)/mlxfwupdate \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxfwupdate \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/cmdparser \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/libmfa \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxarchive \
    -I$(top_srcdir)/mlxfwops/lib \
    -I$(top_srcdir)/pldmlib \
    $(libxml2_CFLAGS) \
    $(libcurl_CFLAGS) \
    $(openssl_CFLAGS)

bin_PROGRAMS += mlxfwupdate/mstfwmanager

mlxfwupdate_mstfwmanager_CXXFLAGS = -g -MP -MD -Wall -W -DMSTFLINT $(INIPARSER_CFLAGS) $(JSON_CFLAGS)
mlxfwupdate_mstfwmanager_CXXFLAGS += -DUSE_XML -DLIBXML_STATIC
mlxfwupdate_mstfwmanager_CXXFLAGS += -DUSE_CURL -DCURL_STATICLIB

mlxfwupdate_mstfwmanager_SOURCES = \
    mlxfwupdate/cmd_line_params.cpp \
    mlxfwupdate/cmd_line_params.h \
    mlxfwupdate/cmd_line_parser.cpp \
    mlxfwupdate/cmd_line_parser.h \
    mlxfwupdate/err_msgs.h \
    mlxfwupdate/fw_version_old_clp.cpp \
    mlxfwupdate/fw_version_old_clp.h \
    mlxfwupdate/fw_version_with_sub_build.cpp \
    mlxfwupdate/fw_version_with_sub_build.h \
    mlxfwupdate/image_access.cpp \
    mlxfwupdate/image_access.h \
    mlxfwupdate/img_version.cpp \
    mlxfwupdate/img_version.h \
    mlxfwupdate/menu.cpp \
    mlxfwupdate/menu.h \
    mlxfwupdate/mlnx_dev.cpp \
    mlxfwupdate/mlnx_dev.h \
    mlxfwupdate/mlxfwmanager.cpp \
    mlxfwupdate/mlxfwmanager.h \
    mlxfwupdate/mlxfwmanager_common.cpp \
    mlxfwupdate/mlxfwmanager_common.h \
    mlxfwupdate/output_fmts.cpp \
    mlxfwupdate/output_fmts.h \
    mlxfwupdate/psid_lookup_db.cpp \
    mlxfwupdate/psid_lookup_db.h \
    mlxfwupdate/psid_query_item.cpp \
    mlxfwupdate/psid_query_item.h \
    mlxfwupdate/server_request.cpp \
    mlxfwupdate/server_request.h

mlxfwupdate_mstfwmanager_DEPENDENCIES = \
    dev_mgt/libdev_mgt.la \
    mvpd/libmvpd.la \
    mlxfwops/lib/libmlxfwops.a \
    pldmlib/libpldm.la \
    mlxconfig/libmlxcfg.la \
    mlxarchive/libmstarchive.la \
    libmfa/libmfa.la \
    ext_libs/minixz/libminixz.la \
    cmdparser/libcmdparser.a \
    mflash/libmflash.la \
    tools_res_mgmt/libtools_res_mgmt.la \
    mft_utils/libmftutils.la \
    cmdif/libcmdif.la \
    reg_access/libreg_access.la \
    tools_layouts/libmlxarchive_layouts.la \
    tools_layouts/libtools_layouts.la \
    xz_utils/libxz_utils.la \
    fw_comps_mgr/libfw_comps_mgr.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    common/libcommon.la \
    $(INIPARSER_LIBS) \
    $(MUPARSER_LIBS) \
    $(SQLITE_LIBS)

LDADD_mstfwmanager = $(libcurl_LIBS) $(libz_LIBS) $(liblzma_LIBS) $(libxml2_LIBS)

if ENABLE_OPENSSL
mlxfwupdate_mstfwmanager_DEPENDENCIES += mlxsign_lib/libmlxsign.la
LDADD_mstfwmanager += $(openssl_LIBS)
endif

if ENABLE_CS
mlxfwupdate_mstfwmanager_DEPENDENCIES += tools_crypto/libtools_crypto.a
LDADD_mstfwmanager += $(openssl_LIBS)
endif

if ENABLE_INBAND
mlxfwupdate_mstfwmanager_DEPENDENCIES += mad_ifc/libmad_ifc.la
endif

if ENABLE_DPA
mlxfwupdate_mstfwmanager_CXXFLAGS += -DENABLE_DPA
mlxfwupdate_mstfwmanager_DEPENDENCIES += mlxdpa/libmstdpa.a
endif

mlxfwupdate_mstfwmanager_LDADD = $(mlxfwupdate_mstfwmanager_DEPENDENCIES) $(JSON_LIBS) $(LDADD_mstfwmanager)
mlxfwupdate_mstfwmanager_LDFLAGS = -static

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxfwupdate_mstfwmanager_CPPFLAGS = $(MLXFWUPDATE_CPPFLAGS)
endif

########### pldmgen ###########
if ENABLE_PLDM_PKG_GEN
PLDMGEN_CPPFLAGS = \
    -I$(top_builddir)/pldmgen \
    -I$(top_srcdir)/pldmgen \
    -I$(top_builddir) \
    -I$(top_srcdir)/pldmgen \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxfwops/lib \
    -I$(top_srcdir)/cmdparser \
    -I$(top_srcdir)/pldm_utils \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/tools_layouts

PLDMGEN_CPPFLAGS += $(JSON_CFLAGS)

PLDMGEN_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES += pldmgen/libpldmgen.la

pldmgen_libpldmgen_la_SOURCES = \
    pldmgen/pldm.h \
    pldmgen/pldm.cpp \
    pldmgen/pldm_arg_parser.h \
    pldmgen/pldm_arg_parser.cpp \
    pldmgen/pldm_component.h \
    pldmgen/pldm_component.cpp \
    pldmgen/pldm_descriptor.h \
    pldmgen/pldm_descriptor.cpp \
    pldmgen/pldm_devicerecord.h \
    pldmgen/pldm_devicerecord.cpp \
    pldmgen/pldm_params.h \
    pldmgen/pldm_params.cpp \
    pldmgen/pldm_time.h \
    pldmgen/pldm_time.cpp

bin_PROGRAMS += pldmgen/mstpldm_pkg_gen

pldmgen_mstpldm_pkg_gen_SOURCES = pldmgen/pldmgen.cpp

pldmgen_mstpldm_pkg_gen_CXXFLAGS =

pldmgen_mstpldm_pkg_gen_LDADD = \
    pldmgen/libpldmgen.la \
    mlxfwops/lib/libmlxfwops.a \
    pldmlib/libpldm.la \
    pldm_utils/libpldm_utils.la \
    libmfa/libmfa.la \
    fw_comps_mgr/libfw_comps_mgr.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    mflash/libmflash.la \
    tools_res_mgmt/libtools_res_mgmt.la \
    dev_mgt/libdev_mgt.la \
    cmdif/libcmdif.la \
    mft_utils/libmftutils.la \
    $(JSON_LIBS) \
    cmdparser/libcmdparser.a \
    reg_access/libreg_access.la \
    tools_layouts/libtools_layouts.la \
    xz_utils/libxz_utils.la \
    ext_libs/minixz/libminixz.la \
    common/libcommon.la \
    $(libcurl_LIBS) \
    $(liblzma_LIBS) \
    -lm \
    ${LDL}

pldmgen_mstpldm_pkg_gen_LDFLAGS = -static

if ENABLE_OPENSSL
pldmgen_mstpldm_pkg_gen_LDADD += mlxsign_lib/libmlxsign.la $(openssl_LIBS)
endif

if ENABLE_CS
pldmgen_mstpldm_pkg_gen_LDADD += tools_crypto/libtools_crypto.a $(openssl_LIBS)
endif

if ENABLE_INBAND
pldmgen_mstpldm_pkg_gen_LDADD += mad_ifc/libmad_ifc.la
endif

if ENABLE_DPA
pldmgen_mstpldm_pkg_gen_CXXFLAGS += -DENABLE_DPA
pldmgen_mstpldm_pkg_gen_LDADD += mlxdpa/libmstdpa.a
endif

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
pldmgen_libpldmgen_la_CPPFLAGS = $(PLDMGEN_CPPFLAGS)
pldmgen_libpldmgen_la_CXXFLAGS = $(PLDMGEN_CXXFLAGS)
pldmgen_mstpldm_pkg_gen_CPPFLAGS = $(PLDMGEN_CPPFLAGS)
endif

########### mlxtokengenerator ###########
MLXTOKENGENERATOR_CPPFLAGS = \
    -I$(top_builddir)/mlxtokengenerator \
    -I$(top_srcdir)/mlxtokengenerator \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxtokengenerator \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mft_core/mft_core_utils \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/cmdif \
    -I$(top_srcdir)/tools_res_mgmt \
    $(libxml2_CFLAGS) \
    $(openssl_CFLAGS)

MLXTOKENGENERATOR_CPPFLAGS += $(MUPARSER_CFLAGS) $(SQLITE_CFLAGS) $(COMPILER_FPIC)

MLXTOKENGENERATOR_CXXFLAGS = -pthread -Wall -W -g -MP -MD -pipe $(JSON_CFLAGS) -Wno-deprecated-declarations $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"

bin_PROGRAMS += mlxtokengenerator/msttokengenerator

mlxtokengenerator_msttokengenerator_SOURCES = \
    mlxtokengenerator/mlxtkngenerator_utils.h \
    mlxtokengenerator/mlxtkngenerator_utils.cpp \
    mlxtokengenerator/mlxtoken.h \
    mlxtokengenerator/mlxtoken.cpp \
    mlxtokengenerator/mlxtkngenerator.h \
    mlxtokengenerator/mlxtkngenerator.cpp

mlxtokengenerator_msttokengenerator_DEPENDENCIES = \
    mlxconfig/libmlxcfg.la \
    mlxfwops/lib/libmlxfwops.a \
    pldmlib/libpldm.la \
    mflash/libmflash.la \
    cmdparser/libcmdparser.a \
    tools_layouts/libtools_layouts.la \
    mft_utils/libmftutils.la \
    mft_core/mft_core_utils/nvtoolslogger/libnvtoolslogger.la \
    mft_core/mft_core_utils/operating_system_api/lib_os_api.la \
    libmfa/libmfa.la \
    cmdif/libcmdif.la \
    dev_mgt/libdev_mgt.la \
    fw_comps_mgr/libfw_comps_mgr.la \
    $(SQLITE_LIBS) \
    ${MTCR_CONF_DIR}/libmtcr_ul.la

if ENABLE_DPA
mlxtokengenerator_msttokengenerator_DEPENDENCIES += mlxdpa/libmstdpa.a
endif

mlxtokengenerator_msttokengenerator_LDFLAGS = -static

if ENABLE_OPENSSL
else
MLXTOKENGENERATOR_CXXFLAGS += -DNO_OPEN_SSL
endif

if ENABLE_FWMGR
mlxtokengenerator_msttokengenerator_DEPENDENCIES += ext_libs/minixz/libminixz.la
endif

mlxtokengenerator_msttokengenerator_LDADD = $(mlxtokengenerator_msttokengenerator_DEPENDENCIES) $(JSON_LIBS) ${LDL}

if DISABLE_XML2
MLXTOKENGENERATOR_CXXFLAGS += -DDISABLE_XML2
else
mlxtokengenerator_msttokengenerator_LDADD += -lxml2
endif

if ENABLE_CS
MLXTOKENGENERATOR_CPPFLAGS += $(openssl_CFLAGS)
mlxtokengenerator_msttokengenerator_LDADD += $(openssl_LIBS)
mlxtokengenerator_msttokengenerator_DEPENDENCIES += tools_crypto/libtools_crypto.a
else
endif

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxtokengenerator_msttokengenerator_CPPFLAGS = $(MLXTOKENGENERATOR_CPPFLAGS)
mlxtokengenerator_msttokengenerator_CXXFLAGS = $(MLXTOKENGENERATOR_CXXFLAGS)

########### flint ###########
FLINT_CPPFLAGS = \
    -I$(top_builddir)/flint \
    -I$(top_srcdir)/flint \
    -I$(top_builddir) \
    -I$(top_srcdir)/flint \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/tools_layouts \
    $(JSON_CFLAGS)

bin_PROGRAMS += flint/mstflint

flint_mstflint_SOURCES = \
    flint/cmd_line_parser.cpp \
    flint/err_msgs.h \
    flint/flint.cpp \
    flint/flint.h \
    flint/flint_params.cpp \
    flint/flint_params.h \
    flint/subcommands.cpp \
    flint/subcommands.h \
    flint/subcommands_linkx.cpp

flint_mstflint_CXXFLAGS = \
    -Wall \
    -pthread \
    -W \
    -g \
    -MP \
    -MD \
    -pipe \
    -DEXTERNAL \
    $(COMPILER_FPIC) \
    -DUNIX \
    -DOS_UNIX \
    -DOS_LINUX

flint_mstflint_DEPENDENCIES =

if ENABLE_CABLES
flint_mstflint_DEPENDENCIES += ${CABLE_ACCESS_DIR}/libcable_access.la
endif

flint_mstflint_DEPENDENCIES += \
    mlxfwops/lib/libmlxfwops.a \
    pldmlib/libpldm.la \
    cmdparser/libcmdparser.a \
    mflash/libmflash.la \
    tools_res_mgmt/libtools_res_mgmt.la \
    cmdif/libcmdif.la \
    dev_mgt/libdev_mgt.la \
    tools_layouts/libtools_layouts.la \
    fw_comps_mgr/libfw_comps_mgr.la \
    mft_utils/libmftutils.la \
    reg_access/libreg_access.la \
    ${MTCR_CONF_DIR}/.libs/libmtcr_ul.a

LDADD_mstflint = ${LDL} $(JSON_LIBS)

flint_mstflint_LDFLAGS = -static

if ENABLE_DC
FLINT_CPPFLAGS += $(libz_CFLAGS)
LDADD_mstflint += $(libz_LIBS)
else
flint_mstflint_CXXFLAGS += -DNO_ZLIB
endif

if ENABLE_CS
FLINT_CPPFLAGS += $(openssl_CFLAGS)
LDADD_mstflint += $(openssl_LIBS)
flint_mstflint_DEPENDENCIES += tools_crypto/libtools_crypto.a
else
endif

if ENABLE_INBAND
flint_mstflint_DEPENDENCIES += mad_ifc/libmad_ifc.la
else
endif

if ENABLE_OPENSSL
FLINT_CPPFLAGS += $(openssl_CFLAGS)
LDADD_mstflint += $(openssl_LIBS)
flint_mstflint_DEPENDENCIES += mlxsign_lib/libmlxsign.la
else
flint_mstflint_CXXFLAGS += -DNO_OPEN_SSL
endif

if ENABLE_FWMGR
FLINT_CPPFLAGS += $(liblzma_CFLAGS)
LDADD_mstflint += $(liblzma_LIBS) -lm
flint_mstflint_DEPENDENCIES += \
    libmfa/libmfa.la \
    ext_libs/minixz/libminixz.la \
    mlxarchive/libmstarchive.la \
    tools_layouts/libmlxarchive_layouts.la \
    xz_utils/libxz_utils.la
else
flint_mstflint_CXXFLAGS += -DNO_MSTARCHIVE
endif

if ENABLE_DPA
flint_mstflint_CXXFLAGS += -DENABLE_DPA
flint_mstflint_DEPENDENCIES += mlxdpa/libmstdpa.a
endif

flint_mstflint_LDADD = $(flint_mstflint_DEPENDENCIES) $(LDADD_mstflint)

# get mst device examples and tool name from makefile
flint_mstflint_CXXFLAGS += -DFLINT_NAME=\"mstflint\" -DFLINT_DISPLAY_NAME=\"MstFlint\"
flint_mstflint_CXXFLAGS += -DMST_DEV_EXAMPLE1=\"03:00.0\" -DMST_DEV_EXAMPLE2=\"mlx4_0\" -DMST_DEV_EXAMPLE3=\"03:00.0\" -DMST_DEV_EXAMPLE4=\"04:00.0\"

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
flint_mstflint_CPPFLAGS = $(FLINT_CPPFLAGS)

########### small_utils ###########

SMALL_UTILS_CPPFLAGS = \
    -I$(top_builddir)/small_utils \
    -I$(top_srcdir)/small_utils \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/mvpd \
    -I$(top_srcdir)/dev_mgt \
    $(COMPILER_FPIC)

bin_PROGRAMS += \
    small_utils/mstmread \
    small_utils/mstmwrite \
    small_utils/mstmcra \
    small_utils/mstmtserver \
    small_utils/mstvpd \
    small_utils/mstcongestion \
    small_utils/mstmget_temp

bin_SCRIPTS += small_utils/mstfwreset

small_utils_mstmread_SOURCES = small_utils/mread.c
small_utils_mstmread_DEPENDENCIES = ${MTCR_CONF_DIR}/libmtcr_ul.la
small_utils_mstmread_LDADD = $(small_utils_mstmread_DEPENDENCIES) ${LDL}
small_utils_mstmread_LDFLAGS = -static

small_utils_mstmwrite_SOURCES = small_utils/mwrite.c
small_utils_mstmwrite_DEPENDENCIES = ${MTCR_CONF_DIR}/libmtcr_ul.la
small_utils_mstmwrite_LDADD = $(small_utils_mstmwrite_DEPENDENCIES) ${LDL}
small_utils_mstmwrite_LDFLAGS = -static

small_utils_mstvpd_SOURCES = small_utils/vpd.c
small_utils_mstvpd_DEPENDENCIES = \
    mvpd/libmvpd.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la \
    tools_layouts/libtools_layouts.la
small_utils_mstvpd_LDADD = $(small_utils_mstvpd_DEPENDENCIES) ${LDL}
small_utils_mstvpd_LDFLAGS = -static

small_utils_mstcongestion_SOURCES = small_utils/congestion.cpp
small_utils_mstcongestion_DEPENDENCIES = \
    cmdif/libcmdif.la \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la \
    tools_layouts/libtools_layouts.la \
    cmdparser/libcmdparser.a \
    ${MTCR_CONF_DIR}/libmtcr_ul.la
small_utils_mstcongestion_LDADD = $(small_utils_mstcongestion_DEPENDENCIES) ${LDL}
small_utils_mstcongestion_LDFLAGS = -static

small_utils_mstmcra_SOURCES = small_utils/mcra.c
small_utils_mstmcra_DEPENDENCIES = ${MTCR_CONF_DIR}/libmtcr_ul.la
small_utils_mstmcra_LDADD = $(small_utils_mstmcra_DEPENDENCIES) ${LDL}
small_utils_mstmcra_LDFLAGS = -static

if LINUX_BUILD
bin_PROGRAMS += small_utils/mstfwctrl

small_utils_mstfwctrl_SOURCES = small_utils/mstfwctrl.c
small_utils_mstfwctrl_DEPENDENCIES = \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la
small_utils_mstfwctrl_LDADD = $(small_utils_mstfwctrl_DEPENDENCIES) ${LDL}
small_utils_mstfwctrl_LDFLAGS = -static
endif

small_utils_mstmtserver_SOURCES = small_utils/mtserver.c small_utils/tcp.c small_utils/tcp.h
small_utils_mstmtserver_CFLAGS = -DMST_UL
small_utils_mstmtserver_DEPENDENCIES = ${MTCR_CONF_DIR}/libmtcr_ul.la
small_utils_mstmtserver_LDADD = $(small_utils_mstmtserver_DEPENDENCIES) ${LDL}
small_utils_mstmtserver_LDFLAGS = -static

small_utils/mstfwreset: common/python_wrapper
	@$(MKDIR_P) $(@D)
	cp common/python_wrapper $@
mstfwresetlibdir = $(libdir)/mstflint/python_tools/mstfwreset

mlxpcilibdir = $(libdir)/mstflint/python_tools/mlxpci
mlxpcilib_DATA = small_utils/binary_file.py small_utils/mlxpci_lib.py

mstfwresetlib_DATA = small_utils/mstfwreset.py

# The mget_temp reading, shared by the CLI and the SDK so the two cannot disagree
# about a device.
noinst_LTLIBRARIES += small_utils/libmgettemp.la
small_utils_libmgettemp_la_SOURCES = small_utils/mget_temp_lib.c small_utils/mget_temp_lib.h small_utils/mget_temp_sensors.h

# (bin_PROGRAMS: duplicate entry dropped)

small_utils_mstmget_temp_SOURCES = small_utils/mget_temp.c small_utils/mget_temp.h
small_utils_mstmget_temp_DEPENDENCIES = \
    small_utils/libmgettemp.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la \
    tools_layouts/libtools_layouts.la
small_utils_mstmget_temp_LDADD = $(small_utils_mstmget_temp_DEPENDENCIES) ${LDL}
small_utils_mstmget_temp_LDFLAGS = -static

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
small_utils_mstmread_CPPFLAGS = $(SMALL_UTILS_CPPFLAGS)
small_utils_mstmwrite_CPPFLAGS = $(SMALL_UTILS_CPPFLAGS)
small_utils_mstmcra_CPPFLAGS = $(SMALL_UTILS_CPPFLAGS)
small_utils_mstmtserver_CPPFLAGS = $(SMALL_UTILS_CPPFLAGS)
small_utils_mstvpd_CPPFLAGS = $(SMALL_UTILS_CPPFLAGS)
small_utils_mstcongestion_CPPFLAGS = $(SMALL_UTILS_CPPFLAGS)
small_utils_mstmget_temp_CPPFLAGS = $(SMALL_UTILS_CPPFLAGS)
small_utils_mstfwctrl_CPPFLAGS = $(SMALL_UTILS_CPPFLAGS)
small_utils_libmgettemp_la_CPPFLAGS = $(SMALL_UTILS_CPPFLAGS)

########### small_utils/mlxfwresetlib ###########
small_utils_mlxfwresetlib_docdir = $(libdir)/mstflint/python_tools/mstfwreset/mlxfwresetlib
dist_small_utils_mlxfwresetlib_doc_DATA = small_utils/mlxfwresetlib/__init__.py small_utils/mlxfwresetlib/mlxfwreset_mlnxdriver.py small_utils/mlxfwresetlib/mlxfwreset_status_checker.py small_utils/mlxfwresetlib/mlxfwreset_utils.py small_utils/mlxfwresetlib/logger.py small_utils/mlxfwresetlib/mcra.py small_utils/mlxfwresetlib/mlnx_peripheral_components.py small_utils/mlxfwresetlib/pci_device.py small_utils/mlxfwresetlib/cmd_reg_mfrl.py small_utils/mlxfwresetlib/drivers_safety_check.py small_utils/mlxfwresetlib/cmd_reg_mroq.py small_utils/mlxfwresetlib/cmd_reg_mpcir.py small_utils/mlxfwresetlib/cmd_reg_mcam.py small_utils/mlxfwresetlib/cmd_reg_mrsi.py small_utils/mlxfwresetlib/hot_reset.py

########### mst_utils ###########
MST_UTILS_CPPFLAGS = \
    -I$(top_builddir)/mst_utils \
    -I$(top_srcdir)/mst_utils \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/dev_mgt \
    $(COMPILER_FPIC)

bin_PROGRAMS += mst_utils/mstdevices_info

mst_utils_mstdevices_info_SOURCES = mst_utils/mdevices_info.c
mst_utils_mstdevices_info_DEPENDENCIES = \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la
mst_utils_mstdevices_info_LDADD = $(mst_utils_mstdevices_info_DEPENDENCIES) ${LDL}
mst_utils_mstdevices_info_LDFLAGS = -static

# jsoncpp is resolved at the END of the link line. libmtcr_ul.a and
# libmst_http_client.a are mutually dependent (mtcr_remote.c calls the client;
# the client needs Json), and ld makes a single pass over each archive, so the
# Json objects carried inside libmtcr_ul are already behind it by the time the
# client's undefined Json symbols show up. Listing jsoncpp last closes that gap.
if USE_LOCAL_JSON
MST_UTILS_MST_JSON_LIBS = ext_libs/json/libjson.la
else
MST_UTILS_MST_JSON_LIBS = -ljsoncpp
endif

# Registers/unregisters devices served by a remote mstserver. Only built
# with --enable-remote, since it drives the MST HTTP client directly and there
# is nothing to register without the mtcr remote path.
if ENABLE_MTCR_REMOTE
# mstremote belongs to the remote feature, which configure already refuses to
# enable without a C++17 compiler - so C++17 is always available here. Raised
# with the rest of the feature rather than held at the tree standard.
#
# It has to be CXXFLAGS: automake emits $(CXXFLAGS) after every per-target
# _CXXFLAGS, so a -std in mstremote_CXXFLAGS would lose to the tree's C++14.
# The append is inside this conditional so a build without --enable-remote
# leaves the directory at the tree standard.

bin_PROGRAMS += mst_utils/mstremote

mst_utils_mstremote_SOURCES = mst_utils/mstremote.cpp
mst_utils_mstremote_CPPFLAGS = $(MST_UTILS_CPPFLAGS) -I$(top_srcdir)/${MTCR_CONF_DIR}
mst_utils_mstremote_CXXFLAGS = $(COMPILER_FPIC)
mst_utils_mstremote_DEPENDENCIES = \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    mst_server/client/libmst_http_client.la \
    cmdparser/libcmdparser.a
# openssl and libcurl come in through libmst_http_client, which speaks TLS.
# mstremote itself no longer computes anything: the passphrase goes to the
# server over the encrypted channel and is checked there against a salted
# verifier.
mst_utils_mstremote_LDADD = $(mst_utils_mstremote_DEPENDENCIES) $(openssl_LIBS) $(mst_remote_curl_LIBS) $(FILESYSTEM_LIBS) ${LDL} -lstdc++ $(MST_UTILS_MST_JSON_LIBS)
mst_utils_mstremote_LDFLAGS = -static
endif

if ENABLE_CABLES
bin_PROGRAMS += mst_utils/mstcable_discovery
mst_utils_mstcable_discovery_SOURCES = mst_utils/cable_discovery.cpp
mst_utils_mstcable_discovery_DEPENDENCIES = \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la \
    mft_utils/libmftutils.la
mst_utils_mstcable_discovery_LDADD = $(mst_utils_mstcable_discovery_DEPENDENCIES) ${LDL}
mst_utils_mstcable_discovery_LDFLAGS = -static
endif

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mst_utils_mstdevices_info_CPPFLAGS = $(MST_UTILS_CPPFLAGS)
mst_utils_mstcable_discovery_CPPFLAGS = $(MST_UTILS_CPPFLAGS)
# The tree builds at -std=c++14 via CXXFLAGS, which automake puts last on the
# compile line; this directory needs C++17, so raise it for its objects only.
MST_UTILS_CXX17_OBJECTS = $(mst_utils_mstdevices_info_OBJECTS) $(mst_utils_mstremote_OBJECTS) $(mst_utils_mstcable_discovery_OBJECTS)
if ENABLE_MTCR_REMOTE
$(MST_UTILS_CXX17_OBJECTS): CXXFLAGS += $(CXX17_STD)
endif

########### mstdump/crd_lib ###########
MSTDUMP_CRD_LIB_CPPFLAGS = \
    -I$(top_builddir)/mstdump/crd_lib \
    -I$(top_srcdir)/mstdump/crd_lib \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/common \
    -I$(top_srcdir)/ext_libs/minixz \
    $(COMPILER_FPIC)
MSTDUMP_CRD_LIB_CFLAGS = -Wall -W -g -MP -MD -pipe -Wno-unused-function $(COMPILER_FPIC) -DMTCR_EXPORT -DMST_UL -DDATA_PATH=\"$(pkgdatadir)\" $(COMPILER_FPIC)

noinst_LIBRARIES += mstdump/crd_lib/libcrdump.a

mstdump_crd_lib_libcrdump_a_SOURCES = mstdump/crd_lib/crdump.c mstdump/crd_lib/crdump.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mstdump_crd_lib_libcrdump_a_CPPFLAGS = $(MSTDUMP_CRD_LIB_CPPFLAGS)
mstdump_crd_lib_libcrdump_a_CFLAGS = $(MSTDUMP_CRD_LIB_CFLAGS)

########### mstdump/crd_main ###########
MSTDUMP_CRD_MAIN_CPPFLAGS = \
    -I$(top_builddir)/mstdump/crd_main \
    -I$(top_srcdir)/mstdump/crd_main \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/mstdump/crd_lib \
    -I$(top_srcdir)/include/mtcr_ul \
    $(COMPILER_FPIC)
MSTDUMP_CRD_MAIN_CFLAGS = -MD -pipe -g -Wall -W $(COMPILER_FPIC)

bin_PROGRAMS += mstdump/crd_main/mstregdump

mstdump_crd_main_mstregdump_SOURCES = mstdump/crd_main/mstdump.c
mstdump_crd_main_mstregdump_LDADD = \
    mstdump/crd_lib/libcrdump.a \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la \
    tools_layouts/libtools_layouts.la \
    mft_utils/libmftutils.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    ext_libs/minixz/libminixz.la \
    -lm \
    ${LDL}
mstdump_crd_main_mstregdump_LDFLAGS = -static
mstdump_crd_main_mstregdump_CFLAGS = -DMSTDUMP_NAME=\"mstregdump\" -DDEV_EXAMPLE=\"0b:00.0\"

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mstdump_crd_main_mstregdump_CPPFLAGS = $(MSTDUMP_CRD_MAIN_CPPFLAGS)

########### mstdump/mstdump_dbs ###########
mstregdumpdir = $(datadir)/@PACKAGE@

# The .csv files stay the source of truth in the repo and are always distributed.
# Compressing them is best effort: the DBs have shipped as plain .csv for years,
# so any failure here falls back to that rather than breaking the build. crd_lib
# reads both forms and prefers a plain .csv placed next to them, so a DB can
# still be overridden in the field.
MSTDUMP_DBS_CSV = $(notdir $(wildcard $(srcdir)/mstdump/mstdump_dbs/*.csv))
MSTDUMP_DBS_XZ = $(MSTDUMP_DBS_CSV:%=mstdump/mstdump_dbs/%.xz)
EXTRA_DIST += $(MSTDUMP_DBS_CSV:%=mstdump/mstdump_dbs/%)
CLEANFILES += $(MSTDUMP_DBS_XZ) $(MSTDUMP_DBS_XZ:%=%.tmp)

if HAVE_XZ
all-local: $(MSTDUMP_DBS_XZ)

# Compress via a temp file so an interrupted or failing xz can never leave a
# partial .csv.xz behind - that would be newer than its .csv, count as up to date
# on the next make, and ship a DB the decoder cannot read. On any failure the
# target is removed and the plain .csv is installed instead.
# CRC32 is the only integrity check the in-tree XZ Embedded decoder accepts, and
# the default preset keeps the dictionary within the decoder's CRD_XZ_DICT_MAX.
mstdump/mstdump_dbs/%.csv.xz: $(srcdir)/mstdump/mstdump_dbs/%.csv
	@$(MKDIR_P) $(@D)
	-@if $(XZ) --check=crc32 -c $< > $@.tmp 2>/dev/null && test -s $@.tmp; then \
	    mv -f $@.tmp $@; \
	else \
	    rm -f $@.tmp $@; \
	    echo "  WARNING: $(XZ) failed for $<; installing it uncompressed"; \
	fi
endif

# Install the compressed form only where one was actually produced; everything
# else falls back to the plain .csv. This also covers the no-xz configuration,
# where no .csv.xz exists at all. These run as install-data and uninstall hooks:
# install-data-local is the SDK's ld.so snippet, which `make install-sdk' runs.
INSTALL_DATA_HOOKS += install-mstdump-dbs
UNINSTALL_HOOKS += uninstall-mstdump-dbs

install-mstdump-dbs:
	$(MKDIR_P) "$(DESTDIR)$(mstregdumpdir)"
	@for f in $(MSTDUMP_DBS_CSV); do \
	    if test -f "mstdump/mstdump_dbs/$$f.xz"; then \
	        echo " $(INSTALL_DATA) mstdump/mstdump_dbs/$$f.xz '$(DESTDIR)$(mstregdumpdir)'"; \
	        $(INSTALL_DATA) "mstdump/mstdump_dbs/$$f.xz" "$(DESTDIR)$(mstregdumpdir)/$$f.xz" || exit 1; \
	    else \
	        echo " $(INSTALL_DATA) $(srcdir)/mstdump/mstdump_dbs/$$f '$(DESTDIR)$(mstregdumpdir)'"; \
	        $(INSTALL_DATA) "$(srcdir)/mstdump/mstdump_dbs/$$f" "$(DESTDIR)$(mstregdumpdir)/$$f" || exit 1; \
	    fi; \
	done

uninstall-mstdump-dbs:
	@for f in $(MSTDUMP_DBS_CSV); do \
	    rm -f "$(DESTDIR)$(mstregdumpdir)/$$f" "$(DESTDIR)$(mstregdumpdir)/$$f.xz"; \
	done

.PHONY: install-mstdump-dbs uninstall-mstdump-dbs

########### efuse ###########

EFUSE_CPPFLAGS = \
    -I$(top_builddir)/efuse \
    -I$(top_srcdir)/efuse \
    -I$(top_builddir) \
    -I$(top_srcdir)/efuse \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_core/mft_core_utils \
    $(COMPILER_FPIC)

EFUSE_CPPFLAGS += $(JSON_CFLAGS)

EFUSE_CXXFLAGS = -Wall -W -DMST_UL -g -MP -MD -pipe -DDATA_PATH=\"$(pkgdatadir)/efuse\"

bin_PROGRAMS += efuse/mstefuse

efuse_mstefuse_SOURCES = efuse/efuse.cpp efuse/efuse.h efuse/efuse_config.cpp efuse/efuse_config.h

efuse_mstefuse_DEPENDENCIES = \
    cmdparser/libcmdparser.a \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la \
    tools_layouts/libtools_layouts.la \
    common/libcommon.la \
    mft_core/mft_core_utils/operating_system_api/lib_os_api.la \
    mft_core/mft_core_utils/mft_exceptions/libmftexceptions.la

efuse_mstefuse_LDADD = $(efuse_mstefuse_DEPENDENCIES) $(JSON_LIBS) -lm ${LDL}

efuse_mstefuse_LDFLAGS = -static

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
efuse_mstefuse_CPPFLAGS = $(EFUSE_CPPFLAGS)
efuse_mstefuse_CXXFLAGS = $(EFUSE_CXXFLAGS)

########### efuse/efuse_dbs ###########
mstefusedir = $(pkgdatadir)/efuse
dist_mstefuse_DATA = $(srcdir)/efuse/efuse_dbs/efuse_config.json

########### adb_parser ###########
if ADB_GENERIC_TOOLS_ENABLED
ADB_PARSER_CPPFLAGS = \
    -I$(top_builddir)/adb_parser \
    -I$(top_srcdir)/adb_parser \
    -I$(top_builddir) \
    -I$(top_srcdir)/adb_parser \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common

ADB_PARSER_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES += adb_parser/libadb_parser.la

adb_parser_libadb_parser_la_SOURCES = \
    adb_parser/adb_condVar.cpp \
    adb_parser/adb_condition.cpp \
    adb_parser/adb_config.cpp \
    adb_parser/adb_db.cpp \
    adb_parser/adb_exceptionHolder.cpp \
    adb_parser/adb_expr.cpp \
    adb_parser/adb_field.cpp \
    adb_parser/adb_instance.cpp \
    adb_parser/adb_logfile.cpp \
    adb_parser/adb_node.cpp \
    adb_parser/adb_parser.cpp \
    adb_parser/adb_xmlCreator.cpp \
    adb_parser/adb_xml_parser.cpp \
    adb_parser/buf_ops.cpp \
    adb_parser/expr.cpp

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
adb_parser_libadb_parser_la_CPPFLAGS = $(ADB_PARSER_CPPFLAGS)
adb_parser_libadb_parser_la_CXXFLAGS = $(ADB_PARSER_CXXFLAGS)
endif

########### mlxreg ###########
if ADB_GENERIC_TOOLS_ENABLED

MLXREG_CPPFLAGS = \
    -I$(top_builddir)/mlxreg \
    -I$(top_srcdir)/mlxreg \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxreg \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxreg

MLXREG_CXXFLAGS = -Wall -W -DMST_UL -g -MP -MD -pipe

mlxreg_mstreg_SOURCES = mlxreg/mlxreg_ui.cpp mlxreg/mlxreg_ui.h

bin_PROGRAMS += mlxreg/mstreg

mlxreg_mstreg_DEPENDENCIES = \
    mlxreg/mlxreg_lib/libmstreg_lib.la \
    cmdparser/libcmdparser.a \
    mft_utils/libmftutils.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    adb_parser/libadb_parser.la \
    cmdif/libcmdif.la \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la \
    tools_layouts/libtools_layouts.la \
    xz_utils/libxz_utils.la \
    ext_libs/minixz/libminixz.la \
    common/libcommon.la

mlxreg_mstreg_LDADD = $(mlxreg_mstreg_DEPENDENCIES) $(liblzma_LIBS) ${LDL} $(expat_LIBS)

mlxreg_mstreg_LDFLAGS = -static

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxreg_mstreg_CPPFLAGS = $(MLXREG_CPPFLAGS)
mlxreg_mstreg_CXXFLAGS = $(MLXREG_CXXFLAGS)
endif

########### mlxreg/mlxreg_lib ###########
if ADB_GENERIC_TOOLS_ENABLED
MLXREG_MLXREG_LIB_CPPFLAGS = \
    -I$(top_builddir)/mlxreg/mlxreg_lib \
    -I$(top_srcdir)/mlxreg/mlxreg_lib \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxreg/mlxreg_lib \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxreg

MLXREG_MLXREG_LIB_CXXFLAGS = -Wall -W -DMST_UL -g -MP -MD -pipe

noinst_LTLIBRARIES += mlxreg/mlxreg_lib/libmstreg_lib.la

mlxreg_mlxreg_lib_libmstreg_lib_la_SOURCES = \
    mlxreg/mlxreg_lib/mlxreg_exception.cpp \
    mlxreg/mlxreg_lib/mlxreg_exception.h \
    mlxreg/mlxreg_lib/mlxreg_lib.cpp \
    mlxreg/mlxreg_lib/mlxreg_lib.h \
    mlxreg/mlxreg_lib/mlxreg_parser.cpp \
    mlxreg/mlxreg_lib/mlxreg_parser.h

mlxreg_mlxreg_lib_libmstreg_lib_la_DEPENDENCIES = \
    mft_utils/libmftutils.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    adb_parser/libadb_parser.la \
    dev_mgt/libdev_mgt.la

mlxreg_mlxreg_lib_libmstreg_lib_la_LIBADD = $(mlxreg_mlxreg_lib_libmstreg_lib_la_DEPENDENCIES)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxreg_mlxreg_lib_libmstreg_lib_la_CPPFLAGS = $(MLXREG_MLXREG_LIB_CPPFLAGS)
mlxreg_mlxreg_lib_libmstreg_lib_la_CXXFLAGS = $(MLXREG_MLXREG_LIB_CXXFLAGS)
endif

########### mlxreg/scripts ###########
if ADB_GENERIC_TOOLS_ENABLED
bin_SCRIPTS += mlxreg/scripts/mstgenerate_pgcb_commands

mlxreg/scripts/mstgenerate_pgcb_commands: common/python_wrapper
	@$(MKDIR_P) $(@D)
	cp common/python_wrapper $@
mstgenerate_pgcb_commandslibdir = $(libdir)/mstflint/python_tools

mstgenerate_pgcb_commandslib_DATA = mlxreg/scripts/mstgenerate_pgcb_commands.py
endif

########### mlxreg/mlxreg_sdk ###########
if ADB_GENERIC_TOOLS_ENABLED
if ENABLE_MSTFLINT_SDK
MLXREG_MLXREG_SDK_CPPFLAGS = \
    -I$(top_builddir)/mlxreg/mlxreg_sdk \
    -I$(top_srcdir)/mlxreg/mlxreg_sdk \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxreg/mlxreg_sdk \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxreg \
    -I$(top_srcdir)/mft_core/mft_core_utils

MLXREG_MLXREG_SDK_CPPFLAGS += $(JSON_CFLAGS)

MLXREG_MLXREG_SDK_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES += mlxreg/mlxreg_sdk/libmlxreg_sdk.la

mlxreg_mlxreg_sdk_libmlxreg_sdk_la_SOURCES = \
    mlxreg/mlxreg_sdk/mlxreg_sdk.cpp \
    mlxreg/mlxreg_sdk/mlxreg_sdk.h \
    mlxreg/mlxreg_sdk/prm_reg_sdk.cpp \
    mlxreg/mlxreg_sdk/prm_reg_sdk.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxreg_mlxreg_sdk_libmlxreg_sdk_la_CPPFLAGS = $(MLXREG_MLXREG_SDK_CPPFLAGS)
mlxreg_mlxreg_sdk_libmlxreg_sdk_la_CXXFLAGS = $(MLXREG_MLXREG_SDK_CXXFLAGS)
endif
endif

########### mlxlink ###########
if ADB_GENERIC_TOOLS_ENABLED

MLXLINK_CPPFLAGS = \
    -I$(top_builddir)/mlxlink \
    -I$(top_srcdir)/mlxlink \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxlink \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxlink \
    -I$(top_srcdir)/mlxreg

MLXLINK_CPPFLAGS += $(JSON_CFLAGS)

MLXLINK_CXXFLAGS = -Wall -W -DMST_UL -g -MP -MD -pipe

bin_PROGRAMS += mlxlink/mstlink

mlxlink_mstlink_CXXFLAGS = -DEXTERNAL
mlxlink_mstlink_SOURCES = mlxlink/mlxlink_main.cpp

mlxlink_mstlink_DEPENDENCIES = \
    mlxlink/modules/libmodules_lib.la \
    mlxlink/modules/printutil/libprint_util_lib.la \
    mlxreg/mlxreg_lib/libmstreg_lib.la \
    cmdparser/libcmdparser.a \
    mft_utils/libmftutils.la \
    ${MTCR_CONF_DIR}/libmtcr_ul.la \
    adb_parser/libadb_parser.la \
    cmdif/libcmdif.la \
    dev_mgt/libdev_mgt.la \
    tools_layouts/libtools_layouts.la \
    xz_utils/libxz_utils.la \
    ext_libs/minixz/libminixz.la \
    common/libcommon.la \
    pci_library/libpci_library.la \
    reg_access/libreg_access.la \
    mft_core/mft_core_utils/operating_system_api/lib_os_api.la \
    mft_core/mft_core_utils/logger/liblogger.la \
    mft_core/mft_core_utils/mft_exceptions/libmftexceptions.la

mlxlink_mstlink_LDADD = $(mlxlink_mstlink_DEPENDENCIES) $(JSON_LIBS) $(liblzma_LIBS) ${LDL} $(expat_LIBS)

mlxlink_mstlink_LDFLAGS = -static

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxlink_mstlink_CPPFLAGS = $(MLXLINK_CPPFLAGS)
endif

########### mlxlink/modules ###########
if ADB_GENERIC_TOOLS_ENABLED

MLXLINK_MODULES_CPPFLAGS = \
    -I$(top_builddir)/mlxlink/modules \
    -I$(top_srcdir)/mlxlink/modules \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxlink/modules \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxlink \
    -I$(top_srcdir)/mlxreg

MLXLINK_MODULES_CPPFLAGS += $(JSON_CFLAGS)

MLXLINK_MODULES_CFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"
MLXLINK_MODULES_CXXFLAGS = -Wall -W -g -MP -MD -pipe #$(COMPILER_FPIC)

noinst_LTLIBRARIES += mlxlink/modules/libmodules_lib.la

mlxlink_modules_libmodules_lib_la_SOURCES = \
    mlxlink/modules/amber_field.cpp \
    mlxlink/modules/amber_field.h \
    mlxlink/modules/mlxlink_amBER_collector.cpp \
    mlxlink/modules/mlxlink_amBER_collector.h \
    mlxlink/modules/mlxlink_cables_commander.cpp \
    mlxlink/modules/mlxlink_cables_commander.h \
    mlxlink/modules/mlxlink_commander.cpp \
    mlxlink/modules/mlxlink_commander.h \
    mlxlink/modules/mlxlink_enums.h \
    mlxlink/modules/mlxlink_err_inj_commander.cpp \
    mlxlink/modules/mlxlink_err_inj_commander.h \
    mlxlink/modules/mlxlink_eye_opener.cpp \
    mlxlink/modules/mlxlink_eye_opener.h \
    mlxlink/modules/mlxlink_maps.cpp \
    mlxlink/modules/mlxlink_maps.h \
    mlxlink/modules/mlxlink_port_info.cpp \
    mlxlink/modules/mlxlink_port_info.h \
    mlxlink/modules/mlxlink_reg_parser.cpp \
    mlxlink/modules/mlxlink_reg_parser.h \
    mlxlink/modules/mlxlink_ui.cpp \
    mlxlink/modules/mlxlink_ui.h \
    mlxlink/modules/mlxlink_user_input.cpp \
    mlxlink/modules/mlxlink_user_input.h \
    mlxlink/modules/mlxlink_utils.cpp \
    mlxlink/modules/mlxlink_utils.h

mlxlink_modules_libmodules_lib_la_LIBADD = \
    mlxlink/modules/printutil/libprint_util_lib.la \
    $(JSON_LIBS)
EXTRA_mlxlink_modules_libmodules_lib_la_DEPENDENCIES = $(JSON_LA)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxlink_modules_libmodules_lib_la_CPPFLAGS = $(MLXLINK_MODULES_CPPFLAGS)
mlxlink_modules_libmodules_lib_la_CFLAGS = $(MLXLINK_MODULES_CFLAGS)
mlxlink_modules_libmodules_lib_la_CXXFLAGS = $(MLXLINK_MODULES_CXXFLAGS)
endif

########### mlxlink/modules/printutil ###########
if ADB_GENERIC_TOOLS_ENABLED
MLXLINK_MODULES_PRINTUTIL_CPPFLAGS = \
    -I$(top_builddir)/mlxlink/modules/printutil \
    -I$(top_srcdir)/mlxlink/modules/printutil \
    -I$(top_builddir) \
    -I$(top_srcdir)/mlxlink/modules/printutil \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxreg

MLXLINK_MODULES_PRINTUTIL_CPPFLAGS += $(JSON_CFLAGS)

MLXLINK_MODULES_PRINTUTIL_CFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"

noinst_LTLIBRARIES += mlxlink/modules/printutil/libprint_util_lib.la

mlxlink_modules_printutil_libprint_util_lib_la_SOURCES = \
    mlxlink/modules/printutil/mlxlink_cmd_print.cpp \
    mlxlink/modules/printutil/mlxlink_cmd_print.h \
    mlxlink/modules/printutil/mlxlink_record.cpp \
    mlxlink/modules/printutil/mlxlink_record.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mlxlink_modules_printutil_libprint_util_lib_la_CPPFLAGS = $(MLXLINK_MODULES_PRINTUTIL_CPPFLAGS)
mlxlink_modules_printutil_libprint_util_lib_la_CFLAGS = $(MLXLINK_MODULES_PRINTUTIL_CFLAGS)
endif

########### hca_capabilities ###########
if ENABLE_MSTFLINT_SDK
HCA_CAPABILITIES_CPPFLAGS = \
    -I$(top_builddir)/hca_capabilities \
    -I$(top_srcdir)/hca_capabilities \
    -I$(top_builddir) \
    -I$(top_srcdir)/hca_capabilities \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxreg

HCA_CAPABILITIES_CPPFLAGS += $(JSON_CFLAGS)

HCA_CAPABILITIES_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES += hca_capabilities/libhca_capabilities.la

hca_capabilities_libhca_capabilities_la_SOURCES = \
    hca_capabilities/hca_capabilities.cpp \
    hca_capabilities/hca_capabilities.h

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
hca_capabilities_libhca_capabilities_la_CPPFLAGS = $(HCA_CAPABILITIES_CPPFLAGS)
hca_capabilities_libhca_capabilities_la_CXXFLAGS = $(HCA_CAPABILITIES_CXXFLAGS)
endif

########### resourcetools ###########

bin_SCRIPTS += resourcetools/mstresourcedump resourcetools/mstresourceparse

resourcetools/mstresourcedump: common/python_wrapper
	@$(MKDIR_P) $(@D)
	cp common/python_wrapper $@

resourcetools/mstresourceparse: common/python_wrapper
	@$(MKDIR_P) $(@D)
	cp common/python_wrapper $@

resourcetools_pythonlibdir = $(libdir)/mstflint/python_tools/resourcetools
dist_resourcetools_pythonlib_SCRIPTS = resourcetools/mstresourcedump.py resourcetools/mstresourceparse.py

segmentspythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/segments
dist_segmentspythonlib_DATA = $(srcdir)/resourcetools/segments/*.py

maindumppythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib
dist_maindumppythonlib_DATA = $(srcdir)/resourcetools/resourcedump_lib/*.py
validationpythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/validation
dist_validationpythonlib_DATA = $(srcdir)/resourcetools/resourcedump_lib/validation/*.py
utilspythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/utils
dist_utilspythonlib_DATA = $(srcdir)/resourcetools/resourcedump_lib/utils/*.py
filterspythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/filters
dist_filterspythonlib_DATA = $(srcdir)/resourcetools/resourcedump_lib/filters/*.py
fetcherspythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/fetchers
dist_fetcherspythonlib_DATA = $(srcdir)/resourcetools/resourcedump_lib/fetchers/*.py
commandspythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/commands
dist_commandspythonlib_DATA = $(srcdir)/resourcetools/resourcedump_lib/commands/*.py
cresourcedumppythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/cresourcedump
dist_cresourcedumppythonlib_DATA = $(srcdir)/resourcetools/resourcedump_lib/cresourcedump/*.py

mainparsepythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourceparse_lib
dist_mainparsepythonlib_DATA = $(srcdir)/resourcetools/resourceparse_lib/*.py
parsersparsepythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourceparse_lib/parsers
dist_parsersparsepythonlib_DATA = $(srcdir)/resourcetools/resourceparse_lib/parsers/*.py
parseutilspythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourceparse_lib/utils
dist_parseutilspythonlib_DATA = $(srcdir)/resourcetools/resourceparse_lib/utils/*.py
parsedatapythonlibdir = $(libdir)/mstflint/python_tools/resourcetools/resourceparse_lib/resource_data
dist_parsedatapythonlib_DATA = $(srcdir)/resourcetools/resourceparse_lib/resource_data/*.py

CLEANFILES += resourcetools/mstresourcedump resourcetools/mstresourceparse

########### resourcetools/resourcedump_lib/src/common ###########
noinst_LTLIBRARIES += resourcetools/resourcedump_lib/src/common/libresource_dump_common.la

resourcetools_resourcedump_lib_src_common_libresource_dump_common_la_SOURCES = \
    resourcetools/resourcedump_lib/src/common/resource_dump_error_handling.h \
    resourcetools/resourcedump_lib/src/common/resource_dump_error_handling.cpp \
    resourcetools/resourcedump_lib/src/common/resource_dump_constants.h
resourcetools_resourcedump_lib_src_common_libresource_dump_common_la_CFLAGS = $(COMPILER_FPIC) -I$(top_srcdir)/include/mtcr_ul
resourcetools_resourcedump_lib_src_common_libresource_dump_common_la_CXXFLAGS = $(COMPILER_FPIC) -I$(top_srcdir)/include/mtcr_ul

resourcetools_resourcedump_lib_src_common_libresource_dump_common_la_DEPENDENCIES = ${MTCR_CONF_DIR}/libmtcr_ul.la
resourcetools_resourcedump_lib_src_common_libresource_dump_common_la_LIBADD = $(resourcetools_resourcedump_lib_src_common_libresource_dump_common_la_DEPENDENCIES)

RD_COMMON_CPPFLAGS = -I$(top_builddir)/resourcetools/resourcedump_lib/src/common -I$(top_srcdir)/resourcetools/resourcedump_lib/src/common -I$(top_builddir)
# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
resourcetools_resourcedump_lib_src_common_libresource_dump_common_la_CPPFLAGS = $(RD_COMMON_CPPFLAGS)

########### resourcetools/resourcedump_lib/src/fetchers ###########

RD_FETCHERS_CPPFLAGS = \
    -I$(top_builddir)/resourcetools/resourcedump_lib/src/fetchers \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/fetchers \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/reg_access \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/common \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/segments

# AM_CFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"
# AM_CXXFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC)

noinst_LTLIBRARIES += resourcetools/resourcedump_lib/src/fetchers/libreg_access_resource_dump_fetcher.la

resourcetools_resourcedump_lib_src_fetchers_libreg_access_resource_dump_fetcher_la_SOURCES = \
    resourcetools/resourcedump_lib/src/fetchers/fetcher.h \
    resourcetools/resourcedump_lib/src/fetchers/fetcher_factory.h \
    resourcetools/resourcedump_lib/src/fetchers/fetcher_factory.cpp \
    resourcetools/resourcedump_lib/src/fetchers/reg_access_resource_dump_fetcher.h \
    resourcetools/resourcedump_lib/src/fetchers/reg_access_resource_dump_fetcher.cpp
if ENABLE_RDMEM
resourcetools_resourcedump_lib_src_fetchers_libreg_access_resource_dump_fetcher_la_SOURCES += \
    resourcetools/resourcedump_lib/src/fetchers/reg_access_resource_dump_mkey_fetcher.h \
    resourcetools/resourcedump_lib/src/fetchers/reg_access_resource_dump_mkey_fetcher.cpp
endif

resourcetools_resourcedump_lib_src_fetchers_libreg_access_resource_dump_fetcher_la_CFLAGS = $(COMPILER_FPIC)
resourcetools_resourcedump_lib_src_fetchers_libreg_access_resource_dump_fetcher_la_CXXFLAGS = $(COMPILER_FPIC)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
resourcetools_resourcedump_lib_src_fetchers_libreg_access_resource_dump_fetcher_la_CPPFLAGS = $(RD_FETCHERS_CPPFLAGS)

########### resourcetools/resourcedump_lib/src/commands ###########

RD_COMMANDS_CPPFLAGS = \
    -I$(top_builddir)/resourcetools/resourcedump_lib/src/commands \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/commands \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/common \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/segments \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/fetchers \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul

noinst_LTLIBRARIES += resourcetools/resourcedump_lib/src/commands/libresource_dump_commands.la

resourcetools_resourcedump_lib_src_commands_libresource_dump_commands_la_SOURCES = \
    resourcetools/resourcedump_lib/src/commands/resource_dump_command.h \
    resourcetools/resourcedump_lib/src/commands/resource_dump_command.cpp \
    resourcetools/resourcedump_lib/src/commands/dump_command.h \
    resourcetools/resourcedump_lib/src/commands/dump_command.cpp \
    resourcetools/resourcedump_lib/src/commands/query_command.h \
    resourcetools/resourcedump_lib/src/commands/query_command.cpp

resourcetools_resourcedump_lib_src_commands_libresource_dump_commands_la_CFLAGS = $(COMPILER_FPIC)
resourcetools_resourcedump_lib_src_commands_libresource_dump_commands_la_CXXFLAGS = $(COMPILER_FPIC)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
resourcetools_resourcedump_lib_src_commands_libresource_dump_commands_la_CPPFLAGS = $(RD_COMMANDS_CPPFLAGS)

########### resourcetools/resourcedump_lib/src/filters ###########
#MTCR_DIR = $(USER_DIR)/${MTCR_CONFIG_DIR}
#REG_ACCESS_DIR = $(USER_DIR)/reg_access
#TOOLS_LAYOUT_DIR = $(USER_DIR)/tools_layout

RD_FILTERS_CPPFLAGS = \
    -I$(top_builddir)/resourcetools/resourcedump_lib/src/filters \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/filters \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/commands \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/fetchers \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/common \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/segments

# AM_CFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"
# AM_CXXFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC)

noinst_LTLIBRARIES += resourcetools/resourcedump_lib/src/filters/libresource_dump_filters.la

resourcetools_resourcedump_lib_src_filters_libresource_dump_filters_la_SOURCES = \
    resourcetools/resourcedump_lib/src/filters/filter.h \
    resourcetools/resourcedump_lib/src/filters/filter.cpp \
    resourcetools/resourcedump_lib/src/filters/include_exclude_segments_filter.h \
    resourcetools/resourcedump_lib/src/filters/include_exclude_segments_filter.cpp \
    resourcetools/resourcedump_lib/src/filters/strip_control_segments_filter.h \
    resourcetools/resourcedump_lib/src/filters/strip_control_segments_filter.cpp

resourcetools_resourcedump_lib_src_filters_libresource_dump_filters_la_CFLAGS = $(COMPILER_FPIC)
resourcetools_resourcedump_lib_src_filters_libresource_dump_filters_la_CXXFLAGS = $(COMPILER_FPIC)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
resourcetools_resourcedump_lib_src_filters_libresource_dump_filters_la_CPPFLAGS = $(RD_FILTERS_CPPFLAGS)

########### resourcetools/resourcedump_lib/src/sdk ###########
RD_SDK_CPPFLAGS = \
    -I$(top_builddir)/resourcetools/resourcedump_lib/src/sdk \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/sdk \
    -I$(top_builddir) \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/sdk \
    -I$(top_srcdir) \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/commands \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/common \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/fetchers \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/filters \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/segments

noinst_LTLIBRARIES += resourcetools/resourcedump_lib/src/sdk/libresource_dump_sdk.la

resourcetools_resourcedump_lib_src_sdk_libresource_dump_sdk_la_SOURCES = \
    resourcetools/resourcedump_lib/src/sdk/resource_dump_sdk.h \
    resourcetools/resourcedump_lib/src/sdk/resource_dump_sdk.cpp \
    resourcetools/resourcedump_lib/src/sdk/resource_dump_api.h \
    resourcetools/resourcedump_lib/src/sdk/resource_dump_api.cpp
resourcetools_resourcedump_lib_src_sdk_libresource_dump_sdk_la_CFLAGS = $(COMPILER_FPIC)
resourcetools_resourcedump_lib_src_sdk_libresource_dump_sdk_la_CXXFLAGS = $(COMPILER_FPIC)

resource_dump_sdk_sodir = $(libdir)/mstflint/sdk
# if !WIN_BUILD
resource_dump_sdk_so_DATA = resourcetools/resourcedump_lib/src/sdk/libresource_dump_sdk.so
# else
# resource_dump_sdk_so_DATA = libresource_dump_sdk.dll
# endif

rdsdkincludedir = $(includedir)/mstflint/sdk/
rdsdkinclude_HEADERS = \
    resourcetools/resourcedump_lib/src/sdk/resource_dump_sdk.h \
    resourcetools/resourcedump_lib/src/segments/resource_dump_segments.h \
    resourcetools/resourcedump_lib/src/segments/resource_dump_segments_le.h \
    resourcetools/resourcedump_lib/src/segments/resource_dump_segments_be.h \
    resourcetools/resourcedump_lib/src/common/resource_dump_types.h

if ENABLE_RDMEM
OFED_LIBS = -libverbs -lmlx5
else
OFED_LIBS =
endif

resource_dump_sdk_so_DEPS = \
    resourcetools/resourcedump_lib/src/commands/.libs/libresource_dump_commands.a \
    resourcetools/resourcedump_lib/src/fetchers/.libs/libreg_access_resource_dump_fetcher.a \
    resourcetools/resourcedump_lib/src/filters/.libs/libresource_dump_filters.a \
    resourcetools/resourcedump_lib/src/common/.libs/libresource_dump_common.a \
    reg_access/.libs/libreg_access.a \
    tools_layouts/.libs/libtools_layouts.a \
    dev_mgt/.libs/libdev_mgt.a \
    ${MTCR_CONF_DIR}/.libs/libmtcr_ul.a \
    $(OFED_LIBS) \
    $(MST_REMOTE_LINK_LIBS) \
    -lstdc++

# if !WIN_BUILD
resourcetools/resourcedump_lib/src/sdk/libresource_dump_sdk.so: resourcetools/resourcedump_lib/src/sdk/libresource_dump_sdk.la \
		resourcetools/resourcedump_lib/src/commands/libresource_dump_commands.la \
		resourcetools/resourcedump_lib/src/fetchers/libreg_access_resource_dump_fetcher.la \
		resourcetools/resourcedump_lib/src/filters/libresource_dump_filters.la \
		resourcetools/resourcedump_lib/src/common/libresource_dump_common.la \
		reg_access/libreg_access.la tools_layouts/libtools_layouts.la dev_mgt/libdev_mgt.la \
		$(MTCR_CONF_DIR)/libmtcr_ul.la
	$(CC) -Wall -pthread -shared ${CFLAGS} ${LDFLAGS} $(COMPILER_FPIC) \
	$(patsubst %.lo,%.o,$(resourcetools_resourcedump_lib_src_sdk_libresource_dump_sdk_la_OBJECTS)) \
	-o $@ $(resource_dump_sdk_so_DEPS)
# else
# libresource_dump_sdk.dll: libresource_dump_sdk.la
# 	$(CC) -Wall -pthread -shared -Wl,--no-undefined,--enable-runtime-pseudo-reloc ${CFLAGS} $(COMPILER_FPIC) libresource_dump_sdk_la-resource_dump_sdk.o \
# 	-o libresource_dump_sdk.dll ${AM_LDFLAGS} $(resource_dump_sdk_so_DEPS) -lws2_32
# endif

CLEANFILES += $(resource_dump_sdk_so_DATA)

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
resourcetools_resourcedump_lib_src_sdk_libresource_dump_sdk_la_CPPFLAGS = $(RD_SDK_CPPFLAGS)

########### mft_sdk ###########
if ENABLE_MSTFLINT_SDK
MFT_SDK_CPPFLAGS = \
    -I$(top_builddir)/mft_sdk \
    -I$(top_srcdir)/mft_sdk \
    -I$(top_builddir) \
    -I$(top_srcdir)/mft_sdk \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_core/mft_core_utils \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxlink \
    -I$(top_srcdir)/mlxreg \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/commands \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/common \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/fetchers \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/filters \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/sdk \
    -I$(top_srcdir)/resourcetools/resourcedump_lib/src/segments

MFT_SDK_CPPFLAGS += $(JSON_CFLAGS)

MFT_SDK_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

EXTRA_DIST += mft_sdk/README.md

# Optional, flag-gated dependencies. The SDK source gates its use of these
# subsystems on the same ENABLE_* macros, so the library is self-consistent
# whether or not the features are configured in.
if ENABLE_VFIO
MFT_SDK_VFIO_LIBS = vfio_driver_access/libvfio_access_driver.la
endif

if ENABLE_NVML
MFT_SDK_NVML_LIBS = \
    mft_core/device/nvml/libnvml_discovery.la \
    mft_core/mft_core_utils/load_shared_library/libload_shared_library.la
endif

# Self-contained SDK shared object: mstflint's counterpart of libmft_sdk.so.
sdklibdir = $(libdir)/mstflint/sdk
sdklib_LTLIBRARIES = mft_sdk/libmstflint_sdk.la

mft_sdk_libmstflint_sdk_la_SOURCES = \
    mft_sdk/mft_sdk_class.cpp \
    mft_sdk/mft_sdk_cr_space_access.cpp \
    mft_sdk/mft_sdk_discovery.cpp \
    mft_sdk/mft_sdk_errors.cpp \
    mft_sdk/mft_sdk_hca_caps.cpp \
    mft_sdk/mft_sdk_i2c_access.cpp \
    mft_sdk/mft_sdk_icmd.cpp \
    mft_sdk/mft_sdk_reg_access.cpp \
    mft_sdk/mft_sdk_resource_dump.cpp \
    mft_sdk/mft_sdk_temperature.cpp \
    mft_sdk/mft_sdk_telemetry.cpp \
    mft_sdk/mft_sdk.h \
    mft_sdk/mft_sdk_class.hpp \
    mft_sdk/mft_sdk_cr_space_access.h \
    mft_sdk/mft_sdk_discovery.h \
    mft_sdk/mft_sdk_errors.h \
    mft_sdk/mft_sdk_hca_caps.h \
    mft_sdk/mft_sdk_i2c_access.h \
    mft_sdk/mft_sdk_icmd.h \
    mft_sdk/mft_sdk_query.h \
    mft_sdk/mft_sdk_reg_access.h \
    mft_sdk/mft_sdk_resource_dump.h \
    mft_sdk/mft_sdk_telemetry.h \
    mft_sdk/mft_sdk_temperature.h \
    mft_sdk/mft_sdk_telemetry_types.h \
    mft_sdk/mft_sdk_types.h

mft_sdk_libmstflint_sdk_la_CXXFLAGS = $(MFT_SDK_CXXFLAGS) $(COMPILER_FPIC)
mft_sdk_libmstflint_sdk_la_LDFLAGS = -shared -avoid-version -Wl,-soname,libmstflint_sdk.so -Wl,--allow-multiple-definition -Wl,--no-undefined

mft_sdk_libmstflint_sdk_la_LIBADD = \
    hca_capabilities/libhca_capabilities.la \
    mlxreg/mlxreg_sdk/libmlxreg_sdk.la \
    mlxlink/modules/libmodules_lib.la \
    $(MSTREG_SDK_WHOLE_ARCHIVE) \
    mft_utils/libmftutils.la \
    small_utils/libmgettemp.la \
    $(MTCR_SDK_WHOLE_ARCHIVE) \
    resourcetools/resourcedump_lib/src/sdk/libresource_dump_sdk.la \
    resourcetools/resourcedump_lib/src/commands/libresource_dump_commands.la \
    resourcetools/resourcedump_lib/src/fetchers/libreg_access_resource_dump_fetcher.la \
    resourcetools/resourcedump_lib/src/filters/libresource_dump_filters.la \
    resourcetools/resourcedump_lib/src/common/libresource_dump_common.la \
    adb_parser/libadb_parser.la \
    cmdif/libcmdif.la \
    dev_mgt/libdev_mgt.la \
    tools_layouts/libtools_layouts.la \
    xz_utils/libxz_utils.la \
    ext_libs/minixz/libminixz.la \
    common/libcommon.la \
    pci_library/libpci_library.la \
    reg_access/libreg_access.la \
    mft_core/mft_core_utils/operating_system_api/lib_os_api.la \
    mft_core/mft_core_utils/logger/liblogger.la \
    mft_core/mft_core_utils/mft_exceptions/libmftexceptions.la \
    cmdparser/libcmdparser.a \
    $(MFT_SDK_VFIO_LIBS) \
    $(MFT_SDK_NVML_LIBS) \
    $(liblzma_LIBS) \
    $(expat_LIBS) \
    $(LDL)

# The two whole-archive inputs come from configure-substituted variables
# (MTCR_SDK_WHOLE_ARCHIVE, MSTREG_SDK_WHOLE_ARCHIVE) that name libtool's
# .libs/*.a directly, which automake cannot see; declare them here.
EXTRA_mft_sdk_libmstflint_sdk_la_DEPENDENCIES = \
    $(MTCR_CONF_DIR)/libmtcr_ul.la \
    mlxreg/mlxreg_lib/libmstreg_lib.la

# Public SDK headers. Kept under the mstflint include tree (to avoid clashing
# with an MFT-provided $(includedir)/mft_sdk), but inside an mft_sdk/ subdir so
# consumers use `#include <mft_sdk/...>` (with -I$(includedir)/mstflint/sdk) --
# consistent with MFT and with the headers' own internal <mft_sdk/...> includes.
sdkincludedir = $(includedir)/mstflint/sdk/mft_sdk
sdkinclude_HEADERS = \
    mft_sdk/mft_sdk.h \
    mft_sdk/mft_sdk_cr_space_access.h \
    mft_sdk/mft_sdk_discovery.h \
    mft_sdk/mft_sdk_errors.h \
    mft_sdk/mft_sdk_hca_caps.h \
    mft_sdk/mft_sdk_i2c_access.h \
    mft_sdk/mft_sdk_icmd.h \
    mft_sdk/mft_sdk_query.h \
    mft_sdk/mft_sdk_reg_access.h \
    mft_sdk/mft_sdk_resource_dump.h \
    mft_sdk/mft_sdk_telemetry.h \
    mft_sdk/mft_sdk_temperature.h \
    mft_sdk/mft_sdk_telemetry_types.h \
    mft_sdk/mft_sdk_types.h

# pkg-config metadata so consumers can build against the SDK with
# `pkg-config --cflags --libs mstflint_sdk`. Installed to the conventional
# $(libdir)/pkgconfig, generated from mstflint_sdk.pc.in by configure.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = mft_sdk/mstflint_sdk.pc

# ldconfig registration for the private SDK library directory.
#
# libmstflint_sdk.so lives in $(libdir)/mstflint/sdk, which no dynamic linker
# searches by default, so a consumer that links it by soname alone (DOCA's
# libdoca_mgmt does) fails with "libmstflint_sdk.so => not found". Ship an
# ld.so.conf.d snippet naming that directory; the packaging then runs ldconfig
# in its post-install scriptlet.
#
# ldsoconfdir is /etc/ld.so.conf.d and deliberately independent of $(sysconfdir)
# -- ldconfig only reads the real /etc, so a --prefix=/opt install must still put
# the snippet there. Configure it with --with[out]-ldsoconfdir. ldsoconffile is a
# plain make variable so a package shipping under a private name (e.g.
# mstflint-sdk-local, installed side by side with a distro mstflint-sdk) can pick
# a non-colliding file name: make install-sdk ldsoconffile=mstflint-sdk-local.conf
ldsoconfdir = @LDSOCONFDIR@
ldsoconffile = mstflint-sdk.conf

if INSTALL_SDK_LDSOCONF
install-data-local:
	$(MKDIR_P) $(DESTDIR)$(ldsoconfdir)
	echo '$(sdklibdir)' > $(DESTDIR)$(ldsoconfdir)/$(ldsoconffile)

uninstall-local:
	rm -f $(DESTDIR)$(ldsoconfdir)/$(ldsoconffile)
endif

# The SDK ships as a redistributable binary: strip the installed shared object
# and drop the libtool .la (nothing links against it, and .la files are not
# wanted in a distribution). Runs after both `make install` and `make install-sdk`.
sdk-install-data-hook:
	$(STRIP) --strip-unneeded $(DESTDIR)$(sdklibdir)/libmstflint_sdk.so
	rm -f $(DESTDIR)$(sdklibdir)/libmstflint_sdk.la
INSTALL_DATA_HOOKS += sdk-install-data-hook

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mft_sdk_libmstflint_sdk_la_CPPFLAGS = $(MFT_SDK_CPPFLAGS)
endif

########### tracers/fwtrace ###########
bin_SCRIPTS += tracers/fwtrace/mstfwtrace

tracers/fwtrace/mstfwtrace: common/python_wrapper
	@$(MKDIR_P) $(@D)
	cp common/python_wrapper $@
CLEANFILES += tracers/fwtrace/mstfwtrace
tracers_fwtrace_pythonlibdir = $(libdir)/mstflint/python_tools/mstfwtrace
tracers_fwtrace_pythonlib_DATA = tracers/fwtrace/mstfwtrace.py tracers/fwtrace/fw_trace_utilities.py tracers/fwtrace/secure_fw_trace.py
EXTRA_DIST += tracers/fwtrace/mstfwtrace.py

########### ibdump ###########
if ENABLE_IBDUMP
# (DEFAULT_INCLUDES = -I$(top_builddir) -- now part of IBDUMP_CPPFLAGS)
IBDUMP_CPPFLAGS = \
    -I$(top_builddir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/cmdif \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/common

IBDUMP_CFLAGS = \
    -W \
    -Wall \
    -g \
    -MP \
    -MD \
    -DWITH_MSTFLINT \
    -DMST_UL \
    $(COMPILER_FPIC) \
    -DPACKAGE_VERSION_STR=\"$(PACKAGE_VERSION)\"

bin_SCRIPTS += ibdump/vpi_tcpdump
bin_PROGRAMS += ibdump/ibdump
ibdump_ibdump_SOURCES = ibdump/ibdump.c
ibdump_ibdump_DEPENDENCIES = \
    cmdif/libcmdif.la \
    dev_mgt/libdev_mgt.la \
    reg_access/libreg_access.la \
    tools_layouts/libtools_layouts.la \
    $(MTCR_CONF_DIR)/libmtcr_ul.la

ibdump_ibdump_LDADD = \
    $(ibdump_ibdump_DEPENDENCIES) \
    -libverbs \
    -lpthread \
    $(LDL) \
    -lm

ibdump_ibdump_LDFLAGS = -static

# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
ibdump_ibdump_CPPFLAGS = $(IBDUMP_CPPFLAGS)
ibdump_ibdump_CFLAGS = $(IBDUMP_CFLAGS)
endif

########### mst_server/service ###########
if ENABLE_MTCR_REMOTE

bin_PROGRAMS += mst_server/service/mstserver

mst_server_service_mstserver_SOURCES = \
    mst_server/service/MstHttpServer.cpp \
    mst_server/service/MstHttpRoutes.cpp \
    mst_server/service/MstServerTool.cpp \
    mst_server/service/MstServerHttpUtil.cpp \
    mst_server/service/MstServerServiceImpl.cpp \
    mst_server/service/MstServerTls.cpp \
    mst_server/service/MstHttpRoutes.h \
    mst_server/service/MstServerTool.h \
    mst_server/service/MstServerHttpUtil.h \
    mst_server/service/MstServerService.h \
    mst_server/service/MstServerServiceImpl.h \
    mst_server/service/MstServerTls.h \
    mst_server/service/MstTlsFingerprint.h

mst_server_service_mstserver_CXXFLAGS = \
    $(COMPILER_FPIC) \
    $(CXX17_STD) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mtcr_ul \
    -I$(top_srcdir)/ext_libs/crow/include \
    -I$(top_srcdir)/ext_libs/asio/include \
    $(openssl_CFLAGS) \
    -DASIO_STANDALONE \
    -DCROW_ENABLE_SSL \
    -DMST_UL \
    -UVERSION \
    -w

mst_server_service_mstserver_DEPENDENCIES = \
    cmdparser/libcmdparser.a \
    ${MTCR_CONF_DIR}/libmtcr_ul.la

# jsoncpp is resolved at the END of the link line. libmtcr_ul.a and
# libmst_http_client.a are mutually dependent (mtcr_remote.c calls the client;
# the client needs Json), and ld makes a single pass over each archive, so the
# Json objects carried inside libmtcr_ul are already behind it by the time the
# client's undefined Json symbols show up. Listing jsoncpp last closes that gap.
if USE_LOCAL_JSON
MST_SERVER_SERVICE_MST_JSON_LIBS = ext_libs/json/libjson.la
else
MST_SERVER_SERVICE_MST_JSON_LIBS = -ljsoncpp
endif

mst_server_service_mstserver_LDADD = $(mst_server_service_mstserver_DEPENDENCIES) $(openssl_LIBS) $(mst_remote_curl_LIBS) $(FILESYSTEM_LIBS) ${LDL} -lpthread -lstdc++ $(MST_SERVER_SERVICE_MST_JSON_LIBS)
# -static: absorb libmtcr_ul rather than linking it dynamically, matching every
# other tool in the tree. mtcr_ul's install-exec-hook deletes
# $(pkglibdir)/libmtcr_ul.so* after install and ships only the static archive,
# so a dynamically linked consumer would fail at run time with
# "libmtcr_ul.so.0: cannot open shared object file".
mst_server_service_mstserver_LDFLAGS = -static

MST_SERVER_SERVICE_CPPFLAGS = -I$(top_builddir)/mst_server/service -I$(top_srcdir)/mst_server/service -I$(top_builddir)
# Directory-wide flags per target (a target's own _XFLAGS replaces them, as before).
mst_server_service_mstserver_CPPFLAGS = $(MST_SERVER_SERVICE_CPPFLAGS)
# The tree builds at -std=c++14 via CXXFLAGS, which automake puts last on the
# compile line; this directory needs C++17, so raise it for its objects only.
MST_SERVER_SERVICE_CXX17_OBJECTS = $(mst_server_service_mstserver_OBJECTS)
$(MST_SERVER_SERVICE_CXX17_OBJECTS): CXXFLAGS += $(CXX17_STD)
endif

########### install and clean hooks ###########
if !MTCR_FREEBSD
# libmtcr_ul ships as a static archive only; also expose it as $(libdir)/libmtcr_ul.a.
install-exec-hook:
	rm -f $(DESTDIR)$(pkglibdir)/libmtcr_ul.so* $(DESTDIR)$(pkglibdir)/libmtcr_ul.la
	ln -snf mstflint/libmtcr_ul.a $(DESTDIR)$(libdir)/libmtcr_ul.a
endif

# Install steps that are not automake primaries. Sections add theirs to these
# lists, so each hook has one definition: automake does not reject a second one
# (at most it warns), and make would then run only one of the two recipes.
install-data-hook: $(INSTALL_DATA_HOOKS)
uninstall-hook: $(UNINSTALL_HOOKS)

# 'make dist' bundles the per-device JSON files without enumerating them.
dist-hook:
	cp -R $(srcdir)/mft_core/device/device_info/json $(distdir)/mft_core/device/device_info/

# tracers/fwtrace leaves packaging leftovers next to its sources.
clean-local:
	-rm -rf tracers/fwtrace/dist tracers/fwtrace/build tracers/fwtrace/*.spec

########### standalone SDK build ###########
# Builds and installs only libmstflint_sdk.so and what it links, skipping the
# rest of the tool suite. Requires ./configure --enable-mstflint-sdk (which
# itself requires --enable-adb-generic-tools).
#
#   make sdk           # build the SDK library and exactly its dependencies
#   make install-sdk   # install the SDK library, headers, .pc, PRM databases
#
# There is no directory list to maintain: the library's own _LIBADD /
# _DEPENDENCIES above are the complete build graph, so `make sdk` builds that
# and nothing else. install-sdk uses automake's per-directory install goals, so
# DESTDIR= and ldsoconffile= on the command line work as before.
if ENABLE_MSTFLINT_SDK
sdk: $(BUILT_SOURCES)
	@$(MAKE) $(AM_MAKEFLAGS) $(sdklib_LTLIBRARIES)

install-sdk: sdk
	@$(MAKE) $(AM_MAKEFLAGS) install-sdklibLTLIBRARIES install-sdkincludeHEADERS \
	  install-pkgconfigDATA install-prmhcaextDATA install-prmswitchextDATA \
	  install-prmgpuextDATA install-data-local
	@$(MAKE) $(AM_MAKEFLAGS) sdk-install-data-hook
else
sdk install-sdk:
	@echo "error: the standalone SDK targets require ./configure --enable-mstflint-sdk" >&2; \
	exit 1
endif

.PHONY: sdk install-sdk sdk-install-data-hook
