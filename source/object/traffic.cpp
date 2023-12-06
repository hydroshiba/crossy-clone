#include "traffic.hpp"

Traffic::Traffic(const Texture& green, const Texture& red, const Vec2& size, const Vec2& pos, const Vec2& off, bool isRed, int clock): 
    Isometric(green, size, pos, off),
    RED(red),
    isRed(isRed),
    interval(300),
    clock(clock) {}

void Traffic::process() {
    if (clock >= interval) {
        isRed = !isRed;
        clock = 0;
        return;
    }

    ++clock;
}

bool Traffic::isRedLight() const {
    return isRed;
}