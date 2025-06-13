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
};

class Button
{
public:
    Button(Texture2D sprite, Vector2 pos)
    {
        this->position = pos;
        this->sprite = sprite;
        this->bounds = { position.x, position.y, (float)sprite.width, (float)sprite.height };
        this->state = ButtonState::None;
    }
    ~Button() { UnloadTexture(sprite); }

    void Update();
    void Draw();

private:
    ButtonState state = ButtonState::None;
    Rectangle bounds = { 0, 0, 0, 0 };
    Texture2D sprite;
    Vector2 position;
};

// This could be a future improvement to handle a list of buttons and handle the switch between buttons
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