#include <iostream>

#include "../header/BoardDisplay.h"


using namespace std;

/**
 * \brief Constructeur de la classe BoardDisplay.
 * \param board Le plateau de jeu.
 * \param sizeCell La taille de la cellule.
 */
BoardDisplay::BoardDisplay(Board& board, int sizeCell) : board(board) {
    Image imgBonusStone = LoadImage("../img/rock.png");
    Image imgBonusTicket = LoadImage("../img/ticket.png");
    Image imgBonusVol = LoadImage("../img/vol.png");

    ImageResize(&imgBonusStone, sizeCell, sizeCell);
    ImageResize(&imgBonusTicket, sizeCell, sizeCell);
    ImageResize(&imgBonusVol, sizeCell, sizeCell);

    textureBonusStone = LoadTextureFromImage(imgBonusStone);
    textureBonusTicket = LoadTextureFromImage(imgBonusTicket);
    textureBonusVol = LoadTextureFromImage(imgBonusVol);

    UnloadImage(imgBonusStone);
    UnloadImage(imgBonusTicket);
    UnloadImage(imgBonusVol);

}

/**
 * \brief Destructeur de la classe BoardDisplay.
 */
BoardDisplay::~BoardDisplay() {
    UnloadTexture(textureBonusStone);
    UnloadTexture(textureBonusTicket);
    UnloadTexture(textureBonusVol);

}

/**
 * \brief Affiche le plateau de jeu.
 * \param startX La coordonnée x de départ.
 * \param startY La coordonnée y de départ.
 * \param size La taille du plateau.
 * \param sizeCell La taille de la cellule.
 * \param sizeCellPreview La taille de la cellule en aperçu.
 * \param previewSize La taille de l'aperçu.
 * \param previewPadding Le padding de l'aperçu.
 * \param padding Le padding.
 * \param firstTurn Indique si c'est le premier tour.
 * \param playerTiles Les tuiles des joueurs.
 * \param currentPlayer Le joueur actuel.
 * \param selectedTile La tuile sélectionnée.
 * \param listPlayers La liste des joueurs.
 * \param clickTileExchange Indique si l'échange de tuiles est cliqué.
 * \param clickRepair Indique si la réparation est cliquée.
 */
void BoardDisplay::display(int startX, int startY, int size, int sizeCell, int sizeCellPreview, int previewSize, int previewPadding, int padding, bool firstTurn, const vector<vector<vector<vector<int>>>>& playerTiles, int currentPlayer, const vector<vector<int>>& selectedTile, vector<Player> listPlayers, bool clickTileExchange, bool clickRepair) {
    string currentPlayerName = listPlayers[currentPlayer].getName();
    Color currentPlayerColor = listPlayers[currentPlayer].getColor();
    int textWidth = MeasureText(currentPlayerName.c_str(), 30);
    DrawRectangle(startX, padding - 50, textWidth + 20, 50, Fade(currentPlayerColor, 0.5f));
    DrawText(currentPlayerName.c_str(), startX + 10, padding - 40, 30, WHITE);

    if (firstTurn) {
        DrawText("INITIALISATION", startX + 750, padding - 40, 30, WHITE);
    } else if (listPlayers[currentPlayer].getNbTilesPlaced() < 10) {
        DrawText(("TOUR " + to_string(listPlayers[currentPlayer].getNbTilesPlaced())).c_str(), startX + 886, padding - 40, 30, WHITE);
    } else {
        DrawText("PARTIE TERMINEE", startX + 705, padding - 40, 30, WHITE);
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Case &currentCase = board.getCase(i, j);
            Color color;
            int playerCase = currentCase.getCasePlayer();
            if (playerCase == 0) {
                color = LIGHTGRAY;
            } else {
                playerCase--;
                color = listPlayers[playerCase].getColor();
            }
            Color colorEmpty = color;

            if (firstTurn) {
                int nbPlayer = listPlayers.size();
                vector<vector<bool>> pos;
                if (nbPlayer <= 4) {
                    pos = {{i < size / 2, j < size / 2}, {i < size / 2, j >= size / 2}, {i >= size / 2, j < size / 2}, {i >= size / 2, j >= size / 2}};
                } else {
                    pos = {{i < size / 3, j < size / 3}, {i < size / 3, j >= size / 3 && j < 2 * size / 3}, {i < size / 3, j >= 2 * size / 3},
                           {i >= size / 3 && i < 2 * size / 3, j < size / 3}, {i >= size / 3 && i < 2 * size / 3, j >= size / 3 && j < 2 * size / 3},
                           {i >= size / 3 && i < 2 * size / 3, j >= 2 * size / 3}, {i >= 2 * size / 3, j < size / 3}, {i >= 2 * size / 3, j >= size / 3 && j < 2 * size / 3},
                           {i >= 2 * size / 3, j >= 2 * size / 3}};
                }
                for (int k = 0; k < nbPlayer; ++k) {
                    if (pos[k][0] && pos[k][1]) {
                        colorEmpty = Fade(listPlayers[k].getColor(), 0.2f);
                    }
                }
            }

            if (currentCase.getType() == 0) {
                DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, colorEmpty);
                DrawRectangleLines(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell,WHITE);
            }
            else if (currentCase.getType() == 1) {
                DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, color);
                DrawRectangleLines(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell,WHITE);
            } else if (currentCase.getType() == 2) {
                DrawTexture(textureBonusTicket, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            } else if (currentCase.getType() == 3) {
                DrawTexture(textureBonusStone, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            } else if (currentCase.getType() == 4) {
                DrawTexture(textureBonusVol, padding + j * sizeCell, padding + i * sizeCell, WHITE);
            }else if (currentCase.getType() == 5) {
                DrawRectangle(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, BLACK);
                DrawRectangleLines(padding + j * sizeCell, padding + i * sizeCell, sizeCell, sizeCell, WHITE);
            }

        }
    }

    if (listPlayers[currentPlayer].getNbTilesPlaced() < 10) {
        DrawText("TUILES A VENIR", startX, startY - 60, 30, WHITE);
        for (int i = 0; i < previewSize && i < playerTiles[currentPlayer].size(); ++i) {
            int offsetX = startX + (sizeCellPreview + previewPadding) * i;
            int offsetY = startY;

            vector<vector<int>> tilePattern = playerTiles[currentPlayer][playerTiles[currentPlayer].size() - 1 - i];
            for (int row = 0; row < tilePattern.size(); ++row) {
                for (int col = 0; col < tilePattern[row].size(); ++col) {
                    if (tilePattern[row][col] == 1) {
                        int posX = offsetX + col * sizeCellPreview;
                        int posY = offsetY + row * sizeCellPreview;
                        Color color = listPlayers[currentPlayer].getColor();
                        DrawRectangle(posX, posY, sizeCellPreview, sizeCellPreview, color);
                        DrawRectangleLines(posX, posY, sizeCellPreview, sizeCellPreview, WHITE);
                    }
                }
            }
        }
    }
    Color colorTextEchange = WHITE;
    Color colorTextRepair = WHITE;
    if (clickTileExchange) {
        colorTextEchange = listPlayers[currentPlayer].getColor();
    }
    if (clickRepair) {
        colorTextRepair = listPlayers[currentPlayer].getColor();
    }

    DrawText(("COUPON D'ECHANGE : " + to_string(listPlayers[currentPlayer].getTileCoupons())).c_str(), startX + 645, startY - 60, 30, BLACK);
    if (listPlayers[currentPlayer].getNbTilesPlaced() < 10) {
        DrawRectangle(startX + 725, startY - 25, 195, 60, Fade(BLACK, 0.5f));
        DrawText("ECHANGER", startX + 740, startY - 10, 30, colorTextEchange);
        if (board.hasCrack()) {
            DrawRectangle(startX + 733, startY + 45, 180, 60, Fade(BLACK, 0.5f));
            DrawText("REPARER", startX + 753, startY + 60, 30, colorTextRepair);
        }
    } else {
        if (currentPlayer != listPlayers.size() - 1) {
            DrawRectangle(startX + 725, startY - 25, 230, 60, Fade(BLACK, 0.5f));
            DrawText("FIN DU TOUR", startX + 740, startY - 10, 30, listPlayers[currentPlayer].getColor());
        }
        else {
            DrawRectangle(startX + 725, startY - 25, 210, 60, Fade(BLACK, 0.5f));
            DrawText("FIN DU JEU", startX + 740, startY - 10, 30, listPlayers[currentPlayer].getColor());
        }
    }
}