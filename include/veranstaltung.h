/*
 * Copyright (C) 2010 Tommi Maekitalo
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * is provided AS IS, WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, and
 * NON-INFRINGEMENT.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */

#ifndef VERANSTALTUNG_H
#define VERANSTALTUNG_H

#include <string>
#include <cxxtools/string.h>
#include <cxxtools/date.h>
#include <cxxtools/clock.h>

namespace cxxtools
{
  class SerializationInfo;
}

struct Veranstaltung
{
    unsigned vid;
    cxxtools::String name;
    cxxtools::Date datum;
    cxxtools::String ort;
    std::string logo;

    bool isNew() const
    { return vid == 0; }

    Veranstaltung()
        : vid(0),
          datum(cxxtools::Clock::getLocalTime().date())
        { }
};

void operator>>= (const cxxtools::SerializationInfo& si, Veranstaltung& v);

void operator<<= (cxxtools::SerializationInfo& si, const Veranstaltung& v);

#endif // VERANSTALTUNG_H
