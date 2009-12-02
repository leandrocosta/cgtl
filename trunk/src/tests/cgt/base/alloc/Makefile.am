ALLOCATOR_CXXSRCS   = allocator_cxx.cc
MEM_EXCEPT_CXXSRCS  = storage_cxx.cc

ALLOCATOR_SRCS = $(ALLOCATOR_CXXSRCS) $(top_builddir)/src/cgt/base/alloc/allocator.h
MEM_EXCEPT_SRCS = $(MEM_EXCEPT_CXXSRCS) $(top_builddir)/src/cgt/base/alloc/storage.h

check_PROGRAMS        = allocator_cxx storage_cxx
allocator_cxx_SOURCES = $(ALLOCATOR_SRCS)
storage_cxx_SOURCES   = $(MEM_EXCEPT_SRCS)
TESTS                 = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	$(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(LIST_CXXSRCS)
