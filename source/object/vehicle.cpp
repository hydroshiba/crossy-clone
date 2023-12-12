#include "vehicle.hpp"

Vehicle::Vehicle(Texture const * const texture, const Vec2& size, const Vec2& pos, const Vec2& off) : Isometric(texture, size, pos) {
    shift(off.x, off.y);
}

void Vehicle::move(float speed) {
    Isometric::x += speed;
}

bool Vehicle::collide(float pos) {
    if (pos == -1.0f) return false;
    return ((Isometric::x <= pos) && (this->Isometric::x + Isometric::width >= pos));
}

void Vehicle::render(Engine* engine) {
    project();
    Isometric::render(engine);
}