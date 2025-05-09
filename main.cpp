#include <iostream>
#include <vector>
#include <string>
#include "Headers/Hero.h"
#include "Headers/Enemy.h"
#include "Headers/CombatManager.h"

int main() {
    std::string name;
    std::cout << "Enter hero name: ";
    std::getline(std::cin, name);
    Hero hero(name);

    std::vector<Enemy> enemies = {
        Enemy("Hest", 4, 1, 100),
        Enemy("Weak Goblin", 4, 2, 200),
        Enemy("Strong Goblin", 8, 3, 400),
        Enemy("Stronger Goblin", 10, 4, 500),
        Enemy("Den stærkeste Goblin", 15, 5, 800),
        Enemy("Abe Kongen", 30, 5, 1000),
        Enemy("Enhjørning", 5, 8, 1500),
        Enemy("Drage", 100, 10, 3000)
    };

    while (hero.isAlive()) {
        std::cout << "\n=== Hero Status ===\n";
        std::cout << "Name: " << hero.getName()
                  << " | HP: " << hero.getHP()
                  << " | XP: " << hero.getXP()
                  << " | Level: " << hero.getLevel()
                  << " | Strength: " << hero.getStrength() << "\n";

        std::cout << "\nChoose an enemy to fight:\n";
        for (size_t i = 0; i < enemies.size(); ++i) {
            std::cout << i + 1 << ". " << enemies[i].getName()
                      << " (HP: " << enemies[i].getHP()
                      << ", Strength: " << enemies[i].getStrength()
                      << ", XP: " << enemies[i].getXPReward() << ")\n";
        }
        std::cout << "0. Quit\n";

        int choice;
        std::cout << "Your choice: ";
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        if (choice < 1 || choice > static_cast<int>(enemies.size())) {
            std::cout << "Invalid choice.\n";
            continue;
        }

        CombatManager::fight(hero, enemies[choice - 1]);

        if (!hero.isAlive()) {
            std::cout << "Game over.\n";
            break;
        }
    }

    return 0;
}
