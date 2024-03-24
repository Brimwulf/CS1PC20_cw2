#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Player.h"
using namespace std;

class GameSaverLoader {
public:
    void saveGame(const string& filename, Player& player);
    void loadGame(const string& filename, Player& player, Area& area);
};
