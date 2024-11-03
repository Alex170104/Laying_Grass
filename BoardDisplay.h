//
// Created by alexd on 03/11/2024.
//

#ifndef LAYING_GRASS_BOARDDISPLAY_H
#define LAYING_GRASS_BOARDDISPLAY_H

#include "raylib.h"
#include "Board.h"


class BoardDisplay {
public:
    BoardDisplay(Board& board);
    void display(int size);

private:
    Board& board;
};


#endif //LAYING_GRASS_BOARDDISPLAY_H
