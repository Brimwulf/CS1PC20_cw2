#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <queue>
#include "Player.h"
#include "Room.h"

// Defining the ghost's behaviour
class Ghost {
public:
    enum State { Idle, Hunting, Roaming };
private:
    State currentState;
    string Type;
    Player* player;
    Area* area;
    Room* currentRoom;
    vector<Clue> clues;
public:
    Ghost(Player* player, Area* area) : currentState(Idle), player(player), area(area), currentRoom(currentRoom) {}
    void upateState();
    void updateStateOnPlayerMove();
    void roam();
    vector<Room*> pathFindToPlayer();
    void hunt();
    void distributeClues();
    string getType() const {
        return Type;
    }
};
