#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "GameObject.h"
#include "item.h"
using namespace std;

class Inventory {
private:
    vector<gameObject*> items;
public:
    void addItem(gameObject* item);
    void useItem(gameObject* item, gameObject& target);
    void dropItem(const Item& item);
};
