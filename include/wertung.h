#ifndef WERTUNG_H
#define WERTUNG_H

#include <string>
#include <cxxtools/string.h>

namespace cxxtools
{
  class SerializationInfo;
}

class WertungManager;

class Wertung
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, Wertung& v);
    friend void operator<<= (cxxtools::SerializationInfo& si, const Wertung& v);
    friend class WertungManager;

    unsigned _vid;
    unsigned _wid;
    unsigned _rid;
    cxxtools::String _name;
    unsigned _abhaengig;
    std::string _urkunde;
    double _preis;

public:
    Wertung()
      : _vid(0),
        _wid(0),
        _rid(0),
        _abhaengig(0),
        _preis(0)
    { }

    unsigned vid() const                         { return _vid; }
    unsigned wid() const                         { return _wid; }
    unsigned rid() const                         { return _rid; }
    const cxxtools::String& name() const         { return _name; }
    unsigned abhaengig() const                   { return _abhaengig; }
    const std::string& urkunde() const           { return _urkunde; }
    double preis() const                         { return _preis; }
};

#endif // WERTUNG_H
