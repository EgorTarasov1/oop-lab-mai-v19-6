#ifndef BATTLE_H
#define BATTLE_H

#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>  

class Battle {
private:
    std::vector<std::unique_ptr<NPC>>& npcs;
    std::vector<Observer*> observers;

public:
    Battle(std::vector<std::unique_ptr<NPC>>& npcs);
    void addObserver(Observer* observer);
    void start(int range);
    void notifyObservers(const std::string& message);
};

#endif // BATTLE_H