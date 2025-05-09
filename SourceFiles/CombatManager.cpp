#include "CombatManager.h"
#include <iostream>

void CombatManager::fight(Hero& hero, Enemy enemy) {
    std::cout << "Fighting " << enemy.getName() << "!\n";

    while (hero.isAlive() && enemy.isAlive()) {
        enemy.takeDamage(hero.getStrength());
        std::cout << "You hit " << enemy.getName() << " for " << hero.getStrength() << " damage.\n";
        if (!enemy.isAlive()) break;

        hero.takeDamage(enemy.getStrength());
        std::cout << enemy.getName() << " hits you for " << enemy.getStrength() << " damage.\n";
        std::cout << "Your HP: " << hero.getHP() << " | Enemy HP: " << enemy.getHP() << "\n\n";
    }

    if (hero.isAlive()) {
        std::cout << "You defeated " << enemy.getName() << " and gained " << enemy.getXPReward() << " XP!\n";
        hero.gainXP(enemy.getXPReward());
    } else {
        std::cout << "You were defeated by " << enemy.getName() << "...\n";
    }
}
