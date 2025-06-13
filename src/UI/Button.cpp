//
// Created by David on 06/06/2025.
//

#include "Button.h"

void Button::Update()
{
    Vector2 mousePos = GetMousePosition();
    if (CheckCollisionPointRec(mousePos, bounds))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            state = ButtonState::Pressed;
        }
        else
        {
            state = ButtonState::Hovered;
        }
    }
    else
    {
        state = ButtonState::None;
    }
}

void Button::Draw()
{
    switch (state)
    {
        case ButtonState::None:
            DrawTexture(sprite, position.x, position.y, WHITE);
            break;
        case ButtonState::Hovered:
            DrawTexture(sprite, position.x, position.y, Fade(WHITE, 0.8f));
            break;
        case ButtonState::Pressed:
            DrawTexture(sprite, position.x, position.y, Fade(WHITE, 0.5f));
            break;
    }
}