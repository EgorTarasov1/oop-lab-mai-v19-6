#ifndef NPC_H
#define NPC_H

#include <string>

class NPC {
protected:
    std::string name;
    int x, y;
    bool isAlive; // Добавлено для отслеживания состояния NPC

public:
    NPC(std::string name, int x, int y);
    virtual ~NPC();
    
    virtual std::string getType() const = 0;
    virtual int getX() const;
    virtual int getY() const;
    std::string getName() const;

    virtual bool canFight(const NPC& other, int range) const;
    virtual void fight(NPC& opponent) = 0;
    void die(); // Метод для "гибели" NPC
    bool alive() const; // Проверка, жив ли NPC
};

class Thief : public NPC {
public:
    Thief(std::string name, int x, int y);
    
    std::string getType() const override;
    void fight(NPC& opponent) override;
};

class Orc : public NPC {
public:
    Orc(std::string name, int x, int y);
    
    std::string getType() const override;
    void fight(NPC& opponent) override;
};

class Werewolf : public NPC {
public:
    Werewolf(std::string name, int x, int y);
    
    std::string getType() const override;
    void fight(NPC& opponent) override;
};

#endif 