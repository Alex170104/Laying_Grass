#include "Game.h"
#include "DisplayMenu.h"

int sizeBoard(int player);

using namespace std;

int main() {
    int screenWidth = 1000;
    int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "Laying Grass");
    SetTargetFPS(60);

    DisplayMenu menu(screenWidth, screenHeight);
    menu.showMenu();

    if (menu.isGameStart()) {
        int nbPlayer = menu.getNumPlayers();
        vector<string> playerNames = menu.getPlayerNames();
        vector<Color> playerColors = menu.getPlayerColors();
        int size = sizeBoard(nbPlayer);
        int sizeCell = (nbPlayer > 4) ? 40 : 50;
        int padding = 100;
        int windowSize = size * sizeCell + 2 * padding;
        InitWindow(windowSize, windowSize + 200, "Laying Grass");

        Game game(size, nbPlayer, sizeCell, padding, playerColors, playerNames);
        game.run();
    }

    return 0;
}

int sizeBoard(int nbPlayer) {
    int size;
    if (2 <= nbPlayer && nbPlayer <= 4){
        size = 20;
    }
    else if (5 <= nbPlayer && nbPlayer <= 9){
        size = 30;
    }
    return size;
}
