LIST_CXXSRCS = search_info_cxx.cc

LIST_SRCS = $(LIST_CXXSRCS) $(top_builddir)/src/cgt/search/search_info.h \
						$(top_builddir)/src/cgt/misc/cxxtest_defs.h

AM_CPPFLAGS             = -DUSE_UT_CXXTEST

check_PROGRAMS	   			= search_info_cxx
search_info_cxx_SOURCES = $(LIST_SRCS)
TESTS              			= $(check_PROGRAMS)

#AM_DEFAULT_SOURCE_EXT	= .cc

%_cxx.cc: %_cxx.h
	  $(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(LIST_CXXSRCS)
