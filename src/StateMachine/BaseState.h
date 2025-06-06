//
// Created by David on 06/06/2025.
//

#pragma once

#include "StateMachine.h"

class BaseState
{
public:
    virtual void EnterState() = 0;
    virtual void ExitState() = 0;
    virtual void UpdateState() = 0;
};