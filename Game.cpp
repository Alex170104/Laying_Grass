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

    // Afficher les tuiles distribuées pour chaque joueur (optionnel)
    for (int i = 0; i < nbPlayer; ++i) {
        std::cout << "Player " << i + 1 << " tiles:" << std::endl;
        for (const auto& tile : playerTiles[i]) {
            for (const auto& row : tile) {
                for (int cell : row) {
                    std::cout << cell << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
}



void Game::run() {
    Tiles tiles;

    int selectedTileIndex = 1; //a changer
    vector<vector<int>> selectedTile = tiles.getTileList()[selectedTileIndex];

    bool isPreviewing = false;

    while (!WindowShouldClose()) {
        boardDisplay.display(size, sizeCell, padding);



        if (IsKeyPressed(KEY_SPACE)) {
            isPreviewing = true;
        }
        if (isPreviewing) {
            Vector2 mousePosition = GetMousePosition();
            int x = (mousePosition.x - padding) / sizeCell;
            int y = (mousePosition.y - padding) / sizeCell;

            bool validPosition = tiles.isValidPosition(x, y, board, size, selectedTile);

            Color tileColor = validPosition ? Fade(GREEN, 0.5f) : Fade(RED, 0.5f);

            tiles.drawTilePattern(x, y, sizeCell, padding, tileColor, selectedTile);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && validPosition) {
                tiles.placeTile(y, x, 1, board, selectedTile);

                board.displayType();
                cout << " " << endl;
                board.displayCasePlayer();
                isPreviewing = false;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                tiles.rotateTilePattern(selectedTile);
            }
            if (IsKeyPressed(KEY_F)) {
                tiles.flip(selectedTile);
            }
        }
    }
    CloseWindow();
}

int Game::getSizeCell() {
    return sizeCell;
}