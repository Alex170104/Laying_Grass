#ifndef LAYING_GRASS_TILES_H
#define LAYING_GRASS_TILES_H

#include "Board.h"

class Tiles {
public:
    Tiles();
    void placeTile(int x, int y, int player, Board& board);
    void rotateTilePattern();

private:
    int tilePattern[3][3];
};

#endif //LAYING_GRASS_TILES_H