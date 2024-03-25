#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Room.h"
#include "Player.h"
#include "Journal.h"
#include "Ghost.h"

class Player;
class Area;
class Journal;
class Ghost;

class commandInterpreter {
public:
    commandInterpreter(Player* player, Area* area, Journal* journal) : player_(player), area_(area), journal_(journal) {} // constructor
    void interpretCommand(const string& command, const string& subCommand = "");
    void preGameCommands(const string& command, const string& subCommand = "");
private:
    Player* player_; // points to the player object
    Area* area_; // points to the area as well.
    Journal* journal_;
    Ghost* ghost_;
};
