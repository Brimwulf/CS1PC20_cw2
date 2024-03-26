#include "item.h"

bool Item::Interact() {
    cout << "You pick up the " << name << endl;
    cout << description << endl;
    cout << "Add it to your inventory? Y/N";
    string choice;
    while (true) {
        cin >> choice;
        if (choice == "Y") {
            return true; // Returning true so that the item can be added to the inventory in main
        }
        else if (choice == "N") {
            cout << "You leave the " << name << " where it is" << endl;
            return false; // Since false the item won't be added to inv.
        }
        else {
            cout << "Invalid, please retry";
        }
    }
}
string Item::getName() const {
    return name;
}
string Item::getDescription() {
    return description;
}