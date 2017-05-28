#include <wertungsgruppe.h>
#include <cxxtools/serializationinfo.h>

void operator>>= (const cxxtools::SerializationInfo& si, Wertungsgruppe& g)
{
  si.getMember("vid") >>= g._vid;
  si.getMember("wid") >>= g._wid;
  si.getMember("gid") >>= g._gid;
  si.getMember("name") >>= g._name;
  si.getMember("rid") >>= g._rid;
}

void operator<<= (cxxtools::SerializationInfo& si, const Wertungsgruppe& g)
{
  si.addMember("vid") <<= g._vid;
  si.addMember("wid") <<= g._wid;
  si.addMember("gid") <<= g._gid;
  si.addMember("name") <<= g._name;
  si.addMember("rid") <<= g._rid;
}
