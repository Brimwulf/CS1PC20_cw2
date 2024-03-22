#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "item.h"
using namespace std;

class Room {
private:
    string description;
    map<string, Room*> exits;
    vector<Item> items;
public:
    Room(const string& desc);
    void addItem(const Item& item) {
        items.push_back(item);
    }
    /*
    * The member function below handles the erasing of an item from the item vector.
    * It scans through the vector comparing the name in "it" to the item passed into the function.
    * If it matches, it erases it from the vector. The "->" is accessing the member of item using a pointer.
    */
    void removeItem(const Item& item) {
        for (auto it = items.begin(); it != items.end(); it++) {
            if (it->getName() == item.getName()) {
                items.erase(it);
                break;
            }
        }
    }
    void addExit(const string& direction, Room* room) {     // This function is taking the string from the function call and the room and adding it to exits.
        exits[direction] = room;
    }
};

class Area {
private:
    map<string, Room*> rooms;
public:
    void addRoom(const string& name, Room* room) {
        rooms.insert({ name,room }); //inserts the room into the map.
    }
    Room* getRoom(const string& name) {
        if (rooms.find(name) != rooms.end()) {
            return rooms[name];
        }
        else {
            return nullptr;     // This is an error catch which checks if the room does actually exit. Returning a ull pointer if not.
        }
    }
    void connectRooms(const string& room1, const string& room2, const string& direction) {
        Room* addRoom1 = getRoom(room1);
        Room* addRoom2 = getRoom(room2);
        if (addRoom1 != nullptr && addRoom2 != nullptr) {   // checking the rooms exist.
            addRoom1->addExit(direction, addRoom2);
        }
    }
    /*
    * This method wasn't immediately obvious to write and I did use generative AI so I will explain how it works. First off this method
    * wouldn't work without the fstream library which is included at the top of this file. It uses the ifstream object to read from the file passed
    * into this method. If the file was not successfully read (!file) then it outputs the error message. Then there's a while loop which steps through
    * every line in the file to read the data. It uses the comma position which allows it to seperate the name and the description in the file
    * and add them to a variable accordingly. Then it creates the room and uses the addRoom method.
    */
    void loadMapFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Unable to open map file." << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            size_t commaPosition = line.find(',');
            if (commaPosition != string::npos) {
                string name = line.substr(0, commaPosition);
                string desc = line.substr(commaPosition + 1);
                Room* room = new Room(desc);
                addRoom(name, room);
            }
        }
    }
};