#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Character.h"
#include "Room.h"
#include "GameObject.h"
using namespace std;

class Player : public Character {
private:
    Room* location;
    Area* area;
    vector<Clue*> clues;
    int clueRoomCount = 0;
public:
    Player(const string& name, int sanity) : Character(name, sanity), location(nullptr) {}
    Room* getLocation();
    void setLocation(Room* room);
    void move(string direction);
    void addClue(Clue* clue);
    int getClueCount() const;
    void setName(const string& nName) {
        Character::setName(nName);
    }
    void setSanity(int nSanity) {
        Character::setSanity(nSanity);
    }
    void setArea(Area* area) {
        this->area = area;
    }
    int getClueRoomCount() {
        return clueRoomCount;
    }
    bool isInsane() const {
        return getSanity() == 0;
    }
};
#endif