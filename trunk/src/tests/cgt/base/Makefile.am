SUBDIRS = alloc exception iterator

LIST_CXXSRCS = list_cxx.cc
VECTOR_CXXSRCS = vector_cxx.cc

LIST_SRCS = $(LIST_CXXSRCS) $(top_builddir)/src/cgt/base/list.h \
						$(top_builddir)/src/cgt/misc/cxxtest_defs.h
VECTOR_SRCS = $(VECTOR_CXXSRCS) $(top_builddir)/src/cgt/base/vector.h \
							$(top_builddir)/src/cgt/misc/cxxtest_defs.h

AM_CPPFLAGS        = -DUSE_UT_CXXTEST

check_PROGRAMS	   = list_cxx vector_cxx
list_cxx_SOURCES   = $(LIST_SRCS)
vector_cxx_SOURCES = $(VECTOR_SRCS)
TESTS              = $(check_PROGRAMS)

#AM_DEFAULT_SOURCE_EXT	= .cc

%_cxx.cc: %_cxx.h
	  $(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(LIST_CXXSRCS)
