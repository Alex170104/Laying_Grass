#ifndef LAYING_GRASS_TILES_H
#define LAYING_GRASS_TILES_H

#include "Board.h"

class Tiles {
public:
    Tiles();
    void placeTile(int x, int y, int player, Board& board);
    void rotateTilePattern();
    void drawTilePattern(int x, int y, int sizeCell, int padding, Color color);
    void flip();
    bool isValidPosition(int x, int y, Board &board, int size);
private:
    int tilePattern[4][4] = {
            {1, 1, 1, 1},
            {1, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    };



};

#endif //LAYING_GRASS_TILES_H