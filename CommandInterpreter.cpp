#include "CommandInterpreter.h"

void commandInterpreter::interpretCommand(const string& command) {
    // This function will have a series of commands which are triggered by ifs.
    if (command == "move") {
        string roomChoice;
        while (true) {
            cout << "enter room name" << endl;
            cin >> roomChoice;
            Room* roomMoveTo = area_->getRoom(roomChoice);
            if (roomMoveTo != nullptr) {
                player_->move(roomMoveTo);
                ghost_->updateStateOnPlayerMove();
                return;
            }
            else if (roomChoice == "cancel") {
                return;
            }
            else {
                cout << "No such room as: " << roomChoice << endl;
            }
        }
    }
    if (command == "read journal") {
        journal_->readJournal();
    }
    if (command == "save") {

    }
    if (command == "read ghost manual") {

    }
    if(command == "")
    // need to add else ifs for other commands.
    // Have the ifs call Player methods like pickupitem and lookaround.
    
    cout << "Unknown command" << endl;

}