#include "Game.h"
#include "raylib.h"
#include "Tiles.h"
#include "displayWin.h"
#include <iostream>
#include <random>
#include "Bonus.h"

Game::Game(int size, int nbPlayer, int sizeCell, int padding, vector<Player> listPlayers)
        : board(size, nbPlayer), nbPlayer(nbPlayer), boardDisplay(board, sizeCell), size(size), sizeCell(sizeCell), padding(padding), listPlayers(listPlayers){}

void Game::run() {
    Tiles tiles;
    Bonus bonus;

    int currentPlayer = 0;
    vector<vector<vector<vector<int>>>> playerTiles = tiles.distributeTiles(nbPlayer);
    vector<vector<int>> selectedTile = playerTiles[currentPlayer].back();
    playerTiles[currentPlayer].pop_back();

    bool isPreviewing = true;
    bool clickTileExchange = false;

    int sizeCellPreview = 20;
    int previewSize = 5;
    int previewPadding = 100;
    int startX = padding;
    int startY = size * sizeCell + 2 * padding;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        bool firstTurn;
        if (listPlayers[currentPlayer].getNbTilesPlaced() == 0) {
            firstTurn = true;
        } else {
            firstTurn = false;
        }

        boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers, turnCount);

        if (isPreviewing) {

            Vector2 mousePosition = GetMousePosition();
            int x = (mousePosition.x - padding) / sizeCell;
            int y = (mousePosition.y - padding) / sizeCell;

            bool validPosition = tiles.isValidPosition(x, y, board, size, selectedTile, firstTurn, currentPlayer, nbPlayer);

            Color playerColor = listPlayers[currentPlayer].getColor();
            Color tileColor = validPosition ? Fade(playerColor, 0.5f) : Fade({30, 30, 30, 255}, 0.8f);

            tiles.drawTilePattern(x, y, sizeCell, padding, tileColor, selectedTile);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && validPosition) {
                tiles.placeTile(y, x, currentPlayer + 1, board, selectedTile);

                isPreviewing = false;

                listPlayers[currentPlayer].incrementNbTilesPlaced();
                currentPlayer = (currentPlayer + 1) % nbPlayer;
                selectedTile = playerTiles[currentPlayer].back();
                playerTiles[currentPlayer].pop_back();
                isPreviewing = true;

                if (listPlayers[currentPlayer].getNbTilesPlaced() == 3) {
                    EndDrawing();
                    BeginDrawing();
                    ClearBackground(RAYWHITE);
                    boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers, turnCount);
                    EndDrawing();
                    vector<Player> orderWinners = calculWin();
                    displayWin displayWin(orderWinners);
                }
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                tiles.rotateTilePattern(selectedTile);
            }
            if (IsKeyPressed(KEY_F)) {
                tiles.flip(selectedTile);
            }
        }else{
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePosition = GetMousePosition();
                vector<vector<int>> tileMove;
                if (clickTileExchange) {
                    for (int i = 0; i < previewSize && i < playerTiles[currentPlayer].size(); ++i) {
                        int offsetX = startX + (sizeCellPreview + previewPadding) * i;
                        int offsetY = startY;

                        for (int row = 0; row < playerTiles[currentPlayer][playerTiles[currentPlayer].size() - 1 - i].size(); ++row) {
                            for (int col = 0; col < playerTiles[currentPlayer][playerTiles[currentPlayer].size() - 1 - i][row].size(); ++col) {
                                int posX = offsetX + col * sizeCellPreview;
                                int posY = offsetY + row * sizeCellPreview;

                                if (mousePosition.x > posX && mousePosition.x < posX + sizeCellPreview &&
                                    mousePosition.y > posY && mousePosition.y < posY + sizeCellPreview) {
                                    bonus.ticketExchange(playerTiles, currentPlayer, i);
                                    isPreviewing = true;
                                    boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer,
                                     selectedTile, listPlayers, turnCount);
                                }
                            }
                        }
                    }
                }
                while (!clickTileExchange) {
                    if (mousePosition.x > startX + 750 && mousePosition.x < startX + 915 &&
                        mousePosition.y > startY + 45 && mousePosition.y < startY + 105) {
                        cout << "Ticket exchange" << endl;
                        clickTileExchange = true;
                    }
                }



            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            clickTileExchange = false;
            isPreviewing = !isPreviewing;
        }

        EndDrawing();
    }
    CloseWindow();
}

vector<Player> Game::calculWin() {
    vector<Player> winnersOrdered;
    vector<Player> listPlayersRestant;
    for (int i = 0; i < nbPlayer; i++) {
        listPlayers[i].setBiggestSquare(biggerSquare(i + 1));
        listPlayers[i].setNbGrassPlaced(nbGrassPlaced(i + 1));
        listPlayersRestant.push_back(listPlayers[i]);
    }
    while (!listPlayersRestant.empty()) {
        int maxSquare = 0;
        int maxGrass = 0;
        int index = 0;
        for (int i = 0; i < listPlayersRestant.size(); i++) {
            if (listPlayersRestant[i].getBiggestSquare() > maxSquare) {
                maxSquare = listPlayersRestant[i].getBiggestSquare();
                maxGrass = listPlayersRestant[i].getNbGrassPlaced();
                index = i;
            } else if (listPlayersRestant[i].getBiggestSquare() == maxSquare) {
                if (listPlayersRestant[i].getNbGrassPlaced() >= maxGrass) {
                    maxSquare = listPlayersRestant[i].getBiggestSquare();
                    maxGrass = listPlayersRestant[i].getNbGrassPlaced();
                    index = i;
                }
            }
        }
        winnersOrdered.push_back(listPlayersRestant[index]);
        listPlayersRestant.erase(listPlayersRestant.begin() + index);
    }
    return winnersOrdered;
}

int Game::biggerSquare(int player) {
    int maxSquare = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board.getCase(i, j).getCasePlayer() == player) {
                int square = 1;
                bool alwaySquare = true;
                while (alwaySquare) {
                    for (int k = 0; k < square; k++) {
                        for (int l = 0; l < square; l++) {
                            if (i + k >= size || j + l >= size || board.getCase(i + k, j + l).getCasePlayer() != player) {
                                alwaySquare = false;
                                break;
                            }
                        }
                        if (!alwaySquare) break;
                    }
                    if (alwaySquare) {
                        square++;
                    }
                }
                if (square - 1 > maxSquare) {
                    maxSquare = square - 1;
                }
            }
        }
    }
    return maxSquare;
}

int Game::nbGrassPlaced(int player) {
    int nbGrass = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board.getCase(i, j).getCasePlayer() == player) {
                nbGrass++;
            }
        }
    }
    return nbGrass;
}