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
    void robbery(Board& board, int currentPlayer, bool& robber, const vector<Player>& listPlayers, vector<vector<vector<vector<int>>>>& playerTiles);
    void ticketExchange(vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, int i);

    int verifBonus(Board &board, int size);
};


#endif //LAYING_GRASS_BONUS_H