ITERATOR_PTR_CXXSRCS   = iterator_ptr_cxx.cc

ITERATOR_PTR_SRCS = $(ITERATOR_PTR_CXXSRCS) $(top_builddir)/src/cgt/base/iterator/iterator_ptr.h

check_PROGRAMS            = iterator_ptr_cxx
iterator_ptr_cxx_SOURCES  = $(ITERATOR_PTR_SRCS)
TESTS                     = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	$(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(LIST_CXXSRCS)
