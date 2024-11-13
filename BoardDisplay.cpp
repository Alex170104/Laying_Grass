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

void BoardDisplay::display(int size, int sizeCell, int padding, bool firstTurn, const vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, const vector<vector<int>>& selectedTile, vector<Player> listPlayers) {
    int sizeCellPreview = 30;
    int previewSize = 5;
    int previewPadding = 150;
    int startX = padding;
    int startY = size * sizeCell + 2 * padding;

    string currentPlayerName = listPlayers[currentPlayer].getName();
    Color currentPlayerColor = listPlayers[currentPlayer].getColor();
    DrawText(currentPlayerName.c_str(), startX, padding - 40, 30, currentPlayerColor);

    if (firstTurn) {
        DrawText("PREMIER TOUR", startX + 750, padding - 40, 30, BLACK);
    }
    else {
        DrawText(("TOUR " + to_string(listPlayers[currentPlayer].getNbTilesPlaced())).c_str(), startX + 870, padding - 40, 30, BLACK);
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Case &currentCase = board.getCase(i, j);
            Color color;
            int playerCase = currentCase.getCasePlayer();
            if (playerCase == 0) {
                color = LIGHTGRAY;
            } else {
                playerCase--;
                color = listPlayers[playerCase].getColor();
            }
            Color colorEmpty = color;

            if (firstTurn) {
                int nbPlayer = listPlayers.size();
                vector<vector<bool>> pos;
                if (nbPlayer <= 4) {
                    pos = {{i < size / 2, j < size / 2}, {i < size / 2, j >= size / 2}, {i >= size / 2, j < size / 2}, {i >= size / 2, j >= size / 2}};
                } else {
                    pos = {{i < size / 3, j < size / 3}, {i < size / 3, j >= size / 3 && j < 2 * size / 3}, {i < size / 3, j >= 2 * size / 3},
                           {i >= size / 3 && i < 2 * size / 3, j < size / 3}, {i >= size / 3 && i < 2 * size / 3, j >= size / 3 && j < 2 * size / 3},
                           {i >= size / 3 && i < 2 * size / 3, j >= 2 * size / 3}, {i >= 2 * size / 3, j < size / 3}, {i >= 2 * size / 3, j >= size / 3 && j < 2 * size / 3},
                           {i >= 2 * size / 3, j >= 2 * size / 3}};
                }
                for (int k = 0; k < nbPlayer; ++k) {
                    if (pos[k][0] and pos[k][1]) {
                        colorEmpty = Fade(listPlayers[k].getColor(), 0.2f);
                    }
                }
            }

            if (currentCase.getType() == 0) {
                DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, colorEmpty);
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
                    Color color = listPlayers[currentPlayer].getColor();
                    DrawRectangle(posX, posY, sizeCellPreview, sizeCellPreview, color);
                    DrawRectangleLines(posX, posY, sizeCellPreview, sizeCellPreview, BLACK);
                }
            }
        }
    }
}