#include "Ghost.h"

void Ghost::upateState() {
    if (player->getClueCount() > 0 && currentState == Idle) {
        currentState = Roaming;
    }
}
void Ghost::updateStateOnPlayerMove() {
    if (currentState == Roaming) {
        int random = rand() % 100;
        if (random < 20) {
            cout << "A chill runs down your spine..." << endl;
            currentState = Hunting;
        }
    }
}
void Ghost::roam() {
    if (currentState == Roaming) {
        Room* newRoom = area->getRandomRoom();
        if (newRoom != nullptr) {
            currentRoom = newRoom;
        }
    }
}
vector<Room*> Ghost::pathFindToPlayer() {
    map<Room*, Room*> prev;     // This keeps track of the path the ghost has taken.
    queue<Room*> queue;
    Room* start = currentRoom;
    Room* end = player->getLocation();
    queue.push(start);
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
            if (prev.find(nextRoom) == prev.end()) {
                queue.push(nextRoom);
                prev[nextRoom] = room;
            }
        }
    }
    return {};
}
void Ghost::hunt() {
    if (currentRoom == player->getLocation()) {
        player->takeDamage(10);
        currentState = Roaming;
    }
    if (currentState == Hunting) {
        vector<Room*> path = pathFindToPlayer();
        if (!path.empty()) {
            currentRoom = path[1];
        }
    }
}