#include "Ghost.h"
#include <set>

void Ghost::upateState() {
    if (player->getClueRoomCount() > 0 && currentState == Idle) {
        currentState = Roaming;
    }
}
void Ghost::updateStateOnPlayerMove() {
    //cout << "\nDEBUG: ghost state: " << currentState << endl;
    //cout << "DEBUG: ghost location: " << currentRoom->getDescription() << "\n" << endl;
    if (player->getClueRoomCount() > 0 && currentState == Idle) {
        currentState = Roaming;
    }
    if (currentState == Roaming) {
        int random = rand() % 100;
        if (random < 20) {          // setting the ghost to be extremely aggressive. If I forget to change this back I'm sorry to any future players.
            cout << "A chill runs down your spine..." << endl;
            currentState = Hunting;
            hunt();
        }
        else if (currentState == Hunting) {
            hunt();
        }
        else {
            roam();
        }
    }
}
void Ghost::roam() {
    if (currentState == Roaming) {
        //cout << "Number of rooms: " << area->getNumberOfRooms() << endl;
        Room* newRoom = area->getRandomRoom();
        if (newRoom != nullptr) {
            currentRoom = newRoom;
        }
        else {
            cout << "DEBUG: Returned nullptr at newstate" << endl;
        }
    }
    else {
        cout << "DEBUG: ghost state: " << currentState << endl;
    }
}
vector<Room*> Ghost::pathFindToPlayer() {
    map<Room*, Room*> prev;     // This keeps track of the path the ghost has taken.
    set<Room*> visited;         // To make sure the loop doesn't get stuck on the same room.
    queue<Room*> queue;
    Room* start = currentRoom;
    Room* end = player->getLocation();
    queue.push(start);
    visited.insert(start);
    while (!queue.empty()) {
        Room* room = queue.front();
        queue.pop();
        if (room == end) {
            vector<Room*> path;
            for (Room* r = end; r != nullptr; r = prev[r]) {
                path.push_back(r);
            }
            reverse(path.begin(), path.end());
            return path;
        }
        for (auto& exit : room->getExits()) {
            Room* nextRoom = exit.second;
            if (visited.find(nextRoom) == visited.end()) {
                queue.push(nextRoom);
                prev[nextRoom] = room;
                visited.insert(nextRoom);
            }
        }
    }
    return {};
}
void Ghost::hunt() {
    if (currentState == Hunting) {
        vector<Room*> path = pathFindToPlayer();
        if (!path.empty() && path.size() > 1) {
            currentRoom = path[1];
        }
    }
    if (currentRoom == player->getLocation()) {
        player->takeDamage(10);
        cout << "A terrible chill passes through you..." << endl;
        currentState = Roaming;
    }
}
void Ghost::distributeClues() {
    for (Clue* clue : clues) {
        Room* room = area->getRandomRoom();
        while (room != nullptr && room->hasClue(clue)) {    // Checker to see if the room has a clue already.
            room = area->getRandomRoom();
        }     
        if (room != nullptr) {
            room->addClue(clue);
        }
        else {
            cout << "DEBUG: returned null at distribution" << endl;
        }
    }
}