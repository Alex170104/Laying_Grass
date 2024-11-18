#include "Game.h"
#include "DisplayMenu.h"

int sizeBoard(int player);

using namespace std;

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
//        int nbPlayer = 3;
        vector<Player> listPlayers = menu.getListPlayers();
//        vector<Player> listPlayers = {Player("Player 1 ", RED), Player("Player 2", BLUE), Player("Player 3", GREEN)};
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
