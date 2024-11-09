#include "Board.h"
#include <iostream>
#include <random>

using namespace std;

Board::Board(int size, int nbPlayer): size(size), nbPlayer(nbPlayer) {
    grid = createBoard();
}

vector<vector<Case>> Board::createBoard() {
    grid = vector<vector<Case>>(size, vector<Case>(size, Case(0, 0, 0, 0)));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            grid[i][j].setX(j);
            grid[i][j].setY(i);
        }
    }
    int nbTileExchange = ceil(1.5 * nbPlayer);
    int nbStone = ceil(0.5 * nbPlayer);
    int nbRobbery = nbPlayer;

    mt19937 re(time(nullptr));
    uniform_int_distribution<int> alea{1, size-2};

    vector<int> listeBonus = {nbTileExchange, nbStone, nbRobbery};
    for (int i = 0; i < 3; ++i) {
        int compteur = 0;
        while (compteur < listeBonus[i]) {
            int x = alea(re);
            int y = alea(re);
            if (grid[x][y].getType() == 0) {
                if (grid[x-1][y].getType() != 0 or grid[x+1][y].getType() != 0 or grid[x][y-1].getType() != 0 or grid[x][y+1].getType() != 0) {
                    continue;
                }
                grid[x][y].setType(i+2);
                compteur++;
            }
        }
        compteur = 0;
    }
    return grid;
}

Case& Board::getCase(int x, int y) {
    return grid[x][y];
}

void Board::displayType() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << grid[i][j].getType() << " ";
        }
        cout << endl;
    }
}
void Board::displayCasePlayer() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << grid[i][j].getCasePlayer() << " ";
        }
        cout << endl;
    }
}
