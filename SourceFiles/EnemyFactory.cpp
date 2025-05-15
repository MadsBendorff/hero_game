#include "EnemyFactory.h"

std::vector<Enemy> EnemyFactory::generateEnemies(int heroLevel) {
    std::vector<Enemy> enemies;

    if (heroLevel < 2) {
        enemies.emplace_back("Weak Goblin", 4, 2, 200); //Bruger emplace nu istedet for fx enemies.push_back(Enemy("Goblin", 10, 2, 100));
        enemies.emplace_back("Hest", 4, 1, 100);
    } else if (heroLevel < 4) {
        enemies.emplace_back("Strong Goblin", 8, 3, 400);
        enemies.emplace_back("Stronger Goblin", 10, 4, 500);
    } else {
        enemies.emplace_back("Abe Kongen", 30, 5, 1000);
        enemies.emplace_back("Drage", 100, 10, 3000);
    }

    return enemies;
}
