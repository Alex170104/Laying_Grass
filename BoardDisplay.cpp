#include "BoardDisplay.h"
#include <iostream>
using namespace std;

BoardDisplay::BoardDisplay(Board& board, int sizeCell) : board(board), sizeCell(sizeCell) {
    Image imgBonusStone;
    Image imgBonusTicket;
    Image imgBonusVol;
    if (sizeCell == 40) {
        imgBonusStone = LoadImage("../img/rock40.png");
        imgBonusTicket = LoadImage("../img/ticket40.png");
        imgBonusVol = LoadImage("../img/fissure40.png");
    }
    else {
        imgBonusStone = LoadImage("../img/rock50.png");
        imgBonusTicket = LoadImage("../img/ticket50.png");
        imgBonusVol = LoadImage("../img/fissure50.png");
    }

    textureBonusStone = LoadTextureFromImage(imgBonusStone);
    textureBonusTicket = LoadTextureFromImage(imgBonusTicket);
    textureBonusVol = LoadTextureFromImage(imgBonusVol);
    UnloadImage(imgBonusStone);
    UnloadImage(imgBonusTicket);
    UnloadImage(imgBonusVol);
}

BoardDisplay::~BoardDisplay() {
    UnloadTexture(textureBonusStone);
}

void BoardDisplay::display(int size, int sizeCell, int padding) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Case &currentCase = board.getCase(i, j);
            Color color = currentCase.caseColor();
            if (currentCase.getType() == 0) {
                DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, color);
                DrawRectangleLines(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell,
                                   BLACK);
            } else if (currentCase.getType() == 1) {
                DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, color);
                DrawRectangleLines(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell,
                                   BLACK);

            } else if (currentCase.getType() == 2) {
                DrawTexture(textureBonusTicket, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            } else if (currentCase.getType() == 3) {
                DrawTexture(textureBonusStone, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            } else if (currentCase.getType() == 4) {
                DrawTexture(textureBonusVol, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            }
        }
    }
}