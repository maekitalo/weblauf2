ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)/include

bin_PROGRAMS = weblauf2

lib_LTLIBRARIES = libweblauf.la

libweblauf_la_SOURCES = \
	lib/managercontext.cpp \
	lib/person.cpp \
	lib/teilnehmermanager.cpp \
	lib/veranstaltung.cpp \
	lib/veranstaltungmanager.cpp \
	lib/wettkampfmanager.cpp \
	lib/wettkampf.cpp \
	lib/wertung.cpp \
	lib/wertungsgruppe.cpp \
	lib/wertungmanager.cpp

libweblauf_la_LIBADD = -lcxxtools -ltntdb

jqueryUiSources = \
	resources/jquery-ui-1.12.1.custom/external/jquery/jquery.js \
	resources/jquery-ui-1.12.1.custom/jquery-ui.theme.min.css \
	resources/jquery-ui-1.12.1.custom/jquery-ui.min.css \
	resources/jquery-ui-1.12.1.custom/jquery-ui.theme.css \
	resources/jquery-ui-1.12.1.custom/jquery-ui.structure.css \
	resources/jquery-ui-1.12.1.custom/jquery-ui.min.js \
	resources/jquery-ui-1.12.1.custom/jquery-ui.js \
	resources/jquery-ui-1.12.1.custom/images/ui-icons_ffffff_256x240.png \
	resources/jquery-ui-1.12.1.custom/images/ui-icons_777777_256x240.png \
	resources/jquery-ui-1.12.1.custom/images/ui-icons_777620_256x240.png \
	resources/jquery-ui-1.12.1.custom/images/ui-icons_cc0000_256x240.png \
	resources/jquery-ui-1.12.1.custom/images/ui-icons_444444_256x240.png \
	resources/jquery-ui-1.12.1.custom/images/ui-icons_555555_256x240.png \
	resources/jquery-ui-1.12.1.custom/jquery-ui.structure.min.css \
	resources/jquery-ui-1.12.1.custom/jquery-ui.css

ecppSources = \
	json/veranstaltung.ecpp \
	json/veranstaltungen.ecpp \
	json/wettkaempfe.ecpp \
	json/wertungen.ecpp \
	webmain.ecpp

staticSources = \
	resources/weblauf2.css \
	resources/dropdown.css \
	resources/js/jquery-3.2.1.js \
	resources/js/require.js \
	resources/js/main.js \
	resources/js/veranstaltung.js \
	resources/js/wettkampf.js \
	resources/js/wertung.js \
	resources/html/veranstaltung.html \
	resources/html/wettkampf.html \
	resources/html/wertung.html \
	$(jqueryUiSources)

weblauf2_SOURCES = \
	main.cpp \
	configuration.cpp \
	$(ecppSources)

nodist_weblauf2_SOURCES = \
	resources.cpp

weblauf2_LDFLAGS = -lcxxtools -ltntnet
weblauf2_LDADD = $(top_builddir)/libweblauf.la

include_HEADERS = \
	configuration.h
	include/person.h \
	include/teilnehmermanager.h \
	include/veranstaltung.h \
	include/veranstaltungmanager.h \
	include/wettkampf.h \
	include/wettkampfmanager.h \
	include/wertung.h \
	include/wertungmanager.h

nobase_dist_noinst_DATA = $(staticSources)

CLEANFILES = $(ecppSources:.ecpp=.cpp) $(ecppSources:.ecpp=.deps) resources.cpp

#
# Rules for tntnet applications
#
ECPPFLAGS=-I$(srcdir)

resources.cpp: $(staticSources) Makefile.am
	$(AM_V_GEN)$(ECPPC) -bb -z -n resources -p -o resources.cpp $(ECPPFLAGS) $(staticSources)

SUFFIXES=.ecpp .cpp

.ecpp.cpp:
	$(AM_V_GEN)$(ECPPC) -n `echo $<|$(SED) 's|^$(srcdir)/||; s|\.ecpp$$||'` $(ECPPFLAGS) -o $@ $<
.ecpp.deps:
	$(AM_V_GEN)$(ECPPC) -M $(ECPPFLAGS) $< | $(SED) '1s|\(.*\).cpp:|\1.cpp $@:|' > $@

-include $(ecppSources:.ecpp=.deps)
