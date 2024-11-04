#include "Game.h"

int sizeBoard(int player);

using namespace std;

int main() {
    int nbPlayer = 4; //INITIALISATION
    int size = sizeBoard(nbPlayer); // Size of the board
    int sizeCell = (nbPlayer > 4) ? 40 : 50;
    int padding = 100;

    Game game(size, sizeCell, padding);
    game.init(nbPlayer);
    game.run();

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
