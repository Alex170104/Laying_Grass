#include <string>
#include "Case.h"



Case::Case(int x, int y, int casePlayer, int type) : x(x), y(y), casePlayer(), type() {}

string Case::getCaseColor() {
    switch (casePlayer) {
        case 1:
            return "BLUE"
        case 2:
            return "RED"
        case 3:
            return "GREEN"
        case 4:
            return "PINK"
        case 5:
            return "GRAY"
        case 6:
            return "YELLOW"
        case 7:
            return "BLUE"
        case 8:
            return "BLUE"
        case 9:
            return "BLUE"
    }
    return string();
}
