noinst_LTLIBRARIES = libcable_access.la

libcable_access_la_SOURCES = cdb_cable_access.cpp cdb_cable_access.h cdb_cable_commander.cpp cdb_cable_commander.h cable_access.cpp cable_access.h
libcable_access_la_CXXFLAGS = -W -Wall -g -MP -MD -fPIC -DMTCR_API="" -DMST_UL -I$(top_srcdir)/${MTCR_CONF_DIR} -I$(top_srcdir)/common -I$(top_srcdir) -I$(top_srcdir)/include/${MTCR_CONF_DIR}/
libcable_access_la_LDFLAGS = -lstdc++ -static
libcable_access_la_DEPENDENCIES = $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la $(top_builddir)/reg_access/libreg_access.la $(top_builddir)/dev_mgt/libdev_mgt.la $(top_builddir)/tools_layouts/libcables_layouts.la 
libcable_access_la_LIBADD = $(libcable_access_la_DEPENDENCIES)