//
// Created by David on 10/06/2025.
//

#pragma once

#include <string>
#include <vector>
#include "../../libs/json.hpp"
#include "raylib.h"
#include "AnimatedTile.hpp"
#include "Level.h"

using json = nlohmann::json;

class Map
{
public:
    Map(const std::string& tileSetJsonPath, const std::string& tileSetPath);
    ~Map() { UnloadTexture(tileSet); }

    void Draw();
    void AddLevel(int number, const std::string& name, const std::string& mapPath);
    void SetCurrentLevel(int index);
    Level& GetCurrentLevel() { return GetLevel(currentLevelIndex); }
    Level& GetLevel(int index);

    const std::vector<Rectangle>& GetSolidColliders() const { return solidColliders; }

private:
    // General
    static Texture2D LoadTileSet(const std::string& path);

    Texture2D tileSet{};
    int tileSetColumns;

    // int tileSize; // In our case defined inside Game namespace (project wide)

    // Levels
    int currentLevelIndex = -1; // -1 = no active Level
    std::vector<Level> levels;

    // Animations
    void ParseAnimatedTiles(const json& tileSetJson);
    void UpdateAnimations();
    std::vector<AnimatedTile> animatedTilesList;

    // Collisions
    void ParseCollisionTiles(const json& tileSetJson);
    void GenerateWorldCollisionRecs();
    std::unordered_map<int, std::vector<Rectangle>> tileColliders;
    std::vector<Rectangle> solidColliders;

};