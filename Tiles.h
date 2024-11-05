//
// Created by alexd on 03/11/2024.
//

#ifndef LAYING_GRASS_TILES_H
#define LAYING_GRASS_TILES_H

#include "Board.h"

class Tiles {
public:
    Tiles();
    void placeTile(int x, int y, int player, Board& board, vector<vector<int>>& tilePattern);
    void rotateTilePattern(vector<vector<int>>& tilePattern);
    void drawTilePattern(int x, int y, int sizeCell, int padding, Color color, vector<vector<int>>& tilePattern);
    void flip(vector<vector<int>>& tilePattern);
    bool isValidPosition(int x, int y, Board& board, int size, vector<vector<int>>& tilePattern);
    vector<vector<vector<int>>> getTileList() const { return listTile; }
    vector<vector<vector<vector<int>>>> distributeTiles(int nbPlayers);

private:
    vector<vector<vector<int>>> listTile = {
            // Forme 1 (2x3)
            {
                    {1, 0, 0},
                    {1, 1, 1}
            },
            // Forme 2 (3x3)
            {
                    {0, 1, 0},
                    {0, 1, 0},
                    {1, 1, 1}
            },
            // Forme 3 (3x3)
            {
                    {0, 1, 0},
                    {1, 1, 1},
                    {0, 1, 0}
            },
            // Forme 4 (2x3)
            {
                    {1, 1, 0},
                    {0, 1, 1}
            },
            // Forme 5 (2x2)
            {
                    {1, 1},
                    {1, 1}
            },
            // Forme 6 (1x4)
            {
                    {1, 1, 1, 1}
            },
            // Forme 7 (2x3)
            {
                    {1, 1, 1},
                    {1, 0, 0}
            },
            // Forme 8 (3x3)
            {
                    {0, 0, 1},
                    {1, 1, 1},
                    {0, 0, 1}
            },
            // Forme 9 (3x3)
            {
                    {1, 0, 0},
                    {1, 1, 1},
                    {0, 0, 1}
            },
            // Forme 10 (2x3)
            {
                    {0, 1, 1},
                    {1, 1, 0}
            },
            // Forme 11 (3x3)
            {
                    {0, 1, 0},
                    {1, 1, 1},
                    {1, 0, 0}
            },
            // Forme 12 (3x3)
            {
                    {1, 1, 0},
                    {0, 1, 0},
                    {0, 1, 1}
            }

    };
};

#endif //LAYING_GRASS_TILES_H