#include "BoardDisplay.h"
#include <iostream>
using namespace std;

BoardDisplay::BoardDisplay(Board& board, int sizeCell) : board(board), sizeCell(sizeCell) {
    if (sizeCell == 40) {
        imgBonusStone = LoadImage("../img/the_rock40.png");
    }
    else {
        imgBonusStone = LoadImage("../img/the_rock50.png");
    }

    textureBonusStone = LoadTextureFromImage(imgBonusStone);
    UnloadImage(imgBonusStone);
}

BoardDisplay::~BoardDisplay() {
    UnloadTexture(textureBonusStone);
}

void BoardDisplay::display(int size, int sizeCell, int padding) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Case& currentCase = board.getCase(i, j);
            Color color = currentCase.caseColor();
            if (currentCase.getType() == 0) {
                DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, color);
                DrawRectangleLines(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, BLACK); // Draw the border
            } else if (currentCase.getType() == 3) {
                // Draw the image for type 2
                DrawTexture(textureBonusStone, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            }
        }
    }

    EndDrawing();
}