#include "WeaponFactory.h"
#include <cstdlib>
#include <ctime>

Weapon* WeaponFactory::createRandomWeapon() {
    int r = rand() % 5;

    switch (r) {
        case 0: return new Weapon("Knife", 5, 0.0, 20);
        case 1: return new Weapon("Stick", 0, 1.0, 10);
        case 2: return new Weapon("Metal Pipe", 0, 2.0, 20);
        case 3: return new Weapon("Sword", 20, 1.0, 30);
        case 4: return new Weapon("Mace", 10, 3.0, 40);
        default: return new Weapon("Bare Hands", 0, 0.0, 0);
    }
}
