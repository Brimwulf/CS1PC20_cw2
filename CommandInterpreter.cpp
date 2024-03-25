#include "CommandInterpreter.h"
#include "GameSaverLoader.h"

void commandInterpreter::interpretCommand(const string& command) {
    // This function will have a series of commands which are triggered by ifs.
    string action, subAction;
    // Trim leading and trailing spaces from the command.
    string trimmedCommand = command;
    size_t first = trimmedCommand.find_first_not_of(' ');
    size_t last = trimmedCommand.find_last_not_of(' ');
    if (first != string::npos && last != string::npos) {
        trimmedCommand = trimmedCommand.substr(first, (last - first + 1));
        // Splitting the command into action and subaction.
        action = trimmedCommand.substr(0, trimmedCommand.find(" "));
        subAction = trimmedCommand.substr(trimmedCommand.find(" ") + 1);
    }
    else {
        cout << "Command cannot be empty or composed entirely of spaces." << endl;
    }

    if (action == "move") {
        player_->move(subAction);
        ghost_->updateStateOnPlayerMove();
        if (player_->getLocation() != nullptr) {
            cout << player_->getLocation()->getDescription() << endl;
        }
        else {
            cout << "DEBUG: returned nullptr at move." << endl;
        }
    }
    else if (action == "read_journal") {
        journal_->readJournal();
    }
    else if (action == "save") {
        GameSaverLoader saver;
        saver.saveGame("savefile.txt", *player_);
    }
    else if (action == "load") {
        GameSaverLoader loader;
        loader.loadGame("savefile.txt", *player_, *area_);
    }
    else if (action == "read_ghost_manual") {
        cout << "Ghost types:" << endl;
        cout << "Demon: A malevolent entity from hell.\nEvidence: A smell of burning lingers where this ghost has been\nReports of pentograms and other runes\nAn inexplicable feeling of dread in places the demon has been\n" << endl;
        cout << "Poltergeist: A particularly active spirit that can affect the physical world\n Evidence: An inexplicable feeling of dread in places the poltergeist has been\nDisturbed objects within rooms\nAn unexplained cold breeze in rooms the poltergeist has been in\n" << endl;
        cout << "Yokai: A trickster spirit from Japanese folklore. \nEvidence: An unexplained cold breeze in rooms the Yōkai has been in\nReports of whispering in places a Yōkai haunts\nDisturbed objects or objects that have vanished or appeared out of thin air" << endl;
    }
    else if (action == "guess_ghost") {
        if (ghost_->getType() == subAction) {
            cout << "Congratulations, you correctly found the ghost type." << endl;
            gameOver = true;
        }
        else {
            //cout << "Hmm... no that doesn't seem right." << endl;
            //Change this case to this when done with code:
            cout << "You guessed incorrectly, game over." << endl;
            gameOver = true;
        }
    }
    else if (action == "check_sanity") {
        int sanity = player_->getSanity();
        cout << "Your current sanity level is: " << sanity << endl;
    }
    else if (action == "help") {
        cout << "Command list: (command (subCommand))" << endl;
        cout << "move (direction)" << endl;
        cout << "read_journal" << endl;
        cout << "save" << endl;
        cout << "load" << endl;
        cout << "read_ghost_manual" << endl;
        cout << "guess_ghost (ghost type)" << endl;
        cout << "check_sanity" << endl;
        cout << "quit" << endl;
    }
    else if (action == "quit") {
        gameOver = true;
    }
    // need to add else ifs for other commands.
    // Have the ifs call Player methods like pickupitem and lookaround.
    else {
        cout << "Unknown command" << endl;
    }
}

void commandInterpreter::preGameCommands(const string& command, const string& subCommand) {
    if (command == "load") {
        GameSaverLoader loader;
        loader.loadGame("savefile.txt", *player_, *area_);
    }
    if (command == "map") {
        if (subCommand == "Abandoned Schoolhouse") {
            area_->loadMapFromFile("Abandoned_Schoolhouse.txt");
        }
        else if (subCommand == "Eery Asylum") {
            area_->loadMapFromFile("Eery_Asylum.txt");
        }
        else if (subCommand == "Old Mansion") {
            area_->loadMapFromFile("Old_Mansion.txt");
        }
        else {
            cout << "No such map as: " << subCommand << endl;
        }
    }
    if (command == "help") {
        cout << "load or map (map) - command structure." << endl;
        cout << "Maps are: Abandoned Schoolhouse, Eery Asylum, Old Mansion" << endl;
    }
}