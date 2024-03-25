#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Room.h"
#include "Player.h"
#include "Journal.h"
#include "Ghost.h"

class commandInterpreter {
public:
    commandInterpreter(Player* player, Area* area, Ghost* ghost) : player_(player), area_(area), ghost_(ghost), gameOver(false) {} // constructor
    void interpretCommand(const string& command);
    void preGameCommands(const string& command, const string& subCommand = "");
    bool gameOverChecker() const {
        return gameOver;
    }
private:
    Player* player_; // points to the player object
    Area* area_; // points to the area as well.
    Journal* journal_;
    Ghost* ghost_;
    bool gameOver;
};

#endif