#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "item.h"
#include "GameObject.h"
using namespace std;

class Room {
private:
    string description;
    map<string, Room*> exits;
    vector<Item> items;
    vector<Clue*> clues;
public:
    Room(const string& desc) : description(desc) {}
    void addItem(const Item& item);
    void addClue(Clue* clue);
    void removeItem(const Item& item);
    void addExit(const string& direction, Room* room);
    map<string, Room*> getExits() const;
    bool hasClue(Clue* clue);
    string getDescription() {
        return description;
    }
    const vector<Clue*>& getClues() const {
        return clues;
    }
};

class Area {
private:
    map<string, Room*> rooms;
public:
    void addRoom(const string& name, Room* room);
    Room* getRoom(const string& name);
    Room* getRandomRoom();
    void connectRooms(const string& room1, const string& room2, const string& direction);   
    void loadMapFromFile(const string& filename);
    int getNumberOfRooms() const {
        return rooms.size();
    }
};

#endif