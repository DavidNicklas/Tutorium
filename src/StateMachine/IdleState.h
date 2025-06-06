//
// Created by David on 06/06/2025.
//

#pragma once

#include <iostream>
#include "BaseState.h"
#include "raylib.h"

class IdleState : public BaseState
{
public:
    void EnterState() override {std::cout << "Entering Idle State" << std::endl; }
    void ExitState() override {std::cout << "Exiting Idle State" << std::endl; }
    void UpdateState() override
    {
        if (GetKeyPressed())
        {
            std::cout << "Transitioning to Walking State" << std::endl;
        }
    }
};

class WalkingState : public BaseState
{
public:
    void EnterState() override { std::cout << "Entering Walking State" << std::endl; }
    void ExitState() override { std::cout << "Exiting Walking State" << std::endl; }
    void UpdateState() override { std::cout << "Updating Walking State" << std::endl; }
};