#ifndef WETTKAMPF_H
#define WETTKAMPF_H

#include <cxxtools/string.h>
#include <cxxtools/time.h>

namespace cxxtools
{
  class SerializationInfo;
}

struct Wettkampf
{
    unsigned vid;
    unsigned wid;
    cxxtools::String name;
    char art;
    unsigned staVon;
    unsigned staBis;
    cxxtools::Time startzeit;

    Wettkampf()
        : vid(0),
          wid(0),
          art(' '),
          staVon(0),
          staBis(0)
        { }
};

void operator>>= (const cxxtools::SerializationInfo& si, Wettkampf& w);

void operator<<= (cxxtools::SerializationInfo& si, const Wettkampf& w);

#endif // WETTKAMPF_H
