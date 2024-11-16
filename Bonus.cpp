//
// Created by alexd on 15/11/2024.
//

#include "Bonus.h"
#include <vector>
#include <iostream>

using namespace std;

Bonus::Bonus() {}

void Bonus::ticketExchange(vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, int i){
    playerTiles[currentPlayer][playerTiles[currentPlayer].size() - 1] = playerTiles[currentPlayer][playerTiles[currentPlayer].size() - 1 - i];
    playerTiles[currentPlayer].erase(playerTiles[currentPlayer].end() - 1 - i, playerTiles[currentPlayer].end() - 1);
}



