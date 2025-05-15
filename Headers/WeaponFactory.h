#ifndef WEAPONFACTORY_H
#define WEAPONFACTORY_H

#include "Weapon.h"

class WeaponFactory {
public:
    static Weapon* createRandomWeapon();
};

#endif
