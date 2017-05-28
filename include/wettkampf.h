#ifndef WETTKAMPF_H
#define WETTKAMPF_H

#include <cxxtools/string.h>
#include <cxxtools/time.h>

namespace cxxtools
{
  class SerializationInfo;
}

class WettkampfManager;
class Wettkampf
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, Wettkampf& w);

    friend void operator<<= (cxxtools::SerializationInfo& si, const Wettkampf& w);
    friend class WettkampfManager;

    unsigned _vid;
    unsigned _wid;
    cxxtools::String _name;
    char _art;
    unsigned _staVon;
    unsigned _staBis;
    cxxtools::Time _startzeit;

public:

    Wettkampf()
        : _vid(0),
          _wid(0),
          _art(' '),
          _staVon(0),
          _staBis(0)
        { }

    unsigned vid() const                         { return _vid; }
    unsigned wid() const                         { return _wid; }
    const cxxtools::String& name() const         { return _name; }
    char art() const                             { return _art; }
    unsigned staVon() const                      { return _staVon; }
    unsigned staBis() const                      { return _staBis; }
    cxxtools::Time startzeit() const             { return _startzeit; }
};

#endif // WETTKAMPF_H
