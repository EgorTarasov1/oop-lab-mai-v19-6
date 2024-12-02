#include "DungeonEditor.h"
#include <iostream>
#include <fstream>

void DungeonEditor::addNPC(const std::string& type, const std::string& name, int x, int y) {
    if (x >= 0 && x <= 500 && y >= 0 && y <= 500) {
        npcs.push_back(NPCFactory::createNPC(type, name, x, y));
    } else {
        std::cout << "Координаты вне диапазона." << std::endl;
    }
}

void DungeonEditor::printNPCs() const {
    for (const auto& npc : npcs) {
        std::cout << npc->getType() << ": " << npc->getName() 
                  << " (X: " << npc->getX() << ", Y: " << npc->getY() << ")" << std::endl;
    }
}

void DungeonEditor::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& npc : npcs) {
            file << npc->getType() << " " << npc->getName() << " " 
                 << npc->getX() << " " << npc->getY() << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
    }
}

void DungeonEditor::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string type, name;
    int x, y;
    if (file.is_open()) {
        while (file >> type >> name >> x >> y) {
            addNPC(type, name, x, y);
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

void DungeonEditor::startBattle(int range) {
    Battle battle(npcs);
    ConsoleObserver consoleObserver;
    FileObserver fileObserver("log.txt");
    
    battle.addObserver(&consoleObserver);
    battle.addObserver(&fileObserver);
    
    battle.start(range);  
}