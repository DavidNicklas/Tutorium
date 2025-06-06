//
// Created by David on 06/06/2025.
//

#pragma once

#include "BaseState.h"

class StateMachine
{
private:
    BaseState* currentState;

public:
    StateMachine()
        : currentState(nullptr)
    {
    }

    StateMachine(BaseState* initialState)
        : currentState(initialState)
    {
        if (currentState)
            currentState->EnterState();
    }

    void ChangeState(BaseState* newState)
    {
        if (!currentState) return;

        currentState->ExitState();
        currentState = newState;
        currentState->EnterState();
    }

    void Update()
    {
        if (currentState)
        {
            currentState->UpdateState();
        }
    }
};