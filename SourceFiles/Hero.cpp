#include "Hero.h"

Hero::Hero(const std::string& name)
    : name(name), level(1), hp(10), strength(2), xp(0), gold(0), weapon(nullptr) {}

void Hero::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}

void Hero::gainXP(int amount) {
    xp += amount;
    levelUpIfNeeded();
}

void Hero::levelUpIfNeeded() {
    int threshold = level * 1000;
    while (xp >= threshold) {
        xp -= threshold;
        level++;
        hp += 2;
        strength += 1;
    }
}

int Hero::getHP() const { return hp; }
int Hero::getStrength() const { return strength; }
int Hero::getXP() const { return xp; }
int Hero::getLevel() const { return level; }
std::string Hero::getName() const { return name; }
bool Hero::isAlive() const { return hp > 0; }

void Hero::addGold(int amount) {
    gold += amount;
}

int Hero::getGold() const {
    return gold;
}

void Hero::setWeapon(Weapon* w) {
    weapon = w;
}

Weapon* Hero::getWeapon() const {
    return weapon;
}

