#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int size): size(size) {
    grid = createBoard();
    displayType();
}

vector<vector<Case>> Board::createBoard() {
    grid = vector<vector<Case>>(size, vector<Case>(size, Case(0, 0, 0, 0)));
    for (int i = 1; i < size-1; ++i) {
        for (int j = 1; j < size-1; ++j) {
            grid[i][j].setType(2);
        }
    }
    return grid;
}

Case& Board::getCase(int x, int y) {
    return grid[x][y];
}

void Board::displayType() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << grid[i][j].getType() << " ";
        }
        cout << endl;
    }
}