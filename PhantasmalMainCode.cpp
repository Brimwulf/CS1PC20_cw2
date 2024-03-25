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

int main() {
    // pre game generation:
    Area area;

    cout << "Welcome to Phantasmal" << endl;
    // Create the player
    string name;
    cout << "What is your name?" << endl;
    getline(cin, name);
    Player player(name, 100);

    // Create the pre-game command interpreter for the pre game
    commandInterpreter preGameCommandInterpreter(&player, &area, nullptr);
    // Get the user inputs for the start "menu"


    bool commandSuccessful = false;
    while (!commandSuccessful) {
        string choice;
        cout << "Would you like to load a save file or open a new map?" << endl;
        getline(cin, choice);
        if (choice == "load") {
            preGameCommandInterpreter.preGameCommands("load");
            commandSuccessful = true;
        }
        else if (choice == "map") {
            string mapName;
            cout << "Choose the map: Abandoned Schoolhouse, Eery Asylum, Old Mansion" << endl;
            getline(cin, mapName);
            preGameCommandInterpreter.preGameCommands("map", mapName); // The extra parameter here allows a subcommand to be added to the command interpreter.
            commandSuccessful = true;
        }
        else if (choice == "help") {
            preGameCommandInterpreter.preGameCommands("help");
        }
        else {
            cout << "Unknown command. Please try 'help' for a list of commands." << endl;
        }
    }
    player.setLocation(area.getRandomRoom()); // puts the player in a random room.
    // for debugging
    if (player.getLocation() != nullptr) {
        cout << player.getLocation()->getDescription() << endl;
    }
    else {
        cout << "Player location not set." << endl;
    }

    // generate a random ghost
    // Can add more ghosts later
    // Getting the random number
    srand(time(0)); //changes the random seed based on the current time... neat right? I thought it was neat..
    int ghostType = rand() % 10 + 1;
    //cout << "random number is: " << ghostType << endl;

    // Generating a ghost using the random number.
    Ghost* ghost;
    if (ghostType <= 3) {       // 30% chance
        ghost = new Ghost(&player, &area, "demon");
        Clue* clue1 = new Clue("This room smells like a fire was recently put out in it.");
        ghost->addClue(clue1);
        Clue* clue2 = new Clue("There's a pentogram written in this room with candles put out on each point.");
        ghost->addClue(clue2);
        Clue* clue3 = new Clue("As you enter the room a wave of dread washes over you.");
        ghost->addClue(clue3);
    }
    else if (ghostType <= 7) {  // 40% chance
        ghost = new Ghost(&player, &area, "poltergeist");
        Clue* clue1 = new Clue("As you enter the room a wave of dread washes over you.");
        ghost->addClue(clue1);
        Clue* clue2 = new Clue("This room is a mess, there are objects strewn across the floor.");
        ghost->addClue(clue2);
        Clue* clue3 = new Clue("This room feels unnaturally cold.");
        ghost->addClue(clue3);
    }
    else {                     // 30% chance
        ghost = new Ghost(&player, &area, "yokai");
        Clue* clue1 = new Clue("This room feels unnaturally cold.");
        ghost->addClue(clue1);
        Clue* clue2 = new Clue("You could swear you hear indecipherable whisperings.");
        ghost->addClue(clue2);
        Clue* clue3 = new Clue("This room is a mess, there are objects strewn across the floor.");
        ghost->addClue(clue3);
    }
    ghost->distributeClues();

    // Creating the command interpreter:
    commandInterpreter gameCommandInterpreter(&player, &area, ghost);

    // Now creating the game loop:
    while (!gameCommandInterpreter.gameOverChecker()) {
        string command;
        cout << "Enter Comand: ";
        getline(cin, command);

        // processing the command.
        gameCommandInterpreter.interpretCommand(command);
    }
    delete ghost;
    return 0;
}

/*
* TO DO: I need to first, write the save game/load class. It needs a series of getters and setters for things like health, etc. It should also load
* the characters inventory and location (code is in onenote). Then I need to write the NPC behaviour for the ghost and create a series of constructors
* that create an instance of the ghost with unique behaviours. Could use inheritance or polymorphism? Then once that's done, create functionality to load
* the map from files and implement the game loop of finding out the ghost type.
*/