#ifndef LAYING_GRASS_DISPLAYMENU_H
#define LAYING_GRASS_DISPLAYMENU_H

#include <iostream>
#include <vector>
#include "raylib.h"
#include "Player.h"

using namespace std;

class DisplayMenu {
public:
    DisplayMenu(int screenWidth, int screenHeight);
    void showMenu();
    bool isGameStart();
    int getNumPlayers() { return listPlayers.size();};
    vector<Player> getListPlayers(){ return listPlayers;};

private:
    int screenWidth;
    int screenHeight;
    bool gameStart;
    int numPlayers;
    int selectedPlayer;
    bool showWarning;
    double warningTimer;
    vector<Player> listPlayers;
    vector<Color> availableColors;
    Texture2D textureDANGER;
    void drawMenu();
    void handleInput();
};

#endif //LAYING_GRASS_DISPLAYMENU_H