#ifndef LAYING_GRASS_BONUS_H
#define LAYING_GRASS_BONUS_H

#include <vector>
#include <iostream>

#include "raylib.h"
#include "Board.h"
#include "Player.h"
#include "BoardDisplay.h"

using namespace std;

/**
 * \brief Classe représentant les bonus dans le jeu.
 */
class Bonus {
public:
    /**
     * \brief Constructeur de la classe Bonus.
     */
    Bonus();

    /**
     * \brief Affiche un pop-up de tuile.
     * \param startTime Le temps de début.
     * \param sizeCell La taille de la cellule.
     * \param size La taille du plateau.
     * \param padding Le padding.
     * \param text Le texte à afficher.
     * \param boardDisplay L'affichage du plateau.
     * \param startX La coordonnée x de départ.
     * \param startY La coordonnée y de départ.
     * \param sizeCellPreview La taille de la cellule en aperçu.
     * \param previewSize La taille de l'aperçu.
     * \param previewPadding Le padding de l'aperçu.
     * \param firstTurn Indique si c'est le premier tour.
     * \param playerTiles Les tuiles des joueurs.
     * \param currentPlayer Le joueur actuel.
     * \param listPlayers La liste des joueurs.
     * \param selectedTile La tuile sélectionnée.
     */
    void popUpTile(float startTime, int sizeCell, int size, int padding, string text, BoardDisplay& boardDisplay, int startX, int startY, int sizeCellPreview, int previewSize, int previewPadding, bool firstTurn, vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, vector<Player> listPlayers, vector<vector<int>> selectedTile);

    /**
     * \brief Affiche un pop-up de bonus.
     * \param startTime Le temps de début.
     * \param sizeCell La taille de la cellule.
     * \param size La taille du plateau.
     * \param padding Le padding.
     * \param text Le texte à afficher.
     * \param boardDisplay L'affichage du plateau.
     * \param startX La coordonnée x de départ.
     * \param startY La coordonnée y de départ.
     * \param sizeCellPreview La taille de la cellule en aperçu.
     * \param previewSize La taille de l'aperçu.
     * \param previewPadding Le padding de l'aperçu.
     * \param firstTurn Indique si c'est le premier tour.
     * \param playerTiles Les tuiles des joueurs.
     * \param currentPlayer Le joueur actuel.
     * \param listPlayers La liste des joueurs.
     * \param selectedTile La tuile sélectionnée.
     */
    void popUpBonus(float startTime, int sizeCell, int size, int padding, string text, BoardDisplay& boardDisplay, int startX, int startY, int sizeCellPreview, int previewSize, int previewPadding, bool firstTurn, vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, vector<Player> listPlayers, vector<vector<int>> selectedTile);

    /**
     * \brief Effectue un vol de tuile.
     * \param currentPlayer Le joueur actuel.
     * \param robber Indique si le joueur est un voleur.
     * \param listPlayers La liste des joueurs.
     * \param playerTiles Les tuiles des joueurs.
     * \param previewSize La taille de l'aperçu.
     * \param sizeCellPreview La taille de la cellule en aperçu.
     * \param previewPadding Le padding de l'aperçu.
     * \return Un tuple contenant le motif de la tuile volée, et ses coordonnées x et y.
     */
    tuple<vector<vector<int>>, int, int> robbery(int currentPlayer, bool robber, vector<Player> listPlayers, vector<vector<vector<vector<int>>>> playerTiles, int previewSize, int sizeCellPreview, int previewPadding);

    /**
     * \brief Effectue un échange de tickets.
     * \param playerTiles Les tuiles des joueurs.
     * \param currentPlayer Le joueur actuel.
     * \param i L'index de la tuile à échanger.
     */
    void ticketExchange(vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, int i);

    /**
     * \brief Vérifie les bonus sur le plateau.
     * \param board Le plateau de jeu.
     * \param size La taille du plateau.
     * \return Le nombre de bonus trouvés.
     */
    int verifBonus(Board &board, int size);
};


#endif //LAYING_GRASS_BONUS_H