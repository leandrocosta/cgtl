DEPTH_ITERATOR_CXXSRCS = depth_iterator_cxx.cc

DEPTH_ITERATOR_SRCS = $(DEPTH_ITERATOR_CXXSRCS) $(top_builddir)/src/cgt/search/depth/depth_iterator.h \
                      $(top_builddir)/src/cgt/misc/cxxtest_defs.h

AM_CPPFLAGS                 = -DUSE_UT_CXXTEST

check_PROGRAMS              = depth_iterator_cxx
depth_iterator_cxx_SOURCES  = $(DEPTH_ITERATOR_SRCS)
TESTS                       = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	$(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(DEPTH_ITERATOR_CXXSRCS)
