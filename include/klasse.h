/*
 * Copyright (C) 2016 Tommi Maekitalo
 *
 */

#ifndef KLASSE_H
#define KLASSE_H

#include <string>

namespace cxxtools
{
  class SerializationInfo;
}

class WeblaufManager;

class Klasse
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, Klasse& k);
    friend void operator<<= (cxxtools::SerializationInfo& si, const Klasse& k);
    friend class WeblaufManager;

    std::string _ak;
    char _geschlecht;
    unsigned _alterVon;
    unsigned _alterBis;
    unsigned short _prioritaet;
    std::string _bezeichnung;

public:
    const std::string& ak() const             { return _ak; }
    char geschlecht() const                   { return _geschlecht; }
    unsigned alterVon() const                 { return _alterVon; }
    unsigned alterBis() const                 { return _alterBis; }
    unsigned short prioritaet() const         { return _prioritaet; }
    const std::string& bezeichnung() const    { return _bezeichnung; }
};

#endif
