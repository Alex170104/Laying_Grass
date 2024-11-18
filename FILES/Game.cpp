#include "Game.h"
#include "raylib.h"
#include "Tiles.h"
#include "displayWin.h"
#include <iostream>
#include <random>
#include "Bonus.h"

using namespace std;


/**
 * @brief Constructeur de la classe Game.
 *
 * @param size Taille du plateau de jeu.
 * @param nbPlayer Nombre de joueurs.
 * @param sizeCell Taille des cellules du plateau.
 * @param padding Espacement autour du plateau.
 * @param listPlayers Liste des joueurs participant au jeu.
 */
Game::Game(int size, int nbPlayer, int sizeCell, int padding, vector<Player> listPlayers)
        : board(size, nbPlayer), nbPlayer(nbPlayer), size(size), sizeCell(sizeCell), padding(padding), listPlayers(listPlayers), boardDisplay(board, sizeCell){}


/**
 * @brief Lance la boucle principale du jeu.
 *
 * Gère les interactions utilisateur, l'affichage du plateau et la logique de jeu.
 */
void Game::run() {
    Tiles tiles;
    Bonus bonus;

    int currentPlayer = 0;
    vector<vector<vector<vector<int>>>> playerTiles = tiles.distributeTiles(nbPlayer);
    vector<vector<int>> selectedTile = playerTiles[currentPlayer].back();
    playerTiles[currentPlayer].pop_back();

    bool isPreviewing = true;
    bool clickTileExchange = false;
    bool clickRepair = false;
    bool clickEmptyCase = false;
    bool robber = false;

    int sizeCellPreview = 20;
    int previewSize = 5;
    int previewPadding = 100;
    int startX = padding;
    int startY = size * sizeCell + 2 * padding;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);

        // Détection du premier tour
        bool firstTurn;
        if (listPlayers[currentPlayer].getNbTilesPlaced() == 0) {
            firstTurn = true;
        } else {
            firstTurn = false;
        }

        // Affichage du plateau et de l'interface
        boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers, clickTileExchange, clickRepair);

        if (isPreviewing) {

            // Gérer l'aperçu de placement de tuile
            Vector2 mousePosition = GetMousePosition();
            int x = (mousePosition.x - padding) / sizeCell;
            int y = (mousePosition.y - padding) / sizeCell;

            bool validPosition = tiles.isValidPosition(x, y, board, size, selectedTile, firstTurn, currentPlayer, nbPlayer);

            Color playerColor = listPlayers[currentPlayer].getColor();
            Color tileColor = validPosition ? Fade(playerColor, 0.5f) : Fade({30, 30, 30, 255}, 0.8f);

            tiles.drawTilePattern(x, y, sizeCell, padding, tileColor, selectedTile);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && validPosition) {

                tiles.placeTile(y, x, currentPlayer + 1, board, selectedTile);
                listPlayers[currentPlayer].incrementNbTilesPlaced();

                isPreviewing = true;

                // Vérification des bonus après le placement
                int newActiveBonus = bonus.verifBonus(board, size);
                if (newActiveBonus != 0) {
                    if (newActiveBonus == 2) {
                        float startTime = GetTime();
                        string text = "+1 coupon d'échange !";
                        bonus.popUpBonus(startTime, sizeCell, size, padding, text, boardDisplay, startX, startY, sizeCellPreview, previewSize, previewPadding, firstTurn, playerTiles, currentPlayer, listPlayers, selectedTile);
                        listPlayers[currentPlayer].addTileCoupons();
                        boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers, clickTileExchange, clickRepair);

                    } else if (newActiveBonus == 3) {
                        isPreviewing = false;
                        float startTime = GetTime();
                        string text = "Vous lancez une pierre !";
                        bonus.popUpBonus(startTime, sizeCell, size, padding, text, boardDisplay, startX, startY, sizeCellPreview, previewSize, previewPadding, firstTurn, playerTiles, currentPlayer, listPlayers, selectedTile);
                        clickEmptyCase = true;

                    } else if (newActiveBonus == 4) {
                        isPreviewing = false;
                        float startTime = GetTime();
                        string text = "Vous volez une tuile !";
                        bonus.popUpBonus(startTime, sizeCell, size, padding, text, boardDisplay, startX, startY, sizeCellPreview, previewSize, previewPadding, firstTurn, playerTiles, currentPlayer, listPlayers, selectedTile);
                        robber = true;
                    }
                }
                if (robber){
                    int player;
                    int index;
                    EndDrawing();
                    tie(selectedTile, player, index) = bonus.robbery(currentPlayer, robber, listPlayers, playerTiles, previewSize, 30, previewPadding);
                    playerTiles[player].erase(playerTiles[player].end() - index - 1);
                    robber = false;
                    isPreviewing = true;
                    continue;
                }
                if (!clickEmptyCase) {
                    currentPlayer = (currentPlayer + 1) % nbPlayer;
                    selectedTile = playerTiles[currentPlayer].back();
                    playerTiles[currentPlayer].pop_back();
                }

                if (listPlayers[currentPlayer].getNbTilesPlaced() >= 10) {
                    EndDrawing();
                    BeginDrawing();
                    ClearBackground(GRAY);
                    boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers, clickTileExchange, clickRepair);
                    EndDrawing();
                    vector<Player> orderWinners = calculWin();
                    displayWin displayWin(orderWinners);
                    displayWin.run();
                    return;
                }
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                tiles.rotateTilePattern(selectedTile);
            }
            if (IsKeyPressed(KEY_F)) {
                tiles.flip(selectedTile);
            }
            // Logique pour placer une pierre
        } else if (clickEmptyCase) {
            Vector2 mousePosition = GetMousePosition();
            int x = (mousePosition.x - padding) / sizeCell;
            int y = (mousePosition.y - padding) / sizeCell;

            if (x >= 0 && x < size && y >= 0 && y < size && board.getCase(y, x).getType() == 0) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && board.getCase(y, x).getType() == 0) {
                    board.getCase(y, x).setType(5);
                    boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer, selectedTile, listPlayers, clickTileExchange, clickRepair);
                    EndDrawing();
                    float startTime = GetTime();
                    string text = "vous avez place une pierre";
                    bonus.popUpBonus(startTime, sizeCell, size, padding, text, boardDisplay, startX, startY, sizeCellPreview, previewSize, previewPadding, firstTurn, playerTiles, currentPlayer, listPlayers, selectedTile);
                    BeginDrawing();
                    clickEmptyCase = false;
                    isPreviewing = true;
                    currentPlayer = (currentPlayer + 1) % nbPlayer;
                    selectedTile = playerTiles[currentPlayer].back();
                    playerTiles[currentPlayer].pop_back();
                }
            }
        } else {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePosition = GetMousePosition();
                vector<vector<int>> tileMove;

                // Logique pour échanger une tuile
                if (clickTileExchange) {
                    clickRepair = false;
                    for (int i = 0; i < previewSize && i < playerTiles[currentPlayer].size(); ++i) {
                        int offsetX = startX + (sizeCellPreview + previewPadding) * i;
                        int offsetY = startY;

                        for (int row = 0; row < playerTiles[currentPlayer][playerTiles[currentPlayer].size() - 1 - i].size(); ++row) {
                            for (int col = 0; col < playerTiles[currentPlayer][playerTiles[currentPlayer].size() - 1 - i][row].size(); ++col) {
                                int posX = offsetX + col * sizeCellPreview;
                                int posY = offsetY + row * sizeCellPreview;

                                if (mousePosition.x > posX && mousePosition.x < posX + sizeCellPreview &&
                                    mousePosition.y > posY && mousePosition.y < posY + sizeCellPreview) {
                                    bonus.ticketExchange(playerTiles, currentPlayer, i);
                                    listPlayers[(currentPlayer + nbPlayer) %nbPlayer].removeTileCoupons();
                                    isPreviewing = true;
                                    clickTileExchange = false;
                                    boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer,selectedTile, listPlayers, clickTileExchange, clickRepair);
                                }
                            }
                        }
                    }
                }
                // Logique pour réparer une case
                if (clickRepair) {
                    clickTileExchange = false;
                    for (int i = 0; i < size; i++) {
                        for (int j = 0; j < size; j++) {
                            if (mousePosition.x > padding + j * sizeCell && mousePosition.x < padding + (j + 1) * sizeCell &&
                                mousePosition.y > padding + i * sizeCell && mousePosition.y < padding + (i + 1) * sizeCell) {
                                if (board.getCase(i, j).getType() == 5) {
                                    board.getCase(i, j).setType(0);
                                    listPlayers[currentPlayer].removeTileCoupons();
                                    isPreviewing = true;
                                    clickRepair = false;
                                    boardDisplay.display(startX, startY, size, sizeCell, sizeCellPreview, previewSize, previewPadding, padding, firstTurn, playerTiles, currentPlayer,selectedTile, listPlayers, clickTileExchange, clickRepair);
                                }
                            }
                        }
                    }
                }
                if (mousePosition.x > startX + 725 && mousePosition.x < startX + 920 &&
                    mousePosition.y > startY - 25 && mousePosition.y < startY + 35 && listPlayers[currentPlayer].getTileCoupons() > 0) {
                    if (listPlayers[currentPlayer].getNbTilesPlaced() < 10) {
                        clickTileExchange = !clickTileExchange;
                        clickRepair = false;
                    }
                    else {
                        endGameEchange(currentPlayer, playerTiles, selectedTile);
                        isPreviewing = true;
                    }
                }
                if (mousePosition.x > startX + 733 && mousePosition.x < startX + 913 &&
                    mousePosition.y > startY + 45 && mousePosition.y < startY + 105 && board.hasCrack() && listPlayers[currentPlayer].getTileCoupons() > 0) {
                    clickRepair = !clickRepair;
                    clickTileExchange = false;
                }
            }
        }

        // Gestion des touches de la barre d'espace
        if (IsKeyPressed(KEY_SPACE) && (!clickEmptyCase)) {
            clickTileExchange = false;
            clickRepair = false;
            isPreviewing = !isPreviewing;
        }
        EndDrawing();
    }
    CloseWindow();
}

void Game::endGameEchange(int currentPlayer, vector<vector<vector<vector<int>>>>& playerTiles, vector<vector<int>>& selectedTile) {
    vector<vector<int>> tile1x1 = {{1}};
    if (listPlayers[currentPlayer].getTileCoupons() > 0) {
        selectedTile = tile1x1;
        listPlayers[currentPlayer].removeTileCoupons();
    }
}

/**
 * @brief Calcule les gagnants de la partie.
 *
 * @return La liste des joueurs gagnants, ordonnée par score décroissant.
 */
vector<Player> Game::calculWin() {
    vector<Player> winnersOrdered;
    vector<Player> listPlayersRestant;
    for (int i = 0; i < nbPlayer; i++) {
        listPlayers[i].setBiggestSquare(biggerSquare(i + 1));
        listPlayers[i].setNbGrassPlaced(nbGrassPlaced(i + 1));
        listPlayersRestant.push_back(listPlayers[i]);
    }
    while (!listPlayersRestant.empty()) {
        int maxSquare = 0;
        int maxGrass = 0;
        int index = 0;
        for (int i = 0; i < listPlayersRestant.size(); i++) {
            if (listPlayersRestant[i].getBiggestSquare() > maxSquare) {
                maxSquare = listPlayersRestant[i].getBiggestSquare();
                maxGrass = listPlayersRestant[i].getNbGrassPlaced();
                index = i;
            } else if (listPlayersRestant[i].getBiggestSquare() == maxSquare) {
                if (listPlayersRestant[i].getNbGrassPlaced() >= maxGrass) {
                    maxSquare = listPlayersRestant[i].getBiggestSquare();
                    maxGrass = listPlayersRestant[i].getNbGrassPlaced();
                    index = i;
                }
            }
        }
        winnersOrdered.push_back(listPlayersRestant[index]);
        listPlayersRestant.erase(listPlayersRestant.begin() + index);
    }
    return winnersOrdered;
}

/**
 * @brief Calcule la plus grande zone de cases contigües d'un joueur.
 *
 * @param player Le joueur dont on veut calculer la plus grande zone.
 * @return La taille de la plus grande zone de cases contigües du joueur.
 */
int Game::biggerSquare(int player) {
    int maxSquare = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board.getCase(i, j).getCasePlayer() == player) {
                int square = 1;
                bool alwaySquare = true;
                while (alwaySquare) {
                    for (int k = 0; k < square; k++) {
                        for (int l = 0; l < square; l++) {
                            if (i + k >= size || j + l >= size || board.getCase(i + k, j + l).getCasePlayer() != player) {
                                alwaySquare = false;
                                break;
                            }
                        }
                        if (!alwaySquare) break;
                    }
                    if (alwaySquare) {
                        square++;
                    }
                }
                if (square - 1 > maxSquare) {
                    maxSquare = square - 1;
                }
            }
        }
    }
    return maxSquare;
}

/**
 * @brief Compte le nombre de cases de type 1 (herbe) d'un joueur.
 *
 * @param player Le joueur dont on veut compter les cases de type 1.
 * @return Le nombre de cases de type 1 du joueur.
 */
int Game::nbGrassPlaced(int player) {
    int nbGrass = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board.getCase(i, j).getCasePlayer() == player) {
                nbGrass++;
            }
        }
    }
    return nbGrass;
}