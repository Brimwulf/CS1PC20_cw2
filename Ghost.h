#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <queue>
#include "Player.h"
#include "Room.h"

class Player;
class Area;

// Defining the ghost's behaviour
class Ghost {
public:
    enum State { Idle, Hunting, Roaming };
private:
    State currentState;
    Player* player;
    Area* area;
    Room* currentRoom;
public:
    Ghost(Player* player, Area* area) : currentState(Idle), player(player), area(area), currentRoom(currentRoom) {}
    void upateState();
    void updateStateOnPlayerMove();
    void roam();
    vector<Room*> pathFindToPlayer();
    void hunt();
};
