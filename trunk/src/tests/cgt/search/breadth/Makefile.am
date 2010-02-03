BREADTH_ITERATOR_CXXSRCS = breadth_iterator_cxx.cc

BREADTH_ITERATOR_SRCS = $(BREADTH_ITERATOR_CXXSRCS) $(top_builddir)/src/cgt/search/breadth/breadth_iterator.h \
                        $(top_builddir)/src/cgt/misc/cxxtest_defs.h

AM_CPPFLAGS                   = -DUSE_UT_CXXTEST

check_PROGRAMS                = breadth_iterator_cxx
breadth_iterator_cxx_SOURCES  = $(BREADTH_ITERATOR_SRCS)
TESTS                         = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	$(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(BREADTH_ITERATOR_CXXSRCS)
