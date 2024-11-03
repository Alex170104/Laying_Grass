//
// Created by alexd on 03/11/2024.
//

#include "Tiles.h"
#include "raylib.h"
#include <iostream>

Tiles::Tiles() {}

void Tiles::placeTile(int x, int y, int player, Board& board){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (tilePattern[i][j] == 1){
                board.getCase(x + i, y + j).setCasePlayer(1);
            }
        }
    }
}

void Tiles::rotateTilePattern() {
    int rotatedPattern[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            rotatedPattern[j][3 - i] = tilePattern[i][j];
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            tilePattern[i][j] = rotatedPattern[i][j];
        }
    }
}

void Tiles::drawTilePattern(int x, int y, int sizeCell, int padding, Color color) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (tilePattern[i][j] == 1) {
                DrawRectangle((x + j) * sizeCell + padding, (y + i) * sizeCell + padding, sizeCell, sizeCell, color);
            }
        }
    }
}

void Tiles::flip() {
    int flippedPattern[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            flippedPattern[i][3 - j] = tilePattern[i][j];
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            tilePattern[i][j] = flippedPattern[i][j];
        }
    }
}

bool Tiles::isValidPosition(int x, int y, Board& board, int size) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (tilePattern[i][j] == 1) {
                int boardX = x + i;
                int boardY = y + j;

                if (boardX < 0 || boardX >= size || boardY < 0 || boardY >= size) {
                    return false;
                }

                if (board.getCase(boardX, boardY).getCasePlayer() != 0) {
                    return false;
                }
            }
        }
    }

    return true;
}