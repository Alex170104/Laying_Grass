#ifndef LAYING_GRASS_BOARD_H
#define LAYING_GRASS_BOARD_H

#include <vector>

#include "Case.h"

/**
 * @class Board
 * @brief Représente le plateau de jeu contenant des cases.
 */
class Board {
public:
    /**
     * \brief Constructeur de la classe Board.
     * \param size La taille du plateau.
     * \param nbPlayer Le nombre de joueurs.
     */
    Board(int size, int nbPlayer);

    /**
     * \brief Méthode pour récupérer le plateau de jeu.
     * \return Un vecteur 2D d'objets Case représentant le plateau.
     */
    vector<vector<Case>> getBoard() const { return grid; }

    /**
     * \brief Obtient une case spécifique du plateau.
     * \param x La coordonnée x de la case.
     * \param y La coordonnée y de la case.
     * \return Une référence à l'objet Case aux coordonnées spécifiées.
     */
    Case &getCase(int x, int y);

 /**
  * \brief Crée le plateau de jeu.
  * \return Un vecteur 2D d'objets Case représentant le plateau créé.
  */
 vector<vector<Case>> createBoard();
 /**
     * \brief Vérifie si le plateau a des fissures.
     * \return True si le plateau a des fissures, sinon False.
     */
 bool hasCrack();

protected:
    vector<vector<Case>> grid; /**< Vecteur 2D représentant la grille de cases. */
    int size; /**< La taille du plateau. */
    int nbPlayer; /**< Le nombre de joueurs. */
};

#endif //LAYING_GRASS_BOARD_H
