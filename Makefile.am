ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libtgaloader.la
libtgaloader_la_SOURCES = src/tgaloader.c
libtgaloader_la_CFLAGS = -I$(srcdir)/include

include_HEADERS = include/tgaloader.h

# Tests

TESTS = tests/t_version \
	tests/t_load8 \
	tests/t_load16 \
	tests/t_load24 \
	tests/t_load32 \
	tests/t_empty_error \
	tests/t_save

XFAIL_TESTS = tests/t_empty_error

check_PROGRAMS = tests/ttgaloader8 \
  tests/ttgaloader16 \
  tests/ttgaloader24 \
  tests/ttgaloader32 \
	tests/ttgaloader_error \
	tests/ttgasave

tests_ttgaloader8_SOURCES = tests/ttgaloader8.c
tests_ttgaloader8_LDADD = libtgaloader.la
tests_ttgaloader8_CFLAGS = -I$(srcdir)/include

tests_ttgaloader16_SOURCES = tests/ttgaloader16.c
tests_ttgaloader16_LDADD = libtgaloader.la
tests_ttgaloader16_CFLAGS = -I$(srcdir)/include

tests_ttgaloader24_SOURCES = tests/ttgaloader24.c
tests_ttgaloader24_LDADD = libtgaloader.la
tests_ttgaloader24_CFLAGS = -I$(srcdir)/include

tests_ttgaloader32_SOURCES = tests/ttgaloader32.c
tests_ttgaloader32_LDADD = libtgaloader.la
tests_ttgaloader32_CFLAGS = -I$(srcdir)/include

tests_ttgaloader_error_SOURCES = tests/ttgaloader_error.c
tests_ttgaloader_error_LDADD = libtgaloader.la
tests_ttgaloader_error_CFLAGS = -I$(srcdir)/include

tests_ttgasave_SOURCES = tests/ttgasave.c
tests_ttgasave_LDADD = libtgaloader.la
tests_ttgasave_CFLAGS = -I$(srcdir)/include
