#include "displayWin.h"

using namespace std;

displayWin::displayWin(vector<Player> orderWinners) : orderWinners(orderWinners) {}

void displayWin::run() {
    InitWindow(800, 700, "Laying Grass - Game Over");
    SetTargetFPS(60);
    Image imgTrophee = LoadImage("../img/trophee.png");
    ImageResize(&imgTrophee, 40, 40);
    textureTrophee = LoadTextureFromImage(imgTrophee);
    UnloadImage(imgTrophee);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Game Over", 275, 50, 50, RED);
        DrawText("Player", 150, 150, 30, BLACK);
        DrawText("Biggest", 350, 135, 30, BLACK);
        DrawText("Square", 350, 165, 30, BLACK);
        DrawText("Number of", 542, 135, 30, BLACK);
        DrawText("Grass", 600, 165,30, BLACK);
        DrawTexture(textureTrophee, 40, 222, WHITE);
        for (int i = 0; i < orderWinners.size(); i++) {
            DrawRectangle(90, 218 + 50 * i, 610, 50, Fade(orderWinners[i].getColor(), 0.25f));
            DrawText((to_string(i+1)).c_str(), 105, 230 + 50 * i, 30, orderWinners[i].getColor());
            DrawText(" | ", 120, 230 + 50 * i, 30, orderWinners[i].getColor());
            DrawText(orderWinners[i].getName().c_str(), 150, 230 + 50 * i, 30, orderWinners[i].getColor());
            DrawText(to_string(orderWinners[i].getBiggestSquare()).c_str(), 398, 230 + 50 * i, 30, orderWinners[i].getColor());
            DrawText(to_string(orderWinners[i].getNbGrassPlaced()).c_str(), 655, 230 + 50 * i, 30, orderWinners[i].getColor());
        }
        EndDrawing();
    }
    CloseWindow();
}

displayWin::~displayWin() {
    UnloadTexture(textureTrophee);
}