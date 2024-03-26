#include "GameSaverLoader.h"
#include "Room.h"


void GameSaverLoader::saveGame(const string& filename, Player& player) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        // Save the player's name and health
        outFile << player.getName() << endl;
        outFile << player.getSanity() << endl;
        outFile << player.getLocation() << endl;
        outFile.close();
    }
    else {
        cout << "Unable to access save file." << endl;
    }
}
void GameSaverLoader::loadGame(const string& filename, Player& player, Area& area) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string name;
        int sanity;
        string roomName;

        getline(inFile, name);
        inFile >> sanity;
        inFile.ignore();
        getline(inFile, roomName);

        player.setName(name);
        player.setSanity(sanity);
        Room* room = area.getRoom(roomName);
        if (room != nullptr) {
            player.setLocation(room);
        }
        else {
            cout << "Players room could not be found." << endl;
        }
        inFile.close();
    }
    else {
        cout << "Unable to access save file." << endl;
    }
}