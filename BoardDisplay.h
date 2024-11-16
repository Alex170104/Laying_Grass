#ifndef LAYING_GRASS_BOARDDISPLAY_H
#define LAYING_GRASS_BOARDDISPLAY_H

#include "raylib.h"
#include "Board.h"
#include "Player.h"

class BoardDisplay {
public:
    BoardDisplay(Board& board, int sizeCell);
    ~BoardDisplay();
    void display(int startX, int startY, int size, int sizeCell, int sizeCellPreview, int previewSize, int previewPadding, int padding, bool firstTurn, const vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, const vector<vector<int>>& selectedTile, vector<Player> listPlayers);



private:
    Board& board;
    Texture2D textureBonusStone;
    Texture2D textureBonusTicket;
    Texture2D textureBonusVol;
    Texture2D textureFissure;
    int sizeCell;
};

#endif //LAYING_GRASS_BOARDDISPLAY_H