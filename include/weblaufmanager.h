/*
 * Copyright (C) 2016 Tommi Maekitalo
 *
 */

#ifndef WEBLAUFMANAGER_H
#define WEBLAUFMANAGER_H

#include <managercontext.h>

#include <klasse.h>

#include <vector>
#include <string>

class WeblaufManager
{
    public:
        explicit WeblaufManager(ManagerContext& ctx)
            : _ctx(ctx)
        { }

        std::vector<std::string> getAkStr();
        std::vector<Klasse> getAk();

    private:
        ManagerContext& _ctx;
};

#endif // WEBLAUFMANAGER_H
