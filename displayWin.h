#ifndef DISPLAYWIN_H
#define DISPLAYWIN_H

#include <vector>
#include "Player.h"

class displayWin {
private:
    Texture2D textureTrophee;
    std::vector<Player> orderWinners;
public:
    displayWin(std::vector<Player> orderWinners);
    void run();
    ~displayWin();
};


#endif //DISPLAYWIN_H
