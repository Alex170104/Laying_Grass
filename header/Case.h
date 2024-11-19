#ifndef LAYING_GRASS_CASE_H
#define LAYING_GRASS_CASE_H

#include <string>

#include "raylib.h"

using namespace std;

/**
 * \brief Classe représentant une case sur le plateau de jeu.
 */
class Case {
public:
    /**
     * \brief Constructeur de la classe Case.
     * \param x La coordonnée x de la case.
     * \param y La coordonnée y de la case.
     * \param casePlayer Le joueur associé à la case.
     * \param type Le type de la case.
     */
    Case(int x, int y, int casePlayer, int type);

    /**
     * \brief Définit la coordonnée x de la case.
     * \param value La nouvelle coordonnée x.
     */
    void setX(int value) { x = value; }

    /**
     * \brief Définit la coordonnée y de la case.
     * \param value La nouvelle coordonnée y.
     */
    void setY(int value) { y = value; }

    /**
     * \brief Obtient le joueur associé à la case.
     * \return Le joueur associé.
     */
    int getCasePlayer() const { return casePlayer; }

    /**
     * \brief Définit le joueur associé à la case.
     * \param value Le nouveau joueur associé.
     */
    void setCasePlayer(int value) { casePlayer = value; }

    /**
     * \brief Obtient le type de la case.
     * \return Le type de la case.
     */
    int getType() const { return type; }

    /**
     * \brief Définit le type de la case.
     * \param value Le nouveau type de la case.
     */
    void setType(int value) { type = value; }

private:
    int x; /**< Coordonnée x de la case. */
    int y; /**< Coordonnée y de la case. */
    int casePlayer; /**< Joueur associé à la case (0: libre, 1: joueur1, 2: joueur2...). */
    int type; /**< Type de la case (0: vide, 1: tuile, 2: bonus(échange de tuiles), 3: bonus(pierre), 4: bonus(vol), 5: obstacle/fissure). */
};

#endif //LAYING_GRASS_CASE_H
