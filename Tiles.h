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
            { // Forme 1 (4x1)
                    {1},
                    {1},
                    {1},
                    {1}
            },
            { // Forme 2 (3x2)
                    {1, 1},
                    {1, 0},
                    {1, 0}
            },
            { // Forme 3 (2x2)
                    {1, 1},
                    {1, 1}
            },
            { // Forme 4 (3x2)
                    {1, 1},
                    {1, 1},
                    {1, 0}
            },
            { // Forme 5 (3x2)
                    {1, 1},
                    {0, 1},
                    {0, 1}
            },
            { // Forme 6 (3x2)
                    {1, 1},
                    {0, 1},
                    {1, 1}
            },
            { // Forme 7 (3x3)
                    {1, 1, 0},
                    {1, 1, 1},
                    {0, 1, 1}
            },
            { // Forme 8 (3x3)
                    {1, 1, 1},
                    {0, 0, 1},
                    {0, 1, 1}
            },
            { // Forme 9 (3x2)
                    {1, 1},
                    {1, 1},
                    {0, 1}
            },
            { // Forme 10 (4x2)
                    {1, 1},
                    {0, 1},
                    {0, 1},
                    {1, 1}
            }

    };


};

#endif //LAYING_GRASS_TILES_H