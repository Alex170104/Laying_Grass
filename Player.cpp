#include "Player.h"

using namespace std;

Player::Player(const string& playerName, const Color playerColor)
        : name(playerName), color(playerColor), tileX(0), tileY(0), tileCoupons(1) {}

void Player::setStartingTile(int x, int y) {
    tileX = x;
    tileY = y;
}

string Player::getName() const {
    return name;
}

void Player::addChar(char c) {
    name += c;
}

void Player::removeChar() {
    name.pop_back();
}

Color Player::getColor() const {
    return color;
}

void Player::setColor(const Color playerColor) {
    color = playerColor;
}

int Player::getNbTilesPlaced() const {
    return nbTilesPlaced;
}

void Player::incrementNbTilesPlaced() {
    nbTilesPlaced++;
}

int Player::getBiggestSquare() const {
    return biggestSquare;
}

void Player::setBiggestSquare(int square) {
    biggestSquare = square;
}

int Player::getNbGrassPlaced() const {
    return nbGrass;
}

void Player::setNbGrassPlaced(int grass) {
    nbGrass = grass;
}

int Player::getTileCoupons() const {
    return tileCoupons;
}

void Player::addTileCoupons() {
    tileCoupons += 1;
}

void Player::removeTileCoupons() {
    tileCoupons -= 1;
}