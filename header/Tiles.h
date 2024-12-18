#ifndef LAYING_GRASS_TILES_H
#define LAYING_GRASS_TILES_H

#include "Board.h"

/**
 * \brief Classe représentant les tuiles du jeu.
 */
class Tiles {
public:
    /**
     * \brief Constructeur de la classe Tiles.
     */
    Tiles();

    /**
     * \brief Place une tuile sur le plateau.
     * \param x La coordonnée x de la tuile.
     * \param y La coordonnée y de la tuile.
     * \param player Le joueur plaçant la tuile.
     * \param board Le plateau de jeu.
     * \param tilePattern Le motif de la tuile.
     */
    void placeTile(int x, int y, int player, Board& board, vector<vector<int>>& tilePattern);

    /**
     * \brief Fait pivoter le motif de la tuile.
     * \param tilePattern Le motif de la tuile.
     */
    void rotateTilePattern(vector<vector<int>>& tilePattern);

    /**
     * \brief Dessine le motif de la tuile.
     * \param x La coordonnée x de la tuile.
     * \param y La coordonnée y de la tuile.
     * \param sizeCell La taille de la cellule.
     * \param padding Le padding.
     * \param color La couleur de la tuile.
     * \param tilePattern Le motif de la tuile.
     */
    void drawTilePattern(int x, int y, int sizeCell, int padding, Color color, vector<vector<int>>& tilePattern);

    /**
     * \brief Retourne le motif de la tuile.
     * \param tilePattern Le motif de la tuile.
     */
    void flip(vector<vector<int>>& tilePattern);

    /**
     * \brief Vérifie si la position de la tuile est valide.
     * \param x La coordonnée x de la tuile.
     * \param y La coordonnée y de la tuile.
     * \param board Le plateau de jeu.
     * \param size La taille de la tuile.
     * \param tilePattern Le motif de la tuile.
     * \param firstTurn Indique si c'est le premier tour.
     * \param currentPlayer Le joueur actuel.
     * \param nbPlayer Le nombre de joueurs.
     * \return true si la position est valide, false sinon.
     */
    bool isValidPosition(int x, int y, Board& board, int size, vector<vector<int>>& tilePattern, bool firstTurn, int currentPlayer, int nbPlayer);

    /**
     * \brief Obtient la liste des motifs de tuiles.
     * \return La liste des motifs de tuiles.
     */
    vector<vector<vector<int>>> getTileList() const { return listTile; }

    /**
     * \brief Distribue les tuiles aux joueurs.
     * \param nbPlayers Le nombre de joueurs.
     * \return La liste des tuiles distribuées.
     */
    vector<vector<vector<vector<int>>>> distributeTiles(int nbPlayers);

private:
    vector<vector<vector<int>>> listTile = { /**< La liste des motifs de tuiles. */
            { // Forme 1 (2x3)
                    {1, 0, 0},
                    {1, 1, 1}
            },
            { // Forme 2 (3x3)
                    {0, 1, 0},
                    {0, 1, 0},
                    {1, 1, 1}
            },
            { // Forme 3 (3x3)
                    {0, 1, 0},
                    {1, 1, 1},
                    {0, 1, 0}
            },
            { // Forme 4 (3x3)
                    {0, 0, 1},
                    {1, 1, 1},
                    {1, 0, 0}
            },
            { // Forme 5 (2x3)
                    {0, 1, 0},
                    {1, 1, 1}
            },
            { // Forme 6 (2x2)
                    {1, 1},
                    {1, 1}
            },
            { // Forme 7 (2x3)
                    {1, 0, 1},
                    {1, 1, 1}
            },
            { // Forme 8 (1x3)
                    {1, 1, 1}
            },
            { // Forme 9 (3x2)
                    {0, 1},
                    {1, 1},
                    {1, 0}
            },
            { // Forme 10 (2x2)
                    {1, 0},
                    {1, 1}
            },
            { // Forme 11 (3x3)
                    {0, 0, 1},
                    {0, 1, 1},
                    {1, 1, 0}
            },
            { // Forme 12 (1x2)
                    {1, 1}
            },
            { // Forme 13 (5x2)
                    {0, 1},
                    {1, 1},
                    {1, 0},
                    {1, 0},
                    {1, 1}
            },
            { // Forme 14 (5x3)
                    {1, 1, 1},
                    {1, 0, 0},
                    {1, 0, 0},
                    {1, 0, 0},
                    {1, 0, 0}
            },
            { // Forme 15 (5x5)
                    {0, 0, 0, 1, 0},
                    {0, 0, 0, 1, 0},
                    {0, 0, 0, 1, 1},
                    {0, 1, 1, 1, 0},
                    {1, 1, 0, 0, 0}
            },
            { // Forme 16 (4x3)
                    {0, 0, 1},
                    {0, 1, 1},
                    {1, 1, 0},
                    {1, 0, 0}
            },
            { // Forme 17 (3x3)
                    {0, 1, 0},
                    {1, 1, 1},
                    {1, 1, 0}
            },
            { // Forme 18 (1x3)
                    {1, 1, 1}
            },
            { // Forme 19 (4x2)
                    {1, 0},
                    {1, 1},
                    {1, 0},
                    {1, 0}
            },
            { // Forme 20 (3x3)
                    {0, 1, 1},
                    {1, 1, 0},
                    {1, 1, 0}
            },
            { // Forme 21 (3x3)
                    {0, 1, 0},
                    {1, 1, 0},
                    {1, 1, 1}
            },
            { // Forme 22 (4x3)
                    {0, 1, 0},
                    {0, 1, 0},
                    {1, 1, 1},
                    {1, 0, 0}
            },
            { // Forme 23 (2x2)
                    {1, 0},
                    {1, 1}
            },
            { // Forme 24 (3x2)
                    {1, 1},
                    {1, 1},
                    {1, 1}
            },
            { // Forme 25 (4x3)
                    {1, 1, 1},
                    {0, 1, 0},
                    {0, 1, 0},
                    {0, 1, 0}
            },
            { // Forme 26 (4x4)
                    {1, 0, 0, 0},
                    {1, 1, 0, 0},
                    {0, 1, 1, 0},
                    {0, 0, 1, 1}
            },
            { // Forme 27 (1x5)
                    {1, 1, 1, 1, 1}
            },
            { // Forme 28 (4x3)
                    {1, 0, 0},
                    {1, 1, 1},
                    {0, 0, 1},
                    {0, 0, 1}
            },
            { // Forme 29 (5x2)
                    {1, 0},
                    {1, 1},
                    {1, 0},
                    {1, 1},
                    {1, 0}
            },
            { // Forme 30 (4x2)
                    {1, 0},
                    {1, 1},
                    {1, 1},
                    {1, 0}
            },
            { // Forme 31 (5x3)
                    {0, 1, 0},
                    {0, 1, 0},
                    {0, 1, 0},
                    {1, 1, 1},
                    {1, 0, 1}
            },
            { // Forme 32 (1x2)
                    {1, 1}
            },
            { // Forme 33 (3x4)
                    {1, 0, 0, 0},
                    {1, 1, 1, 0},
                    {1, 0, 1, 1}
            },
            { // Forme 34 (5x2)
                    {0, 1},
                    {0, 1},
                    {1, 1},
                    {1, 0},
                    {1, 0}
            },
            { // Forme 35 (5x4)
                    {1, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 1, 1},
                    {1, 1, 0, 0},
                    {1, 0, 0, 0}
            },
            { // Forme 36 (4x2)
                    {1, 0},
                    {1, 0},
                    {1, 1},
                    {1, 0}
            },
            { // Forme 37 (3x2)
                    {0, 1},
                    {1, 1},
                    {1, 0}
            },
            { // Forme 38 (2x4)
                    {1, 0, 0, 1},
                    {1, 1, 1, 1}
            },
            { // Forme 39 (3x5)
                    {0, 0, 0, 1, 1},
                    {1, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1}
            },
            { // Forme 40 (4x4)
                    {1, 0, 0, 0},
                    {1, 0, 0, 0},
                    {1, 1, 0, 0},
                    {0, 1, 1, 1}
            },
            { // Forme 41 (5x3)
                    {1, 1, 0},
                    {0, 1, 1},
                    {1, 1, 0},
                    {0, 1, 1},
                    {0, 1, 0}
            },
            { // Forme 42 (3x2)
                    {1, 0},
                    {1, 1},
                    {1, 1}
            },
            { // Forme 43 (3x4)
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {1, 1, 1, 1}
            },
            { // Forme 44 (2x2)
                    {1, 1},
                    {1, 1}
            },
            { // Forme 45 (4x2)
                    {0, 1},
                    {1, 1},
                    {1, 1},
                    {1, 0}
            },
            { // Forme 46 (3x3)
                    {1, 1, 1},
                    {0, 1, 0},
                    {1, 1, 0}
            },
            { // Forme 47 (1x4)
                    {1, 1, 1, 1}
            },
            { // Forme 48 (2x3)
                    {0, 1, 0},
                    {1, 1, 1}
            },
            { // Forme 49 (3x4)
                    {1, 0, 0, 0},
                    {1, 0, 0, 0},
                    {1, 1, 1, 1}
            },
            { // Forme 50 (3x4)
                    {0, 1, 1, 0},
                    {1, 1, 0, 0},
                    {0, 1, 1, 1}
            },
            { // Forme 51 (4x2)
                    {0, 1},
                    {1, 1},
                    {1, 0},
                    {1, 0}
            },
            { // Forme 52 (2x3)
                    {1, 0, 0},
                    {1, 1, 1}
            },
            { // Forme 53 (5x2)
                    {1, 0},
                    {1, 1},
                    {1, 0},
                    {1, 0},
                    {1, 0}
            },
            { // Forme 54 (5x5)
                    {0, 0, 1, 1, 1},
                    {0, 0, 1, 0, 0},
                    {0, 0, 1, 0, 0},
                    {0, 0, 1, 0, 0},
                    {1, 1, 1, 0, 0}
            },
            { // Forme 55 (6x2)
                    {0, 1},
                    {0, 1},
                    {1, 1},
                    {1, 0},
                    {1, 1},
                    {1, 0}
            },
            { // Forme 56 (1x4)
                    {1, 1, 1, 1}
            },
            { // Forme 57 (4x4)
                    {1, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 1, 1},
                    {0, 0, 0, 1}
            },
            { // Forme 58 (5x3)
                    {0, 1, 0},
                    {0, 1, 0},
                    {1, 1, 1},
                    {0, 1, 0},
                    {0, 1, 0}
            },
            { // Forme 59 (3x3)
                    {0, 0, 1},
                    {0, 0, 1},
                    {1, 1, 1}
            },
            { // Forme 60 (6x1)
                    {1},
                    {1},
                    {1},
                    {1},
                    {1},
                    {1}
            },
            { // Forme 61 (4x3)
                    {1, 0, 1},
                    {1, 1, 1},
                    {0, 1, 0},
                    {1, 1, 0}
            },
            { // Forme 62 (4x4)
                    {0, 0, 1, 0},
                    {1, 1, 1, 0},
                    {0, 1, 1, 1},
                    {0, 1, 0, 0}
            },
            { // Forme 63 (4x3)
                    {0, 1, 1},
                    {0, 1, 0},
                    {0, 1, 0},
                    {1, 1, 1}
            },
            { // Forme 64 (5x2)
                    {1, 0},
                    {1, 0},
                    {1, 1},
                    {1, 0},
                    {1, 0}
            },
            { // Forme 65 (4x4)
                    {1, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 1},
                    {1, 1, 1, 1}
            },
            { // Forme 66 (5x3)
                    {0, 0, 1},
                    {0, 1, 1},
                    {1, 1, 0},
                    {1, 0, 0},
                    {1, 1, 0}
            },
            { // Forme 67 (6x3)
                    {0, 1, 1},
                    {0, 1, 0},
                    {0, 1, 0},
                    {0, 1, 0},
                    {1, 1, 0},
                    {1, 0, 0}
            },
            { // Forme 68 (2x4)
                    {1, 0, 1, 0},
                    {1, 1, 1, 1}
            },
            { // Forme 69 (4x4)
                    {1, 1, 0, 0},
                    {0, 1, 0, 1},
                    {0, 1, 0, 1},
                    {0, 1, 1, 1}
            },
            { // Forme 70 (5x2)
                    {1, 0},
                    {1, 1},
                    {1, 0},
                    {1, 0},
                    {1, 0}
            },
            { // Forme 71 (5x4)
                    {1, 0, 0, 0},
                    {1, 0, 1, 0},
                    {1, 1, 1, 1},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0}
            },
            { // Forme 72 (7x2)
                    {1, 1},
                    {1, 0},
                    {1, 0},
                    {1, 0},
                    {1, 0},
                    {1, 0},
                    {1, 0}
            },
            { // Forme 73 (4x3)
                    {0, 1, 0},
                    {1, 1, 1},
                    {1, 0, 0},
                    {1, 0, 0}
            },
            { // Forme 74 (1x2)
                    {1, 1}
            },
            { // Forme 75 (3x3)
                    {0, 0, 1},
                    {1, 0, 1},
                    {1, 1, 1}
            },
            { // Forme 76 (3x3)
                    {0, 1, 0},
                    {1, 1, 1},
                    {1, 0, 1}
            },
            { // Forme 77 (5x5)
                    {0, 0, 1, 0, 0},
                    {0, 0, 1, 0, 0},
                    {1, 1, 1, 1, 1},
                    {0, 0, 1, 0, 0},
                    {0, 0, 1, 0, 0}
            },
            { // Forme 78 (6x4)
                    {0, 0, 0, 1},
                    {0, 0, 1, 1},
                    {0, 0, 1, 0},
                    {0, 0, 1, 0},
                    {0, 1, 1, 0},
                    {1, 1, 0, 0}
            },
            { // Forme 79 (5x2)
                    {1, 1},
                    {1, 0},
                    {1, 1},
                    {1, 0},
                    {1, 1}
            },
            { // Forme 80 (5x4)
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {1, 1, 1, 1},
                    {0, 1, 0, 0}
            },
            { // Forme 81 (5x2)
                    {0, 1},
                    {1, 1},
                    {1, 0},
                    {1, 0},
                    {1, 0}
            },
            { // Forme 82 (4x3)
                    {0, 1, 1},
                    {0, 1, 0},
                    {1, 1, 0},
                    {1, 0, 0}
            },
            { // Forme 83 (6x3)
                    {0, 1, 1},
                    {0, 1, 0},
                    {1, 1, 0},
                    {0, 1, 1},
                    {0, 1, 0},
                    {0, 1, 0}
            },
            { // Forme 84 (6x3)
                    {1, 1, 0},
                    {1, 1, 0},
                    {0, 1, 1},
                    {0, 1, 0},
                    {0, 1, 0},
                    {0, 1, 0}
            },
            { // Forme 85 (4x3)
                    {0, 1, 0},
                    {0, 1, 1},
                    {1, 1, 0},
                    {0, 1, 0}
            },
            { // Forme 86 (2x4)
                    {1, 1, 0, 0},
                    {1, 1, 1, 1}
            },
            { // Forme 87 (4x4)
                    {0, 0, 1, 1},
                    {1, 1, 1, 0},
                    {1, 0, 0, 0},
                    {1, 1, 0, 0}
            },
            { // Forme 88 (4x3)
                    {0, 1, 1},
                    {0, 1, 0},
                    {0, 1, 0},
                    {1, 1, 0}
            },
            { // Forme 89 (4x3)
                    {0, 1, 0},
                    {0, 1, 0},
                    {1, 1, 1},
                    {0, 1, 0}
            },
            { // Forme 90 (4x3)
                    {1, 1, 1},
                    {1, 0, 1},
                    {1, 0, 0},
                    {1, 1, 0}
            },
            { // Forme 91 (4x3)
                    {0, 1, 0},
                    {0, 1, 1},
                    {1, 1, 0},
                    {1, 0, 0}
            },
            { // Forme 92 (3x3)
                    {1, 0, 0},
                    {1, 1, 0},
                    {1, 1, 1}
            },
            { // Forme 93 (4x2)
                    {1, 0},
                    {1, 0},
                    {1, 0},
                    {1, 1}
            },
            { // Forme 94 (3x4)
                    {0, 1, 0, 0},
                    {1, 1, 1, 1},
                    {1, 0, 0, 0}
            },
            { // Forme 95 (4x3)
                    {0, 1, 1},
                    {1, 1, 0},
                    {1, 0, 0},
                    {1, 0, 0}
            },
            { // Forme 96 (4x2)
                    {0, 1},
                    {1, 1},
                    {1, 0},
                    {1, 1}
            },
    };
};

#endif //LAYING_GRASS_TILES_H