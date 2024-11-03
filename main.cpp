#include <iostream>
#include "Board.h"
#include "BoardDisplay.h"
#include "raylib.h"

int sizeBoard(int player);

using namespace std;

int main() {
    int nbPlayer = 5;
    int size = sizeBoard(nbPlayer);
    Board board(nbPlayer, size);

    BoardDisplay boardDisplay(board);
    int sizeCell = (nbPlayer > 4) ? 30 : 50;
    int padding = 50;
    int windowSize = size * sizeCell + 2 * padding;


    // Initialisation de Raylib
    InitWindow(windowSize, windowSize, "Board Display");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        boardDisplay.display(size);
    }

    // Fermeture de Raylib
    CloseWindow();

    return 0;
}

int sizeBoard(int nbPlayer) {
    int size;
    if (2 <= nbPlayer && nbPlayer <= 4){
        size = 20;
    }
    else if (5 <= nbPlayer && nbPlayer <= 9){
        size = 30;
    }
    return size;
}
