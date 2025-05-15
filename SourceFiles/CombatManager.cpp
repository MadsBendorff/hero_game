#include "CombatManager.h"
#include <iostream>
#include "Weapon.h"

void CombatManager::fight(Hero& hero, Enemy enemy) {
    std::cout << "Fighting " << enemy.getName() << "!\n";

    while (hero.isAlive() && enemy.isAlive()) {
        Weapon* weapon = hero.getWeapon();
        int damage = 0;

        if (weapon != nullptr && !weapon->isBroken()) {
            damage = weapon->getBaseDamage() + (hero.getStrength() * weapon->getStrengthModifier());
            weapon->reduceDurability();
            if (weapon->isBroken()) {
                std::cout << "Your " << weapon->getName() << " broke!\n";
            }
        } else {
            damage = hero.getStrength();
        }

        enemy.takeDamage(damage);
        std::cout << "You hit " << enemy.getName() << " for " << damage << " damage.\n";

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
