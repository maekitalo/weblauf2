#ifndef TEILNEHMERMANAGER_H
#define TEILNEHMERMANAGER_H

#include "person.h"
#include "teilnehmer.h"

#include <managercontext.h>

#include <vector>

class TeilnehmerManager
{
    public:
        explicit TeilnehmerManager(ManagerContext& ctx)
            : _ctx(ctx)
        { }

        std::vector<Person> searchPerson(unsigned vid, const std::string& s);
        std::vector<Person> getPersonen();
        std::vector<Teilnehmer> getPersonen(unsigned vid);
        std::vector<Teilnehmer> getTeilnehmer(unsigned vid);

    private:
        ManagerContext& _ctx;
};

#endif
