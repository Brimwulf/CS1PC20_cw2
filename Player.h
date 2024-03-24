#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Character.h"
#include "Room.h"
#include "GameObject.h"
using namespace std;

class Room;
class Clue;

class Player : public Character {
private:
    Room* location;
    vector<Clue*> clues;
public:
    Player(const string& name, int sanity) : Character(name, sanity), location(nullptr) {}
    Room* getLocation();
    void setLocation(Room* room);
    void move(Room* room);
    void addClue(Clue* clue);
    int getClueCount() const;
    void setName(const string& nName) {
        Character::setName(nName);
    }
    void setSanity(int nSanity) {
        Character::setSanity(nSanity);
    }
};
