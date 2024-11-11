#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "BoardDisplay.h"
#include "Player.h"

class Game {
public:
    Game(int size, int sizeCell, int padding, int nbPlayer, vector<Player> listPlayers);
    void run();
    int biggerSquare(int player);

private:
    Board board;
    BoardDisplay boardDisplay;
    int size;
    int sizeCell;
    int padding;
    int nbPlayer;
    vector<Player> listPlayers;

    void drawUpcomingTiles(const vector<vector<vector<vector<int>>>> &playerTiles, int currentPlayer, int padding);

    int nbGrassPlaced(int player);

    void win(int currentPlayer);
};

#endif // GAME_H