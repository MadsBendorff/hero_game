#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <vector>
#include <string>
#include "Enemy.h"

class EnemyFactory {
public:
    static std::vector<Enemy> generateEnemies(int heroLevel); //kan kalde funktion uden at oprette et objekt af klasse "static"
};

#endif
