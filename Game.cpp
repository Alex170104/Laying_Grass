#include "Game.h"
#include "raylib.h"
#include <stdexcept>

Game::Game(int size, int sizeCell, int padding)
    : board(size), boardDisplay(board), size(size), sizeCell(sizeCell), padding(padding) {}


void Game::run() {
    int windowSize = size * sizeCell + 2 * padding;
    InitWindow(windowSize, windowSize, "Game");
    SetTargetFPS(100);

    while (!WindowShouldClose()) {
        handleMouseClick();
        boardDisplay.display(size, sizeCell, padding);
    }
    CloseWindow();
}

void Game::handleMouseClick() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        int x = (mousePosition.x - padding) / sizeCell;
        int y = (mousePosition.y - padding) / sizeCell;

        if (x >= 0 && x < size && y >= 0 && y < size) {
            Case& clickedCase = board.getCase(y, x);
            clickedCase.setCasePlayer(1); // Example: set player to 1
        }
    }
}