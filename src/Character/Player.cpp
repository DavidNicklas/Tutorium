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

    dir = Vector2Normalize(dir);

    // Frame-independent speed
    float delta = GetFrameTime();
    Vector2 velocity = Vector2Scale(dir, movementSpeed * delta);
    Vector2 next = Vector2Add(position, velocity);

    Rectangle nextBounds = { next.x - playerRadius, next.y - playerRadius, playerRadius * 2, playerRadius * 2 };
    if (CanMoveTo(nextBounds, colliders)) {
        position = next;
    }
}

bool Player::CanMoveTo(Rectangle nextPos, const std::vector<Rectangle>& colliders) {
    for (const auto& collider : colliders) {
        if (CheckCollisionRecs(nextPos, collider)) return false;
    }
    return true;
}