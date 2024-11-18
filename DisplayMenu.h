#ifndef LAYING_GRASS_DISPLAYMENU_H
#define LAYING_GRASS_DISPLAYMENU_H

#include <iostream>
#include <vector>
#include "raylib.h"
#include "Player.h"

using namespace std;

/**
 * \brief Classe pour afficher le menu du jeu.
 */
class DisplayMenu {
public:
    /**
     * \brief Constructeur de la classe DisplayMenu.
     * \param screenWidth La largeur de l'écran.
     * \param screenHeight La hauteur de l'écran.
     */
    DisplayMenu(int screenWidth, int screenHeight);

    /**
     * \brief Destructeur de la classe DisplayMenu.
     */
    ~DisplayMenu();

    /**
     * \brief Affiche le menu.
     */
    void showMenu();

    /**
     * \brief Vérifie si le jeu a commencé.
     * \return true si le jeu a commencé, false sinon.
     */
    bool isGameStart();

    /**
     * \brief Obtient le nombre de joueurs.
     * \return Le nombre de joueurs.
     */
    int getNumPlayers() { return listPlayers.size();};

    /**
     * \brief Obtient la liste des joueurs.
     * \return La liste des joueurs.
     */
    vector<Player> getListPlayers(){ return listPlayers;};

private:
    int screenWidth; /**< La largeur de l'écran. */
    int screenHeight; /**< La hauteur de l'écran. */
    bool gameStart; /**< Indique si le jeu a commencé. */
    int numPlayers; /**< Le nombre de joueurs. */
    int selectedPlayer; /**< Le joueur sélectionné. */
    bool showWarning; /**< Indique si un avertissement doit être affiché. */
    double warningTimer; /**< Le minuteur pour l'avertissement. */
    vector<Player> listPlayers; /**< La liste des joueurs. */
    vector<Color> availableColors; /**< Les couleurs disponibles pour les joueurs. */
    Texture2D textureDANGER; /**< La texture pour l'avertissement de danger. */

    /**
     * \brief Dessine le menu.
     */
    void drawMenu();

    /**
     * \brief Gère les entrées utilisateur.
     */
    void handleInput();
};

#endif //LAYING_GRASS_DISPLAYMENU_H