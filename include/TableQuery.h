#ifndef FRAME_TABLEQUERY_H
#define FRAME_TABLEQUERY_H

#include <string>
#include <vector>
#include <cxxtools/regex.h>

namespace cxxtools
{
    class SerializationInfo;
    class QueryParams;
}

class TableQuery
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, TableQuery& tableQuery);
    friend void operator<<= (cxxtools::SerializationInfo& si, const TableQuery& tableQuery);

public:
    class Search
    {
        friend void operator>>= (const cxxtools::SerializationInfo& si, Search& search);
        friend void operator<<= (cxxtools::SerializationInfo& si, const Search& search);

        std::string _value;
        bool _regex;
        mutable cxxtools::Regex _re;

    public:
        const std::string& value() const { return _value; }
        bool regex() const               { return _regex; }
        bool match(const std::string& value) const;
    };

    class Column
    {
        friend void operator>>= (const cxxtools::SerializationInfo& si, Column& column);
        friend void operator<<= (cxxtools::SerializationInfo& si, const Column& column);

        std::string _data;
        std::string _name;
        bool _searchable;
        bool _orderable;
        Search _search;

    public:
        const std::string& data() const  { return _data; }
        const std::string& name() const  { return _name; }
        bool searchable() const          { return _searchable; }
        bool orderable() const           { return _orderable; }
        const Search& search() const     { return _search; }
    };

    class Order
    {
        friend void operator>>= (const cxxtools::SerializationInfo& si, Order& order);
        friend void operator<<= (cxxtools::SerializationInfo& si, const Order& order);

        unsigned _column;
        bool _asc;

    public:
        unsigned column() const     { return _column; }
        bool asc() const            { return _asc; }
    };

private:
    bool _draw;
    std::vector<Column> _columns;
    std::vector<Order> _order;
    unsigned _start;
    unsigned _length;
    Search _search;

public:
    typedef std::vector<Column>::const_iterator const_iterator;
    typedef std::vector<Column>::value_type value_type;

    bool draw() const                           { return _draw; }
    const_iterator begin()                      { return _columns.begin(); }
    const_iterator end()                        { return _columns.end(); }
    const std::vector<Column>& columns() const  { return _columns; }
    const std::vector<Order>& order() const     { return _order; }
    unsigned start() const                      { return _start; }
    unsigned length() const                     { return _length; }
    const Search& search() const                { return _search; }

    int compare(const cxxtools::SerializationInfo& row1, const cxxtools::SerializationInfo& row2) const;
};

void operator<<= (TableQuery& q, const cxxtools::QueryParams& p);

#endif
