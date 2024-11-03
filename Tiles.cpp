#include "Tiles.h"

using namespace std;

Tiles::Tiles() {}

void Tiles::placeTile(int x, int y, int player, Board& board){
    int tilePattern[3][3] = {
            {1, 1, 1},
            {0, 0, 1},
            {0, 0, 1}
    };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (tilePattern[i][j] == 1){
                board.getCase(x + i, y + j).setCasePlayer(1);
            }
        }
    }
}

void Tiles::rotateTilePattern() {
    int rotatedPattern[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            rotatedPattern[j][2 - i] = tilePattern[i][j];
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            tilePattern[i][j] = rotatedPattern[i][j];
        }
    }
}
