#ifndef LAYING_GRASS_BOARD_H
#define LAYING_GRASS_BOARD_H

#include <vector>
#include "Case.h"

class Board {
public:
    Board(int size);
    vector<vector<Case>> getBoard() const { return grid; }
    Case &getCase(int x, int y);

protected:
    vector<vector<Case>> grid;

};

#endif //LAYING_GRASS_BOARD_H
