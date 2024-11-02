#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int nbPlayer) {
    if (2 <= nbPlayer && nbPlayer <= 4){
        size = 20;
    }
    else if (5 <= nbPlayer && nbPlayer <= 9){
        size = 30;
    }

    // Initialize the board
    board.resize(size, vector<Case>(size, Case(0, 0, 0, 0)));
}

void Board::printBoard() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i][j].caseColor() << " ";
        }
        cout << endl;
    }
}