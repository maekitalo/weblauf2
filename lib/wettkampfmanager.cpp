/*
 * Copyright (C) 2015 Tommi Maekitalo
 *
 */

#include "wettkampfmanager.h"

#include <managercontextimpl.h>

#include <tntdb/statement.h>
#include <tntdb/row.h>
#include <tntdb/cxxtools/time.h>

#include <cxxtools/log.h>

log_define("weblauf.wettkampf.manager")

Wettkampf WettkampfManager::getWettkampf(unsigned vid, unsigned wid)
{
    log_debug("getWettkampf(" << vid << ", " << wid << ')');

    tntdb::Statement st = _ctx.impl().conn().prepareCached(R"SQL(
        select wet_wid, wet_name, wet_art, wet_sta_von, wet_sta_bis, wet_startzeit
          from wettkampf
         where wet_vid = :vid
           and wet_wid = :wid
        )SQL");

    Wettkampf wettkampf;
    wettkampf._vid = vid;

    st.set("vid", vid)
      .set("wid", wid)
      .selectRow()
      .get(wettkampf._wid)
      .get(wettkampf._name)
      .get(wettkampf._art)
      .get(wettkampf._staVon)
      .get(wettkampf._staBis)
      .get(wettkampf._startzeit);

    return wettkampf;
}

std::vector<Wettkampf> WettkampfManager::getWettkaempfe(unsigned vid)
{
    tntdb::Statement st = _ctx.impl().conn().prepareCached(R"SQL(
        select wet_wid, wet_name, wet_art, wet_sta_von, wet_sta_bis, wet_startzeit
          from wettkampf
         where wet_vid = :vid
          order by wet_wid
        )SQL");

    st.set("vid", vid);

    std::vector<Wettkampf> wettkaempfe;
    for (auto r: st)
    {
        wettkaempfe.resize(wettkaempfe.size() + 1);
        auto& w = wettkaempfe.back();
        w._vid = vid;
        r.get(w._wid)
         .get(w._name)
         .get(w._art)
         .get(w._staVon)
         .get(w._staBis)
         .get(w._startzeit);
    }

    log_debug(wettkaempfe.size() << " wettkaempfe found");

    return wettkaempfe;
}
