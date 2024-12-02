#include "Battle.h"
#include <iostream>
#include <algorithm> 

Battle::Battle(std::vector<std::unique_ptr<NPC>>& npcs) : npcs(npcs) {}

void Battle::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Battle::start(int range) {
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = 0; j < npcs.size(); ++j) {
            if (i != j && npcs[i]->canFight(*npcs[j], range) && npcs[i]->alive() && npcs[j]->alive()) {
                npcs[i]->fight(*npcs[j]);
            }
        }
    }

    npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
        [](const std::unique_ptr<NPC>& npc) { return !npc->alive(); }), npcs.end());
}

void Battle::notifyObservers(const std::string& message) {
    for (Observer* observer : observers) {
        observer->update(message);
    }
}