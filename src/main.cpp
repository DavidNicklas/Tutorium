#include <cstdlib>

#include "raylib.h"
#include "config.h"

int main() {
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here

    // Main game loop
    while (!WindowShouldClose())
    {
        // Game Logic Update

        // Drawing
        BeginDrawing();
            ClearBackground(WHITE);
            DrawText("Hello, world!", 10, 10, 30, LIGHTGRAY);

        EndDrawing();
    } // Main game loop end

    // De-initialization here

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
