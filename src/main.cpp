#include <cstdlib>

#include "raylib.h"
#include <fstream>
#include "config.h"
#include "../libs/json.hpp"
#include "StateMachine/StateMachine.h"
#include "StateMachine/IdleState.h"
#include "UI/Button.h"

using json = nlohmann::json;

void DrawMap(json loadedJsonMap, Texture2D tileSet, int tileSize, int tileSetColumns);

int main() {
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    std::ifstream file("assets/maps/TutoriumSampleMap.json");
    json loadedJsonMap;
    file >> loadedJsonMap; // Read the file into the json object using >> overloaded operator

    Texture2D tileSet = LoadTexture("assets/graphics/tilesets/Tileset.png");

    const int tileSize = 16;
    const int tileSetColumns = 27;

    // State Machine Initialization
    StateMachine stateMachine;
    IdleState idleState;

    stateMachine.ChangeState(&idleState);

    Button testButton(LoadTexture("assets/graphics/ui/Button1.png"), { 100, 100 });
    Button testButton2(LoadTexture("assets/graphics/ui/Button1.png"), { 200, 100 });

    // Main game loop
    while (!WindowShouldClose())
    {
        // Game Logic Update
        testButton.Update();
        testButton2.Update();

        // Drawing
        BeginDrawing();
            ClearBackground(WHITE);

            DrawMap(loadedJsonMap, tileSet, tileSize, tileSetColumns);
            testButton.Draw();
            testButton2.Draw();
        EndDrawing();
    } // Main game loop end

    // De-initialization here
    UnloadTexture(tileSet);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}


// Helper Functions

void DrawMap(json loadedJsonMap, Texture2D tileSet, int tileSize, int tileSetColumns)
{
    auto layerCount = loadedJsonMap["layers"].size();
    for (int i = 0; i < layerCount; ++i)
    {
        auto layer = loadedJsonMap["layers"][i];
        int mapWidth = layer["width"];
        int mapHeight = layer["height"];
        // Draw the loaded map
        for (int y = 0; y < mapHeight; y++)
        {
            for (int x = 0; x < mapWidth; x++)
            {
                int index = y * mapWidth + x;
                int tiledID = layer["data"][index];
                if (tiledID == 0) continue; // Skip empty tiles

                int tiledIndex = tiledID - 1;
                Rectangle srcRect = {
                        static_cast<float>((tiledIndex % tileSetColumns) * tileSize), // Assuming tile size is 32x32
                        static_cast<float>((tiledIndex / tileSetColumns) * tileSize),
                        (float)tileSize, (float)tileSize
                };

                Vector2 pos = { (float)(x * tileSize) * 1.0f, (float)(y * tileSize) * 1.0f };
                // Draw the tile
                DrawTextureRec(tileSet, srcRect, pos, WHITE);
            }
        }
    }
}
