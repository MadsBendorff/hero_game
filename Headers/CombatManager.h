#ifndef COMBATMANAGER_H
#define COMBATMANAGER_H
#include "Hero.h"
#include "Enemy.h"

class CombatManager {
public:
    static void fight(Hero& hero, Enemy enemy);
};

#endif
