/*
 * Copyright (C) 2017 Tommi Maekitalo
 *
 */

#include <teilnehmer.h>
#include <cxxtools/serializationinfo.h>

void operator>>= (const cxxtools::SerializationInfo& si, Teilnehmer& p)
{
    si >>= static_cast<Person&>(p);
    if (!si.getMember("startnummer", p._startnummer))
        p._startnummer = 0;
}

void operator<<= (cxxtools::SerializationInfo& si, const Teilnehmer& p)
{
    si <<= static_cast<const Person&>(p);
    si.addMember("startnummer") <<= p._startnummer;
}
