/*
 * Copyright (C) 2016 Tommi Maekitalo
 *
 */

#ifndef PERSON_H
#define PERSON_H

#include <cxxtools/string.h>

namespace cxxtools
{
    class SerializationInfo;
}

class TeilnehemerManager;

class Person
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, Person& p);
    friend void operator<<= (cxxtools::SerializationInfo& si, const Person& p);
    friend class TeilnehmerManager;

    unsigned _pid;
    cxxtools::String _nachname;
    cxxtools::String _vorname;
    cxxtools::String _verein;
    char _geschlecht;
    unsigned _jahrgang;
    cxxtools::String _strasse;
    cxxtools::String _plz;
    cxxtools::String _ort;
    cxxtools::String _land;
    cxxtools::String _nationalitaet;

public:
    unsigned pid() const                         { return _pid; }
    const cxxtools::String& nachname() const     { return _nachname; }
    const cxxtools::String& vorname() const      { return _vorname; }
    const cxxtools::String& verein() const       { return _verein; }
    char geschlecht() const                      { return _geschlecht; }
    unsigned jahrgang() const                    { return _jahrgang; }
    const cxxtools::String& strasse() const      { return _strasse; }
    const cxxtools::String& plz() const          { return _plz; }
    const cxxtools::String& ort() const          { return _ort; }
    const cxxtools::String& land() const         { return _land; }
    const cxxtools::String& nationalitaet() const{ return _nationalitaet; }

    bool maennlich() const   { return _geschlecht == 'M'; }
    bool weiblich() const    { return _geschlecht == 'W'; }
};

#endif
