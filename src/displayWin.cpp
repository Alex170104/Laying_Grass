#include "../header/displayWin.h"

using namespace std;

/**
 * \brief Constructeur de la classe displayWin.
 * \param orderWinners Le vecteur des joueurs gagnants.
 */
displayWin::displayWin(vector<Player> orderWinners) : orderWinners(orderWinners) {}

/**
 * \brief Exécute l'affichage de l'écran de fin de jeu.
 */
void displayWin::run() {
    InitWindow(800, 700, "Laying Grass - Game Over");
    SetTargetFPS(60);
    Image imgTrophee = LoadImage("../img/trophee.png");
    ImageResize(&imgTrophee, 40, 40);
    textureTrophee = LoadTextureFromImage(imgTrophee);
    UnloadImage(imgTrophee);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);

        DrawText("Game Over", 275, 50, 50, GOLD);
        DrawRectangle(80, 130, 640, 50 + 100 * orderWinners.size(), Fade(BLACK, 0.1f));
        DrawText("Joueur", 110, 160, 30, WHITE);
        DrawText("Plus grand", 325, 145, 30, WHITE);
        DrawText("carré", 360, 175, 30, WHITE);
        DrawText("Nombre de", 542, 145, 30, WHITE);
        DrawText("cases", 610, 175,30, WHITE);
        DrawTexture(textureTrophee, 40, 222, WHITE);
        for (int i = 0; i < orderWinners.size(); i++) {
            DrawRectangle(90, 218 + 50 * i, 610, 50, Fade(orderWinners[i].getColor(), 0.25f));
            DrawText((to_string(i+1)).c_str(), 105, 230 + 50 * i, 30, WHITE);
            DrawText(" | ", 120, 230 + 50 * i, 30, orderWinners[i].getColor());
            DrawText(orderWinners[i].getName().c_str(), 150, 230 + 50 * i, 30, WHITE);
            DrawText(to_string(orderWinners[i].getBiggestSquare()).c_str(), 398, 230 + 50 * i, 30, WHITE);
            DrawText(to_string(orderWinners[i].getNbGrassPlaced()).c_str(), 650, 230 + 50 * i, 30, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
}

/**
 * \brief Destructeur de la classe displayWin.
 */
displayWin::~displayWin() {
    UnloadTexture(textureTrophee);
}