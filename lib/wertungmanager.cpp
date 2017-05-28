/*
 * Copyright (C) 2015 Tommi Maekitalo
 *
 */

#include "wertungmanager.h"

#include <managercontextimpl.h>

#include <tntdb/connection.h>
#include <tntdb/statement.h>
#include <tntdb/row.h>

#include <cxxtools/log.h>

log_define("weblauf.wertung.manager")

Wertung WertungManager::getWertung(unsigned vid, unsigned wid, unsigned rid)
{
    log_debug("getWertung(" << vid << ", " << wid << ", " << rid << ')');

    tntdb::Statement st = _ctx.impl().conn().prepareCached(R"SQL(
        select wer_rid, wer_name, wer_abhaengig, wer_urkunde, wer_preis
          from wertung
         where wer_vid = :vid
           and wer_wid = :wid
           and wer_rid = :rid
        )SQL");

    Wertung wertung;
    wertung._vid = vid;
    wertung._wid = wid;

    st.set("vid", vid)
      .set("wid", wid)
      .set("rid", rid)
      .selectRow()
      .get(wertung._rid)
      .get(wertung._name)
      .get(wertung._abhaengig)
      .get(wertung._urkunde)
      .get(wertung._preis);

    return wertung;
}

std::vector<Wertung> WertungManager::getWertungen(unsigned vid, unsigned wid)
{
    log_debug("getWertungen(" << vid << ", " << wid << ')');

    tntdb::Statement st = _ctx.impl().conn().prepareCached(R"SQL(
        select wer_rid, wer_name, wer_abhaengig, wer_urkunde, wer_preis
          from wertung
         where wer_vid = :vid
           and wer_wid = :wid
          order by wer_rid
        )SQL");

    st.set("vid", vid)
      .set("wid", wid);

    std::vector<Wertung> wertungen;

    for (auto r: st)
    {
        Wertung w;
        w._vid = vid;
        w._wid = wid;
        r.get(w._rid)
         .get(w._name)
         .get(w._abhaengig)
         .get(w._urkunde)
         .get(w._preis);
        wertungen.emplace_back(std::move(w));
    }

    log_debug(wertungen.size() << " Wertungen");

    return wertungen;
}

Wertungsgruppe WertungManager::getWertungsgruppe(unsigned vid, unsigned wid, unsigned gid)
{
    log_debug("getWertungsgruppe(" << vid << ", " << wid << ", " << gid << ')');

    Wertungsgruppe wertungsgruppe;

    tntdb::Statement st = _ctx.impl().conn().prepareCached(R"SQL(
        select wgr_name, wgw_rid
          from wgruppe
          left outer join wgruppewer
            on wgr_vid = wgw_vid
           and wgr_wid = wgw_wid
           and wgr_gid = wgw_gid
         where vid = :vid
           and wid = :wid
           and gid = :gid
        )SQL");

    st.set("vid", vid)
      .set("wid", wid)
      .set("gid", gid);

    wertungsgruppe._vid = vid;
    wertungsgruppe._wid = wid;
    wertungsgruppe._gid = gid;

    for (auto r: st)
    {
        r[0].get(wertungsgruppe._name);
        unsigned rid;
        if (r[1].get(rid))
            wertungsgruppe._rid.push_back(rid);
    }

    return wertungsgruppe;
}

std::vector<Wertungsgruppe> WertungManager::getWertungsgruppen(unsigned vid, unsigned wid)
{
    log_debug("getWertungsgruppen(" << vid << ", " << wid << ')');

    std::vector<Wertungsgruppe> wertungsgruppen;

    tntdb::Statement st = _ctx.impl().conn().prepareCached(R"SQL(
        select wgr_gid, wgr_name, wgw_rid
          from wgruppe
          left outer join wgruppewer
            on wgr_vid = wgw_vid
           and wgr_wid = wgw_wid
           and wgr_gid = wgw_gid
         where wgr_vid = :vid
           and wgr_wid = :wid
        )SQL");

    st.set("vid", vid)
      .set("wid", wid);

    unsigned gid = 0;

    for (auto r: st)
    {
        r[0].get(gid);

        if (wertungsgruppen.empty() || wertungsgruppen.back()._gid != gid)
        {
            wertungsgruppen.emplace_back();
            auto& w = wertungsgruppen.back();
            w._vid = vid;
            w._wid = wid;
            w._gid = gid;
        }

        auto& w = wertungsgruppen.back();
        r[1].get(w._name);

        unsigned rid;
        if (r[2].get(rid))
            w._rid.push_back(rid);
    }

    log_debug(wertungsgruppen.size() << " Wertungsgruppen");

    return wertungsgruppen;
}
