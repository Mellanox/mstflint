VERSION    = 3.0.0-7
PREFIX     = /usr
EXE        = ibdump
CC = gcc
MACH      = $(shell uname -m | sed -e 's/ //g')
UNAME_M = $(shell uname -m)
OS_NAME = $(shell lsb_release -si)

MSTFLINT_INCLUDE_DIR = /usr/local/include/mstflint
CFLAGS    += -Wall -W # -Werror
CFLAGS    += -g
CFLAGS    += -MP -MD -DPACKAGE_VERSION_STR=\"$(VERSION)\"
ifeq ($(WITH_MSTFLINT),yes)
CFLAGS    += -DWITH_MSTFLINT -DMST_UL -I$(MSTFLINT_INCLUDE_DIR)
else
ifeq ($(WITHOUT_FW_TOOLS),yes)
CFLAGS    += -DWITHOUT_FW_TOOLS
else
CFLAGS    += -DWITH_MFT -DIBDUMP_A0_MODE  -I/usr/include/mft/
WITH_MFT   = yes
endif
endif

ifeq ($(LIBS_EXP),yes)
CFLAGS    += -DLIBS_EXP
endif
LOADLIBES =
LDFLAGS  +=

ifdef RELEASE
CFLAGS    += -O2
endif

LOADLIBES   += -libverbs

ifeq ($(WITH_MFT), yes)
LIBMFT=/usr/lib/mft/
LIB64MFT=/usr/lib64/mft/
LIBMFTCORE=/usr/lib/mft/libmft_core.a
LIB64MFTCORE=/usr/lib64/mft/libmft_core.a
IBDUMP_LAYOUTS=/usr/include/mft/tools_layouts/ibdump_layouts.h
ifneq "$(wildcard $(LIBMFT) )" ""
LOADLIBES   += -L/usr/lib/mft/
endif
ifneq "$(wildcard $(LIB64MFT) )" ""
LOADLIBES   += -L/usr/lib64/mft/
endif
LOADLIBES   += -lmemaccess -lcmdif -ldev_mgt -lreg_access -ltools_layouts -lmtcr_ul -lstdc++
ifneq "$(wildcard $(LIBMFTCORE) )" ""
LOADLIBES += -lmft_core -lstdc++
endif
ifneq "$(wildcard $(LIB64MFTCORE) )" ""
LOADLIBES += -lmft_core -lstdc++
endif
ifneq "$(wildcard $(IBDUMP_LAYOUTS) )" ""
CFLAGS  += -DIBDUMP_LAYOUTS
LOADLIBES = -libverbs -L/usr/lib/mft/ -L/usr/lib64/mft/ -lmemaccess -lcmdif_ibdump -lmtcr -lstdc++
endif
endif

ifeq ($(WITH_MSTFLINT), yes)
LIBMSTFLINT=/usr/lib/mstflint/
LIB64MSTFLINT=/usr/lib64/mstflint/
LIBMSTFLINT_LOCAL=/usr/local/lib/mstflint/
LIB64MSTFLINT_LOCAL=/usr/local/lib64/mstflint/
ifneq "$(wildcard $(LIBMSTFLINT) )" ""
LOADLIBES   += -L/usr/lib/mstflint/
endif
ifneq "$(wildcard $(LIB64MSTFLINT) )" ""
LOADLIBES   += -L/usr/lib64/mstflint/
endif
ifneq "$(wildcard $(LIBMSTFLINT_LOCAL) )" ""
LOADLIBES   += -L/usr/local/lib/mstflint/
endif
ifneq "$(wildcard $(LIB64MSTFLINT_LOCAL) )" ""
LOADLIBES   += -L/usr/local/lib64/mstflint/
endif
LOADLIBES   += -lcmdif -ldev_mgt -lreg_access -ltools_layouts -lmtcr_ul
endif

LOADLIBES   += -ldl -lpthread

ifeq ($(MACH), $(filter $(MACH), ppc64 ppc64le))
CFLAGS += -m64
LDFLAGS += -m64
endif

ifeq ($(M32),1)
CFLAGS += -m32
LDFLAGS += -m32
endif


all: $(EXE)

TRGMODULES  = \
	ibdump.c

ifeq ($(WITH_MFT),yes)
TRGMODULES += ibd_hw_access.c
endif

TRGOBJS  = $(TRGMODULES:%.c=%.o)
TRGDEPS  = $(TRGMODULES:%.c=%.d)

libibvsmad/libibvsmad.a:
	make -C ./libibvsmad

#
# Build ID
#

BLD_VER=devel
CFLAGS += '-DBLD_VER_STR="$(BLD_VER)"'

-include $(TRGDEPS)

clean:
	rm -fr $(TRGDEPS) $(TRGOBJS) $(EXE)

# Special compilation rules

gitversion.h:
	./gitversion.sh gitversion.h || 1

$(EXE):	$(TRGOBJS) gitversion.h

install: ibdump
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install $(EXE) $(DESTDIR)$(PREFIX)/bin/$(EXE)
	install vpi_tcpdump $(DESTDIR)$(PREFIX)/bin/vpi_tcpdump

.DELETE_ON_ERROR:
.PHONY: all install clean release shared static
