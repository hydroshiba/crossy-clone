#include "vehicle.hpp"

Vehicle::Vehicle(Texture const* const texture, const Vec2& size, const Vec2& pos, const Vec2& off) : Isometric(texture, size, pos) {
    shift(off.x, off.y);
}

void Vehicle::move(float speed) {
    Isometric::x += speed;
}

bool Vehicle::collide(Player* player) {
    float playerLeft = player->position().x - (player->collisionSize().x * 0.5f);
    float playerRight = playerLeft + player->collisionSize().x;

    float left = x;
    float right = left + collisionSize().x;

    if(left <= playerLeft && playerLeft <= right) return true;
    if(left <= playerRight && playerRight <= right) return true;
    return false;
}

void Vehicle::render(Engine* engine, int offset) {
    Isometric::y += offset;
    project();
    Isometric::render(engine);
    Isometric::y -= offset;
}