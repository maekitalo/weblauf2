/*
 * Copyright (C) 2016 Tommi Maekitalo
 *
 */

#include <person.h>
#include <cxxtools/serializationinfo.h>

void operator>>= (const cxxtools::SerializationInfo& si, Person& p)
{
    si.getMember("pid") >>= p._pid;
    si.getMember("nachname") >>= p._nachname;
    si.getMember("vorname") >>= p._vorname;
    si.getMember("verein") >>= p._verein;
    si.getMember("geschlecht") >>= p._geschlecht;
    si.getMember("jahrgang") >>= p._jahrgang;
    si.getMember("strasse") >>= p._strasse;
    si.getMember("plz") >>= p._plz;
    si.getMember("ort") >>= p._ort;
    si.getMember("land") >>= p._land;
    si.getMember("nationalitaet") >>= p._nationalitaet;
}

void operator<<= (cxxtools::SerializationInfo& si, const Person& p)
{
    si.addMember("pid") <<= p._pid;
    si.addMember("nachname") <<= p._nachname;
    si.addMember("vorname") <<= p._vorname;
    si.addMember("verein") <<= p._verein;
    si.addMember("geschlecht") <<= p._geschlecht;
    si.addMember("jahrgang") <<= p._jahrgang;
    si.addMember("strasse") <<= p._strasse;
    si.addMember("plz") <<= p._plz;
    si.addMember("ort") <<= p._ort;
    si.addMember("land") <<= p._land;
    si.addMember("nationalitaet") <<= p._nationalitaet;
}
