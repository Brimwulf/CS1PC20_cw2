#include "Journal.h"

void Journal::addClue(gameObject* clue, string desc) {
    Clue* clueObj = dynamic_cast<Clue*>(clue);
    if (clueObj != nullptr) {
        clues[clue] = clueObj->getDescription();
        /*updateJournal();*/
    }
}
/*void updateJournal() {
    status =
}*/
void Journal::complete() {

}
void Journal::readJournal() const {
    if (clues.empty()) {
        cout << "No clues collected yet." << endl;
    }
    else {
        cout << "Collected clues:" << endl;
        for (const auto& clue : clues) {
            Clue* clueObj = dynamic_cast<Clue*>(clue.first);
            if (clueObj != nullptr) {
                cout << " | " << clueObj->getDescription() << " | " << clue.second << endl;
            }
        }
    }
}