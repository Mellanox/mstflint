# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

# ---------------------------------------------------------------------------
# mstflint SDK unit tests -- built ON the machine under test, AGAINST the
# SDK that is installed on it.
#
# Do not substitute MFT's prebuilt harness: it is built by a different
# toolchain (COW vs SSO std::string) and resolves C++ symbols out of whichever
# .so it loads, both of which link cleanly and fail at run time. Built here it
# shares the machine's compiler and touches only the SDK's C API.
#
#   Sources          this tree (test_utils.*, mlxlink/*, ...)
#   SDK headers      $(SDK_INCDIR)      <- installed by the SDK package
#   SDK library      $(SDK_LIBDIR)      <- installed by the SDK package
#   mlxlink enums    $(REPO_ROOT)/mlxlink/modules  <- test-support headers,
#                    pure enum/string constants, not part of the SDK ABI
#
# Usage:
#   make -C mft_sdk/unit_tests gtest      # once: build the bundled gtest
#   make -C mft_sdk/unit_tests unified    # DEFAULT: the multi-suite harness
#                                         #   -- what print-env points at, and
#                                         #   what the Python suites need
#   make -C mft_sdk/unit_tests op_info    # fast path: op-info C and C++ only
#   make -C mft_sdk/unit_tests print-env  # env block for the Python suites
# ---------------------------------------------------------------------------

# --- Where the installed SDK lives -----------------------------------------
# Resolution order, highest priority first:
#
#   1. SDK_INCDIR / SDK_LIBDIR given on the command line or in the environment
#   2. the mstflint_sdk pkg-config module      <- what DOCA actually uses
#   3. $(SDK_PREFIX) plus a lib64-vs-lib probe <- last resort
#
# pkg-config outranks the prefix probe because that is how DOCA consumes the
# SDK, and it is the only route that finds a relocated install.
PKG_CONFIG ?= pkg-config
SDK_PKG    ?= mstflint_sdk
SDK_PC_FOUND := $(shell $(PKG_CONFIG) --exists $(SDK_PKG) 2>/dev/null && echo yes)

SDK_PREFIX ?= /usr
# lib64 on RPM distros, lib on Debian ones; override SDK_LIBDIR to be explicit.
SDK_LIBSUBDIR ?= $(if $(wildcard $(SDK_PREFIX)/lib64/mstflint/sdk),lib64,lib)

ifeq ($(SDK_PC_FOUND),yes)
SDK_LIBDIR ?= $(shell $(PKG_CONFIG) --variable=libdir $(SDK_PKG))
SDK_INCDIR ?= $(shell $(PKG_CONFIG) --variable=includedir $(SDK_PKG))
SDK_ORIGIN := pkg-config($(SDK_PKG))
else
SDK_LIBDIR ?= $(SDK_PREFIX)/$(SDK_LIBSUBDIR)/mstflint/sdk
SDK_INCDIR ?= $(SDK_PREFIX)/include/mstflint/sdk
SDK_ORIGIN := SDK_PREFIX=$(SDK_PREFIX) (no $(SDK_PKG).pc found)
endif

# --- Optional SDK APIs: probe, do not assume ---------------------------------
# The i2c entry points are declared by the headers but only defined in the .so
# when the SDK was built with --enable-i2c, so the suites gate them at compile
# time. Never pass -DMFT_SDK_HAS_I2C=0: the suites test it with #ifdef, so a
# zero value enables that code and breaks the link.
SDK_HAS_I2C := $(shell nm -D --defined-only $(SDK_LIBDIR)/libmstflint_sdk.so 2>/dev/null \
                 | grep -qw mstGetI2cSecondary && echo 1 || echo 0)
# Two macro names for the same --enable-i2c option, both from this one probe.
I2C_DEFS := $(if $(filter 1,$(SDK_HAS_I2C)),-DMFT_SDK_HAS_I2C=1 -DMFT_SDK_HAS_I2C_SECONDARY=1,)

# MFT_SDK_HAS_TELEMETRY_JSON is not probed: that surface is missing from the
# HEADERS too, so a symbol probe would enable code that does not compile.

# --- Tree layout ------------------------------------------------------------
TESTS_DIR := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
REPO_ROOT := $(abspath $(TESTS_DIR)/../..)
BUILD_DIR ?= $(TESTS_DIR)/build-tests

# --- gtest ------------------------------------------------------------------
# Built from source by the `gtest` target, with this machine's compiler, so it
# matches the ABI of everything else here. GTEST_TARBALL may point at a local
# googletest tarball; otherwise the source is fetched over the network.
GTEST_DIR     ?= $(BUILD_DIR)/gtest
GTEST_TARBALL ?=
GTEST_URL     ?= https://github.com/google/googletest/archive/refs/tags/release-1.8.1.tar.gz
GTEST_INC     := $(GTEST_DIR)/src/googletest/include
GTEST_LIB     := $(GTEST_DIR)/libgtest.a

# --- Toolchain --------------------------------------------------------------
CC       ?= gcc
CXX      ?= g++
CSTD     ?= -std=gnu99
CXXSTD   ?= -std=c++14
WARN     ?= -Wall -W
OPT      ?= -O2 -g

# The SDK's public headers are included as <mft_sdk/...>, so SDK_INCDIR is the
# directory that CONTAINS mft_sdk/. TESTS_DIR supplies test_utils.h and
# mlxreg/mlxreg_fields.h; REPO_ROOT supplies mlxlink/modules/mlxlink_enums.h.
INCLUDES := -I$(SDK_INCDIR) -I$(TESTS_DIR) -I$(REPO_ROOT)

# Link by soname against the installed SDK. -rpath makes the binary runnable
# without LD_LIBRARY_PATH even when the ld.so.conf.d snippet is absent (the
# Python suites also export MFT_SDK_SO_DIR, so either route works).
LDFLAGS  := -L$(SDK_LIBDIR) -Wl,-rpath,$(SDK_LIBDIR)
LDLIBS   := -lmstflint_sdk

# --- Binaries ---------------------------------------------------------------
# C++ (gtest) op-info test. op_info_test.cpp carries its own main() when
# MFT_SDK_SO_UNIFIED is undefined, so no separate driver TU is needed.
OP_INFO_CPP_BIN := $(BUILD_DIR)/mstflint_sdk_op_info_cpp_test
OP_INFO_CPP_SRC := $(TESTS_DIR)/mlxlink/op_info_test.cpp $(TESTS_DIR)/test_utils.cpp

# Unified C++ harness: every gtest suite in one binary, selected at run time
# with --gtest_filter; the Python drivers point MFT_SDK_SO_TEST_BIN here.
# Suites whose SDK entry points are missing gate those cases at compile time
# instead of dropping out of the binary, so the gap stays visible in
# --gtest_list_tests rather than hiding behind a run-time filter.
CPP_BIN := $(BUILD_DIR)/mstflint_sdk_cpp_test
CPP_SUITES := $(sort $(wildcard $(TESTS_DIR)/*/*_test.cpp)) \
	$(TESTS_DIR)/mlxreg/mlxreg_fields.h
CPP_SUITE_SRCS := $(filter %.cpp,$(CPP_SUITES))

# Unified C driver. utils.py invokes the C column as `<bin> <suite> <BDF>`,
# so the C binary must be the multi-suite driver even when only one suite is
# being validated; each suite's main() is renamed under MFT_SDK_C_UNIFIED.
C_BIN     := $(BUILD_DIR)/mstflint_sdk_c_test
C_DRIVER  := $(TESTS_DIR)/mft_sdk_c_test_main.cpp
C_SUITES  := $(sort $(wildcard $(TESTS_DIR)/*/*_test.c))

# --- hca_caps standalone probe ----------------------------------------------
# Build canary only: test_hca_caps_validation.py compiles this file itself at
# run time. hca_caps_probe.c must NEVER join C_SUITES -- its unguarded main()
# would collide with the C driver's.
HCA_CAPS_PROBE_BIN := $(BUILD_DIR)/hca_caps_probe
HCA_CAPS_PROBE_SRC := $(TESTS_DIR)/hca_caps/hca_caps_probe.c
# (rules live below `all`, so they cannot become the default goal)

# --- DOCA integration contract ----------------------------------------------
# A stand-in for DOCA's libs/doca_mgmt: plain C, resolved through pkg-config,
# linked WITHOUT an rpath. Deliberately unlike every other binary here -- see
# doca_contract/probe.c for why each of those four properties matters.
DOCA_DIR         := $(TESTS_DIR)/doca_contract
DOCA_PROBE_BIN   := $(BUILD_DIR)/doca_contract_probe
DOCA_PROBE_SRC   := $(DOCA_DIR)/probe.c
DOCA_SYMBOLS     := $(DOCA_DIR)/doca_symbols.txt
DOCA_CHECK       := $(DOCA_DIR)/check_contract.sh
# fwctl device name the probe tries to open; override for a machine that has one
DOCA_FWCTL       ?= fwctl0

# Take the flags from pkg-config verbatim when it is available -- the point of
# this target is to exercise the .pc, not to second-guess it.
ifeq ($(SDK_PC_FOUND),yes)
DOCA_CFLAGS := $(shell $(PKG_CONFIG) --cflags $(SDK_PKG))
DOCA_LIBS   := $(shell $(PKG_CONFIG) --libs $(SDK_PKG))
else
DOCA_CFLAGS := -I$(SDK_INCDIR)
DOCA_LIBS   := -L$(SDK_LIBDIR) -lmstflint_sdk
endif

.PHONY: all op_info unified gtest clean distclean check-sdk print-env help \
        doca-contract check-doca hca-caps-probe prepare test check-ref-cli

# --- one-time preparation ----------------------------------------------------
# `prepare` installs the SDK, then the CLI, then builds the harness; every suite
# runs against that one installation. The CLI step must configure WITHOUT
# --enable-mstflint-sdk or it overwrites the SDK installed first. Its
# mstreg/mstlink are the oracle; utils.py otherwise defaults to MFT's tools.
SDK_CONFIGURE_FLAGS ?= --enable-mstflint-sdk --enable-adb-generic-tools --prefix=/usr
CLI_CONFIGURE_FLAGS ?= --prefix=/usr --enable-adb-generic-tools
SUDO ?= sudo
JOBS ?= $(shell nproc 2>/dev/null || echo 4)

prepare:
	@set -e; cd $(REPO_ROOT); \
	echo "==> [1/3] building and installing the SDK"; \
	rm -rf tools_layouts/.libs; rm -f tools_layouts/*.o tools_layouts/*.lo tools_layouts/*.la; \
	rm -f mft_sdk/libmstflint_sdk.la mft_sdk/.libs/libmstflint_sdk.so*; \
	./autogen.sh >/dev/null; \
	./configure $(SDK_CONFIGURE_FLAGS) >/dev/null; \
	grep -q '^#define PACKAGE_STRING' config.h || { \
	  echo "error: config.h has no #defines; re-run ./autogen.sh && ./configure" >&2; exit 1; }; \
	$(MAKE) sdk -j$(JOBS) >/dev/null; \
	test -f mft_sdk/.libs/libmstflint_sdk.so || { echo "error: SDK did not build" >&2; exit 1; }; \
	$(SUDO) $(MAKE) install-sdk >/dev/null; \
	$(SUDO) $(shell command -v ldconfig || echo /sbin/ldconfig); \
	SDK_SUM=$$(md5sum $$($(PKG_CONFIG) --variable=libdir $(SDK_PKG))/libmstflint_sdk.so | cut -d' ' -f1); \
	echo "    SDK installed, md5 $$SDK_SUM"; \
	echo "==> [2/3] building and installing the mstflint CLI (no SDK flag)"; \
	./configure $(CLI_CONFIGURE_FLAGS) >/dev/null; \
	$(MAKE) -j$(JOBS) >/dev/null; \
	$(SUDO) $(MAKE) install >/dev/null; \
	$(SUDO) $(shell command -v ldconfig || echo /sbin/ldconfig); \
	NOW=$$(md5sum $$($(PKG_CONFIG) --variable=libdir $(SDK_PKG))/libmstflint_sdk.so | cut -d' ' -f1); \
	test "$$SDK_SUM" = "$$NOW" || { \
	  echo "error: the CLI install OVERWROTE the SDK ($$SDK_SUM -> $$NOW)." >&2; \
	  echo "       step 2 must not pass --enable-mstflint-sdk." >&2; exit 1; }; \
	echo "    SDK unchanged after the CLI install"; \
	echo "==> [3/3] building the test harness"; \
	$(MAKE) -C $(TESTS_DIR) unified >/dev/null; \
	echo "==> prepare complete"
	@$(MAKE) --no-print-directory -C $(TESTS_DIR) check-ref-cli

# The oracle must be mstflint's CLI. Checked separately so `test` can assert it
# even when prepare was run earlier or by someone else.
check-ref-cli:
	@for t in mstreg mstlink; do \
	  test -x /usr/bin/$$t || { \
	    echo "error: /usr/bin/$$t missing -- run 'make prepare'" >&2; exit 1; }; \
	done
	@echo "reference CLI: /usr/bin/mstreg /usr/bin/mstlink (mstflint's own)"

# Run every comparison suite against the ONE installed SDK and the ONE harness
# built by prepare. DEVICE is required; pass DEVICE=0000:21:00.0.
test: check-ref-cli
	@test -n "$(DEVICE)" || { echo "usage: make test DEVICE=0000:21:00.0" >&2; exit 1; }
	@test -x $(CPP_BIN) || { echo "error: harness missing -- run 'make prepare'" >&2; exit 1; }
	@env $(shell $(MAKE) --no-print-directory -C $(TESTS_DIR) print-env | sed 's/^export //') \
	  $(TESTS_DIR)/run_all_suites.py -d $(DEVICE) $(if $(JSON),--json $(JSON),)

# Pinned so adding a target above cannot silently change the default goal.
.DEFAULT_GOAL := all

# Must build what print-env names: op_info holds a single fixture, so the other
# Python suites match 0 tests and report their empty C++ column as a pass.
all: unified

help:
	@echo "Targets:"
	@echo "  gtest         build the bundled googletest (run once)"
	@echo "  unified       build the multi-suite C++ harness + the C driver"
	@echo "                (the DEFAULT target; print-env names $(CPP_BIN))"
	@echo "  op_info       fast path: op-info C and C++ test binaries only"
	@echo "                (single fixture -- not enough for the Python suites)"
	@echo "  hca-caps-probe compile hca_caps/hca_caps_probe.c (build canary)"
	@echo "  doca-contract build the DOCA-shaped probe (pkg-config, no rpath)"
	@echo "  check-doca    build the probe and assert DOCA's integration contract"
	@echo "  print-env     print the env block the Python suites expect"
	@echo "  clean         remove built test binaries (keeps gtest)"
	@echo "  distclean     remove everything under $(BUILD_DIR)"
	@echo ""
	@echo "SDK resolved via: $(SDK_ORIGIN)"
	@echo "Optional APIs:    i2c entry points in the .so: $(if $(filter 1,$(SDK_HAS_I2C)),yes -- i2c cases COMPILED IN,no -- i2c cases report a named skip)"
	@echo "Variables: SDK_LIBDIR=$(SDK_LIBDIR)"
	@echo "           SDK_INCDIR=$(SDK_INCDIR) GTEST_DIR=$(GTEST_DIR)"

# Fail early and legibly if the SDK package is not installed, rather than
# emitting a wall of "No such file or directory" from the compiler.
check-sdk:
	@test -f "$(SDK_INCDIR)/mft_sdk/mft_sdk.h" || { \
	  echo "ERROR: SDK headers not found at $(SDK_INCDIR)/mft_sdk/mft_sdk.h"; \
	  echo "       install the SDK first, e.g.:"; \
	  echo "         ./build_sdk.sh --prefix /usr --build-only && sudo make install-sdk"; \
	  exit 1; }
	@test -f "$(SDK_LIBDIR)/libmstflint_sdk.so" || { \
	  echo "ERROR: SDK library not found at $(SDK_LIBDIR)/libmstflint_sdk.so"; \
	  exit 1; }

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# --- gtest ------------------------------------------------------------------
gtest: $(GTEST_LIB)

$(GTEST_LIB): | $(BUILD_DIR)
	@set -e; \
	if [ ! -d "$(GTEST_DIR)/src/googletest" ]; then \
	  mkdir -p "$(GTEST_DIR)/src"; \
	  if [ -r "$(GTEST_TARBALL)" ]; then \
	    echo "  GTEST    unpacking $(GTEST_TARBALL)"; \
	    tar xf "$(GTEST_TARBALL)" -C "$(GTEST_DIR)/src"; \
	  else \
	    echo "  GTEST    fetching $(GTEST_URL)"; \
	    curl -fsSL "$(GTEST_URL)" | tar xz -C "$(GTEST_DIR)/src" --strip-components=1; \
	  fi; \
	fi; \
	echo "  CXX      gtest-all.cc"; \
	$(CXX) $(CXXSTD) $(OPT) -isystem "$(GTEST_INC)" -I"$(GTEST_DIR)/src/googletest" \
	  -pthread -c "$(GTEST_DIR)/src/googletest/src/gtest-all.cc" -o "$(GTEST_DIR)/gtest-all.o"; \
	ar rcs "$(GTEST_LIB)" "$(GTEST_DIR)/gtest-all.o"; \
	echo "  AR       $(GTEST_LIB)"

# --- op_info ----------------------------------------------------------------
op_info: $(OP_INFO_CPP_BIN) $(C_BIN)
	@echo ""
	@echo "Built:"
	@echo "  C++  $(OP_INFO_CPP_BIN)"
	@echo "  C    $(C_BIN)"

$(OP_INFO_CPP_BIN): $(OP_INFO_CPP_SRC) $(GTEST_LIB) | $(BUILD_DIR)
	@$(MAKE) --no-print-directory check-sdk
	@echo "  CXXLD    $@"
	$(CXX) $(CXXSTD) $(OPT) $(WARN) $(INCLUDES) -isystem $(GTEST_INC) \
	  $(OP_INFO_CPP_SRC) $(GTEST_LIB) -pthread \
	  $(LDFLAGS) $(LDLIBS) -o $@

# --- unified ----------------------------------------------------------------
unified: $(CPP_BIN) $(C_BIN)
	@echo ""
	@echo "Built:"
	@echo "  C++  $(CPP_BIN)   (all compilable gtest suites)"
	@echo "  C    $(C_BIN)"

# mft_sdk_test_main.cpp owns main() here, so every suite TU is compiled with
# MFT_SDK_SO_UNIFIED to suppress its own.
$(CPP_BIN): $(CPP_SUITE_SRCS) $(TESTS_DIR)/mft_sdk_test_main.cpp $(TESTS_DIR)/test_utils.cpp $(GTEST_LIB) | $(BUILD_DIR)
	@$(MAKE) --no-print-directory check-sdk
	@echo "  CXXLD    $@"
	$(CXX) $(CXXSTD) $(OPT) $(WARN) -DMFT_SDK_SO_UNIFIED $(I2C_DEFS) $(INCLUDES) -isystem $(GTEST_INC) \
	  $(TESTS_DIR)/mft_sdk_test_main.cpp $(TESTS_DIR)/test_utils.cpp $(CPP_SUITE_SRCS) \
	  $(GTEST_LIB) -pthread \
	  $(LDFLAGS) $(LDLIBS) -o $@

# The C suites are compiled as C, the driver and test_utils as C++, then
# linked with the C++ driver (test_utils.cpp and the gtest-free driver both
# need libstdc++).
C_OBJS := $(patsubst $(TESTS_DIR)/%.c,$(BUILD_DIR)/c/%.o,$(C_SUITES))

$(BUILD_DIR)/c/%.o: $(TESTS_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "  CC       $<"
	$(CC) $(CSTD) $(OPT) $(WARN) -DMFT_SDK_C_UNIFIED $(I2C_DEFS) $(INCLUDES) -c $< -o $@

$(C_BIN): $(C_OBJS) $(C_DRIVER) $(TESTS_DIR)/test_utils.cpp | $(BUILD_DIR)
	@$(MAKE) --no-print-directory check-sdk
	@echo "  CXXLD    $@"
	$(CXX) $(CXXSTD) $(OPT) $(WARN) -DMFT_SDK_SO_UNIFIED $(INCLUDES) \
	  $(C_DRIVER) $(TESTS_DIR)/test_utils.cpp $(C_OBJS) \
	  $(LDFLAGS) $(LDLIBS) -o $@

# --- DOCA contract ----------------------------------------------------------
doca-contract: $(DOCA_PROBE_BIN)
	@echo ""
	@echo "Built:"
	@echo "  C    $(DOCA_PROBE_BIN)   (pkg-config, no rpath)"

# No $(LDFLAGS) on purpose: with no rpath the loader must find the SDK through
# the ld.so.conf.d snippet, as it does for DOCA. Adding one would make this
# target pass through the regression it exists to detect.
$(DOCA_PROBE_BIN): $(DOCA_PROBE_SRC) | $(BUILD_DIR)
	@$(MAKE) --no-print-directory check-sdk
	@echo "  CCLD     $@"
	$(CC) $(CSTD) $(OPT) $(WARN) $(DOCA_PROBE_SRC) $(DOCA_CFLAGS) $(DOCA_LIBS) -o $@

# --- hca_caps standalone probe ----------------------------------------------
hca-caps-probe: $(HCA_CAPS_PROBE_BIN)
	@echo ""
	@echo "Built:"
	@echo "  C    $(HCA_CAPS_PROBE_BIN)   (build canary; the suite compiles its own copy)"

$(HCA_CAPS_PROBE_BIN): $(HCA_CAPS_PROBE_SRC) | $(BUILD_DIR)
	@$(MAKE) --no-print-directory check-sdk
	@echo "  CCLD     $@"
	$(CC) $(CSTD) $(OPT) $(WARN) $(HCA_CAPS_PROBE_SRC) $(INCLUDES) \
	  $(LDFLAGS) $(LDLIBS) -o $@

check-doca: $(DOCA_PROBE_BIN)
	@PKG_CONFIG="$(PKG_CONFIG)" SDK_PKG="$(SDK_PKG)" \
	  $(DOCA_CHECK) --probe "$(DOCA_PROBE_BIN)" \
	                --symbols "$(DOCA_SYMBOLS)" --fwctl "$(DOCA_FWCTL)"

# --- helpers ----------------------------------------------------------------
# MFT_SDK_SO_TEST_BIN must name the UNIFIED harness: utils.py points every
# suite at this one path and filters its own fixture, so a binary without it
# runs 0 tests. Consumed as `eval "$(make print-env)"`, which discards the exit
# status -- hence the checks run before any echo, stdout empty on failure.
print-env:
	@test -x "$(CPP_BIN)" || { \
	  echo "ERROR: unified harness not built: $(CPP_BIN)" >&2; \
	  echo "       MFT_SDK_SO_TEST_BIN would name a file that does not exist," >&2; \
	  echo "       and every Python compare suite would abort." >&2; \
	  echo "       Build it first:  make -C $(TESTS_DIR) unified" >&2; \
	  exit 1; }
	@test -x "$(C_BIN)" || { \
	  echo "ERROR: unified C driver not built: $(C_BIN)" >&2; \
	  echo "       Build it first:  make -C $(TESTS_DIR) unified" >&2; \
	  exit 1; }
	@echo "export MFT_SDK_SO_DIR=$(SDK_LIBDIR)"
	@echo "export MFT_SDK_SO_TEST_BIN=$(CPP_BIN)"
	@echo "export MFT_SDK_C_SO_TEST_BIN=$(C_BIN)"
	@echo "export MFT_SDK_LINK_TOOL=/usr/bin/mstlink"
	@echo "export MFT_SDK_REG_TOOL=/usr/bin/mstreg"

clean:
	rm -rf $(BUILD_DIR)/c $(OP_INFO_CPP_BIN) $(C_BIN) $(CPP_BIN) $(DOCA_PROBE_BIN) \
	       $(HCA_CAPS_PROBE_BIN)

distclean:
	rm -rf $(BUILD_DIR)
