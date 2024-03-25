#ifndef GHOST_H
#define GHOST_H

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
    vector<Clue*> clues;
public:
    Ghost(Player* player, Area* area, const string& type) : currentState(Idle), player(player), area(area), currentRoom(currentRoom), Type(type) {
        currentRoom = area->getRandomRoom();
    }
    void upateState();
    void updateStateOnPlayerMove();
    void roam();
    vector<Room*> pathFindToPlayer();
    void hunt();
    void distributeClues();
    void addClue(Clue* clue) {
        clues.push_back(clue);
    }
    string getType() const {
        return Type;
    }
};
#endif