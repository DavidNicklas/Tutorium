//
// Created by David on 10/06/2025.
//

#include "Map.h"
#include "config.h"

using json = nlohmann::json;

Map::Map(const std::string& tileSetJsonPath, const std::string& tileSetPath)
{
    json tileSetJson = JsonUtility::LoadJson(tileSetJsonPath);
    ParseAnimatedTiles(tileSetJson);
    ParseCollisionTiles(tileSetJson);
    tileSet = LoadTileSet(tileSetPath);

    tileSetColumns = tileSet.width / Game::TileSize; // Calculate the number of columns in the tile set
}

Texture2D Map::LoadTileSet(const std::string& path)
{
    return LoadTexture(path.c_str());
}

void Map::ParseAnimatedTiles(const json& tileSetJson)
{
    if (!tileSetJson.contains("tiles")) return;

    for (auto& [tileIDStr, tileData] : tileSetJson["tiles"].items())
    {
        if (tileData.contains("animation"))
        {
            int animatedTileID = tileData["id"];
            AnimatedTile animatedTile;
            for (const auto& frame : tileData["animation"])
            {
                animatedTile.frames.push_back(frame["tileid"]);
                animatedTile.durations.push_back(frame["duration"]);
                animatedTile.tileID = animatedTileID; // Set the tile ID for the animated tile
            }
            animatedTilesList.push_back(animatedTile);
        }
    }
}

void Map::ParseCollisionTiles(const json& tileSetJson)
{
    if (!tileSetJson.contains("tiles")) return;

    for (const auto& tile : tileSetJson["tiles"])
    {
        int tileID = tile["id"];
        if (tile.contains("objectgroup"))
        {
            const auto& objectGroup = tile["objectgroup"];
            for (const auto& object : objectGroup["objects"])
            {
                Rectangle collisionRect = {
                    static_cast<float>(object["x"]),
                    static_cast<float>(object["y"]),
                    static_cast<float>(object["width"]),
                    static_cast<float>(object["height"])
                };
                tileColliders[tileID].push_back(collisionRect);
            }
        }
    }
}

void Map::Draw()
{
    if (currentLevelIndex < 0 || currentLevelIndex >= levels.size()) return;

    auto mapJson = GetCurrentLevel().GetMap();
    int tileSize = Game::TileSize;

    UpdateAnimations();

    for (const auto& layer : mapJson["layers"])
    {
        if (layer["type"] != "tilelayer") continue;

        int layerWidth = layer["width"];
        int layerHeight = layer["height"];
        const auto& data = layer["data"];

        for (int y = 0; y < layerHeight; y++)
        {
            for (int x = 0; x < layerWidth; x++)
            {
                int index = y * layerWidth + x;
                int originalTileID = data[index];
                if (originalTileID == 0) continue;

                int tileID = originalTileID - 1;

                // Check if the tile is animated
                for (const auto& animatedTile : animatedTilesList)
                {
                    if (animatedTile.tileID == tileID)
                    {
                        tileID = animatedTile.GetCurrentFrameTileID();
                    }
                }

                Rectangle srcRect =
                        {
                                static_cast<float>((tileID % tileSetColumns) * tileSize),
                                static_cast<float>((tileID / tileSetColumns) * tileSize),
                                static_cast<float>(tileSize),
                                static_cast<float>(tileSize)
                        };

                Vector2 pos =
                        {
                                static_cast<float>(x * tileSize),
                                static_cast<float>(y * tileSize)
                        };

                DrawTextureRec(tileSet, srcRect, pos, WHITE);
            }
        }
    }

    // Draw Collision rec
    for (const auto& collider : solidColliders)
    {
        DrawRectangleRec(collider, { 255, 0, 0, 100 }); // Semi-transparent red for visibility
    }
}

void Map::AddLevel(int number, const std::string& name, const std::string& mapPath)
{
    Level level = Level(number, name, mapPath);
    levels.push_back(level);

    if (currentLevelIndex == -1) currentLevelIndex = 0;

    // Sort levels by number
    std::sort(levels.begin(), levels.end(), [](const Level& a, const Level& b) {
        return a.GetNumber() < b.GetNumber();
    });
}

void Map::SetCurrentLevel(int number) {
    int index = number - 1;
    if (index >= 0 && index < levels.size()) {
        currentLevelIndex = index;
    }
    else {
        std::cerr << "Invalid level index: " << number << std::endl;
    }

    GenerateWorldCollisionRecs();
}

Level& Map::GetLevel(int index)
{
    if (index < 0 || index >= levels.size())
    {
        std::cerr << "Index out of bounds" << std::endl;
        return levels[0]; // Return a default level or handle the error as needed
    }

    return levels[index];
}

void Map::UpdateAnimations()
{
    for (auto& tile : animatedTilesList)
    {
        tile.Update();
    }
}

void Map::GenerateWorldCollisionRecs()
{
    solidColliders.clear();

    const auto& mapJson = GetCurrentLevel().GetMap();
    const int tileSize = Game::TileSize;

    for (const auto& layer : mapJson["layers"]) {
        if (layer["type"] != "tilelayer") continue;

        int layerWidth = layer["width"];
        const auto& data = layer["data"];

        for (int y = 0; y < layer["height"]; y++) {
            for (int x = 0; x < layerWidth; x++) {
                int index = y * layerWidth + x;
                int rawTileID = data[index];
                if (rawTileID == 0) continue;

                int tileID = rawTileID - 1;
                if (tileColliders.count(tileID)) {
                    for (const auto& rect : tileColliders[tileID]) {
                        Rectangle worldRect = {
                                x * tileSize + rect.x,
                                y * tileSize + rect.y,
                                rect.width,
                                rect.height
                        };
                        solidColliders.push_back(worldRect);
                    }
                }
            }
        }
    }
}
