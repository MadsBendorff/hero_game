#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
public:
    Weapon(const std::string& name, int baseDamage, double strengthModifier, int durability);

    std::string getName() const;
    int getBaseDamage() const;
    double getStrengthModifier() const;
    int getDurability() const;
    void reduceDurability();
    bool isBroken() const;

private:
    std::string name;
    int baseDamage;
    double strengthModifier;
    int durability;
};

#endif
