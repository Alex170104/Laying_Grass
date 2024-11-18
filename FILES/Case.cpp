#include "Case.h"

/**
 * \brief Constructeur de la classe Case.
 * \param x La coordonnée x de la case.
 * \param y La coordonnée y de la case.
 * \param casePlayer Le joueur associé à la case.
 * \param type Le type de la case.
 */
Case::Case(int x, int y, int casePlayer, int type) : x(x), y(y), casePlayer(casePlayer), type(type) {}