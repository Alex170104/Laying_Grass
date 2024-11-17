#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "BoardDisplay.h"
#include "Player.h"


class Game {
public:
    Game(int size, int nbPlayer, int sizeCell, int padding, vector<Player> listPlayers);
    void run();
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
    int verifBonus();
    BoardDisplay boardDisplay;
};

#endif // GAME_H