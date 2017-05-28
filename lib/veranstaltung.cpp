#include <veranstaltung.h>
#include <cxxtools/serializationinfo.h>

void operator>>= (const cxxtools::SerializationInfo& si, Veranstaltung& v)
{
  si.getMember("vid") >>= v._vid;
  si.getMember("name") >>= v._name;
  si.getMember("datum") >>= v._datum;
  si.getMember("ort") >>= v._ort;
  si.getMember("logo") >>= v._logo;
}

void operator<<= (cxxtools::SerializationInfo& si, const Veranstaltung& v)
{
  si.setTypeName("Veranstaltung");

  si.addMember("vid") <<= v._vid;
  si.addMember("name") <<= v._name;
  si.addMember("datum") <<= v._datum;
  si.addMember("ort") <<= v._ort;
  si.addMember("logo") <<= v._logo;
}
