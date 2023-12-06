#include "vehicle.hpp"

Vehicle::Vehicle(const Texture& texture, const Vec2& size, const Vec2& pos, const Vec2& off) : Isometric(texture, size, pos, off) {}

void Vehicle::move(const float& speed) {
    pos.x += speed;
    project();
}

bool Vehicle::collide(const float& pos) {
    return (this->pos.x + size.x >= pos);
}