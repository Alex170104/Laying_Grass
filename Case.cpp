#include <string>
#include "Case.h"
#include "raylib.h"


Case::Case(int x, int y, int casePlayer, int type) : x(x), y(y), casePlayer(casePlayer), type(type) {}



Color Case::caseColor() const {
    switch (casePlayer) {
        case 1: return BLUE;
        case 2: return RED;
        case 3: return GREEN;
        case 4: return PINK;
        case 5: return GRAY;
        case 6: return YELLOW;
        case 7: return ORANGE;
        case 8: return PURPLE;
        case 9: return BROWN;
        default: return WHITE;
    }
}
