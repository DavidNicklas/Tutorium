#include <cstdlib>

#include "raylib.h"
#include "config.h"
#include "../libs/json.hpp"
#include "StateMachine/StateMachine.h"
#include "StateMachine/IdleState.h"
#include "UI/Button.h"
#include "Map/Map.h"

using json = nlohmann::json;

int main() {
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    Map map("assets/maps/TileSet.json", "assets/graphics/tilesets/Tileset.png");
    map.AddLevel(1, "Level 1", "assets/maps/TutoriumSampleMap.json");

    // State Machine Initialization
    StateMachine stateMachine;
    IdleState idleState;

    stateMachine.ChangeState(&idleState);

    Button testButton(LoadTexture("assets/graphics/ui/Button1.png"), { 100, 100 });

    // Main game loop
    while (!WindowShouldClose())
    {
        // Game Logic Update
        testButton.Update();

        // Drawing
        BeginDrawing();
            ClearBackground(WHITE);
            map.Draw();
            testButton.Draw();
        EndDrawing();
    } // Main game loop end

    // De-initialization here

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}