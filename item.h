#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Item {
private:
    string name;
    string description;
public:
    Item(const string& name, const string& desc)
        : name(name), description(desc) {}
    bool Interact();
    string getName() const;
    string getDescription();
};
#endif