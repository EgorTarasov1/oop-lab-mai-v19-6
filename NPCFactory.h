#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include "NPC.h"
#include <memory>
#include <string>

class NPCFactory {
public:
    static std::unique_ptr<NPC> createNPC(const std::string& type, const std::string& name, int x, int y);
};

#endif