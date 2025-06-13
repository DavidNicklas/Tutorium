//
// Created by David on 10/06/2025.
//

#pragma once

#include <vector>
#include <iostream>
#include "raylib.h"

struct AnimatedTile
{
    std::vector<int> frames;
    std::vector<int> durations;
    float timer = 0.0f;
    int currentFrame = 0;
    int tileID = 0;

    void Update()
    {
        timer += GetFrameTime() * 1000; // deltaTime in seconds
        if (timer >= (float)durations[currentFrame])
        {
            // Move to the next frame
            currentFrame = (currentFrame + 1) % frames.size();

            // Reset the timer
            timer -= (float)durations[currentFrame];
        }
    }

    int GetCurrentFrameTileID() const
    {
        return frames[currentFrame];
    }
};
