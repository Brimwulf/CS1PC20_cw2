#include "Player.h"

Room* Player::getLocation() {
    return location;
}
void Player::setLocation(Room* room) {
    location = room;

    // Print out any clues that are in the room.
    const vector<Clue*>& clues = room->getClues();
    for (Clue* clue : clues) {
        if (clue != nullptr) {
            cout << clue->getDescription() << endl;
            clueRoomCount++;
        }

        else {
            cout << "Found null clue in the room" << endl;
        }
    }
}
void Player::move(string direction) {
    Room* currentRoom = this->getLocation();
    map<string, Room*> exits = currentRoom->getExits();
    Room* nextRoom = exits[direction];
    if (exits.find(direction) != exits.end()) {      // Checking if the room exists
        this->setLocation(nextRoom);
    }
    else {
        cout << "You can't go that way" << endl;
    }
}
void Player::addClue(Clue* clue) {
    if (clue != nullptr) {
        clues.push_back(clue);
    }
    else {
        cout << "DEBUG: Returned nullptr at addclue" << endl;
    }
}
int Player::getClueCount() const {
    return clues.size();
}