SUBDIRS = alloc exception iterator

CXXTSRCS_HASH 	= hash_cxx.cc
CXXTSRCS_HEAP 	= heap_cxx.cc
CXXTSRCS_LIST 	= list_cxx.cc
CXXTSRCS_QUEUE 	= queue_cxx.cc
CXXTSRCS_STACK 	= stack_cxx.cc
CXXTSRCS_VECTOR = vector_cxx.cc
CXXTSRCS				= $(CXXTSRCS_HASH) $(CXXTSRCS_HEAP) $(CXXTSRCS_LIST) $(CXXTSRCS_QUEUE) $(CXXTSRCS_STACK) $(CXXTSRCS_VECTOR)

SRCS_HASH 	= $(CXXTSRCS_HASH) $(top_builddir)/src/cgt/base/hash.h \
							$(top_builddir)/src/cgt/misc/cxxtest_defs.h
SRCS_HEAP 	= $(CXXTSRCS_HEAP) $(top_builddir)/src/cgt/base/heap.h \
							$(top_builddir)/src/cgt/misc/cxxtest_defs.h
SRCS_LIST 	= $(CXXTSRCS_LIST) $(top_builddir)/src/cgt/base/list.h \
							$(top_builddir)/src/cgt/misc/cxxtest_defs.h
SRCS_QUEUE 	= $(CXXTSRCS_QUEUE) $(top_builddir)/src/cgt/base/queue.h \
							$(top_builddir)/src/cgt/misc/cxxtest_defs.h
SRCS_STACK 	= $(CXXTSRCS_STACK) $(top_builddir)/src/cgt/base/stack.h \
							$(top_builddir)/src/cgt/misc/cxxtest_defs.h
SRCS_VECTOR = $(CXXTSRCS_VECTOR) $(top_builddir)/src/cgt/base/vector.h \
							$(top_builddir)/src/cgt/misc/cxxtest_defs.h

AM_CPPFLAGS        = -DUSE_UT_CXXTEST

check_PROGRAMS	   = hash_cxx heap_cxx list_cxx queue_cxx stack_cxx vector_cxx
hash_cxx_SOURCES   = $(SRCS_HASH)
heap_cxx_SOURCES   = $(SRCS_HEAP)
list_cxx_SOURCES   = $(SRCS_LIST)
queue_cxx_SOURCES  = $(SRCS_QUEUE)
stack_cxx_SOURCES  = $(SRCS_STACK)
vector_cxx_SOURCES = $(SRCS_VECTOR)
TESTS              = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	  $(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(CXXTSRCS)
