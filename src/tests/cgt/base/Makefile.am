SUBDIRS = alloc exception iterator

CXXTSRCS_HASH 	= hash_cxx.cc
CXXTSRCS_LIST 	= list_cxx.cc
CXXTSRCS_VECTOR = vector_cxx.cc
CXXTSRCS				= $(CXXTSRCS_HASH) $(CXXTSRCS_LIST) $(CXXTSRCS_VECTOR)

SRCS_HASH 	= $(CXXTSRCS_HASH) $(top_builddir)/src/cgt/base/hash.h \
							$(top_builddir)/src/cgt/misc/cxxtest_defs.h
SRCS_LIST 	= $(CXXTSRCS_LIST) $(top_builddir)/src/cgt/base/list.h \
							$(top_builddir)/src/cgt/misc/cxxtest_defs.h
SRCS_VECTOR = $(CXXTSRCS_VECTOR) $(top_builddir)/src/cgt/base/vector.h \
							$(top_builddir)/src/cgt/misc/cxxtest_defs.h

AM_CPPFLAGS        = -DUSE_UT_CXXTEST

check_PROGRAMS	   = hash_cxx list_cxx vector_cxx
hash_cxx_SOURCES   = $(SRCS_HASH)
list_cxx_SOURCES   = $(SRCS_LIST)
vector_cxx_SOURCES = $(SRCS_VECTOR)
TESTS              = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	  $(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(CXXTSRCS)
