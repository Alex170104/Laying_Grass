#include "BoardDisplay.h"
#include <iostream>

using namespace std;

BoardDisplay::BoardDisplay(Board& board, int sizeCell) : board(board), sizeCell(sizeCell) {
    Image imgBonusStone = LoadImage("../img/rock.png");
    Image imgBonusTicket = LoadImage("../img/ticket.png");
    Image imgBonusVol = LoadImage("../img/vol.png");
    Image imgFissure = LoadImage("../img/fissure.png");
    ImageResize(&imgBonusStone, sizeCell, sizeCell);
    ImageResize(&imgBonusTicket, sizeCell, sizeCell);
    ImageResize(&imgBonusVol, sizeCell, sizeCell);
    ImageResize(&imgFissure, sizeCell, sizeCell);
    textureBonusStone = LoadTextureFromImage(imgBonusStone);
    textureBonusTicket = LoadTextureFromImage(imgBonusTicket);
    textureBonusVol = LoadTextureFromImage(imgBonusVol);
    textureFissure = LoadTextureFromImage(imgFissure);
    UnloadImage(imgBonusStone);
    UnloadImage(imgBonusTicket);
    UnloadImage(imgBonusVol);
    UnloadImage(imgFissure);
}

BoardDisplay::~BoardDisplay() {
    UnloadTexture(textureBonusStone);
    UnloadTexture(textureBonusTicket);
    UnloadTexture(textureBonusVol);
    UnloadTexture(textureFissure);
}

void BoardDisplay::display(int startX, int startY, int size, int sizeCell, int sizeCellPreview, int previewSize, int previewPadding, int padding, bool firstTurn, const vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, const vector<vector<int>>& selectedTile, vector<Player> listPlayers) {

    string currentPlayerName = listPlayers[currentPlayer].getName();
    Color currentPlayerColor = listPlayers[currentPlayer].getColor();
    DrawText(currentPlayerName.c_str(), startX, padding - 40, 30, currentPlayerColor);

    if (firstTurn) {
        DrawText("INITIALIZATION", startX + 350, padding - 40, 30, BLACK);
    } else if (listPlayers[currentPlayer].getNbTilesPlaced() < 10) {
        DrawText(("TURN " + to_string(listPlayers[currentPlayer].getNbTilesPlaced())).c_str(), startX + 490, padding - 40, 30, BLACK);
    }
    else {
        DrawText("GAME OVER", startX + 415, padding - 40, 30, BLACK);
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
            }else if (currentCase.getType() == 5) {
                DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, DARKGRAY);
                DrawRectangleLines(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, BLACK);
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

    DrawText("COUPON D'ECHANGE", startX + 675, startY - 60, 30, BLACK);
    DrawText(to_string(listPlayers[currentPlayer].getTileCoupons()).c_str(), startX + 825, startY, 30, BLACK);
    DrawRectangle(startX + 750, startY + 45, 165, 60, Fade(BLACK, 0.5f));
    DrawText("UTILISER", startX + 760, startY + 60, 30, WHITE);

}