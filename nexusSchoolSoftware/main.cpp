#include "raylib.h"
#include "colors.h"
#include "gui.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SW, SH, "Nexus School Software");
    SetTargetFPS(60);

    // Initialize the core application data
    App a{};
    initializeAccounts(a.accounts, maxAccounts);
    initializeHomeworkAssignments(a.hw);
    initializeQuestionBank(a.qbank, questionBankSize);

    // Main Game Loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(C_BG);

        // Let the GUI system handle all drawing and logic based on current screen
        DrawAppScreen(a);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}