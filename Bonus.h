//
// Created by alexd on 15/11/2024.
//

#ifndef LAYING_GRASS_BONUS_H
#define LAYING_GRASS_BONUS_H

#include <vector>
#include <iostream>
#include "raylib.h"
#include "Board.h"
#include "Player.h"
#include "BoardDisplay.h"

using namespace std;

class Bonus {
public:
    Bonus();
    void popUpBonus(float startTime, int sizeCell, int size, int padding, string text, BoardDisplay boardDisplay, int startX, int startY, int sizeCellPreview, int previewSize, int previewPadding, bool firstTurn, vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, vector<Player> listPlayers, vector<vector<int>> selectedTile);
    bool stone(bool clickEmptyCase, Board &board, int sizeCell, int padding);
    void robbery(Board& board, int currentPlayer, bool& robber, const vector<Player>& listPlayers, vector<vector<vector<vector<int>>>>& playerTiles);
    void ticketExchange(vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, int i);
};


#endif //LAYING_GRASS_BONUS_H