#include "Game.h"
#include "DisplayMenu.h"

int sizeBoard(int player);

using namespace std;

int main() {
    int screenWidth = 1000;
    int screenHeight = 1200-200;
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
        int sizeCell = (nbPlayer > 4) ? 30 : 30;
        int padding = 100;
        int windowSize = size * sizeCell + 2 * padding;
        if (nbPlayer > 4) {
            InitWindow(windowSize + 320, windowSize + 200, "Laying Grass - GAME");
        } else {
            InitWindow(windowSize + 320, windowSize + 150, "Laying Grass - GAME");
        }

        Game game(size, nbPlayer, sizeCell, padding, listPlayers);
        game.run();
    }

    return 0;
}

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
