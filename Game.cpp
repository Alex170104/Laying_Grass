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

                //Fin de jeu
                win(currentPlayer);
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

void Game::win(int currentPlayer) {
    if (listPlayers[currentPlayer].getNbTilesPlaced() == 10) {
        int playerWinFinal = 0;
        vector<int> playerWinners;
        int maxSquare = 0;
        for (int i = 1; i < nbPlayer+1; i++) {
            int square = biggerSquare(i);
            if (square > maxSquare) {
                playerWinners.clear();
                playerWinners.push_back(i);
                maxSquare = square;
            } else if (square == maxSquare) {
                playerWinners.push_back(i);
            }
        }
        if (playerWinners.size() == 1) {
            playerWinFinal = playerWinners[0];
        } else {
            int maxGrass = 0;
            for (int i = 1; i < playerWinners.size()+1; i++) {
                int grass = nbGrassPlaced(playerWinners[i]);
                if (grass >= maxGrass) {
                    playerWinFinal = playerWinners[i];
                    maxGrass = grass;
                }
            }
        }
        cout << "Player " << listPlayers[playerWinFinal-1].getName() << " win !" << std::endl;
    }
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