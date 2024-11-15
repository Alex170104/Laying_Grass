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
    void removeChar();
    Color getColor() const;
    void setColor(const Color playerColor);

    int getBiggestSquare() const;
    void setBiggestSquare(int square);
    int getNbGrassPlaced() const;
    void setNbGrassPlaced(int grass);

    int getTileCoupons() const;

    void addTileCoupons();

    void removeTileCoupons();

private:
    std::string name;
    Color color;
    int tileX, tileY;
    int tileCoupons;
    int nbTilesPlaced = 0;

    int biggestSquare;
    int nbGrass;
};


#endif //LAYING_GRASS_PLAYER_H
