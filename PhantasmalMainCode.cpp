// CS1PC20-Cw2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "item.h"
#include "Room.h"
using namespace std;

class Character {
private:
    string name;
    int health;
    vector<Item> inventory;
public:
    Character(const string& name, int health);
    void takeDamage(int damage);
    void AddToInv(const Item& item) {
        inventory.push_back(item);
    }
};

class Player : public Character {
private:
    Room* location;
public:
    Player(const string& name, int health);
    Room* getLocation() {
        return location;
    }
    void setLocation(Room* room) {
        location = room;
    }
};

/* int Player() {   
    cout << "What is your name? ";
    string name;
    cin >> name;
    int health;
    health = 100;
    return name, health;
} */

int main() {
    //Create Rooms
    Room startRoom("You are in a dimly lit room");
    Room hallway("You are in a long hallway");
    Room lootRoom("You have entered a room filled with loot");

    //Define exits between rooms
    startRoom.addExit("north", &hallway);
    hallway.addExit("south", &startRoom);
    hallway.addExit("north", &lootRoom);
    lootRoom.addExit("south", &hallway);

    //Create items
    Item key("Key", "A key, it must open something");
    Item sword("Sword", "Some say the pen is mightier than the sword... but you beg to differ");

    //Add items to room
    startRoom.addItem(key);
    lootRoom.addItem(sword);

    //Create a Player
    Player player("Alice", 100);

    //Set the player's starting location
    player.setLocation(&startRoom);

    //Game loop
    while (true) {
        cout << "Current Location: " << player.getLocation() > getDescription() << endl;
        cout << "Items in around you: " << endl;
        for (const Item& item : player.getLocation()->getItems()) {
            cout << "- " << item.getName() << ": " << item.getDescription() << endl;
        }
        cout << "Options: ";
        cout << "1. Look around | ";
        cout << "2. Interact with an item | ";
        cout << "3. Move to another room | ";
        cout << "4. Quit" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            //Player looks around (no actions required)
            cout << "You check the room around you" << endl;
            // Later I'd like to add something that shows the items in the current room for this option
        }
        else if (choice == 2) {
            //Player interacts with an item in the room
            cout << "Enter the name of the item you want to interact with: ";
            string itemName;
            cin >> itemName;
            for (Item& item : player.getLocation()->getItems()) {
                if (item.getName() == itemName) {
                    if (item.Interact()) {
                        player.AddToInv(item);
                    }
                }
            }
        }
        else if (choice == 3) {
            cout << "Are you sure you want to quit? Y/N";
            string quitChoice;
            cin >> quitChoice;
            if (quitChoice == "Y") {
                break;
            }
            else {
                continue;
            }
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
    return 0;
}