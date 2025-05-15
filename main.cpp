#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Hero.h"
#include "Enemy.h"
#include "CombatManager.h"
#include "EnemyFactory.h"
#include "Cave.h"
#include "WeaponFactory.h"
#include "DatabaseManager.h"
#include <limits>

int main() {
    DatabaseManager db("game.db");

    std::cout << "1. Start game\n";
    std::cout << "2. Show battle log\n";
    std::cout << "3. Show heroes\n";
    std::cout << "4. Show top hero per weapon\n";
    std::cout << "5. Show monster kills per hero\n";
    std::cout << "6. Show weapon kills by a specific hero\n";
    std::cout << "7. Exit\n";
    std::cout << "Your choice: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Rydder alt i input bufferen.

    if (choice == 2) {  
        db.showAllBattles();
        return 0;
    } else if (choice == 3) {
        db.showAllHeroes();
        return 0;
    } else if (choice == 4) {
        db.showTopHeroPerWeapon();
        return 0;
    } else if (choice == 5) {
        db.showHeroKillCounts();
        return 0;
    }
    else if (choice == 6) {
        std::string heroName;
        std::cout << "Enter hero name: ";
        std::getline(std::cin, heroName);
        db.showWeaponKillsByHero(heroName);
        return 0;
    }
    else if (choice == 7) {
        std::cout << "Program exited.\n";
        return 0;
    }

    // --- Hero creation/loading ---
    std::string name;
    std::cout << "Enter hero name: ";
    std::getline(std::cin, name);

    std::cout << "Do you want to load this hero from the database? (yes/no): ";
    std::string loadChoice;
    std::getline(std::cin, loadChoice);

    Hero hero(name); 

    if (loadChoice == "yes") {
        int level, xp, gold;
        if (db.loadHero(name, level, xp, gold)) {
            hero = Hero(name, level, xp, gold);
            std::cout << "Hero loaded successfully.\n";
        } else {
            std::cout << "Hero not found. A new one will be created.\n";
        }
    } else {
        std::cout << "Creating new hero...\n";
        hero = Hero(name); 
    }

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
        std::cout << "Your choice: ";
        int caveChoice;
        std::cin >> caveChoice;

        if (caveChoice == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        if (caveChoice < 1 || caveChoice > static_cast<int>(caves.size())) {
            std::cout << "Invalid choice.\n";
            continue;
        }

        Cave& selectedCave = caves[caveChoice - 1];
        auto& enemies = selectedCave.getEnemies();

        std::cout << "Entering " << selectedCave.getName() << "...\n";
        for (Enemy& enemy : enemies) {
            if (!hero.isAlive()) break;

            CombatManager::fight(hero, enemy);

            Weapon* weapon = hero.getWeapon();
            std::string weaponName = (weapon ? weapon->getName() : "None");

            db.logBattle(hero.getName(), enemy.getName(), weaponName);
        }

        if (hero.isAlive()) {
            std::cout << "You completed the cave and earned " << selectedCave.getGold() << " gold!\n";
            hero.addGold(selectedCave.getGold());

            int chance = rand() % 5;
            if (chance == 0) {
                Weapon* newWeapon = WeaponFactory::createRandomWeapon();
                hero.setWeapon(newWeapon);
                std::cout << "You found a weapon!: " << newWeapon->getName() << "\n";
            }
        } else {
            std::cout << "You died in the cave...\n";
        }
    }

    db.logHero(hero.getName(), hero.getLevel(), hero.getXP(), hero.getGold());

    return 0;
}
