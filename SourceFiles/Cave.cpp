#include "Cave.h"

Cave::Cave(const std::string& name, int gold, const std::vector<Enemy>& enemies)
    : name(name), gold(gold), enemies(enemies) {}

std::string Cave::getName() const { return name; }
int Cave::getGold() const { return gold; }
std::vector<Enemy>& Cave::getEnemies() { return enemies; }
