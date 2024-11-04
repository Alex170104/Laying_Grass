#include "BoardDisplay.h"
#include <iostream>
using namespace std;

BoardDisplay::BoardDisplay(Board& board) : board(board) {
    imgBonusStone = LoadImage("../img/the_rock.png");
    cout << "Image loaded" << endl;
    textureBonusStone = LoadTextureFromImage(imgBonusStone);
    cout << "Texture loaded" << endl;
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
            } else if (currentCase.getType() == 2) {
                // Draw the image for type 2
                DrawTexture(textureBonusStone, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            }
        }
    }

    EndDrawing();
}