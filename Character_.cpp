#include "Character.h"

void Character::takeDamage(int damage) {
    sanity -= damage; // decrease health by damage
    if (sanity < 0) {
        sanity = 0; // health cannot be less than 0.
    }
}
void Character::AddToInv(const Item& item) {
    inventory.push_back(item);
}