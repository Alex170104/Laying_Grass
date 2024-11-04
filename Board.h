#ifndef LAYING_GRASS_BOARD_H
#define LAYING_GRASS_BOARD_H

#include <vector>
#include "Case.h"

class Board {
public:
    Board(int size);
    vector<vector<Case>> getBoard() const { return grid; }
    Case &getCase(int x, int y);
    vector<vector<Case>> createBoard();
    void displayType();
    void displayCasePlayer();

protected:
    vector<vector<Case>> grid;
    int size;


};

#endif //LAYING_GRASS_BOARD_H
