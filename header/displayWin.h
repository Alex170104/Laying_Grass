#ifndef DISPLAYWIN_H
#define DISPLAYWIN_H

#include <vector>

#include "Player.h"

/**
 * \brief Classe pour afficher l'écran de victoire.
 */
class displayWin {
private:
    Texture2D textureTrophee;
    std::vector<Player> orderWinners;
public:
    /**
     * \brief Constructeur de la classe displayWin.
     * \param orderWinners La liste des joueurs dans l'ordre des gagnants.
     */
    displayWin(std::vector<Player> orderWinners);

    /**
     * \brief Affiche l'écran de victoire.
     */
    void run();

    /**
     * \brief Destructeur de la classe displayWin.
     */
    ~displayWin();
};


#endif //DISPLAYWIN_H
