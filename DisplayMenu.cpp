#include "DisplayMenu.h"
#include <iostream>
#include "raylib.h"

DisplayMenu::DisplayMenu(int screenWidth, int screenHeight)
        : screenWidth(screenWidth), screenHeight(screenHeight), gameStart(false), numPlayers(4), selectedPlayer(-1) {
    listPlayers.resize(numPlayers, Player("", GRAY));
    availableColors = {RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, BROWN, LIME, DARKGRAY};
    Image imgDANGER;
    imgDANGER = LoadImage("../img/DANGER.png");
    textureDANGER = LoadTextureFromImage(imgDANGER);
    UnloadImage(imgDANGER);
}

DisplayMenu::~DisplayMenu() {
    UnloadTexture(textureDANGER);
}

void DisplayMenu::showMenu() {
    while (!WindowShouldClose() && !gameStart) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (showWarning){
            DrawTexture(textureDANGER, screenWidth / 2 - 50, 200, WHITE);
            DrawText("Please enter a name", screenWidth / 2 - 200, 350, 40, RED);
            DrawText("and select a color for each player", screenWidth / 2 - 350, 400, 40, RED);
            if (GetTime() - warningTimer > 3){
                showWarning = false;
            }
        } else {
            drawMenu();
            handleInput();
        }
        EndDrawing();
    }
}

bool DisplayMenu::isGameStart() {
    return gameStart;
}

void DisplayMenu::drawMenu() {
    DrawText("Create Players", screenWidth / 2 - 150, 0, 40, BLACK);
    DrawText("Number of Players:", 100, 100, 40, BLACK);
    DrawText(to_string(numPlayers).c_str(), 500, 100, 40, RED);
    DrawText("Use UP/DOWN keys to change", 100, 150, 20, BLACK);

    for (int i = 0; i < numPlayers; ++i) {
        Color color = (i == selectedPlayer) ? RED : BLACK;
        DrawText(("Player " + to_string(i + 1) + ": " + listPlayers[i].getName()).c_str(), 100, 200 + 75 * i, 40, color);
        Color squareColor = (listPlayers[i].getColor().r == GRAY.r && listPlayers[i].getColor().g == GRAY.g && listPlayers[i].getColor().b == GRAY.b && listPlayers[i].getColor().a == GRAY.a) ? RAYWHITE : listPlayers[i].getColor();
        DrawRectangle(50, 200 + 75 * i, 40, 40, squareColor);
    }

    DrawText("Available Colors:", 100, 200 + 75 * numPlayers, 20, BLACK);
    for (int i = 0; i < availableColors.size(); ++i) {
        DrawRectangle(100 + i * 50, 230 + 75 * numPlayers, 40, 40, availableColors[i]);
    }

    DrawText("Start Game", screenWidth / 2 - 50, screenHeight - 100, 20, BLACK);
}

void DisplayMenu::handleInput() {
    if (IsKeyPressed(KEY_UP)) {
        numPlayers = (numPlayers < 9) ? numPlayers + 1 : 9;
        listPlayers.resize(numPlayers, Player("", GRAY));
    }
    if (IsKeyPressed(KEY_DOWN)) {
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

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosition = GetMousePosition();
        for (int i = 0; i < numPlayers; ++i) {
            if (mousePosition.x > 100 && mousePosition.x < 600 &&
                mousePosition.y > 200 + 75 * i && mousePosition.y < 250 + 75 * i) {
                selectedPlayer = i;
            }
        }
        if (mousePosition.x > screenWidth / 2 - 50 && mousePosition.x < screenWidth / 2 + 50 &&
            mousePosition.y > screenHeight - 100 && mousePosition.y < screenHeight - 80) {
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
                if (mousePosition.x > 100 + i * 50 && mousePosition.x < 140 + i * 50 &&
                    mousePosition.y > 230 + 75 * numPlayers && mousePosition.y < 270 + 75 * numPlayers) {
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

            listPlayers[selectedPlayer].addChar((char)key);
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !listPlayers[selectedPlayer].getName().empty()) {
            listPlayers[selectedPlayer].removeChar();
        }
    }
}