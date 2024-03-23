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
    void takeDamage(int damage) {
        health -= damage; // decrease health by damage
        if (health < 0) {
            health = 0; // health cannot be less than 0.
        }
    }
    void AddToInv(const Item& item) {
        inventory.push_back(item);
    }
};

class Player : public Character {
private:
    Room* location;
public:
    Player(const string& name, int health) : Character(name, health), location(nullptr) {}
    Room* getLocation() {
        return location;
    }
    void setLocation(Room* room) {
        location = room;
    }
    void move(Room* room) {
        if (room != nullptr) {      // Checking if the room exists
            location = room;
        }
        else {
            cout << "No such room as: " << room << endl;
        }
    }
};

class commandInterpreter {
public:
    commandInterpreter(Player* player, Area* area, Journal* journal) : player_(player), area_(area), journal_(journal) {} // constructor
    void interpretCommand(const string& command) {
        // This function will have a series of commands which are triggered by ifs.
        if (command == "move") {
            string roomChoice;
            while (true) {
                cout << "enter room name" << endl;
                cin >> roomChoice;
                Room* roomMoveTo = area_->getRoom(roomChoice);
                if (roomMoveTo != nullptr) {
                    player_->move(roomMoveTo);
                    return;
                }
                else if (roomChoice == "cancel") {
                    return;
                }
                else {
                    cout << "No such room as: " << roomChoice << endl;
                }
            }
        }
        if (command == "read journal") {
            journal_->readJournal();
        }
        // need to add else ifs for other commands.
        // Have the ifs call Player methods like pickupitem and lookaround.
        else {
            cout << "Unknown command" << endl;
        }
    }
private:
    Player* player_; // points to the player object
    Area* area_; // points to the area as well.
    Journal* journal_;
};

//Creating a framework for interacting with objects:
class gameObject {
public:
    virtual void interact(gameObject& other) = 0;   // Virtual function which allows interact to be called at any point.
};

class Clue : public gameObject {
private:
    string description;
public:
    Clue(const string& desc) : description(desc) {} // constructor to create a clue.
    string getDescription() const {
        return description;
    }
    void interact(gameObject& other) override {
        // Needs implementing the interaction with the clue.
    }
};
// use inheritance below to create some game objects. For example:
// class Key : public gameObject { ..... }

class Inventory {
private:
    vector<gameObject*> items;
public:
    void addItem(gameObject* item) {
        if (item != nullptr) {
            items.push_back(item);
        }
        else {
            cout << "No such item as: " << item << endl;
        }
    }
    void useItem(gameObject* item, gameObject& target) {
        // I'll figure out what to do with this method later... probably.
    }
    void dropItem(const Item& item) {
        cout << "You drop the: " << item.getName() << endl;
        for (auto it = items.begin(); it != items.end(); it++) {
            items.erase(it);
            break;
        }
    }
};

// Defining the ghost's behaviour
class Ghost {
private:
    enum State{Idle,Hunting,Roaming};
    State currentState();
public:
    Ghost() : currentState(Idle) {}
    void upate() {

    }
};

// This class will be used to track the player's progress in finding the ghost. It should allow players to check what clues they have collected so far.
// I also want to add a behaviour to Ghost that makes it enter Roaming after the player collects the first clue and is more likely to enter Hunting 
// the more clues they have.
class Journal {
private:
    map<gameObject*,string> clues;  // This map will contain the collected clues.
public:
    void addClue(gameObject* clue, string desc) {
        Clue* clueObj = dynamic_cast<Clue*>(clue);
        if (clueObj != nullptr) {
            clues[clue] = clueObj->getDescription();
            /*updateJournal();*/
        }
    }
    enum Status { Empty, InProgress, AllEvidenceCollected };
    Status status;
    Journal() : status(Empty) {}
    
    /*void updateJournal() {
        status = 
    }*/
    void complete() {

    }
    void readJournal() const {
        if (clues.empty()) {
            cout << "No clues collected yet." << endl;
        }
        else {
            cout << "Collected clues:" << endl;
            for (const auto& clue : clues) {
                Clue* clueObj = dynamic_cast<Clue*>(clue.first);
                if (clueObj != nullptr) {
                    cout << " | " << clueObj->getDescription() << " | " << clue.second << endl;
                }
            }
        }
    }
};

class GameSaverLoader {
public:
    void saveGame(const string& filename, Player& player) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            // Save the player's name and health
            outFile << player.getLocation() << endl;
        }
        else {
            cout << "Unable to access save file." << endl;
        }
    }
    void loadGame(const string& filename) {

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

/*
* This function is responsible for building the game world. It will contain all the logic to place items
* in different rooms and create a player.
*/
void preGameBuild() {
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
}

int main() {

    Player player("Alice", 100);
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
    /*Player player("Alice", 100);*/

    //Set the player's starting location
    player.setLocation(&startRoom);

    //preGameBuild();
    //commandInterpreter interpreter(&player);
    //string command;
    //Player player("Alice", 100);
    ////Game loop
    //while (true) {

    //    cout << "> ";
    //    getline(cin, command);
    //    if (command == "quit") {
    //        break;
    //    }
    //    interpreter.interpretCommand(command);
        // Command interpreter functionality ready to be implemented.

    while(true) {
        cout << "Current Location: " << player.getLocation() > startRoom.getDescription() << endl;
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

/*
* TO DO: I need to first, write the save game/load class. It needs a series of getters and setters for things like health, etc. It should also load
* the characters inventory and location (code is in onenote). Then I need to write the NPC behaviour for the ghost and create a series of constructors
* that create an instance of the ghost with unique behaviours. Could use inheritance or polymorphism? Then once that's done, create functionality to load
* the map from files and implement the game loop of finding out the ghost type.
*/