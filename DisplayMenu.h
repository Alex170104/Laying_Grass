#ifndef LAYING_GRASS_DISPLAYMENU_H
#define LAYING_GRASS_DISPLAYMENU_H

#include <iostream>
#include <vector>
#include "raylib.h"

using namespace std;

class DisplayMenu {
public:
    DisplayMenu(int screenWidth, int screenHeight);
    void showMenu();
    bool isGameStart();
    int getNumPlayers() { return playerNames.size();};
    vector<string> getPlayerNames(){ return playerNames;};
    vector<Color> getPlayerColors(){ return playerColors;};

private:
    int screenWidth;
    int screenHeight;
    bool gameStart;
    int numPlayers;
    int selectedPlayer;
    vector<string> playerNames;
    vector<Color> playerColors;
    vector<Color> availableColors;
    void drawMenu();
    void handleInput();
};

#endif //LAYING_GRASS_DISPLAYMENU_H