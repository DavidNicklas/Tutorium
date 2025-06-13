//
// Created by David on 10/06/2025.
//

#pragma once

#include <string>
#include <fstream>
#include "../libs/json.hpp"

using json = nlohmann::json;

class JsonUtility
{
public:
    static json LoadJson(const std::string& jsonFilePath)
    {
        std::ifstream file(jsonFilePath);
        json loadedJsonMap;
        file >> loadedJsonMap; // Read the file into the json object using >> overloaded operator
        return loadedJsonMap;
    }
};
