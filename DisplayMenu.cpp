//
// Created by alexd on 08/11/2024.
//

#include "DisplayMenu.h"
#include <iostream>
#include "raylib.h"

DisplayMenu::DisplayMenu(int screenWidth, int screenHeight)
        : screenWidth(screenWidth), screenHeight(screenHeight), gameStart(false), numPlayers(4), selectedPlayer(-1) {
    playerNames.resize(numPlayers, "");
    playerColors.resize(numPlayers, GRAY);
    availableColors = {RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, BROWN, LIME, DARKGRAY};
}

void DisplayMenu::showMenu() {
    while (!WindowShouldClose() && !gameStart) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawMenu();
        handleInput();
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
        DrawText(("Player " + to_string(i + 1) + ": " + playerNames[i]).c_str(), 100, 200 + 75 * i, 40, color);
        Color squareColor = (playerColors[i].r == GRAY.r && playerColors[i].g == GRAY.g && playerColors[i].b == GRAY.b && playerColors[i].a == GRAY.a) ? RAYWHITE : playerColors[i];
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
        playerNames.resize(numPlayers, "");
        playerColors.resize(numPlayers, GRAY);
    }
    if (IsKeyPressed(KEY_DOWN)) {
        if (numPlayers > 2){
            for (int i = numPlayers - 1; i >= numPlayers - 1; --i) {
                if (!(playerColors[i].r == GRAY.r && playerColors[i].g == GRAY.g && playerColors[i].b == GRAY.b && playerColors[i].a == GRAY.a)) {
                    availableColors.push_back(playerColors[i]);
                }
            }
            numPlayers--;
            playerNames.resize(numPlayers, "");
            playerColors.resize(numPlayers, GRAY);
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
            gameStart = true;
        }

        if (selectedPlayer != -1) {
            for (int i = 0; i < availableColors.size(); ++i) {
                if (mousePosition.x > 100 + i * 50 && mousePosition.x < 140 + i * 50 &&
                    mousePosition.y > 230 + 75 * numPlayers && mousePosition.y < 270 + 75 * numPlayers) {
                    if (!(playerColors[selectedPlayer].r == GRAY.r && playerColors[selectedPlayer].g == GRAY.g && playerColors[selectedPlayer].b == GRAY.b && playerColors[selectedPlayer].a == GRAY.a)) {
                        availableColors.push_back(playerColors[selectedPlayer]);
                    }
                    playerColors[selectedPlayer] = availableColors[i];
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

            playerNames[selectedPlayer] += (char)key;
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !playerNames[selectedPlayer].empty()) {
            playerNames[selectedPlayer].pop_back();
        }
    }
}