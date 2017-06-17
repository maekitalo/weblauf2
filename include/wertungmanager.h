/*
 * Copyright (C) 2015 Tommi Maekitalo
 *
 */

#ifndef WERTUNGMANAGER_H
#define WERTUNGMANAGER_H

#include "wertung.h"
#include "wertungsgruppe.h"
#include <managercontext.h>
#include <vector>

class WertungManager
{
    public:
        explicit WertungManager(ManagerContext& ctx)
            : _ctx(ctx)
            { }

        Wertung getWertung(unsigned vid, unsigned wid, unsigned rid);
        std::vector<Wertung> getWertungen(unsigned vid, unsigned wid);
        std::vector<std::string> getAk(unsigned vid, unsigned wid, unsigned rid);

        void putWertung(const Wertung& w);
        void delWertung(unsigned vid, unsigned wid, unsigned rid);
        void delWertung(const Wertung& w)
        { delWertung(w.vid(), w.wid(), w.rid()); }

        Wertungsgruppe getWertungsgruppe(unsigned vid, unsigned wid, unsigned gid);
        std::vector<Wertungsgruppe> getWertungsgruppen(unsigned vid, unsigned wid);

    private:
        ManagerContext& _ctx;
};

#endif // WERTUNGMANAGER_H
