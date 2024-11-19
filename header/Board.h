#ifndef LAYING_GRASS_BOARD_H
#define LAYING_GRASS_BOARD_H

#include <vector>
#include "Case.h"

/**
 * @class Board
 * @brief Représente un plateau de jeu contenant des cases.
 */
class Board {
public:
    Board(int size, int nbPlayer);
    vector<vector<Case>> getBoard() const { return grid; }
    Case &getCase(int x, int y);
    vector<vector<Case>> createBoard();
    void displayType();
    void displayCasePlayer();
    bool hasCrack();
protected:
    vector<vector<Case>> grid;
    int size;
    int nbPlayer;
};

#endif //LAYING_GRASS_BOARD_H
