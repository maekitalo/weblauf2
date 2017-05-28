/*
 * Copyright (C) 2016 Tommi Maekitalo
 *
 */

#include "teilnehmermanager.h"
#include <managercontextimpl.h>

#include <tntdb/statement.h>
#include <tntdb/row.h>

#include <cxxtools/regex.h>
#include <cxxtools/convert.h>
#include <cxxtools/log.h>

log_define("teilnehmer.manager")

std::vector<Person> TeilnehmerManager::searchPerson(unsigned vid, const std::string& s)
{
    static cxxtools::Regex isnumber("^[0-9]+$");

    tntdb::Statement sel;

    if (isnumber.match(s))
    {
        log_debug("suche nach Startnummer <" << s << '>');

        sel = _ctx.impl().conn().prepareCached(R"SQL(
            select per_pid, per_nachname, per_vorname, per_verein, per_geschlecht,
                   per_jahrgang, per_strasse, per_plz, per_ort, per_land,
                   per_nationalitaet
              from person
              left outer join startnummer
                on sta_pid = per_pid
               and sta_vid = :vid
             where per_nachname like :search || '%'
                or per_vorname like :search || '%'
                or sta_snr = :startnummer
            )SQL");

        sel.set("vid", vid)
           .set("startnummer", cxxtools::convert<unsigned>(s));
    }
    else
    {
        log_debug("suche nach Name <" << s << '>');

        sel = _ctx.impl().conn().prepareCached(R"SQL(
            select per_pid, per_nachname, per_vorname, per_verein, per_geschlecht,
                   per_jahrgang, per_strasse, per_plz, per_ort, per_land,
                   per_nationalitaet
              from person
             where per_nachname like :search || '%'
                or per_vorname like :search || '%'
            )SQL");
    }

    std::vector<Person> personen;

    sel.set("search", s);

    for (auto r: sel)
    {
        log_debug("lese person");

        Person p;
        r.get(p._pid)
         .get(p._nachname)
         .get(p._vorname)
         .get(p._verein)
         .get(p._geschlecht)
         .get(p._jahrgang)
         .get(p._strasse)
         .get(p._plz)
         .get(p._ort)
         .get(p._land)
         .get(p._nationalitaet);

        personen.emplace_back(std::move(p));
    }

    log_debug(personen.size() << " personen gefunden");

    return personen;
}

std::vector<Person> TeilnehmerManager::getPersonen()
{
    tntdb::Statement sel = _ctx.impl().conn().prepareCached(R"SQL(
        select per_pid, per_nachname, per_vorname, per_verein, per_geschlecht,
               per_jahrgang, per_strasse, per_plz, per_ort, per_land,
               per_nationalitaet
          from person
        )SQL");

    std::vector<Person> personen;

    for (auto r: sel)
    {
        Person p;
        r.get(p._pid)
         .get(p._nachname)
         .get(p._vorname)
         .get(p._verein)
         .get(p._geschlecht)
         .get(p._jahrgang)
         .get(p._strasse)
         .get(p._plz)
         .get(p._ort)
         .get(p._land)
         .get(p._nationalitaet);

        personen.emplace_back(std::move(p));
    }

    return personen;
}

std::vector<Teilnehmer> TeilnehmerManager::getPersonen(unsigned vid)
{
    tntdb::Statement sel = _ctx.impl().conn().prepareCached(R"SQL(
        select per_pid, per_nachname, per_vorname, per_verein, per_geschlecht,
               per_jahrgang, per_strasse, per_plz, per_ort, per_land,
               per_nationalitaet, sta_snr
          from person
          left outer join startnummer
            on per_pid = sta_pid
           and sta_vid = :vid
        )SQL");

    sel.set("vid", vid);

    std::vector<Teilnehmer> teilnehmer;

    for (auto r: sel)
    {
        Teilnehmer p;
        bool isnull;
        r.get(p._pid)
         .get(p._nachname)
         .get(p._vorname)
         .get(p._verein)
         .get(p._geschlecht)
         .get(p._jahrgang)
         .get(p._strasse)
         .get(p._plz)
         .get(p._ort)
         .get(p._land)
         .get(p._nationalitaet)
         .get(p._startnummer, isnull);

        teilnehmer.emplace_back(std::move(p));
    }

    return teilnehmer;
}

std::vector<Teilnehmer> TeilnehmerManager::getTeilnehmer(unsigned vid)
{
    tntdb::Statement sel = _ctx.impl().conn().prepareCached(R"SQL(
        select per_pid, per_nachname, per_vorname, per_verein, per_geschlecht,
               per_jahrgang, per_strasse, per_plz, per_ort, per_land,
               per_nationalitaet, sta_snr
          from person
          join startnummer
            on per_pid = sta_pid
         where sta_vid = :vid
        )SQL");

    sel.set("vid", vid);

    std::vector<Teilnehmer> teilnehmer;

    for (auto r: sel)
    {
        Teilnehmer p;
        r.get(p._pid)
         .get(p._nachname)
         .get(p._vorname)
         .get(p._verein)
         .get(p._geschlecht)
         .get(p._jahrgang)
         .get(p._strasse)
         .get(p._plz)
         .get(p._ort)
         .get(p._land)
         .get(p._nationalitaet)
         .get(p._startnummer);

        teilnehmer.emplace_back(std::move(p));
    }

    return teilnehmer;
}
