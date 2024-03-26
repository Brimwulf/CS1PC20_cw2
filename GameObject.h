#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

//Creating a framework for interacting with objects:
class gameObject {
public:
    virtual void interact(gameObject& other) = 0;   // Virtual function which allows interact to be called at any point.
};

class Clue : public gameObject {
private:
    string description;
public:
    Clue(const string& desc) : description(desc) {} // constructor to create a clue.
    string getDescription() const;
    void interact(gameObject& other) override;
};
// use inheritance below to create some game objects. For example:
// class Key : public gameObject { ..... }
#endif // !GAMEOBJECT_H
