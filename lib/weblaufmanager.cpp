/*
 * Copyright (C) 2016 Tommi Maekitalo
 *
 */

#include "weblaufmanager.h"
#include <managercontextimpl.h>

#include <tntdb/connection.h>
#include <tntdb/statement.h>
#include <tntdb/row.h>

std::vector<std::string> WeblaufManager::getAkStr()
{
    tntdb::Statement sel = _ctx.impl().conn().prepareCached(R"SQL(
        select kls_ak
          from klasse
        )SQL");

    std::vector<std::string> ak;
    for (auto r: sel)
    {
        ak.emplace_back();
        r.get(ak.back());
    }

    return ak;
}

std::vector<Klasse> WeblaufManager::getAk()
{
    tntdb::Statement sel = _ctx.impl().conn().prepareCached(R"SQL(
        select kls_ak, kls_geschlecht, kls_alter_von, kls_alter_bis,
               kls_prioritaet, kls_bezeichnung
          from klasse
        )SQL");

    std::vector<Klasse> ak;
    for (auto r: sel)
    {
        ak.emplace_back();
        Klasse& k = ak.back();
        r.get(k._ak)
         .get(k._geschlecht)
         .get(k._alterVon)
         .get(k._alterBis)
         .get(k._prioritaet)
         .get(k._bezeichnung);
    }

    return ak;
}
