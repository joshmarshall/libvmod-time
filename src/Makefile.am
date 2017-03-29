AM_CPPFLAGS = -I$(VARNISHSRC)/include -I$(VARNISHSRC)/bin/varnishd -I$(VARNISHSRC)

vmoddir = $(VMODDIR)

vmod_LTLIBRARIES = libvmod_time.la

libvmod_time_la_LDFLAGS = -module -export dynamic -avoid-version -shared
libvmod_time_la_SOURCES = vcc_if.c vcc_if.h vmod_time.c

vcc_if.c vcc_if.h: *.vcc
	@PYTHON@ @VMODTOOL@ $(top_srcdir)/src/vmod_time.vcc

VMOD_TESTS = tests/*.vtc
.PHONY: $(VMOD_TESTS)

tests/*.vtc:
	$(VARNISHSRC)/bin/varnishtest/varnishtest -Dvarnishd=$(VARNISHSRC)/bin/varnishd/varnishd -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = vmod_time.vcc $(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c $(builddir)/vcc_if.h
