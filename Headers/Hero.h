#ifndef HERO_H
#define HERO_H
#include <string>

class Hero {
public:
    Hero(const std::string& name);
    void takeDamage(int dmg);
    void gainXP(int xp);
    void levelUpIfNeeded();
    int getHP() const;
    int getStrength() const;
    int getXP() const;
    int getLevel() const;
    std::string getName() const;
    bool isAlive() const;
    void addGold(int amount);
    int getGold() const;

private:
    std::string name;
    int hp;
    int strength;
    int xp;
    int level;
    int gold;
};

#endif 