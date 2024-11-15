#ifndef LAYING_GRASS_BOARDDISPLAY_H
#define LAYING_GRASS_BOARDDISPLAY_H

#include "raylib.h"
#include "Board.h"
#include "Player.h"

class BoardDisplay {
public:
    BoardDisplay(Board& board, int sizeCell);
    ~BoardDisplay();
    void display(int size, int sizeCell, int padding, bool firstTurn, const vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, const vector<vector<int>>& selectedTile, vector<Player> listPlayers, int turnCount);



private:
    Board& board;
    Texture2D textureBonusStone;
    Texture2D textureBonusTicket;
    Texture2D textureBonusVol;
    Texture2D textureFissure;
    int sizeCell;
};

#endif //LAYING_GRASS_BOARDDISPLAY_H