#ifndef LAYING_GRASS_BOARD_H
#define LAYING_GRASS_BOARD_H

#include <vector>
#include "Case.h"

class Board {
public:
    Board(int size);
    vector<vector<Case>> getBoard() const { return board; }
    Case &getCase(int x, int y);

private:
    vector<vector<Case>> board;


};

#endif //LAYING_GRASS_BOARD_H
