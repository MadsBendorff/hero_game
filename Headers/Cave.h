#ifndef CAVE_H
#define CAVE_H

#include <string>
#include <vector>
#include "Enemy.h"

class Cave {
public:
    Cave(const std::string& name, int gold, const std::vector<Enemy>& enemies);

    std::string getName() const;
    int getGold() const;
    std::vector<Enemy>& getEnemies();

private:
    std::string name;
    int gold;
    std::vector<Enemy> enemies;
};

#endif
