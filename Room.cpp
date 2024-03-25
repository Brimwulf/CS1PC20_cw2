#include "Room.h"
using namespace std;

void Room::addItem(const Item& item) {
    items.push_back(item);
}
/*
* The member function below handles the erasing of an item from the item vector.
* It scans through the vector comparing the name in "it" to the item passed into the function.
* If it matches, it erases it from the vector. The "->" is accessing the member of item using a pointer.
*/
void Room::removeItem(const Item& item) {
    for (auto it = items.begin(); it != items.end(); it++) {
        if (it->getName() == item.getName()) {
            items.erase(it);
            break;
        }
    }
}
void Room::addExit(const string& direction, Room* room) {     // This function is taking the string from the function call and the room and adding it to exits.
    exits[direction] = room;
}
map<string, Room*> Room::getExits() const {
    return exits;
}
void Room::addClue(Clue* clue) {
    clues.push_back(clue);
}
bool Room::hasClue(Clue* clue) {        // Adding a checker function that can be used by ghost to make sure a room only has one clue.
    for (Clue* c : clues) {
        if (c == clue) {
            return true;
        }
    }
    return false;
}

// Area methods:
void Area::addRoom(const string& name, Room* room) {
    rooms.insert({ name,room }); //inserts the room into the map.
}
Room* Area::getRoom(const string& name) {
    if (rooms.find(name) != rooms.end()) {
        return rooms[name];
    }
    else {
        return nullptr;     // This is an error catch which checks if the room does actually exit. Returning a ull pointer if not.
    }
}
Room* Area::getRandomRoom() {
    if (rooms.size() == 0) {
        cout << "returned null." << endl;
        return nullptr; //error handling :)
    }
    int index = rand() % rooms.size(); // generates a random room.
    auto iterator = rooms.begin();
    advance(iterator, index);
    return iterator->second;
}
void Area::connectRooms(const string& room1, const string& room2, const string& direction) {
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
void Area::loadMapFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open map file." << endl;
        return;
    }
    string line;
    map<string, string> roomExits;
    while (getline(file, line)) {
        //cout << "Processing line: " << line << endl;
        size_t commaPosition = line.find(',');
        if (commaPosition != string::npos) {
            string name = line.substr(0, commaPosition);
            string rest = line.substr(commaPosition + 1);
            commaPosition = rest.find(',');
            string desc = rest.substr(0, commaPosition);
            Room* room = new Room(desc);
            addRoom(name, room);

            //cout << "Added room: " << name << endl;

            // Save exits for later processing
            string exits = rest.substr(commaPosition + 1);
            roomExits[name] = exits;
        }
    }

    // Now that all rooms are added, add the exits
    for (const auto& pair : roomExits) {
        string roomName = pair.first;
        string exits = pair.second;
        Room* room = getRoom(roomName);
        stringstream ss(exits);
        string exit;
        while (getline(ss, exit, ',')) {
            size_t colonPosition = exit.find(':');
            if (colonPosition != string::npos) {
                string direction = exit.substr(0, colonPosition);
                string exitRoomName = exit.substr(colonPosition + 1);
                Room* exitRoom = getRoom(exitRoomName);
                //cout << "exitRoomName is set to: " << exitRoomName << "And direction is: " << direction << endl;
                if (exitRoom != nullptr) {
                    room->addExit(direction, exitRoom);
                    //cout << "Added exit from " << roomName << " to " << exitRoomName << " in direction " << direction << endl;
                }
                else {
                    cout << "DEBUG: Returned nullptr at loadmap" << endl;
                }
            }
        }
    }

}