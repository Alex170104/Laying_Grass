#ifndef LAYING_GRASS_BOARDDISPLAY_H
#define LAYING_GRASS_BOARDDISPLAY_H

#include "raylib.h"
#include "Board.h"
#include "Player.h"

/**
 * \brief Classe pour afficher le plateau de jeu.
 */
class BoardDisplay {
public:
    /**
     * \brief Constructeur de la classe BoardDisplay.
     * \param board Le plateau de jeu.
     * \param sizeCell La taille de la cellule.
     */
    BoardDisplay(Board& board, int sizeCell);

    /**
     * \brief Destructeur de la classe BoardDisplay.
     */
    ~BoardDisplay();

    /**
     * \brief Affiche le plateau de jeu.
     * \param startX La coordonnée x de départ.
     * \param startY La coordonnée y de départ.
     * \param size La taille du plateau.
     * \param sizeCell La taille de la cellule.
     * \param sizeCellPreview La taille de la cellule en aperçu.
     * \param previewSize La taille de l'aperçu.
     * \param previewPadding Le padding de l'aperçu.
     * \param padding Le padding.
     * \param firstTurn Indique si c'est le premier tour.
     * \param playerTiles Les tuiles des joueurs.
     * \param currentPlayer Le joueur actuel.
     * \param selectedTile La tuile sélectionnée.
     * \param listPlayers La liste des joueurs.
     * \param clickTileExchange Indique si l'échange de tuiles est cliqué.
     * \param clickRepair Indique si la réparation est cliquée.
     */
    void display(int startX, int startY, int size, int sizeCell, int sizeCellPreview, int previewSize, int previewPadding, int padding, bool firstTurn, const vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, const vector<vector<int>>& selectedTile, vector<Player> listPlayers, bool clickTileExchange, bool clickRepair);
private:
    Board& board; /**< Référence au plateau de jeu. */
    Texture2D textureBonusStone; /**< Texture pour le bonus de pierre. */
    Texture2D textureBonusTicket; /**< Texture pour le bonus de ticket. */
    Texture2D textureBonusVol; /**< Texture pour le bonus de vol. */
    int sizeCell; /**< Taille de la cellule. */
};

#endif //LAYING_GRASS_BOARDDISPLAY_H