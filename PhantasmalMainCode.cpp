// CS1PC20-Cw2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include "Character.h"
#include "CommandInterpreter.h"
#include "GameObject.h"
#include "GameSaverLoader.h"
#include "Ghost.h"
#include "Inventory.h"
#include "item.h"
#include "Journal.h"
#include "Player.h"
#include "Room.h"

using namespace std;

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

    

    return 0;
}

/*
* TO DO: I need to first, write the save game/load class. It needs a series of getters and setters for things like health, etc. It should also load
* the characters inventory and location (code is in onenote). Then I need to write the NPC behaviour for the ghost and create a series of constructors
* that create an instance of the ghost with unique behaviours. Could use inheritance or polymorphism? Then once that's done, create functionality to load
* the map from files and implement the game loop of finding out the ghost type.
*/