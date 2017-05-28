/*
 * Copyright (C) 2017 Tommi Maekitalo
 *
 */

#ifndef TEILNEHMER_H
#define TEILNEHMER_H

#include <person.h>

namespace cxxtools
{
    class SerializationInfo;
}

class TeilnehemerManager;

class Teilnehmer : public Person
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, Teilnehmer& t);
    friend void operator<<= (cxxtools::SerializationInfo& si, const Teilnehmer& t);
    friend class TeilnehmerManager;

    unsigned _startnummer;

public:
    Teilnehmer()
        : _startnummer(0)
        { }

    unsigned startnummer() const                 { return _startnummer; }
};

#endif
