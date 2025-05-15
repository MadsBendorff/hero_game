#include "Weapon.h"

Weapon::Weapon(const std::string& name, int baseDamage, double strengthModifier, int durability)
    : name(name), baseDamage(baseDamage), strengthModifier(strengthModifier), durability(durability) {}

std::string Weapon::getName() const { return name; }
int Weapon::getBaseDamage() const { return baseDamage; }
double Weapon::getStrengthModifier() const { return strengthModifier; }
int Weapon::getDurability() const { return durability; }

void Weapon::reduceDurability() {
    if (durability > 0) durability--;
}

bool Weapon::isBroken() const {
    return durability <= 0;
}
