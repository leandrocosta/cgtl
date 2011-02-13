SUBDIRS = breadth depth

SEARCH_INFO_CXXSRCS = search_info_cxx.cc
SEARCH_STATE_CXXSRCS = search_state_cxx.cc

SEARCH_INFO_SRCS = $(SEARCH_INFO_CXXSRCS) $(top_builddir)/src/cgt/search/search_info.h \
						$(top_builddir)/src/cgt/misc/cxxtest_defs.h
SEARCH_STATE_SRCS = $(SEARCH_STATE_CXXSRCS) $(top_builddir)/src/cgt/search/search_info.h \
						$(top_builddir)/src/cgt/misc/cxxtest_defs.h

AM_CPPFLAGS             = -DUSE_UT_CXXTEST

check_PROGRAMS	   			= search_info_cxx search_state_cxx
search_info_cxx_SOURCES = $(SEARCH_INFO_SRCS)
search_state_cxx_SOURCES = $(SEARCH_STATE_SRCS)
TESTS              			= $(check_PROGRAMS)

#AM_DEFAULT_SOURCE_EXT	= .cc

%_cxx.cc: %_cxx.h
	  $(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(LIST_CXXSRCS)
