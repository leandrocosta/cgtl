LIST_CXXSRCS = list_cxx.cc

LIST_SRCS = $(LIST_CXXSRCS) $(top_builddir)/src/cgt/base/list.h

#bin_PROGRAMS       = list_cxx
#list_cxx_SOURCES   = $(LIST_SRCS)

check_PROGRAMS	= list_cxx
#AM_DEFAULT_SOURCE_EXT	= .cc
list_cxx_SOURCES   = $(LIST_SRCS)
TESTS = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	  $(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(LIST_CXXSRCS)
