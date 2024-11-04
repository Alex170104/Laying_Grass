#include "Game.h"
#include "raylib.h"
#include "Tiles.h"
#include <iostream>

Game::Game(int size, int nbPlayer, int sizeCell, int padding)
        : board(size, nbPlayer), nbPlayer(nbPlayer), boardDisplay(board, sizeCell), size(size), sizeCell(sizeCell), padding(padding) {}

void Game::run() {
    Tiles tiles;

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

            bool validPosition = tiles.isValidPosition(x, y, board, size);

            Color tileColor = validPosition ? Fade(GREEN, 0.5f) : Fade(RED, 0.5f);

            tiles.drawTilePattern(x, y, sizeCell, padding, tileColor);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && validPosition) {
                tiles.placeTile(y, x, 1, board);
                isPreviewing = false;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                tiles.rotateTilePattern();
            }
            if (IsKeyPressed(KEY_F)) {
                tiles.flip();
            }
        }
    }
    CloseWindow();
}

int Game::getSizeCell() {
    return sizeCell;
}