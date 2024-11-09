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

void BoardDisplay::display(int size, int sizeCell, int padding, bool firstTurn, int nbPlayer, const vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, const vector<vector<int>>& selectedTile, const vector<Color>& playerColors, const vector<string>& playerNames) {
    int sizeCellPreview = 30;
    int previewSize = 5;
    int previewPadding = 150;
    int startX = padding;
    int startY = size * sizeCell + 2 * padding;

    string currentPlayerName = playerNames[currentPlayer];
    Color currentPlayerColor = playerColors[currentPlayer];
    DrawText(currentPlayerName.c_str(), startX, padding - 40, 30, currentPlayerColor);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Case &currentCase = board.getCase(i, j);
            Color color = currentCase.caseColor();
            Color colorEmpty = color;
            if (firstTurn) {
                if (nbPlayer <= 4) {
                    if (i < size / 2 and j < size / 2) {
                        colorEmpty = Fade(BLUE, 0.2f);
                    }
                    else if (i < size / 2 and j >= size / 2) {
                        colorEmpty = Fade(RED, 0.2f);
                    }
                    else if (i >= size / 2 and j < size / 2) {
                        colorEmpty = Fade(GREEN, 0.2f);
                    }
                    else {
                        colorEmpty = Fade(YELLOW, 0.2f);
                    }
                } else {
                    if (i < size / 3 and j < size / 3) {
                        colorEmpty = Fade(BLUE, 0.2f);
                    }
                    else if (i < size / 3 and j >= size / 3 and j < 2 * size / 3) {
                        colorEmpty = Fade(RED, 0.2f);
                    }
                    else if (i < size / 3 and j >= 2 * size / 3) {
                        colorEmpty = Fade(GREEN, 0.2f);
                    }
                    else if (i >= size / 3 and i < 2 * size / 3 and j < size / 3) {
                        colorEmpty = Fade(YELLOW, 0.2f);
                    }
                    else if (i >= size / 3 and i < 2 * size / 3 and j >= size / 3 and j < 2 * size / 3) {
                        colorEmpty = Fade(GRAY, 0.2f);
                    }
                    else if (i >= size / 3 and i < 2 * size / 3 and j >= 2 * size / 3) {
                        colorEmpty = Fade(LIME, 0.2f);
                    }
                    else if (i >= 2 * size / 3 and j < size / 3) {
                        colorEmpty = Fade(ORANGE, 0.2f);
                    }
                    else if (i >= 2 * size / 3 and j >= size / 3 and j < 2 * size / 3) {
                        colorEmpty = Fade(PURPLE, 0.2f);
                    }
                    else {
                        colorEmpty = Fade(BROWN, 0.2f);
                    }
                }
            }

            if (currentCase.getType() == 0) {
                DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, color);
                DrawRectangleLines(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell,BLACK);
            }
            else if (currentCase.getType() == 1) {
                DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, color);
                DrawRectangleLines(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell,BLACK);
            } else if (currentCase.getType() == 2) {
                DrawTexture(textureBonusTicket, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            } else if (currentCase.getType() == 3) {
                DrawTexture(textureBonusStone, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            } else if (currentCase.getType() == 4) {
                DrawTexture(textureBonusVol, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            }
        }
    }

    DrawText("TUILES A VENIR", startX, startY - 60, 30, BLACK);

    for (int i = 0; i < previewSize && i < playerTiles[currentPlayer].size(); ++i) {
        int offsetX = startX + (sizeCellPreview + previewPadding) * i;
        int offsetY = startY;

        vector<vector<int>> tilePattern = playerTiles[currentPlayer][playerTiles[currentPlayer].size() - 1 - i];
        for (int row = 0; row < tilePattern.size(); ++row) {
            for (int col = 0; col < tilePattern[row].size(); ++col) {
                if (tilePattern[row][col] == 1) {
                    int posX = offsetX + col * sizeCellPreview;
                    int posY = offsetY + row * sizeCellPreview;
                    Color color = Case(currentPlayer + 1, 0, currentPlayer + 1, 0).caseColor();
                    DrawRectangle(posX, posY, sizeCellPreview, sizeCellPreview, color);
                    DrawRectangleLines(posX, posY, sizeCellPreview, sizeCellPreview, BLACK);
                }
            }
        }
    }
}