#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int size) {
    grid = vector<vector<Case>>(size, vector<Case>(size, Case(0, 0, 5, 0)));
    cout << "Board created:" << endl;
}

Case& Board::getCase(int x, int y) {
    return grid[x][y];
}