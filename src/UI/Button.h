//
// Created by David on 06/06/2025.
//

#pragma once

#include <vector>
#include "raylib.h"

enum ButtonState
{
    None,
    Hovered,
    Pressed,
    Disabled
};

class Button
{
private:
    ButtonState state = ButtonState::None;
    Rectangle bounds = { 0, 0, 0, 0 };
    Texture2D sprite;
    Vector2 position;

public:
    Button(Texture2D sprite, Vector2 pos)
    {
        this->position = pos;
        this->sprite = sprite;
        this->bounds = { position.x, position.y, (float)sprite.width, (float)sprite.height };
        this->state = ButtonState::None;
    }

    void Update()
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

    void Draw()
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
            case ButtonState::Disabled:
                DrawTexture(sprite, position.x, position.y, Fade(WHITE, 0.3f));
                break;
        }

        DrawRectangleRoundedLines(bounds, 0, 0, 5, GREEN);
    }
};


class ButtonList
{
public:
    void SwitchButton(bool up)
    {
        if (up) currentIndex++;
        else currentIndex--;

        currentButton = buttons[currentIndex % buttons.size()];
    }
private:
    std::vector<Button> buttons;
    int currentIndex = 0;
    Button currentButton;
};