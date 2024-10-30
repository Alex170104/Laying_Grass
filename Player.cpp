//
// Created by alexd on 30/10/2024.
//

#include "Player.h"

Player::Player(const string& playerName, const string& playerColor)
        : name(playerName), color(playerColor), tileX(0), tileY(0), tileCoupons(1) {}

void Player::setStartingTile(int x, int y) {
    tileX = x;
    tileY = y;
}
