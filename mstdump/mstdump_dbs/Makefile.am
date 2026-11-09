#--
# Copyright (c) 2004-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#--
mstregdumpdir = $(datadir)/@PACKAGE@

# The .csv files stay the source of truth in the repo and are always distributed.
# Compressing them is best effort: the DBs have shipped as plain .csv for years,
# so any failure here falls back to that rather than breaking the build. crd_lib
# reads both forms and prefers a plain .csv placed next to them, so a DB can
# still be overridden in the field.
CSV_FILES = $(notdir $(wildcard $(srcdir)/*.csv))
EXTRA_DIST = $(CSV_FILES)
CLEANFILES = $(CSV_FILES:%=%.xz) $(CSV_FILES:%=%.xz.tmp)

if HAVE_XZ
all-local: $(CSV_FILES:%=%.xz)

# Compress via a temp file so an interrupted or failing xz can never leave a
# partial .csv.xz behind - that would be newer than its .csv, count as up to date
# on the next make, and ship a DB the decoder cannot read. On any failure the
# target is removed and the plain .csv is installed instead.
# CRC32 is the only integrity check the in-tree XZ Embedded decoder accepts, and
# the default preset keeps the dictionary within the decoder's CRD_XZ_DICT_MAX.
%.csv.xz: $(srcdir)/%.csv
	-@if $(XZ) --check=crc32 -c $< > $@.tmp 2>/dev/null && test -s $@.tmp; then \
	    mv -f $@.tmp $@; \
	else \
	    rm -f $@.tmp $@; \
	    echo "  WARNING: $(XZ) failed for $<; installing it uncompressed"; \
	fi
endif

# Install the compressed form only where one was actually produced; everything
# else falls back to the plain .csv. This also covers the no-xz configuration,
# where no .csv.xz exists at all.
install-data-local:
	$(MKDIR_P) "$(DESTDIR)$(mstregdumpdir)"
	@for f in $(CSV_FILES); do \
	    if test -f "$$f.xz"; then \
	        echo " $(INSTALL_DATA) $$f.xz '$(DESTDIR)$(mstregdumpdir)'"; \
	        $(INSTALL_DATA) "$$f.xz" "$(DESTDIR)$(mstregdumpdir)/$$f.xz" || exit 1; \
	    else \
	        echo " $(INSTALL_DATA) $(srcdir)/$$f '$(DESTDIR)$(mstregdumpdir)'"; \
	        $(INSTALL_DATA) "$(srcdir)/$$f" "$(DESTDIR)$(mstregdumpdir)/$$f" || exit 1; \
	    fi; \
	done

uninstall-local:
	@for f in $(CSV_FILES); do \
	    rm -f "$(DESTDIR)$(mstregdumpdir)/$$f" "$(DESTDIR)$(mstregdumpdir)/$$f.xz"; \
	done
