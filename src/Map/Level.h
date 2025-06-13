//
// Created by David on 13/06/2025.
//

#pragma once

#include <string>
#include <utility>
#include "../../libs/json.hpp"
#include "../../libs/JsonUtility.hpp"

using json = nlohmann::json;

class Level
{
public:
    Level(int number, std::string name, const std::string& mapPath) :
            number(number),
            name(std::move(name)),
            mapJson(JsonUtility::LoadJson(mapPath)) {}

    [[nodiscard]] int GetNumber() const { return number; }
    [[nodiscard]] std::string GetName() const { return name; }
    [[nodiscard]] const json& GetMap() const { return mapJson; }

private:
    int number; // e.g. Level 1 or Level 2
    std::string name;
    json mapJson;
};
