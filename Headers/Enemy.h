#ifndef ENEMY_H
#define ENEMY_H
#include <string>

class Enemy {
public:
    Enemy(std::string name, int hp, int strength, int xpReward);

    void takeDamage(int dmg);
    int getHP() const;
    int getStrength() const;
    std::string getName() const;
    int getXPReward() const;
    bool isAlive() const;

private:
    std::string name;
    int hp;
    int strength;
    int xpReward;
};

#endif
