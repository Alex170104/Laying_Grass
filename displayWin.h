#ifndef DISPLAYWIN_H
#define DISPLAYWIN_H

#include <vector>
#include "Player.h"

class displayWin {
private:
    Texture2D textureTrophee;
public:
    displayWin(std::vector<Player> orderWinners);

    ~displayWin();
};


#endif //DISPLAYWIN_H
