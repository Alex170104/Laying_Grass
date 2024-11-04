#ifndef LAYING_GRASS_BOARDDISPLAY_H
#define LAYING_GRASS_BOARDDISPLAY_H

#include "raylib.h"
#include "Board.h"

class BoardDisplay {
public:
    BoardDisplay(Board& board, int sizeCell);
    ~BoardDisplay();
    void display(int size, int sizeCell, int padding);


private:
    Board& board;
    Texture2D textureBonusStone;
    Texture2D textureBonusTicket;
    Texture2D textureBonusVol;
    int sizeCell;
};

#endif //LAYING_GRASS_BOARDDISPLAY_H