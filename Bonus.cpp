//
// Created by alexd on 15/11/2024.
//

#include "Bonus.h"

using namespace std;

Bonus::Bonus() {}

void Bonus::popUpBonus(float startTime, int sizeCell, int size, int padding, string text, BoardDisplay boardDisplay, int startX, int startY, int sizeCellPreview, int previewSize, int previewPadding, bool firstTurn, vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, vector<Player> listPlayers, vector<vector<int>> selectedTile) {
    while (GetTime() - startTime < 2.0f) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers);
        DrawRectangle((GetScreenWidth() - 500) / 2, padding + (size * sizeCell) / 2 - 50, 500, 100,
                      WHITE);
        DrawText(text.c_str(),
                 (GetScreenWidth() - MeasureText(text.c_str(), 30)) / 2,
                 padding + (size * sizeCell) / 2 - 15, 30, BLACK);
        EndDrawing();
    }
}

void Bonus::ticketExchange(vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, int i){
    playerTiles[currentPlayer][playerTiles[currentPlayer].size() - 1] = playerTiles[currentPlayer][playerTiles[currentPlayer].size() - 1 - i];
    playerTiles[currentPlayer].erase(playerTiles[currentPlayer].end() - 1 - i, playerTiles[currentPlayer].end() - 1);
}

bool Bonus::stone(bool clickEmptyCase, Board &board, int sizeCell, int padding) {
    if (clickEmptyCase) {

    }
    return clickEmptyCase;
}

void Bonus::robbery(Board& board, int currentPlayer, bool& robber, const vector<Player>& listPlayers, vector<vector<vector<vector<int>>>>& playerTiles) {
        bool displayPlayer = true;
        bool displayTileRobbery = false;
        int startX = 100;
        int startY = 500;
        int nameWidth = 200;
        int nameHeight = 70;
        int namePadding = 20;
        string selectedPlayerName;
        int selectedPlayerIndex = -1;
        while (robber) {

            BeginDrawing();
            ClearBackground(RAYWHITE);

            if (displayPlayer) {

                DrawText("Vous pouvez choisir un joueur pour lui dérober une tuile", startX + 10, 300, 30, BLACK);

                for (int i = 0; i < listPlayers.size(); ++i) {
                    int posX = startX + (i % 3) * (nameWidth + namePadding);
                    int posY = startY + (i / 3) * (nameHeight + namePadding);

                    if (i == currentPlayer) {
                        DrawRectangle(posX, posY, nameWidth, nameHeight, Fade(GRAY, 0.25f));
                        DrawText(listPlayers[i].getName().c_str(), posX + 10, posY + 15, 30, GRAY);
                    } else {
                        DrawRectangle(posX, posY, nameWidth, nameHeight, Fade(listPlayers[i].getColor(), 0.25f));
                        DrawText(listPlayers[i].getName().c_str(), posX + 10, posY + 15, 30, listPlayers[i].getColor());
                    }
                }
            }
            if (displayTileRobbery) {

                int sizeCellPreview = 40;
                int previewSize = 5;
                int previewPadding = 175;

                ClearBackground(RAYWHITE);
                DrawText("Choisissez une tuile à derober à :", startX + 10, 300, 40, BLACK);
                DrawText(listPlayers[selectedPlayerIndex].getName().c_str(), startX + 10, 350, 40, listPlayers[selectedPlayerIndex].getColor());

                for (int i = 0; i < previewSize && i < playerTiles[selectedPlayerIndex].size(); ++i) {
                    int offsetX = startX + (sizeCellPreview + previewPadding) * i;
                    int offsetY = startY;

                    vector<vector<int>> tilePattern = playerTiles[selectedPlayerIndex][playerTiles[selectedPlayerIndex].size() - 1 -
                                                                                 i];
                    for (int row = 0; row < tilePattern.size(); ++row) {
                        for (int col = 0; col < tilePattern[row].size(); ++col) {
                            if (tilePattern[row][col] == 1) {
                                int posX = offsetX + col * sizeCellPreview;
                                int posY = offsetY + row * sizeCellPreview;
                                Color color = listPlayers[selectedPlayerIndex].getColor();
                                DrawRectangle(posX, posY, sizeCellPreview, sizeCellPreview, color);
                                DrawRectangleLines(posX, posY, sizeCellPreview, sizeCellPreview, BLACK);
                            }
                        }
                    }
                }
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePosition = GetMousePosition();

                if (displayPlayer) {
                    for (int i = 0; i < listPlayers.size(); ++i) {
                        int posX = startX + (i % 3) * (nameWidth + namePadding);
                        int posY = startY + (i / 3) * (nameHeight + namePadding);
                        if (mousePosition.x > posX && mousePosition.x < posX + nameWidth &&
                            mousePosition.y > posY && mousePosition.y < posY + nameHeight) {
                            if (i != currentPlayer) {
                                displayTileRobbery = true;
                                displayPlayer = false;
                                selectedPlayerIndex = i;
                            }
                        }
                    }
                }else if (displayTileRobbery){
                    robber = false;
                }
            }

            EndDrawing();
        }
    }



