#include <table/Response.h>
#include <table/Query.h>

#include <cxxtools/json.h>
#include <algorithm>

namespace table
{

std::vector<unsigned> apply(const Query& query, const cxxtools::SerializationInfo& data, unsigned& recordsFiltered)
{
    std::vector<unsigned> ret;

    for (unsigned rownum = 0; rownum < data.memberCount(); ++rownum)
    {
        auto row = data.getMember(rownum);
        bool found = false;
        for (unsigned colnum = 0; colnum < query.columns().size(); ++colnum)
        {
            if (!query.columns()[colnum].searchable())
                continue;

            std::string value;
            row.getMember(query.columns()[colnum].data()) >>= value;

            // global search - as long as the text is globally not found we continue searching for it
            if (!found)
                found = query.search().match(value);

            // column search - if we find one non match, we break the loop since
            // this row is no candidate any more
            if (colnum < query.columns().size()
                    && !query.columns()[colnum].search().match(value))
            {
                found = false;
                break;
            }
        }

        if (found)
            ret.push_back(rownum);
    }

    recordsFiltered = ret.size();

    std::sort(ret.begin(), ret.end(), [&] (unsigned idx1, unsigned idx2) -> bool
        {
            int c = query.compare(data.getMember(idx1), data.getMember(idx2));
            return c < 0;
        });

    if (ret.size() > query.start() + query.length())
        ret.erase(ret.begin() + query.start() + query.length(), ret.end());

    if (ret.size() > query.start())
        ret.erase(ret.begin(), ret.begin() + query.start());

    return ret;
}

}
