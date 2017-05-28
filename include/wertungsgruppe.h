/*
 * Copyright (C) 2015 Tommi Maekitalo
 *
 */

#ifndef WERTUNGSGRUPPE_H
#define WERTUNGSGRUPPE_H

#include <cxxtools/string.h>
#include <vector>

namespace cxxtools
{
  class SerializationInfo;
}

class Wertungsgruppe
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, Wertungsgruppe& g);
    friend void operator<<= (cxxtools::SerializationInfo& si, const Wertungsgruppe& g);
    friend class WertungManager;

    unsigned _vid;
    unsigned _wid;
    unsigned _gid;
    cxxtools::String _name;
    std::vector<unsigned> _rid;

public:
    unsigned vid() const                         { return _vid; }
    unsigned wid() const                         { return _wid; }
    unsigned gid() const                         { return _gid; }
    const cxxtools::String& name() const         { return _name; }
    const std::vector<unsigned>& rid() const     { return _rid; }
};

#endif // WERTUNGSGRUPPE_H

