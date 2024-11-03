#ifndef LAYING_GRASS_CASE_H
#define LAYING_GRASS_CASE_H

#include <string>
#include "raylib.h"
using namespace std;

class Case {
public:
    Case(int x, int y, int casePlayer, int type);

    int getX() const { return x; }
    void setX(int value) { x = value; }

    int getY() const { return y; }
    void setY(int value) { y = value; }

    int getCasePlayer() const { return casePlayer; }
    void setCasePlayer(int value) { casePlayer = value; }

    int getType() const { return type; }
    void setType(int value) { type = value; }

    Color caseColor() const;

protected:
    int x;
    int y;
    int casePlayer;
    int type;

};

#endif //LAYING_GRASS_CASE_H
