#include "DungeonEditor.h"
#include <cstdlib> 
#include <ctime>  
#include <iostream>

int main() {
    srand(static_cast<unsigned int>(time(0))); 
    DungeonEditor editor;

    // Пример добавления NPC
    editor.addNPC("Thief", "Thief1", 100, 100);
    editor.addNPC("Thief", "Thief2", 120, 110); 
    editor.addNPC("Orc", "Orc1", 150, 150);
    editor.addNPC("Orc", "Orc2", 160, 140); 
    editor.addNPC("Werewolf", "Werewolf1", 200, 200);
    editor.addNPC("Werewolf", "Werewolf2", 220, 210); 

    // Печать NPC
    std::cout << "Initial NPCs:" << std::endl;
    editor.printNPCs();

    // Начало битвы
    std::cout << "\nStarting battle..." << std::endl;
    editor.startBattle(150);

    return 0;
}