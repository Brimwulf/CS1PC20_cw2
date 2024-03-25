#include "CommandInterpreter.h"
#include "GameSaverLoader.h"

void commandInterpreter::interpretCommand(const string& command, const string& subCommand = "") {
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
        GameSaverLoader saver;
        saver.saveGame("savefile.txt", *player_);
    }
    if (command == "load") {
        GameSaverLoader loader;
        loader.loadGame("savefile.txt", *player_, *area_);
    }
    if (command == "read ghost manual") {
        cout << "Ghost types:" << endl;
        cout << "Demon: A malevolent entity from hell.\nEvidence: A smell of burning lingers where this ghost has been\nReports of pentograms and other runes\nAn inexplicable feeling of dread in places the demon has been\n" << endl;
        cout << "Poltergeist: A particularly active spirit that can affect the physical world\n Evidence: An inexplicable feeling of dread in places the poltergeist has been\nDisturbed objects within rooms\nAn unexplained cold breeze in rooms the poltergeist has been in\n" << endl;
        cout << "Yōkai: A trickster spirit from Japanese folklore. \nEvidence: An unexplained cold breeze in rooms the Yōkai has been in\nReports of whispering in places a Yōkai haunts\nDisturbed objects or objects that have vanished or appeared out of thin air" << endl;
    }
    if (command == "interact with clue") {

    }
    if (command == "guess ghost") {
        if (ghost_->getType() == subCommand) {
            cout << "Congratulations, you correctly found the ghost type." << endl;
            exit(0); // for now this ends the game.
            // need to add end game logic.
        }
        else {
            cout << "Hmm... no that doesn't seem right." << endl;
        }
    }
    if (command == "check sanity") {
        player_->getSanity();
    }
    if (command == "help") {
        cout << "Command list: (command (subCommand))" << endl;
        cout << "move (direction)" << endl;
        cout << "read journal" << endl;
        cout << "save" << endl;
        cout << "load" << endl;
        cout << "read ghost manual" << endl;
        cout << "guess ghost (ghost type)" << endl;
        cout << "interact with clue" << endl;
        cout << "check sanity" << endl;
    }
    // need to add else ifs for other commands.
    // Have the ifs call Player methods like pickupitem and lookaround.
    
    cout << "Unknown command" << endl;

}

void commandInterpreter::preGameCommands(const string& command, const string& subCommand = "") {
    if (command == "load") {
        GameSaverLoader loader;
        loader.loadGame("savefile.txt", *player_, *area_);
    }
    if (command == "map") {
        if (subCommand == "Abandoned Schoolhouse") {
            area_->loadMapFromFile("Abandoned_Schoolhouse.txt");
        }
        if (subCommand == "Eery Asylum") {
            area_->loadMapFromFile("Eery_Asylum.txt");
        }
        if (subCommand == "Old Mansion") {
            area_->loadMapFromFile("Old_Mansion.txt");
        }
        cout << "No such map as: " << subCommand << endl;
    }
    if (command == "help") {
        cout << "load or map (map) - command structure." << endl;
        cout << "Maps are: Abandoned Schoolhouse, Eery Asylum, Old Mansion" << endl;
    }
}