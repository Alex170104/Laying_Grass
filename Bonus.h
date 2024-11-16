//
// Created by alexd on 15/11/2024.
//

#ifndef LAYING_GRASS_BONUS_H
#define LAYING_GRASS_BONUS_H

#include <vector>
#include <iostream>
#include "raylib.h"

using namespace std;

class Bonus {
public:
    Bonus();
    void ticketExchange(vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, int i);
};


#endif //LAYING_GRASS_BONUS_H
