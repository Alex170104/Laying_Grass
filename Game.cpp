#include "Game.h"
#include "raylib.h"
#include "Tiles.h"
#include <iostream>
#include <random>

Game::Game(int size, int nbPlayer, int sizeCell, int padding, vector<Player> listPlayers)
        : board(size, nbPlayer), nbPlayer(nbPlayer), boardDisplay(board, sizeCell), size(size), sizeCell(sizeCell), padding(padding), listPlayers(listPlayers){}


void Game::run() {
    Tiles tiles;

    int currentPlayer = 0;
    vector<vector<vector<vector<int>>>> playerTiles = tiles.distributeTiles(nbPlayer);
    vector<vector<int>> selectedTile = playerTiles[currentPlayer].back();
    playerTiles[currentPlayer].pop_back();

    bool isPreviewing = true;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(Color {192, 192, 192, 255});

        bool firstTurn;
        if (listPlayers[currentPlayer].getNbTilesPlaced() == 0) {
            firstTurn = true;
        } else {
            firstTurn = false;
        }
        boardDisplay.display(size, sizeCell, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers);

        if (IsKeyPressed(KEY_SPACE)) {
            isPreviewing = true;
        }

        if (isPreviewing) {

            Vector2 mousePosition = GetMousePosition();
            int x = (mousePosition.x - padding) / sizeCell;
            int y = (mousePosition.y - padding) / sizeCell;

            bool validPosition = tiles.isValidPosition(x, y, board, size, selectedTile);

            if (firstTurn) {
                if (!(x >= 0 && x < size / 2 && y >= 0 && y < size / 2)) {
                    validPosition = false;
                }
            }


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

            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                tiles.rotateTilePattern(selectedTile);
            }
            if (IsKeyPressed(KEY_F)) {
                tiles.flip(selectedTile);
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            isPreviewing = !isPreviewing;
        }

        EndDrawing();
    }
    CloseWindow();
}

int Game::biggerSquare(int player) {
    int maxSquare = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board.getCase(i, j).getCasePlayer() == player) {
                bool alwaySquare = true;
                while (alwaySquare) {
                    int square = 1;
                    for (int k = 1; k < size; k++) {
                        if (i + k < size && j + k < size) {
                            if (board.getCase(i + k, j).getCasePlayer() == player &&
                                board.getCase(i, j + k).getCasePlayer() == player &&
                                board.getCase(i + k, j + k).getCasePlayer() == player) {
                                square++;
                            } else {
                                alwaySquare = false;
                                break;
                            }
                        } else {
                            alwaySquare = false;
                            break;
                        }
                    }
                    if (square > maxSquare) {
                        maxSquare = square;
                    }
                }
            }
        }
    }
    return maxSquare;
}