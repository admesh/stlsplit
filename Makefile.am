ACLOCAL_AMFLAGS = -I m4

AM_LDFLAGS = @DEAD_STRIP@
AM_LDFLAGS += -no-undefined

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libstlsplit.pc

doc_DATA = \
	README.md \
	COPYING \
	AUTHORS \
	ChangeLog


EXTRA_DIST = \
	$(doc_DATA) \
	libstlsplit.pc.in

CLEANFILES = libstlsplit.pc

bin_PROGRAMS = stlsplit
stlsplit_SOURCES = \
	cli.cpp
stlsplit_LDADD = \
	libstlsplit.la

# libstlsplit libtool versioning
LIBSTLSPLIT_CURRENT=1
LIBSTLSPLIT_REVISION=0
LIBSTLSPLIT_AGE=0

pkginclude_HEADERS = stlsplit.h
lib_LTLIBRARIES = libstlsplit.la

libstlsplit_la_SOURCES = \
	stlsplit.cpp

libstlsplit_la_LDFLAGS = \
	$(AM_LDFLAGS) \
	-version-info $(LIBSTLSPLIT_CURRENT):$(LIBSTLSPLIT_REVISION):$(LIBSTLSPLIT_AGE)

distclean-local:
	rm -rf *.cache *~

AUTHORS:
	git log --format='%aN <%aE>' | sort -u > $@

ChangeLog:
	./fortag.sh >$@

dist-hook: AUTHORS ChangeLog
