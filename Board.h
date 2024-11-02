#ifndef LAYING_GRASS_BOARD_H
#define LAYING_GRASS_BOARD_H

#include <vector>
#include "Case.h"

class Board {
public:
    int size;
    int nbPlayer;

    Board(int nbPlayer);

    vector<vector<Case>> getBoard() const { return board; }
    void printBoard() const;

private:
    vector<vector<Case>> board;


};

#endif //LAYING_GRASS_BOARD_H
