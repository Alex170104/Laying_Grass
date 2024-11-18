//
// Created by alexd on 15/11/2024.
//

#include "Bonus.h"

using namespace std;

Bonus::Bonus() {}

void Bonus::popUpBonus(float startTime, int sizeCell, int size, int padding, string text, BoardDisplay& boardDisplay, int startX, int startY, int sizeCellPreview, int previewSize, int previewPadding, bool firstTurn, vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, vector<Player> listPlayers, vector<vector<int>> selectedTile) {
    while (GetTime() - startTime < 2.0f) {
        BeginDrawing();
        ClearBackground(GRAY);
        boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers, false, false);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                      Fade(BLACK, 0.7f));
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

tuple<vector<vector<int>>, int, int> Bonus::robbery(int currentPlayer, bool robber, vector<Player> listPlayers, vector<vector<vector<vector<int>>>> playerTiles, int previewSize, int sizeCellPreview, int previewPadding) {
    bool displayPlayer = true;
    bool displayTileRobbery = false;
    int startX = 100;
    int startY = 500;
    int nameWidth = 200;
    int nameHeight = 70;
    int namePadding = 20;
    string selectedPlayerName;
    int selectedPlayerIndex = -1;
    vector<vector<int>> tilePattern;
    while (robber) {

        BeginDrawing();
        ClearBackground(GRAY);

        if (displayPlayer) {
            DrawText("Choisissez un joueur !", startX + 10, 300, 40, WHITE);
        }
        for (int i = 0; i < listPlayers.size(); ++i) {
            int posX = startX + (i % 3) * (nameWidth + namePadding);
            int posY = startY + (i / 3) * (nameHeight + namePadding) + 300;

            if (i == currentPlayer) {
                DrawRectangle(posX, posY, nameWidth, nameHeight, Fade(DARKGRAY, 0.25f));
                DrawText(listPlayers[i].getName().c_str(), posX + (nameWidth - MeasureText(listPlayers[i].getName().c_str(), 30)) / 2, posY + (nameHeight - 30) / 2, 30, DARKGRAY);
            } else {
                DrawRectangle(posX, posY, nameWidth, nameHeight, Fade(listPlayers[i].getColor(), 0.25f));
                DrawText(listPlayers[i].getName().c_str(), posX + (nameWidth - MeasureText(listPlayers[i].getName().c_str(), 30)) / 2, posY + (nameHeight - 30) / 2, 30, WHITE);
            }
        }
        if (displayTileRobbery) {

            ClearBackground(GRAY);
            DrawText("Choisissez une tuile à derober à :", startX + 10, 300, 40, WHITE);
            DrawText(listPlayers[selectedPlayerIndex].getName().c_str(), startX + 10, 350, 40, listPlayers[selectedPlayerIndex].getColor());

            for (int i = 0; i < previewSize && i < playerTiles[selectedPlayerIndex].size(); ++i) {
                int offsetX = startX + (sizeCellPreview + previewPadding) * i;
                int offsetY = startY;

                tilePattern = playerTiles[selectedPlayerIndex][playerTiles[selectedPlayerIndex].size() - 1 -
                                                                             i];
                for (int row = 0; row < tilePattern.size(); ++row) {
                    for (int col = 0; col < tilePattern[row].size(); ++col) {
                        if (tilePattern[row][col] == 1) {
                            int posX = offsetX + col * sizeCellPreview;
                            int posY = offsetY + row * sizeCellPreview;
                            Color color = listPlayers[selectedPlayerIndex].getColor();
                            DrawRectangle(posX, posY, sizeCellPreview, sizeCellPreview, color);
                            DrawRectangleLines(posX, posY, sizeCellPreview, sizeCellPreview, WHITE);
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
                    int posY = startY + (i / 3) * (nameHeight + namePadding) + 300;
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
                for (int i = 0; i < listPlayers.size(); ++i) {
                    int posX = startX + (i % 3) * (nameWidth + namePadding);
                    int posY = startY + (i / 3) * (nameHeight + namePadding) + 300;
                    if (mousePosition.x > posX && mousePosition.x < posX + nameWidth &&
                        mousePosition.y > posY && mousePosition.y < posY + nameHeight) {
                        if (i != selectedPlayerIndex && i != currentPlayer) {
                            selectedPlayerIndex = i;
                        }
                    }
                }
                for (int i = 0; i < previewSize && i < playerTiles[selectedPlayerIndex].size(); ++i) {
                    int offsetX = startX + (sizeCellPreview + previewPadding) * i;
                    int offsetY = startY;

                    tilePattern = playerTiles[selectedPlayerIndex][playerTiles[selectedPlayerIndex].size() - 1 - i];

                    for (int row = 0; row < tilePattern.size(); ++row) {
                        for (int col = 0; col < tilePattern[row].size(); ++col) {
                            int posX = offsetX + col * sizeCellPreview;
                            int posY = offsetY + row * sizeCellPreview;
                            if (mousePosition.x > posX && mousePosition.x < posX + sizeCellPreview &&
                                mousePosition.y > posY && mousePosition.y < posY + sizeCellPreview) {
                                return {tilePattern, selectedPlayerIndex, i};
                            }
                        }
                    }
                }
            }
        }
        EndDrawing();
    }
}

int Bonus::verifBonus(Board& board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board.getCase(j, i).getType() > 1 and board.getCase(j, i).getType() < 5 and board.getCase(j, i).getCasePlayer() == 0) {
                int playerNeighbor = board.getCase(j-1, i).getCasePlayer();
                if (board.getCase(j, i+1).getCasePlayer() == playerNeighbor and board.getCase(j+1, i).getCasePlayer() == playerNeighbor and board.getCase(j, i-1).getCasePlayer() == playerNeighbor) {
                    if (playerNeighbor != 0) {
                        board.getCase(j, i).setCasePlayer(playerNeighbor);
                        return board.getCase(j, i).getType();
                    }
                }
            }
        }
    }
    return 0;
}