#include "Game.h"
#include "raylib.h"
#include "Tiles.h"
#include <iostream>
#include <random>

Game::Game(int size, int nbPlayer, int sizeCell, int padding)
        : board(size, nbPlayer), nbPlayer(nbPlayer), boardDisplay(board, sizeCell), size(size), sizeCell(sizeCell), padding(padding) {}

void Game::init(int nbPlayer) {
    Tiles tiles;
    vector<vector<vector<vector<int>>>> playerTiles = tiles.distributeTiles(nbPlayer);
}


void Game::run() {
    Tiles tiles;

    int currentPlayer = 0;
    vector<vector<vector<vector<int>>>> playerTiles = tiles.distributeTiles(nbPlayer);
    vector<vector<int>> selectedTile = playerTiles[currentPlayer].back();
    playerTiles[currentPlayer].pop_back();

    bool isPreviewing = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
//        ClearBackground({10,10,10,255});
        ClearBackground(GRAY);

        boardDisplay.display(size, sizeCell, padding);

        if (IsKeyPressed(KEY_SPACE)) {
            isPreviewing = true;
        }
        if (isPreviewing) {
            Vector2 mousePosition = GetMousePosition();
            int x = (mousePosition.x - padding) / sizeCell;
            int y = (mousePosition.y - padding) / sizeCell;

            bool validPosition = tiles.isValidPosition(x, y, board, size, selectedTile);

            Color playerColor = Case(currentPlayer + 1, 0, currentPlayer + 1, 0).caseColor();
            Color tileColor = validPosition ? Fade(playerColor, 0.5f) : Fade({30,30,30,255}, 0.8f);

            tiles.drawTilePattern(x, y, sizeCell, padding, tileColor, selectedTile);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && validPosition) {
                tiles.placeTile(y, x, currentPlayer + 1, board, selectedTile);

                //board.displayType();
                //cout << " " << endl;
                //board.displayCasePlayer();
                isPreviewing = false;

                currentPlayer = (currentPlayer + 1) % 4;
                selectedTile = playerTiles[currentPlayer].back();
                playerTiles[currentPlayer].pop_back();

                cout << biggerSquare(1) << endl;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                tiles.rotateTilePattern(selectedTile);
            }
            if (IsKeyPressed(KEY_F)) {
                tiles.flip(selectedTile);
            }
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