ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I$(top_srcdir)/include

bin_PROGRAMS = weblauf2

lib_LTLIBRARIES = libweblauf.la

libweblauf_la_SOURCES = \
	lib/klasse.cpp \
	lib/managercontext.cpp \
	lib/person.cpp \
	lib/table/Query.cpp \
	lib/table/Response.cpp \
	lib/teilnehmer.cpp \
	lib/teilnehmermanager.cpp \
	lib/veranstaltung.cpp \
	lib/veranstaltungmanager.cpp \
	lib/weblaufmanager.cpp \
	lib/wettkampfmanager.cpp \
	lib/wettkampf.cpp \
	lib/wertung.cpp \
	lib/wertungsgruppe.cpp \
	lib/wertungmanager.cpp

libweblauf_la_LIBADD = -lcxxtools -ltntdb

ecppSources = \
	action/veranstaltung/del.ecpp \
	action/veranstaltung/save.ecpp \
	action/wettkampf/del.ecpp \
	action/wettkampf/save.ecpp \
	action/wertung/del.ecpp \
	action/wertung/save.ecpp \
	actionmain.ecpp \
	json/ak.ecpp \
	json/veranstaltung.ecpp \
	json/veranstaltungen.ecpp \
	json/wettkampf.ecpp \
	json/wettkaempfe.ecpp \
	json/wertungen.ecpp \
	json/wertung.ecpp \
	json/personen.ecpp \
	json/teilnehmer.ecpp \
	webmain.ecpp

staticSources = \
	resources/weblauf2.css \
	resources/dropdown.css \
	resources/js/main.js \
	resources/js/teilnehmer.js \
	resources/js/veranstaltung.js \
	resources/js/weblauf.js \
	resources/js/wettkampf.js \
	resources/js/wertung.js \
	resources/html/teilnehmer.html \
	resources/html/veranstaltung.html \
	resources/html/veranstaltung/edit.html \
	resources/html/wettkampf.html \
	resources/html/wertung.html

weblauf2_SOURCES = \
	action.cpp \
	configuration.cpp \
	main.cpp \
	$(ecppSources)

nodist_weblauf2_SOURCES = \
	resources.cpp \
	modules.cpp

weblauf2_LDFLAGS = -lcxxtools -ltntnet
weblauf2_LDADD = $(top_builddir)/libweblauf.la

include_HEADERS = \
	actionreply.h \
	configuration.h \
	include/klasse.h \
	include/person.h \
	include/table/Query.h \
	include/table/Response.h \
	include/teilnehmer.h \
	include/teilnehmermanager.h \
	include/veranstaltung.h \
	include/veranstaltungmanager.h \
	include/weblaufmanager.h \
	include/wettkampf.h \
	include/wettkampfmanager.h \
	include/wertung.h \
	include/wertungmanager.h \
	noty.h

nobase_dist_noinst_DATA = $(staticSources)

CLEANFILES = $(ecppSources:.ecpp=.cpp) $(ecppSources:.ecpp=.deps) resources.cpp modules.cpp

#
# Rules for tntnet applications
#
ECPPFLAGS=-I$(srcdir)

resources.cpp: $(staticSources) Makefile.am
	$(AM_V_GEN)$(ECPPC) -bb -z -n resources -p -r resources/ -o resources.cpp $(ECPPFLAGS) $(staticSources)

modules.cpp: Makefile.am package.json
	sh -c "find node_modules/ -type f -a ! -name '\.*' -a ! -name '*.md' -a ! -name '*.markdown' -a ! -name '*.scss' -a ! -name package.json -a ! -name '*.txt' -a ! -name '*.map'|egrep -v 'tests|demos' | xargs $(ECPPC) -bb -z -n modules -p -r node_modules/ -o $(top_builddir)/modules.cpp"

SUFFIXES=.ecpp .cpp

.ecpp.cpp:
	$(AM_V_GEN)$(ECPPC) -n `echo $<|$(SED) 's|^$(srcdir)/||; s|\.ecpp$$||'` $(ECPPFLAGS) -o $@ $<
.ecpp.deps:
	$(AM_V_GEN)$(ECPPC) -M $(ECPPFLAGS) $< | $(SED) '1s|\(.*\).cpp:|\1.cpp $@:|' > $@

-include $(ecppSources:.ecpp=.deps)
