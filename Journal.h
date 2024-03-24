#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "GameObject.h"
using namespace std;

class gameObject;
class Clue;

// This class will be used to track the player's progress in finding the ghost. It should allow players to check what clues they have collected so far.
// I also want to add a behaviour to Ghost that makes it enter Roaming after the player collects the first clue and is more likely to enter Hunting 
// the more clues they have.
class Journal {
private:
    map<gameObject*, string> clues;  // This map will contain the collected clues.
public:
    void addClue(gameObject* clue, string desc);
    enum Status { Empty, InProgress, AllEvidenceCollected };
    Status status;
    Journal() : status(Empty) {}

    /*void updateJournal() {
        status =
    }*/
    void complete();
    void readJournal() const;
};
