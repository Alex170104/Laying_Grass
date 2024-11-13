#include "Game.h"
#include "DisplayMenu.h"

int sizeBoard(int player);

using namespace std;

int main() {
    int screenWidth = 800;
    int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Laying Grass");
    SetTargetFPS(60);

    DisplayMenu menu(screenWidth, screenHeight);
    menu.showMenu();
    CloseWindow();

    if (menu.isGameStart()) {
        int nbPlayer = menu.getNumPlayers();
        vector<Player> listPlayers = menu.getListPlayers();
        int size = sizeBoard(nbPlayer);
        int sizeCell = (nbPlayer > 4) ? 20 : 30;
        int padding = 80;
        int windowSize = size * sizeCell + 2 * padding;
        InitWindow(windowSize, windowSize + 200, "Laying Grass");

//        if (!win){
            Game game(size, nbPlayer, sizeCell, padding, listPlayers);
            game.run();
//        }
//        else {
//            CloseWindow();
//        }


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
