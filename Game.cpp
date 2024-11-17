#include "Game.h"
#include "raylib.h"
#include "Tiles.h"
#include "displayWin.h"
#include <iostream>
#include <random>
#include "Bonus.h"

using namespace std;

Game::Game(int size, int nbPlayer, int sizeCell, int padding, vector<Player> listPlayers)
        : board(size, nbPlayer), nbPlayer(nbPlayer), size(size), sizeCell(sizeCell), padding(padding), listPlayers(listPlayers), boardDisplay(board, sizeCell){}

void Game::run() {
    Tiles tiles;
    Bonus bonus;

    int currentPlayer = 0;
    vector<vector<vector<vector<int>>>> playerTiles = tiles.distributeTiles(nbPlayer);
    vector<vector<int>> selectedTile = playerTiles[currentPlayer].back();
    playerTiles[currentPlayer].pop_back();

    bool isPreviewing = true;
    bool clickTileExchange = false;
    bool clickEmptyCase = false;
    bool robber = false;

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

        boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers);

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
                listPlayers[currentPlayer].incrementNbTilesPlaced();

                isPreviewing = true;

                int newActiveBonus = verifBonus();
                if (newActiveBonus != 0) {
                    if (newActiveBonus == 2) {
                        float startTime = GetTime();
                        string text = "+1 coupon d'échange !";
                        bonus.popUpBonus(startTime, sizeCell, size, padding, text, boardDisplay, startX, startY, sizeCellPreview, previewSize, previewPadding, firstTurn, playerTiles, currentPlayer, listPlayers, selectedTile);
                        listPlayers[currentPlayer].addTileCoupons();
                        boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers);

                    } else if (newActiveBonus == 3) {
                        isPreviewing = false;
                        float startTime = GetTime();
                        string text = "Vous avez un Bonus !";
                        bonus.popUpBonus(startTime, sizeCell, size, padding, text, boardDisplay, startX, startY, sizeCellPreview, previewSize, previewPadding, firstTurn, playerTiles, currentPlayer, listPlayers, selectedTile);
                        clickEmptyCase = true;

                    } else if (newActiveBonus == 4) {
                        isPreviewing = false;
                        float startTime = GetTime();
                        string text = "Vous avez un Bonus !";
                        bonus.popUpBonus(startTime, sizeCell, size, padding, text, boardDisplay, startX, startY, sizeCellPreview, previewSize, previewPadding, firstTurn, playerTiles, currentPlayer, listPlayers, selectedTile);
                        robber = true;
                    }
                }
                if (robber){
                    int player;
                    int index;
                    EndDrawing();
                    tie(selectedTile, player, index) = bonus.robbery(currentPlayer, robber, listPlayers, playerTiles, previewSize, sizeCellPreview, previewPadding);
                    playerTiles[player].erase(playerTiles[player].end() - index - 1);
                    robber = false;
                    isPreviewing = true;
                    continue;
                }
                if (!clickEmptyCase) {
                    currentPlayer = (currentPlayer + 1) % nbPlayer;
                    selectedTile = playerTiles[currentPlayer].back();
                    playerTiles[currentPlayer].pop_back();
                }

                if (listPlayers[currentPlayer].getNbTilesPlaced() == 10) {
                    EndDrawing();
                    BeginDrawing();
                    ClearBackground(RAYWHITE);
                    boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers);
                    EndDrawing();
                    vector<Player> orderWinners = calculWin();
                    displayWin displayWin(orderWinners);
                    displayWin.run();
                    return;
                }
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                tiles.rotateTilePattern(selectedTile);
            }
            if (IsKeyPressed(KEY_F)) {
                tiles.flip(selectedTile);
            }
        }else if (clickEmptyCase) {
            Vector2 mousePosition = GetMousePosition();
            int x = (mousePosition.x - padding) / sizeCell;
            int y = (mousePosition.y - padding) / sizeCell;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && board.getCase(y, x).getType() == 0) {
                board.getCase(y, x).setType(5);
                boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers);
                EndDrawing();
                float startTime = GetTime();
                string text = "vous avez place une pierre";
                bonus.popUpBonus(startTime, sizeCell, size, padding, text, boardDisplay, startX, startY, sizeCellPreview, previewSize, previewPadding, firstTurn, playerTiles, currentPlayer, listPlayers, selectedTile);
                BeginDrawing();
                clickEmptyCase = false;
                isPreviewing = true;
                currentPlayer = (currentPlayer + 1) % nbPlayer;
                selectedTile = playerTiles[currentPlayer].back();
                playerTiles[currentPlayer].pop_back();

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
                                    listPlayers[(currentPlayer + nbPlayer) %nbPlayer].removeTileCoupons();
                                    isPreviewing = true;
                                    boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer,
                                     selectedTile, listPlayers);
                                }
                            }
                        }
                    }
                }
                while (!clickTileExchange) {
                    if (mousePosition.x > startX + 750 && mousePosition.x < startX + 915 &&
                        mousePosition.y > startY + 45 && mousePosition.y < startY + 105) {
                        clickTileExchange = true;
                    }else{
                        break;
                    }
                }
            }
        }
        if (IsKeyPressed(KEY_SPACE) && !clickEmptyCase) {
            clickTileExchange = false;
            isPreviewing = !isPreviewing;
        }

        EndDrawing();
    }
    CloseWindow();
}

int Game::verifBonus() {
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