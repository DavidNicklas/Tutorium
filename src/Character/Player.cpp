//
// Created by David on 13/06/2025.
//

#include "Player.h"

void Player::Move(const std::vector<Rectangle>& colliders) {
    Vector2 dir = { 0, 0 };
    if (IsKeyDown(KEY_W)) dir.y -= 1.0f;
    if (IsKeyDown(KEY_S)) dir.y += 1.0f;
    if (IsKeyDown(KEY_A)) dir.x -= 1.0f;
    if (IsKeyDown(KEY_D)) dir.x += 1.0f;

    if (dir.x == 0 && dir.y == 0) return;

    // Normalize to achieve same speed in all directions
    dir = Vector2Normalize(dir);

    // Frame-independent speed
    float delta = GetFrameTime();
    float moveAmount = movementSpeed * delta;

    // Separate horizontal and vertical movement to avoid diagonal speed increase
    // Horizontal movement
    Vector2 nextPosX = { position.x + dir.x * moveAmount, position.y };
    Rectangle boundsX = {
            nextPosX.x - playerRadius,
            nextPosX.y - playerRadius,
            playerRadius * 2,
            playerRadius * 2
    };
    if (CanMoveTo(boundsX, colliders)) {
        position.x = nextPosX.x;
    }

    // Vertical movement
    Vector2 nextPosY = { position.x, position.y + dir.y * moveAmount };
    Rectangle boundsY = {
            nextPosY.x - playerRadius,
            nextPosY.y - playerRadius,
            playerRadius * 2,
            playerRadius * 2
    };
    if (CanMoveTo(boundsY, colliders)) {
        position.y = nextPosY.y;
    }
}

bool Player::CanMoveTo(Rectangle nextPos, const std::vector<Rectangle>& colliders) {
    for (const auto& collider : colliders) {
        if (CheckCollisionRecs(nextPos, collider)) return false;
    }
    return true;
}