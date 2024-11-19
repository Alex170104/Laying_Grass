#include "../header/Game.h"
#include "../header/DisplayMenu.h"

using namespace std;

/**
 * @mainpage La documentation technique du jeu LAYING GRASS GAME !
 * **Vous pouvez acceder à toutes les classes et fonctions du projet en cliquant sur les onglets ci-dessus.**
 * @author **Alexandre DISCHAMPS**
 * @author **Camille CRETOIS--BLANCHARD**
 * @version **1.0**
 * @date **18/11/2024**
 *
 * **Le projet est developpé en C++ avec la librairie Raylib.**
 */

int sizeBoard(int player);

/**
 * \brief Point d'entrée principal du programme.
 * \return Code de sortie du programme.
 */
int main() {
    int screenWidth = 1000;
    int screenHeight = 1200;
    InitWindow(screenWidth, screenHeight, "Laying Grass - INIT");
    SetTargetFPS(60);

    DisplayMenu menu(screenWidth, screenHeight);
    menu.showMenu();
    CloseWindow();

    if (menu.isGameStart()) {
        int nbPlayer = menu.getNumPlayers();
        vector<Player> listPlayers = menu.getListPlayers();
        int size = sizeBoard(nbPlayer);
        int sizeCell = (nbPlayer > 4) ? 30 : 50;
        int padding = 100;
        int windowSize = size * sizeCell + 2 * padding;
        if (nbPlayer > 4) {
            InitWindow(windowSize, windowSize + 200, "Laying Grass - GAME");
        } else {
            InitWindow(windowSize, windowSize + 150, "Laying Grass - GAME");
        }

        Game game(size, nbPlayer, sizeCell, padding, listPlayers);
        game.run();
    }

    return 0;
}

/**
 * \brief Calcule la taille du plateau en fonction du nombre de joueurs.
 * \param nbPlayer Le nombre de joueurs.
 * \return La taille du plateau.
 */
int sizeBoard(int nbPlayer) {
    int size;
    if (2 <= nbPlayer && nbPlayer <= 4){
        size = 20;
    }
    else {
        size = 30;
    }
    return size;
}
