#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int nbPlayer, int size) {

    // Initialize the board
    board.resize(size, vector<Case>(size, Case(0, 0, 0, 0)));
}