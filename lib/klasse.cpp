/*
 * Copyright (C) 2016 Tommi Maekitalo
 *
 */

#include <klasse.h>
#include <cxxtools/serializationinfo.h>

void operator>>= (const cxxtools::SerializationInfo& si, Klasse& k)
{
    si.getMember("ak") >>= k._ak;
    si.getMember("geschlecht") >>= k._geschlecht;
    si.getMember("alterVon") >>= k._alterVon;
    si.getMember("alterBis") >>= k._alterBis;
    si.getMember("prioritaet") >>= k._prioritaet;
    si.getMember("bezeichnung") >>= k._bezeichnung;
}

void operator<<= (cxxtools::SerializationInfo& si, const Klasse& k)
{
    si.addMember("ak") <<= k._ak;
    si.addMember("geschlecht") <<= k._geschlecht;
    si.addMember("alterVon") <<= k._alterVon;
    si.addMember("alterBis") <<= k._alterBis;
    si.addMember("prioritaet") <<= k._prioritaet;
    si.addMember("bezeichnung") <<= k._bezeichnung;
    si.setTypeName("Klasse");
}
