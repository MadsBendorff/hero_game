#include <iostream>
#include <vector>
#include <string>
#include "Hero.h"
#include "Enemy.h"
#include "CombatManager.h"
#include "EnemyFactory.h"
#include "Cave.h"
#include "WeaponFactory.h"
#include <ctime> 


int main() {
    std::string name;
    std::cout << "Enter hero name: ";
    std::getline(std::cin, name);
    Hero hero(name);
    srand(time(0));

    std::vector<Cave> caves = {
        Cave("Goblin Nest", 50, EnemyFactory::generateEnemies(hero.getLevel())),
        Cave("Dragon Den", 100, EnemyFactory::generateEnemies(hero.getLevel())),
        Cave("The Dark Forest", 75, EnemyFactory::generateEnemies(hero.getLevel()))
    };

    while (hero.isAlive()) {
        std::cout << "\n=== Hero Status ===\n";
        std::cout << "Name: " << hero.getName()
                  << " | HP: " << hero.getHP()
                  << " | XP: " << hero.getXP()
                  << " | Level: " << hero.getLevel()
                  << " | Strength: " << hero.getStrength()
                  << " | Gold: " << hero.getGold() << "\n";

        Weapon* weapon = hero.getWeapon();
        if (weapon != nullptr) {
            std::cout << "Weapon: " << weapon->getName()
                      << " | Durability: " << weapon->getDurability() << "\n";
        } else {
            std::cout << "Weapon: None\n";
        }

        std::cout << "\nChoose a cave to enter:\n";
        for (size_t i = 0; i < caves.size(); ++i) {
            std::cout << i + 1 << ". " << caves[i].getName()
                      << " (Gold reward: " << caves[i].getGold() << ")\n";
        }

        std::cout << "0. Quit\n";

        int choice;
        std::cout << "Your choice: ";
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        if (choice < 1 || choice > static_cast<int>(caves.size())) {
            std::cout << "Invalid choice.\n";
            continue;
        }

        Cave& selectedCave = caves[choice - 1];
        auto& enemies = selectedCave.getEnemies();

        std::cout << "Entering " << selectedCave.getName() << "...\n";
        for (Enemy& enemy : enemies) {
            if (!hero.isAlive()) break;
            CombatManager::fight(hero, enemy);
        }

        if (hero.isAlive()) {
            std::cout << "You completed the cave and earned " << selectedCave.getGold() << " gold!\n";
            hero.addGold(selectedCave.getGold());

            int chance = rand() % 5;
            if (chance == 0) {
                Weapon* newWeapon = WeaponFactory::createRandomWeapon();
                hero.setWeapon(newWeapon);
                std::cout << "You found a weapon!: " << newWeapon->getName() << "!\n";
            }
        } 
        else {
            std::cout << "You died in the cave...\n";
        }
    }

    return 0;
}

