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
    Item(const string& name, const string& desc);
    void Interact();
    void getName();
    void getDescription();
};