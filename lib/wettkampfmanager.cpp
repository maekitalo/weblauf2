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

void WettkampfManager::putWettkampf(const Wettkampf& w)
{
    if (w.wid() == 0)
    {
        tntdb::Statement selwid = _ctx.impl().conn().prepareCached(R"SQL(
            select max(wet_wid)
              from wettkampf
             where wet_vid = :vid
        )SQL");

        tntdb::Statement ins = _ctx.impl().conn().prepareCached(R"SQL(
            insert into wettkampf
                (wet_vid, wet_wid, wet_name, wet_art, wet_sta_von, wet_sta_bis, wet_startzeit)
            values
                (:vid, :wid, :name, :art, :sta_von, :sta_bis, :startzeit)
        )SQL");

        unsigned wid = 0;
        selwid.set("vid", w.vid())
              .selectValue()
              .get(wid);

        ins.set("vid", w._vid)
           .set("wid", wid + 1)
           .set("name", w._name)
           .set("art", w._art)
           .set("sta_von", w._staVon)
           .set("sta_bis", w._staBis)
           .set("startzeit", w._startzeit)
           .execute();
    }
    else
    {
        tntdb::Statement upd = _ctx.impl().conn().prepareCached(R"SQL(
            update wettkampf
               set wet_name = :name,
                   wet_art = :art,
                   wet_sta_von = :staVon,
                   wet_sta_bis = :staBis,
                   wet_startzeit = :startzeit
             where wet_vid = :vid
               and wet_wid = :wid
        )SQL");

        upd.set("vid", w._vid)
           .set("wid", w._wid)
           .set("name", w._name)
           .set("art", w._art)
           .set("sta_von", w._staVon)
           .set("sta_bis", w._staBis)
           .set("startzeit", w._startzeit)
           .execute();
    }
}

void WettkampfManager::delWettkampf(unsigned vid, unsigned wid)
{
    tntdb::Statement del = _ctx.impl().conn().prepareCached(R"SQL(
        delete from wettkampf
         where wet_vid = :vid
           and wet_wid = :wid
    )SQL");

    del.set("vid", vid)
       .set("wid", wid)
       .execute();
}
