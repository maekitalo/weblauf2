#ifndef WERTUNG_H
#define WERTUNG_H

#include <string>
#include <cxxtools/string.h>

namespace cxxtools
{
  class SerializationInfo;
}

struct Wertung
{
    static const unsigned nullrid = static_cast<unsigned>(-1);

    unsigned vid;
    unsigned wid;
    unsigned rid;
    cxxtools::String name;
    unsigned abhaengig;
    std::string urkunde;
    unsigned preis; // in cents

    Wertung()
      : vid(0),
        wid(0),
        rid(0),
        abhaengig(0)
    { }

};

void operator>>= (const cxxtools::SerializationInfo& si, Wertung& v);

void operator<<= (cxxtools::SerializationInfo& si, const Wertung& v);

#endif // WERTUNG_H
