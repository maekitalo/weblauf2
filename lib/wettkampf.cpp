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

#include <wettkampf.h>
#include <cxxtools/serializationinfo.h>

void operator>>= (const cxxtools::SerializationInfo& si, Wettkampf& w)
{
    si.getMember("vid") >>= w._vid;
    try
    {
        si.getMember("wid") >>= w._wid;
    }
    catch (const std::exception&)
    {
        w._wid = 0;
    }
    si.getMember("name") >>= w._name;
    si.getMember("art") >>= w._art;
    si.getMember("staVon") >>= w._staVon;
    si.getMember("staBis") >>= w._staBis;
    si.getMember("startzeit") >>= w._startzeit;
}

void operator<<= (cxxtools::SerializationInfo& si, const Wettkampf& w)
{
    si.addMember("vid") <<= w._vid;
    si.addMember("wid") <<= w._wid;
    si.addMember("name") <<= w._name;
    si.addMember("art") <<= w._art;
    si.addMember("staVon") <<= w._staVon;
    si.addMember("staBis") <<= w._staBis;
    si.addMember("startzeit") <<= w._startzeit;
}
