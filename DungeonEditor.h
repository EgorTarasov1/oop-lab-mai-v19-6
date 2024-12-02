#ifndef DUNGEONEDITOR_H
#define DUNGEONEDITOR_H

#include "NPC.h"
#include "NPCFactory.h"
#include "Battle.h"
#include <vector>
#include <string>

class DungeonEditor {
private:
    std::vector<std::unique_ptr<NPC>> npcs;

public:
    void addNPC(const std::string& type, const std::string& name, int x, int y);
    void printNPCs() const;
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void startBattle(int range);
};

#endif 