EXCEPTION_CXXSRCS   = exception_cxx.cc
MEM_EXCEPT_CXXSRCS  = mem_except_cxx.cc

EXCEPTION_SRCS = $(EXCEPTION_CXXSRCS) $(top_builddir)/src/cgt/base/exception/exception.h
MEM_EXCEPT_SRCS = $(MEM_EXCEPT_CXXSRCS) $(top_builddir)/src/cgt/base/exception/mem_except.h

check_PROGRAMS          = exception_cxx mem_except_cxx
exception_cxx_SOURCES   = $(EXCEPTION_SRCS)
mem_except_cxx_SOURCES  = $(MEM_EXCEPT_SRCS)
TESTS                   = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	$(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(LIST_CXXSRCS)
