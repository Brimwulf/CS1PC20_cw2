#include "Player.h"

Room* Player::getLocation() {
    return location;
}
void Player::setLocation(Room* room) {
    location = room;
}
void Player::move(Room* room) {
    if (room != nullptr) {      // Checking if the room exists
        location = room;
    }
    else {
        cout << "No such room as: " << room << endl;
    }
}
void Player::addClue(Clue* clue) {
    if (clue != nullptr) {
        clues.push_back(clue);
    }
}
int Player::getClueCount() const {
    return clues.size();
}