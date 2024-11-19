#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "BoardDisplay.h"
#include "Player.h"
#include "Tiles.h"

/**
 * \brief Classe représentant le jeu.
 */
class Game {
public:
    /**
     * \brief Constructeur de la classe Game.
     * \param size La taille du plateau.
     * \param nbPlayer Le nombre de joueurs.
     * \param sizeCell La taille de la cellule.
     * \param padding Le padding.
     * \param listPlayers La liste des joueurs.
     */
    Game(int size, int nbPlayer, int sizeCell, int padding, vector<Player> listPlayers);

    /**
     * \brief Lance le jeu.
     */
    void run();

    /**
     * \brief Calcule la plus grande zone carrée pour un joueur.
     * \param player Le joueur.
     * \return La taille de la plus grande zone carrée.
     */
    int biggerSquare(int player);

private:
    Board board; /**< Le plateau de jeu. */
    Tiles tiles; /**< Les tuiles. */
    int size; /**< La taille du plateau. */
    int sizeCell; /**< La taille de la cellule. */
    int padding; /**< Le padding. */
    int nbPlayer; /**< Le nombre de joueurs. */
    int turnCount; /**< Le nombre de tours. */
    vector<Player> listPlayers; /**< La liste des joueurs. */
    bool turnEndExchange = false; /**< Le tour est celui correspondant à l'achat de tuile 1x1 */

    bool isTilePlacementValid(vector<vector<int>> selectedTile, int currentPlayer, Board board, bool firstTurn, Tiles tiles) const; /**< Vérifie si il retse de la place pour la tuile. */

    /**
     * \brief Calcule le nombre de cases d'herbe placées par un joueur.
     * \param player Le joueur.
     * \return Le nombre de cases d'herbe placées.
     */
    int nbGrassPlaced(int player);

    /**
     * \brief Calcule les gagnants du jeu.
     * \return La liste des joueurs gagnants.
     */
    vector<Player> calculWin();
    BoardDisplay boardDisplay; /**< L'affichage du plateau de jeu. */
};

#endif // GAME_H