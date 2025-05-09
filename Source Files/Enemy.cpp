#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, int strength, int xpReward)
    : name(name), hp(hp), strength(strength), xpReward(xpReward) {}

void Enemy::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}

int Enemy::getHP() const { return hp; }
int Enemy::getStrength() const { return strength; }
std::string Enemy::getName() const { return name; }
int Enemy::getXPReward() const { return xpReward; }
bool Enemy::isAlive() const { return hp > 0; }
