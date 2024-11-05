#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "BoardDisplay.h"

class Game {
public:
    Game(int size, int sizeCell, int padding, int nbPlayer);
    void init(int nbPlayer);
    void run();
private:
    Board board;
    BoardDisplay boardDisplay;
    int size;
    int sizeCell;
    int padding;
    int nbPlayer;
};

#endif // GAME_H