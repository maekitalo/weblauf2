#include <table/Query.h>

#include <cxxtools/serializationinfo.h>
#include <cxxtools/serializationerror.h>
#include <cxxtools/query_params.h>
#include <cxxtools/log.h>

#include <algorithm>

log_define("table.Query")

namespace table
{

static int compareValues(const cxxtools::SerializationInfo& col1, const cxxtools::SerializationInfo& col2)
{
    if (col1.isNull())
    {
        return col2.isNull() ? 0 : -1;
    }
    else if (col1.isBool())
    {
        if (col2.isNull())
            return 1;

        if (!col2.isBool())
            return -1;

        bool value1;
        bool value2;
        col1 >>= value1;
        col2 >>= value2;
        return value1 == value2 ? 0
             : value1 ? 1 : -1;
    }
    else if (col1.isInt())
    {
        if (col2.isNull() || col2.isBool())
            return 1;

        if (!col2.isInt())
            return -1;

        cxxtools::SerializationInfo::int_type value1;
        cxxtools::SerializationInfo::int_type value2;
        col1 >>= value1;
        col2 >>= value2;
        return value1 < value2 ? -1
             : value1 > value2 ? 1
             : 0;
    }
    else if (col1.isUInt())
    {
        if (col2.isNull() || col2.isBool() || col2.isInt())
            return 1;

        if (!col2.isUInt())
            return -1;

        cxxtools::SerializationInfo::unsigned_type value1;
        cxxtools::SerializationInfo::unsigned_type value2;
        col1 >>= value1;
        col2 >>= value2;
        return value1 < value2 ? -1
             : value1 > value2 ? 1
             : 0;
    }
    else if (col1.isFloat() || col1.isDouble() || col1.isLongDouble())
    {
        if (col2.isNull() || col2.isBool() || col2.isInt() || col2.isUInt())
            return 1;

        if (!col2.isFloat() && !col2.isDouble() && !col2.isLongDouble())
            return -1;

        long double value1;
        long double value2;
        col1 >>= value1;
        col2 >>= value2;
        return value1 < value2 ? -1
             : value1 > value2 ? 1
             : 0;
    }

    cxxtools::String value1;
    cxxtools::String value2;
    col1 >>= value1;
    col2 >>= value2;
    int c = value1.compare(value2);
    return c;
}

int Query::compare(const cxxtools::SerializationInfo& row1, const cxxtools::SerializationInfo& row2) const
{
    for (auto o: _order)
    {
        const cxxtools::SerializationInfo& col1 = row1.getMember(_columns[o.column()].data());
        const cxxtools::SerializationInfo& col2 = row2.getMember(_columns[o.column()].data());
        int c = compareValues(col1, col2);
        if (c != 0)
            return o.asc() ? c : -c;
    }

    return 0;
}

void operator>>= (const cxxtools::SerializationInfo& si, Query& tableQuery)
{
    si.getMember("draw") >>= tableQuery._draw;
    si.getMember("columns") >>= tableQuery._columns;
    si.getMember("order") >>= tableQuery._order;
    si.getMember("start") >>= tableQuery._start;
    si.getMember("length") >>= tableQuery._length;
    si.getMember("search") >>= tableQuery._search;
    for (auto o: tableQuery._order)
        if (o.column() >= tableQuery._columns.size())
            throw cxxtools::SerializationError("invalid ordering");
}

void operator<<= (cxxtools::SerializationInfo& si, const Query& tableQuery)
{
    si.addMember("draw") <<= tableQuery._draw;
    si.addMember("columns") <<= tableQuery._columns;
    si.addMember("order") <<= tableQuery._order;
    si.addMember("start") <<= tableQuery._start;
    si.addMember("length") <<= tableQuery._length;
    si.addMember("search") <<= tableQuery._search;
}

bool Query::Search::match(const std::string& value) const
{
    if (_value.empty())
        return true;

    if (_regex)
    {
        try
        {
            if (_re.empty())
                _re = cxxtools::Regex(_value, REG_EXTENDED|REG_ICASE);
        }
        catch (const std::exception&)
        {
            return false;
        }

        return _re.match(value);
    }
    else
    {
        auto it = std::search(
            value.begin(), value.end(),
            _value.begin(), _value.end(),
            [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
          );
        return it != value.end();
    }
}

void operator>>= (const cxxtools::SerializationInfo& si, Query::Search& search)
{
    si.getMember("value") >>= search._value;
    si.getMember("regex") >>= search._regex;
}

void operator<<= (cxxtools::SerializationInfo& si, const Query::Search& search)
{
    si.addMember("value") <<= search._value;
    si.addMember("regex") <<= search._regex;
}

void operator>>= (const cxxtools::SerializationInfo& si, Query::Column& column)
{
    si.getMember("data") >>= column._data;
    si.getMember("name") >>= column._name;
    si.getMember("searchable") >>= column._searchable;
    si.getMember("orderable") >>= column._orderable;
    si.getMember("search") >>= column._search;
}

void operator<<= (cxxtools::SerializationInfo& si, const Query::Column& column)
{
    si.addMember("data") <<= column._data;
    si.addMember("name") <<= column._name;
    si.addMember("searchable") <<= column._searchable;
    si.addMember("orderable") <<= column._orderable;
    si.addMember("search") <<= column._search;
}

void operator>>= (const cxxtools::SerializationInfo& si, Query::Order& order)
{
    std::string dir;
    si.getMember("column") >>= order._column;
    si.getMember("dir") >>= dir;
    order._asc = (dir == "asc");
}

void operator<<= (cxxtools::SerializationInfo& si, const Query::Order& order)
{
    si.addMember("column") <<= order._column;
    si.addMember("dir") <<= (order._asc ? "asc" : "desc");
}

void operator<<= (Query& q, const cxxtools::QueryParams& p)
{
    log_debug("convert query params " << p.getUrl());
    cxxtools::SerializationInfo si;
    si <<= p;
    log_debug(si);
    si >>= q;
}

}
