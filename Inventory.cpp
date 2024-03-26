#include "Inventory.h"

void Inventory::addItem(gameObject* item) {
    if (item != nullptr) {
        items.push_back(item);
    }
    else {
        cout << "No such item as: " << item << endl;
    }
}
void Inventory::useItem(gameObject* item, gameObject& target) {
    // I'll figure out what to do with this method later... probably.
}
void Inventory::dropItem(const Item& item) {
    cout << "You drop the: " << item.getName() << " Thunk!" << endl;
    for (auto it = items.begin(); it != items.end(); it++) {
        items.erase(it);
        break;
    }
}
