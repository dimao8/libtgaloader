#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([tgaloader], [0.1.0.1], [dimao8@yandex.ru])
AC_CONFIG_SRCDIR([src/tgaloader.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AC_LANG([C])
AM_INIT_AUTOMAKE([1.11 foreign subdir-objects silent-rules])

# Check for libtool
LT_INIT([dlopen win32-dll])
LT_LANG([C])

# Checks for programs.
CFLAGS="-std=gnu11"
AC_PROG_CC(clang llwm-gcc gcc)

# Check endiannes
AC_C_BIGENDIAN

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
