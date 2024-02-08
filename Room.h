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
    void addItem(const Item& item);
    void removeItem(const Item& item);
    void addExit(map<string, Room*>& exits);
};
