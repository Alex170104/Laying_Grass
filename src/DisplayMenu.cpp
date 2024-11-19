#include <iostream>
#include <random>
#include <algorithm>

#include "../header/DisplayMenu.h"
#include "raylib.h"

/**
 * \brief Constructeur de la classe DisplayMenu.
 * \param screenWidth La largeur de l'écran.
 * \param screenHeight La hauteur de l'écran.
 */
DisplayMenu::DisplayMenu(int screenWidth, int screenHeight)
        : screenWidth(screenWidth), screenHeight(screenHeight), gameStart(false), numPlayers(4), selectedPlayer(-1) {
    listPlayers.resize(numPlayers, Player("", GRAY));
    availableColors = {PINK, RED, ORANGE, YELLOW, GREEN, DARKGREEN, BLUE, VIOLET, BEIGE};
    Image imgDANGER;
    imgDANGER = LoadImage("../img/DANGER.png");
    textureDANGER = LoadTextureFromImage(imgDANGER);
    UnloadImage(imgDANGER);
}

/**
 * \brief Destructeur de la classe DisplayMenu.
 */
DisplayMenu::~DisplayMenu() {
    UnloadTexture(textureDANGER);
}

/**
 * \brief Affiche le menu principal.
 */
void DisplayMenu::showMenu() {
    while (!WindowShouldClose() && !gameStart) {
        BeginDrawing();
        ClearBackground(GRAY);

        if (showWarning){
            DrawRectangle(screenWidth / 8, screenHeight / 3, screenWidth * 3 / 4, screenHeight / 3, Fade(BLACK, 0.8f));
            DrawTexture(textureDANGER, screenWidth / 2 - 50, screenHeight / 4 + 150, WHITE);
            DrawText("Veuillez entrer un nom", screenWidth / 2 - MeasureText("Veuillez entrer un nom", 40) / 2, screenHeight / 4 + 350, 40, RED);
            DrawText("et sélectionner une couleur", screenWidth / 2 - MeasureText("et sélectionner une couleur", 40) / 2, screenHeight / 4 + 400, 40, RED);
            if (GetTime() - warningTimer > 3) {
                showWarning = false;
            }
        } else {
            drawMenu();
            handleInput();
        }
        EndDrawing();
    }
}

/**
 * \brief Vérifie si le jeu a commencé.
 * \return true si le jeu a commencé, false sinon.
 */
bool DisplayMenu::isGameStart() const {
    return gameStart;
}

/**
 * \brief Dessine le menu principal.
 */
void DisplayMenu::drawMenu() {
    DrawRectangle(40, 100, screenWidth - 80, screenHeight - 150, RAYWHITE);
    DrawRectangle(screenWidth / 2 - 220, 30, 470, 60, Fade(BLACK, 0.8f));
    DrawText("Création des joueurs", screenWidth / 2 - 200, 40, 40, WHITE);
    DrawText("Nombre de joueurs:", 100, 150, 40, BLACK);
    DrawRectangle(500, 140, 60, 60, Fade(RED, 0.8f));
    DrawText(to_string(numPlayers).c_str(), 520, 150, 40, WHITE);
    DrawText("Utilisez les flèches HAUT/BAS pour changer", 100, 200, 20, BLACK);

    for (int i = 0; i < numPlayers; ++i) {
        Color color = (i == selectedPlayer) ? Fade(RED, 0.8f) : BLACK;
        DrawText(("Joueur " + to_string(i + 1) + ": " + listPlayers[i].getName()).c_str(), 100, 250 + 75 * i, 40, color);
        Color squareColor = (listPlayers[i].getColor().r == GRAY.r && listPlayers[i].getColor().g == GRAY.g && listPlayers[i].getColor().b == GRAY.b && listPlayers[i].getColor().a == GRAY.a) ? GRAY : listPlayers[i].getColor();
        DrawCircle(70, 270 + 75 * i, 20, squareColor);
    }

    DrawText("Couleurs disponibles :", 100, 250 + 75 * numPlayers, 20, BLACK);
    for (int i = 0; i < availableColors.size(); ++i) {
        DrawCircle(120 + i * 60, 305 + 75 * numPlayers, 25, availableColors[i]);
    }

    DrawRectangle(screenWidth / 2 - 170, screenHeight - 160, 308, 60, Fade(BLACK, 0.8f));
    DrawText("Lancer le jeu", screenWidth / 2 - 150, screenHeight - 150, 40, WHITE);
}

/**
 * \brief Gère les entrées utilisateur pour le menu.
 */
void DisplayMenu::handleInput() {
    if (IsKeyPressed(KEY_UP)) {
        if (numPlayers > 2){
            for (int i = numPlayers - 1; i >= numPlayers - 1; --i) {
                if (!(listPlayers[i].getColor().r == GRAY.r && listPlayers[i].getColor().g == GRAY.g && listPlayers[i].getColor().b == GRAY.b && listPlayers[i].getColor().a == GRAY.a)) {
                    availableColors.push_back(listPlayers[i].getColor());
                }
            }
            numPlayers--;
            listPlayers.resize(numPlayers, Player("", GRAY));
        }
    }
    if (IsKeyPressed(KEY_DOWN)) {
        numPlayers = (numPlayers < 9) ? numPlayers + 1 : 9;
        listPlayers.resize(numPlayers, Player("", GRAY));
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosition = GetMousePosition();
        for (int i = 0; i < numPlayers; ++i) {
            if (mousePosition.x > 100 && mousePosition.x < 600 &&
                mousePosition.y > 250 + 75 * i && mousePosition.y < 300 + 75 * i) {
                selectedPlayer = i;
            }
        }
        if (mousePosition.x > screenWidth / 2 - 120 && mousePosition.x < screenWidth / 2 + 155 &&
            mousePosition.y > screenHeight - 160 && mousePosition.y < screenHeight - 110) {
            bool allPlayersReady = true;
            for (const auto& player : listPlayers) {
                if (player.getName().empty() || (player.getColor().r == GRAY.r && player.getColor().g == GRAY.g && player.getColor().b == GRAY.b && player.getColor().a == GRAY.a)) {
                    allPlayersReady = false;
                    break;
                }
            }
            if (allPlayersReady) {
                gameStart = true;
            } else {
                showWarning = true;
                warningTimer = GetTime();
            }
        }

        if (selectedPlayer != -1) {
            for (int i = 0; i < availableColors.size(); ++i) {
                if (mousePosition.x > 120 + i * 60 - 25 && mousePosition.x < 120 + i * 60 + 25 &&
                    mousePosition.y > 305 + 75 * numPlayers - 50 && mousePosition.y < 305 + 75 * numPlayers + 25) {
                    if (!(listPlayers[selectedPlayer].getColor().r == GRAY.r && listPlayers[selectedPlayer].getColor().g == GRAY.g && listPlayers[selectedPlayer].getColor().b == GRAY.b && listPlayers[selectedPlayer].getColor().a == GRAY.a)) {
                        availableColors.push_back(listPlayers[selectedPlayer].getColor());
                    }
                    listPlayers[selectedPlayer].setColor(availableColors[i]);
                    availableColors.erase(availableColors.begin() + i);
                    selectedPlayer = -1;
                    break;
                }
            }
        }
    }

    if (selectedPlayer != -1) {
        int key = GetKeyPressed();
        if (key >= 32 && key <= 125) {
            // Map QWERTY keys to AZERTY
            if (key == 'A') key = 'Q';
            else if (key == 'Q') key = 'A';
            else if (key == 'Z') key = 'W';
            else if (key == 'W') key = 'Z';
            else if (key == 'M') key = ';';
            else if (key == ';') key = 'M';

            if (listPlayers[selectedPlayer].getName().size() < 12) {
                listPlayers[selectedPlayer].addChar((char)key);
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !listPlayers[selectedPlayer].getName().empty()) {
            listPlayers[selectedPlayer].removeChar();
        }
    }
}

vector<Player> DisplayMenu::getRandomListPlayers() {
    random_device rd;
    mt19937 g(rd());
    shuffle(listPlayers.begin(), listPlayers.end(), g);
    return listPlayers;
}