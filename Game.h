#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "BoardDisplay.h"

class Game {
public:
    Game(int size, int sizeCell, int padding, int nbPlayer, vector<Color> playerColors, vector<string> playerNames);
    void run();
    int biggerSquare(int player);

private:
    Board board;
    BoardDisplay boardDisplay;
    int size;
    int sizeCell;
    int padding;
    int nbPlayer;
    vector<Color> playerColors;
    vector<string> playerNames;

    void drawUpcomingTiles(const vector<vector<vector<vector<int>>>> &playerTiles, int currentPlayer, int padding);
};

#endif // GAME_H