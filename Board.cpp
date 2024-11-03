#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int size) {
    board.resize(size, vector<Case>(size, Case(0, 0, 0, 0)));
    cout << "Board created:" << endl;
}

Case& Board::getCase(int x, int y) {
    return board[x][y];
}