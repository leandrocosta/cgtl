#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(cgtl, 0.01, leandro.costa@gmail.com)
AC_CONFIG_SRCDIR([src/cgt/adjacency.h])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

CPPFLAGS="-Wall"
INCLUDES='-I$(top_srcdir)/src'
AC_SUBST(INCLUDES)

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/examples/Makefile])
AC_OUTPUT
