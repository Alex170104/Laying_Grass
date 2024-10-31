//
// Created by alexd on 30/10/2024.
//

#ifndef LAYING_GRASS_PLAYER_H
#define LAYING_GRASS_PLAYER_H

#include <string>

using namespace std;

class Player {
public:
    string name;
    string color;
    int tileX, tileY; // Coordonnées de la tuile de départ
    int tileCoupons;

    Player(const string& playerName, const string& playerColor);
    void setStartingTile(int x, int y);
};


#endif //LAYING_GRASS_PLAYER_H
