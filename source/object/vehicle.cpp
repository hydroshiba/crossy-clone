#include "vehicle.hpp"

Vehicle::Vehicle(Texture const * const texture, const Vec2& size, const Vec2& pos, const Vec2& off) : Isometric(texture, size, pos) {
    shift(off.x, off.y);
}

void Vehicle::move(float speed) {
    Isometric::x += speed;
}

// bool Vehicle::collide(float pos) {
//     if (pos == -1.0f) return false;
//     return ((this->Isometric::x <= pos) && (this->Isometric::x + 2.0f >= pos));
// }

bool Vehicle::collide(float pos) {
    if (pos == -1.0f) return false;

    float dist = (texture->getWidth() - width * 0.5f) / (width * 0.5f);
    float left = Isometric::x;
    float right = Isometric::x + dist;

    return (left <= pos && pos <= right);
}

void Vehicle::render(Engine* engine, int offset) {
    Isometric::y += offset;
    project();
    Isometric::render(engine);
    Isometric::y -= offset;
}