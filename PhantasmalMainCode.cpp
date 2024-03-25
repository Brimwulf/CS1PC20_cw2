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
// The amount of includes here hurts my head and I'm hoping its not horrendously bad practice to do it this way.

using namespace std;

/*
* This function is responsible for building the game world. It will contain all the logic to place clues
* in different rooms and create a player.
*/
void preGameBuild() {
    Area area;

    cout << "Welcome to Phantasmal" << endl;
    // Create the player
    string name;
    cout << "What is your name?" << endl;
    cin >> name;
    Player player(name, 100);

    // Create the pre-game command interpreter for the pre game
    commandInterpreter preGameCommandInterpreter(&player, &area, nullptr);
    // Get the user inputs for the start "menu"
    string choice;
    cout << "Would you like to load a save file or open a new map?" << endl;
    cin >> choice;
    if (choice == "load") {
        preGameCommandInterpreter.preGameCommands("load");
    }
    else if (choice == "map") {
        string mapName;
        cout << "Choose the map: Abandoned Schoolhouse, Eery Asylum, Old Mansion" << endl;
        cin >> mapName;
        preGameCommandInterpreter.preGameCommands("map", mapName); // The extra parameter here allows a subcommand to be added to the command interpreter.
    }

    player.setLocation(area.getRandomRoom()); // puts the player in a random room.
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