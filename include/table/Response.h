#ifndef FRAME_TABLERESPONSE_H
#define FRAME_TABLERESPONSE_H

#include <cxxtools/serializationinfo.h>
#include <table/Query.h>
#include <utility>
#include <string>

namespace table
{

class Query;

std::vector<unsigned> apply(const Query& query, const cxxtools::SerializationInfo& data, unsigned& recordsFiltered);

template <typename ObjectType>
class Response
{
public:
    typedef std::vector<ObjectType> TableType;

private:
    unsigned _draw;
    unsigned _recordsTotal;
    unsigned _recordsFiltered;
    TableType _data;
    std::string _error;

public:
    friend
    void operator>>= (const cxxtools::SerializationInfo& si, Response& tableResponse)
    {
        si.getMember("draw") >>= tableResponse._draw;
        si.getMember("recordsTotal") >>= tableResponse._recordsTotal;
        si.getMember("recordsFiltered") >>= tableResponse._recordsFiltered;
        si.getMember("data") >>= tableResponse._data;
        si.getMember("error") >>= tableResponse._error;
    }

    friend
    void operator<<= (cxxtools::SerializationInfo& si, const Response& tableResponse)
    {
        si.addMember("draw") <<= tableResponse._draw;
        si.addMember("recordsTotal") <<= tableResponse._recordsTotal;
        si.addMember("recordsFiltered") <<= tableResponse._recordsFiltered;
        si.addMember("data") <<= tableResponse._data;
        si.addMember("error") <<= tableResponse._error;
    }

    Response()
        : _draw(0),
          _recordsTotal(0),
          _recordsFiltered(0)
        { }

    explicit Response(TableType&& data)
        : _draw(0),
          _recordsTotal(0),
          _recordsFiltered(0),
          _data(data)
        { }

    unsigned draw() const              { return _draw; }
    unsigned recordsTotal() const      { return _recordsTotal; }
    unsigned recordsFiltered() const   { return _recordsFiltered; }
    const TableType& data() const      { return _data; }
    const std::string& error() const   { return _error; }

    void draw(unsigned v)              { _draw = v; }
    void recordsTotal(unsigned v)      { _recordsTotal = v; }
    void recordsFiltered(unsigned v)   { _recordsFiltered = v; }
    void data(const TableType& v)      { _data = v; }
    TableType& data()                  { return _data; }
    void error(const std::string& v)   { _error = v; }

    // Apply filtering and sorting to data
    void apply(const Query& query)
    {
        cxxtools::SerializationInfo si;
        si <<= _data;
        std::vector<unsigned> idx = table::apply(query, si, _recordsFiltered);
        recordsTotal(data().size());

        TableType newData;
        newData.reserve(idx.size());
        for (unsigned n = 0; n < idx.size(); ++n)
            newData.push_back(std::move(_data[idx[n]]));
        _data.swap(newData);
    }

    // Optimized version - pass possibly cached serialization info to appy
    // method to save the step to serialize the data first.

    void apply(const Query& query, const cxxtools::SerializationInfo& si)
    {
        std::vector<unsigned> idx = table::apply(query, si, _recordsFiltered);
        recordsTotal(data().size());

        TableType newData;
        newData.reserve(idx.size());
        for (unsigned n = 0; n < idx.size(); ++n)
            newData.push_back(std::move(_data[idx[n]]));
        _data.swap(newData);
    }

};

}

#endif
