#include <wertung.h>
#include <cxxtools/serializationinfo.h>

template <typename T>
void tryGet(const cxxtools::SerializationInfo& si, const std::string& member, T& value)
{
    try
    {
        si.getMember(member) >>= value;
    }
    catch (const std::exception&)
    {
    }
}

void operator>>= (const cxxtools::SerializationInfo& si, Wertung& w)
{
    si.getMember("vid") >>= w._vid;
    si.getMember("wid") >>= w._wid;
    tryGet(si, "rid", w._rid);
    si.getMember("name") >>= w._name;
    tryGet(si, "abhaengig", w._abhaengig);
    si.getMember("urkunde") >>= w._urkunde;
    tryGet(si, "preis", w._preis);
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
