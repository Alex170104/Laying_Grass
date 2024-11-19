#include "../header/Player.h"

using namespace std;

/**
 * \brief Constructeur de la classe Player.
 * \param playerName Le nom du joueur.
 * \param playerColor La couleur du joueur.
 */
Player::Player(const string& playerName, const Color playerColor)
        : name(playerName), color(playerColor), tileX(0), tileY(0), tileCoupons(1) {}

/**
* \brief Définit la tuile de départ du joueur.
* \param x La coordonnée x de la tuile.
* \param y La coordonnée y de la tuile.
*/
void Player::setStartingTile(int x, int y) {
    tileX = x;
    tileY = y;
}

/**
 * \brief Obtient le nom du joueur.
 * \return Le nom du joueur.
 */
string Player::getName() const {
    return name;
}

/**
 * \brief Ajoute un caractère au nom du joueur.
 * \param c Le caractère à ajouter.
 */
void Player::addChar(char c) {
    name += c;
}

/**
 * \brief Supprime le dernier caractère du nom du joueur.
 */
void Player::removeChar() {
    name.pop_back();
}

/**
 * \brief Obtient la couleur du joueur.
 * \return La couleur du joueur.
 */
Color Player::getColor() const {
    return color;
}

/**
 * \brief Définit la couleur du joueur.
 * \param playerColor La nouvelle couleur du joueur.
 */
void Player::setColor(const Color playerColor) {
    color = playerColor;
}

/**
 * \brief Obtient le nombre de tuiles placées par le joueur.
 * \return Le nombre de tuiles placées.
 */
int Player::getNbTilesPlaced() const {
    return nbTilesPlaced;
}

/**
 * \brief Incrémente le nombre de tuiles placées par le joueur.
 */
void Player::incrementNbTilesPlaced() {
    nbTilesPlaced++;
}

/**
 * \brief Obtient la taille du plus grand carré formé par le joueur.
 * \return La taille du plus grand carré.
 */
int Player::getBiggestSquare() const {
    return biggestSquare;
}

/**
 * \brief Définit la taille du plus grand carré formé par le joueur.
 * \param square La nouvelle taille du plus grand carré.
 */
void Player::setBiggestSquare(int square) {
    biggestSquare = square;
}

/**
 * \brief Obtient le nombre de cases d'herbe placées par le joueur.
 * \return Le nombre de cases d'herbe placées.
 */
int Player::getNbGrassPlaced() const {
    return nbGrass;
}

/**
 * \brief Définit le nombre de cases d'herbe placées par le joueur.
 * \param grass Le nouveau nombre de cases d'herbe placées.
 */
void Player::setNbGrassPlaced(int grass) {
    nbGrass = grass;
}

/**
 * \brief Obtient le nombre de coupons de tuiles du joueur.
 * \return Le nombre de coupons de tuiles.
 */
int Player::getTileCoupons() const {
    return tileCoupons;
}

/**
 * \brief Ajoute un coupon de tuile au joueur.
 */
void Player::addTileCoupons() {
    tileCoupons += 1;
}

/**
 * \brief Supprime un coupon de tuile du joueur.
 */
void Player::removeTileCoupons() {
    tileCoupons -= 1;
}