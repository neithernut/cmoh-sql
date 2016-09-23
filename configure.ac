# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([CMOH_SQL], [0.0], [cmoh@nut.email])
AC_CONFIG_SRCDIR([include/cmoh/sql/])
AM_INIT_AUTOMAKE([foreign subdir-objects])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
PKG_CHECK_MODULES([CMOH], [cmoh])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX(14, [noext])

AC_CONFIG_FILES([
    Makefile
])
AC_OUTPUT
