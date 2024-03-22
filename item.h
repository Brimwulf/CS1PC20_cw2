#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Item {
private:
    string name;
    string description;
public:
    Item(const string& name, const string& desc)
        : name(name), description(desc) {}
    void Interact();
    void getName();
    void getDescription();
};



void Item::Interact() {
    cout << "You pick up the " << name << endl;
    cout << description << endl;
    cout << "Add it to your inventory? Y/N";
    string choice;
    while (true) {
        cin >> choice;
        if (choice == "Y") {
            //Call the AddToInv function from class Character and add the item being interacted with
            Character::AddToInv; /*I'm fairly sure this needs parameters but I don't know how to add them
                                   I'll ask Pat when I next get a chance to*/
            break;
        }
        else if (choice == "N") {
            cout << "You leave the " << name << " where it is" << endl;
            break;
        }
        else {
            cout << "Invalid, please retry";
        }
    }
}