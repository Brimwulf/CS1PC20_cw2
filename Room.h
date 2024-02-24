#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "item.h"
using namespace std;

class Room {
private:
    string description;
    map<string, Room*> exits;
    vector<Item> items;
public:
    Room(const string& desc);
    int addItem(const Item& item) {
        items.push_back(item);
    }
    int removeItem(const Item& item) {
        items.erase(item);      // This part of the code needs to erase the item passed into it by item from the items vector.
    }
    void addExit(const string& direction, Room* room) {     // This function is taking the string from the function call and the room and adding it to exits.
        exits[direction] = room;
    }
};
