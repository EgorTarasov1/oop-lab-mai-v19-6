#include "NPCFactory.h"

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Thief") {
        return std::make_unique<Thief>(name, x, y);
    } else if (type == "Orc") {
        return std::make_unique<Orc>(name, x, y);
    } else if (type == "Werewolf") {
        return std::make_unique<Werewolf>(name, x, y);
    }
    return nullptr;
}