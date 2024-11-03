#include "BoardDisplay.h"
#include <iostream>
using namespace std;

BoardDisplay::BoardDisplay(Board& board) : board(board) {}

void BoardDisplay::display(int size, int sizeCell, int padding) {

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Case& currentCase = board.getCase(i, j);
            Color color = currentCase.caseColor();
            DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, color);
            DrawRectangleLines(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, BLACK); // Draw the border
        }
    }
}
