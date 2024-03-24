#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "item.h"
using namespace std;

class Character {
private:
    string name;
    int sanity;
    vector<Item> inventory;
public:
    Character(const string& name, int sanity) : name(name), sanity(sanity) {}
    void takeDamage(int damage);
    void AddToInv(const Item& item);
    string getName() const {
        return name;
    }
    int getSanity() const {
        return sanity;
    }
    void setName(const string& nName) {
        name = nName;
    }
    void setSanity(int nSanity) {
        sanity = nSanity;
    }
};
