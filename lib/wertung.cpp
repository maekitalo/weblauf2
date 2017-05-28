#include <wertung.h>
#include <cxxtools/serializationinfo.h>

void operator>>= (const cxxtools::SerializationInfo& si, Wertung& w)
{
  si.getMember("vid") >>= w._vid;
  si.getMember("wid") >>= w._wid;
  si.getMember("rid") >>= w._rid;
  si.getMember("name") >>= w._name;
  si.getMember("abhaengig", w._abhaengig);
  si.getMember("urkunde") >>= w._urkunde;
  si.getMember("preis") >>= w._preis;
}

void operator<<= (cxxtools::SerializationInfo& si, const Wertung& w)
{
  si.addMember("vid") <<= w._vid;
  si.addMember("wid") <<= w._wid;
  si.addMember("rid") <<= w._rid;
  si.addMember("name") <<= w._name;
  si.addMember("abhaengig") <<= w._abhaengig;
  si.addMember("urkunde") <<= w._urkunde;
  si.addMember("preis") <<= w._preis;
}
