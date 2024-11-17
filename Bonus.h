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
    void popUpBonus(float startTime, int sizeCell, int size, int padding, string text, BoardDisplay& boardDisplay, int startX, int startY, int sizeCellPreview, int previewSize, int previewPadding, bool firstTurn, vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, vector<Player> listPlayers, vector<vector<int>> selectedTile);
    tuple<vector<vector<int>>, int, int> robbery(int currentPlayer, bool robber, vector<Player> listPlayers, vector<vector<vector<vector<int>>>> playerTiles, int previewSize, int sizeCellPreview, int previewPadding);
    void ticketExchange(vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, int i);
};


#endif //LAYING_GRASS_BONUS_H