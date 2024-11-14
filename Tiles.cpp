#include "Tiles.h"
#include "raylib.h"
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

Tiles::Tiles() {}

void Tiles::placeTile(int x, int y, int player, Board& board, vector<vector<int>>& tilePattern) {
    int tileHeight = tilePattern.size();
    int tileWidth = tilePattern[0].size();
    //cout << "tileHeight: " << tileHeight << "tileWidth" << tileWidth << endl;

    for (int i = 0; i < tileHeight; ++i) {
        for (int j = 0; j < tileWidth; ++j) {
            if (tilePattern[i][j] == 1) {
                int boardX = x + i;
                int boardY = y + j;
                board.getCase(boardX, boardY).setCasePlayer(player);
                board.getCase(boardX, boardY).setType(1);
            }
        }
    }
}

// Rotation d'une tuile spécifique
void Tiles::rotateTilePattern(vector<vector<int>>& tilePattern) {
    int tileHeight = tilePattern.size();
    int tileWidth = tilePattern[0].size();
    vector<vector<int>> rotatedPattern(tileWidth, vector<int>(tileHeight));

    for (int i = 0; i < tileHeight; ++i) {
        for (int j = 0; j < tileWidth; ++j) {
            rotatedPattern[j][tileHeight - i - 1] = tilePattern[i][j];
        }
    }
    tilePattern = rotatedPattern;
}

// Affiche une tuile spécifique
void Tiles::drawTilePattern(int x, int y, int sizeCell, int padding, Color color, vector<vector<int>>& tilePattern) {

    int rows = tilePattern.size();
    int cols = tilePattern[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (tilePattern[i][j] == 1) {
                int posX = (x + j) * sizeCell + padding;
                int posY = (y + i) * sizeCell + padding;
                DrawRectangle(posX, posY, sizeCell, sizeCell, color);
            }
        }
    }
}

// Miroir horizontal d'une tuile spécifique
void Tiles::flip(vector<vector<int>>& tilePattern) {
    int tileHeight = tilePattern.size();
    int tileWidth = tilePattern[0].size();
    vector<vector<int>> flippedPattern(tileHeight, vector<int>(tileWidth, 0));

    for (int i = 0; i < tileHeight; ++i) {
        for (int j = 0; j < tileWidth; ++j) {
            flippedPattern[i][tileWidth - 1 - j] = tilePattern[i][j];
        }
    }
     tilePattern = flippedPattern;
}

// Vérifie le plateau
bool Tiles::isValidPosition(int x, int y, Board& board, int size, vector<vector<int>>& tilePattern, bool firstTurn, int currentPlayer, int nbPlayer) {
    vector<vector<bool>> pos;
    if (nbPlayer <= 4) {
        pos = {{x < size / 2,  y < size / 2},
               {x >= size / 2, y < size / 2},
               {x < size / 2,  y >= size / 2},
               {x >= size / 2, y >= size / 2}};
    } else {
        pos = {{x < size / 3,                      y < size / 3},
               {x >= size / 3 && x < 2 * size / 3, y < size / 3},
               {x >= 2 * size / 3,                 y < size / 3},
               {x < size / 3,                      y >= size / 3 && y < 2 * size / 3},
               {x >= size / 3 && x < 2 * size / 3, y >= size / 3 && y < 2 * size / 3},
               {x >= 2 * size / 3,                 y >= size / 3 && y < 2 * size / 3},
               {x < size / 3,                      y >= 2 * size / 3},
               {x >= size / 3 && x < 2 * size / 3, y >= 2 * size / 3},
               {x >= 2 * size / 3,                 y >= 2 * size / 3}};
    }
    for (int k = 0; k < pos.size(); ++k) {
        if (x < 0 || x >= size || y < 0 || y >= size){
            return false;
        }
        if (pos[k][0] && pos[k][1] && firstTurn) {
            if (k == currentPlayer) {
                return true;
            }
            return false;
        }
    }

    int tileHeight = tilePattern.size();
    int tileWidth = tilePattern[0].size();
    bool adjacentToSamePlayer = false;

    for (int i = 0; i < tileHeight; ++i) {
        for (int j = 0; j < tileWidth; ++j) {
            if (tilePattern[i][j] == 1) {
                int boardX = x + j;
                int boardY = y + i;

                if (boardX < 0 || boardX >= size || boardY < 0 || boardY >= size) {
                    return false;
                }
                if (board.getCase(boardY, boardX).getCasePlayer() != 0) {
                    return false;
                }
                if ((boardX > 0 && board.getCase(boardY, boardX - 1).getCasePlayer() == currentPlayer + 1) ||
                    (boardX < size - 1 && board.getCase(boardY, boardX + 1).getCasePlayer() == currentPlayer + 1) ||
                    (boardY > 0 && board.getCase(boardY - 1, boardX).getCasePlayer() == currentPlayer + 1) ||
                    (boardY < size - 1 && board.getCase(boardY + 1, boardX).getCasePlayer() == currentPlayer + 1)) {
                    adjacentToSamePlayer = true;
                }
            }
        }
    }
    return adjacentToSamePlayer;
}

vector<vector<vector<vector<int>>>> Tiles::distributeTiles(int nbPlayers) {
    vector<vector<int>> tile0 = {
            {1}
    };
    vector<vector<vector<int>>> tileList = getTileList();
    shuffle(tileList.begin(), tileList.end(), mt19937{random_device{}()});

    vector<vector<vector<vector<int>>>> playerTiles(nbPlayers);
    for (size_t i = 0; i < tileList.size(); ++i) {
        playerTiles[i % nbPlayers].push_back(tileList[i]);
    }
    for (int i = 0; i < nbPlayers; ++i) {
        playerTiles[i % nbPlayers].push_back(tile0);
    }
    return playerTiles;
}

