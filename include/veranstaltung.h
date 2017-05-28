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

class VeranstaltungManager;

class Veranstaltung
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, Veranstaltung& v);
    friend void operator<<= (cxxtools::SerializationInfo& si, const Veranstaltung& v);
    friend class VeranstaltungManager;

    unsigned _vid;
    cxxtools::String _name;
    cxxtools::Date _datum;
    cxxtools::String _ort;
    std::string _logo;

public:
    Veranstaltung()
        : _vid(0),
          _datum(cxxtools::Clock::getLocalTime().date())
        { }

    unsigned vid() const                         { return _vid; }
    const cxxtools::String& name() const         { return _name; }
    cxxtools::Date datum() const                 { return _datum; }
    const cxxtools::String& ort() const          { return _ort; }
    const std::string& logo() const              { return _logo; }
    bool isNew() const                           { return _vid == 0; }
};

#endif // VERANSTALTUNG_H
