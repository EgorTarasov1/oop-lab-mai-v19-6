#include "NPC.h"
#include <iostream>
#include <cmath>
#include <cstdlib>   
#include <ctime>     

NPC::NPC(std::string name, int x, int y) : name(name), x(x), y(y), isAlive(true) {}

NPC::~NPC() {}

int NPC::getX() const { return x; }
int NPC::getY() const { return y; }
std::string NPC::getName() const { return name; }

bool NPC::canFight(const NPC& other, int range) const {
    if (!isAlive || !other.alive()) return false; 
    int distance = std::sqrt(std::pow(x - other.getX(), 2) + std::pow(y - other.getY(), 2));
    return distance <= range;
}

void NPC::die() { isAlive = false; } 
bool NPC::alive() const { return isAlive; } 

// Thief
Thief::Thief(std::string name, int x, int y) : NPC(name, x, y) {}

std::string Thief::getType() const { return "Thief"; }

void Thief::fight(NPC& opponent) {
    if (this->alive() && opponent.alive() && this->getName() != opponent.getName()) {
        if (opponent.getType() == "Werewolf") {
            int result = rand() % 2; 
            if (result == 0) {
                std::cout << this->getName() << " is killing " << opponent.getName() << "!" << std::endl;
                opponent.die(); 
                std::cout << opponent.getName() << " was killed by " << this->getName() << std::endl;
            } else {
                std::cout << opponent.getName() << " is killing " << this->getName() << "!" << std::endl;
                this->die();
                std::cout << this->getName() << " was killed by " << opponent.getName() << std::endl;
            }
        }
    }
}

// Orc
Orc::Orc(std::string name, int x, int y) : NPC(name, x, y) {}

std::string Orc::getType() const { return "Orc"; }

void Orc::fight(NPC& opponent) {
    if (this->alive() && opponent.alive() && this->getName() != opponent.getName()) {
        if (opponent.getType() == "Thief") {
            std::cout << this->getName() << " is killing " << opponent.getName() << "!" << std::endl;
            opponent.die();
            std::cout << opponent.getName() << " was killed by " << this->getName() << std::endl;
        }
    }
}

// Werewolf
Werewolf::Werewolf(std::string name, int x, int y) : NPC(name, x, y) {}

std::string Werewolf::getType() const { return "Werewolf"; }

void Werewolf::fight(NPC& opponent) {
    if (this->alive() && opponent.alive() && this->getName() != opponent.getName()) {
        if (opponent.getType() == "Thief") {
            std::cout << this->getName() << " is killing " << opponent.getName() << "!" << std::endl;
            opponent.die();
            std::cout << opponent.getName() << " was killed by " << this->getName() << std::endl;
        }
    }
}