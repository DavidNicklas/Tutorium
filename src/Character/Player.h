//
// Created by David on 13/06/2025.
//

#pragma once

#include <memory>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "../StateMachine/StateMachine.h"

class Player {
public:
    Vector2 position = { 0, 0 };
    StateMachine stateMachine;

    void Move(const std::vector<Rectangle>& colliders);
    bool CanMoveTo(Rectangle nextPos, const std::vector<Rectangle>& colliders);

    void Update() {
        stateMachine.Update();
    }

    void Draw() {
        DrawCircleV(position, playerRadius, BLUE);
    }

private:
    float movementSpeed = 100.0f;
    float playerRadius = 8.0f;
};