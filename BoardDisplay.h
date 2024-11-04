#ifndef LAYING_GRASS_BOARDDISPLAY_H
#define LAYING_GRASS_BOARDDISPLAY_H

#include "raylib.h"
#include "Board.h"

class BoardDisplay {
public:
    BoardDisplay(Board& board);
    ~BoardDisplay();
    void display(int size, int sizeCell, int padding);


private:
    Board& board;
    Image imgBonusStone;
    Texture2D textureBonusStone; // Add this line
};

#endif //LAYING_GRASS_BOARDDISPLAY_H