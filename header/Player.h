#ifndef LAYING_GRASS_PLAYER_H
#define LAYING_GRASS_PLAYER_H

#include <string>

#include "raylib.h"

using namespace std;

/**
 * \brief Classe représentant un joueur.
 */
class Player {
public:
    /**
    * \brief Constructeur de la classe Player.
    * \param playerName Le nom du joueur.
    * \param playerColor La couleur du joueur.
    */
    Player(const std::string& playerName, const Color playerColor);

    /**
     * \brief Définit la tuile de départ du joueur.
     * \param x La coordonnée x de la tuile de départ.
     * \param y La coordonnée y de la tuile de départ.
     */
    void setStartingTile(int x, int y);

    /**
     * \brief Obtient le nombre de tuiles placées par le joueur.
     * \return Le nombre de tuiles placées.
     */
    int getNbTilesPlaced() const;

    /**
     * \brief Incrémente le nombre de tuiles placées par le joueur.
     */
    void incrementNbTilesPlaced();

    /**
     * \brief Définit le nombre de tuiles placées par le joueur.
     * \param nbTiles Le nouveau nombre de tuiles placées.
     */
    void setNbTilesPlaced(int nbTiles);

    /**
     * \brief Obtient le nom du joueur.
     * \return Le nom du joueur.
     */
    string getName() const;

    /**
     * \brief Ajoute un caractère au nom du joueur.
     * \param c Le caractère à ajouter.
     */
    void addChar(char c);

    /**
     * \brief Supprime un caractère du nom du joueur.
     */
    void removeChar();

    /**
     * \brief Obtient la couleur du joueur.
     * \return La couleur du joueur.
     */
    Color getColor() const;

    /**
     * \brief Définit la couleur du joueur.
     * \param playerColor La nouvelle couleur du joueur.
     */
    void setColor(const Color playerColor);

    /**
     * \brief Obtient la plus grande zone carrée du joueur.
     * \return La taille de la plus grande zone carrée.
     */
    int getBiggestSquare() const;

    /**
     * \brief Définit la plus grande zone carrée du joueur.
     * \param square La nouvelle taille de la plus grande zone carrée.
     */
    void setBiggestSquare(int square);

    /**
     * \brief Obtient le nombre de cases d'herbe placées par le joueur.
     * \return Le nombre de cases d'herbe placées.
     */
    int getNbGrassPlaced() const;

    /**
     * \brief Définit le nombre de cases d'herbe placées par le joueur.
     * \param grass Le nouveau nombre de cases d'herbe placées.
     */
    void setNbGrassPlaced(int grass);

    /**
     * \brief Obtient le nombre de coupons de tuiles du joueur.
     * \return Le nombre de coupons de tuiles.
     */
    int getTileCoupons() const;

    /**
     * \brief Ajoute un coupon de tuile au joueur.
     */
    void addTileCoupons();

    /**
     * \brief Supprime un coupon de tuile du joueur.
     */
    void removeTileCoupons();

private:
    std::string name; /**< Le nom du joueur. */
    Color color; /**< La couleur du joueur. */
    int tileX, tileY; /**< Les coordonnées de la tuile de départ. */
    int tileCoupons; /**< Le nombre de coupons de tuiles. */
    int nbTilesPlaced = 0; /**< Le nombre de tuiles placées. */
    int biggestSquare; /**< La taille de la plus grande zone carrée. */
    int nbGrass; /**< Le nombre de cases d'herbe placées. */
};


#endif //LAYING_GRASS_PLAYER_H
