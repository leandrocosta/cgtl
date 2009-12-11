CXXTSRCS_ALLOCATOR  = allocator_cxx.cc
CXXTSRCS_MEM_EXCEPT	= storage_cxx.cc
CXXTSRCS						= $(CXXTSRCS_ALLOCATOR) $(CXXTSRCS_MEM_EXCEPT)

SRCS_ALLOCATOR	= $(CXXTSRCS_ALLOCATOR) $(top_builddir)/src/cgt/base/alloc/allocator.h \
									$(top_builddir)/src/cgt/misc/cxxtest_defs.h
SRCS_MEM_EXCEPT = $(CXXTSRCS_MEM_EXCEPT) $(top_builddir)/src/cgt/base/alloc/storage.h \
									$(top_builddir)/src/cgt/misc/cxxtest_defs.h

AM_CPPFLAGS           = -DUSE_UT_CXXTEST

check_PROGRAMS        = allocator_cxx storage_cxx
allocator_cxx_SOURCES = $(SRCS_ALLOCATOR)
storage_cxx_SOURCES   = $(SRCS_MEM_EXCEPT)
TESTS                 = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	$(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(CXXTSRCS)
