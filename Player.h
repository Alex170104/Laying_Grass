#ifndef LAYING_GRASS_PLAYER_H
#define LAYING_GRASS_PLAYER_H

#include <string>
#include "raylib.h"

class Player {
public:
    Player(const std::string& playerName, const Color playerColor);
    void setStartingTile(int x, int y);
    int getNbTilesPlaced() const;
    void incrementNbTilesPlaced();
    std::string getName() const;
    void addChar(char c);
    Color getColor() const;
    void setColor(const Color playerColor);
private:
    std::string name;
    Color color;
    int tileX, tileY;
    int tileCoupons;
    int nbTilesPlaced;
};


#endif //LAYING_GRASS_PLAYER_H
