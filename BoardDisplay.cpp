//
// Created by alexd on 03/11/2024.
//

#include "BoardDisplay.h"
using namespace std;

BoardDisplay::BoardDisplay(Board& board) : board(board) {}

void BoardDisplay::display(int size) {
    int sizeCell = 50;
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Color color;
            string caseColor = board.getBoard()[i][j].caseColor();
            if (caseColor == "BLUE") color = BLUE;
            else if (caseColor == "RED") color = RED;
            else if (caseColor == "GREEN") color = GREEN;
            else if (caseColor == "PINK") color = PINK;
            else if (caseColor == "GRAY") color = GRAY;
            else if (caseColor == "YELLOW") color = YELLOW;
            else if (caseColor == "ORANGE") color = ORANGE;
            else if (caseColor == "PURPLE") color = PURPLE;
            else if (caseColor == "BROWN") color = BROWN;
            else color = WHITE;

            DrawRectangle(j * sizeCell, i * sizeCell, sizeCell, sizeCell, color);
            DrawRectangleLines(j * sizeCell, i * sizeCell, sizeCell, sizeCell, BLACK); // Draw the border
        }
    }

    EndDrawing();
}
