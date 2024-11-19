#include <iostream>
#include <random>

#include "../header/Board.h"

using namespace std;

/**
 * @class Board
 * @brief Représente un plateau de jeu contenant des cases.
 */
Board::Board(int size, int nbPlayer) : size(size), nbPlayer(nbPlayer) {
    grid = createBoard();
}

/**
 * @brief Crée le plateau de jeu et initialise les cases.
 *
 * Cette fonction crée une grille bidimensionnelle de cases.
 * Elle attribue des coordonnées à chaque case et place des bonus (TileExchange, Stone, Robbery)
 * aléatoirement en respectant certaines contraintes.
 *
 * @return Un vecteur bidimensionnel représentant le plateau de jeu.
 */
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
    uniform_int_distribution<int> alea{1, size - 2};

    vector<int> listeBonus = {nbTileExchange, nbStone, nbRobbery};
    for (int i = 0; i < 3; ++i) {
        int compteur = 0;
        while (compteur < listeBonus[i]) {
            int x = alea(re);
            int y = alea(re);
            if (grid[x][y].getType() == 0) {
                if (grid[x - 1][y].getType() != 0 || grid[x + 1][y].getType() != 0 ||
                    grid[x][y - 1].getType() != 0 || grid[x][y + 1].getType() != 0) {
                    continue;
                }
                grid[x][y].setType(i + 2);
                compteur++;
            }
        }
    }
    return grid;
}

/**
 * @brief Accède à une case spécifique du plateau.
 *
 * @param x Coordonnée X de la case.
 * @param y Coordonnée Y de la case.
 * @return La référence à la case située aux coordonnées spécifiées.
 */
Case& Board::getCase(int x, int y) {
    return grid[x][y];
}

bool Board::hasCrack() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (grid[i][j].getType() == 5) {
                return true;
            }
        }
    }
    return false;
}

