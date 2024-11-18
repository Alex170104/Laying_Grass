#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "BoardDisplay.h"
#include "Player.h"


class Game {
public:
    Game(int size, int nbPlayer, int sizeCell, int padding, vector<Player> listPlayers);
    void run();

    void endGameEchange(int currentPlayer, vector<vector<vector<vector<int>>>> &playerTiles, vector<vector<int>> &selectedTile);

    int biggerSquare(int player);

private:
    Board board;
    int size;
    int sizeCell;
    int padding;
    int nbPlayer;
    int turnCount;
    vector<Player> listPlayers;
    int nbGrassPlaced(int player);
    vector<Player> calculWin();
    BoardDisplay boardDisplay;
};

#endif // GAME_H