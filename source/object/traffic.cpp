#include "traffic.hpp"

Traffic::Traffic(const float& pos, const Texture& red, const Texture& green) :
    Isometric(green, {100.0f, 100.0f}, {pos, 0.0f}),
    isRed(false),
    trafficRed(red),
    trafficGreen(green)
    {
        hrClock_TP now = high_resolution_clock::now();
        prev = now;
    }

Traffic::Traffic(const int& pos, const Texture& red, const Texture& green) :
    Isometric(green, {100.0f, 100.0f}, {static_cast<float>(pos), 0.0f}),
    isRed(false),
    trafficRed(red),
    trafficGreen(green)
    {
        hrClock_TP now = high_resolution_clock::now();
        prev = now;
    }

Traffic::Traffic(const float& pos, const bool& isRed, const Texture& red, const Texture& green) :
    Isometric(green, {100.0f, 100.0f}, {pos, 0.0f}),
    isRed(isRed),
    trafficRed(red),
    trafficGreen(green)
    {
        hrClock_TP now = high_resolution_clock::now();
        prev = now;
    }

Traffic::Traffic(const int& pos, const bool& isRed, const Texture& red, const Texture& green) :
    Isometric(green, {100.0f, 100.0f}, {static_cast<float>(pos), 0.0f}),
    isRed(isRed),
    trafficRed(red),
    trafficGreen(green)
    {
        hrClock_TP now = high_resolution_clock::now();
        prev = now;
    }

void Traffic::process(const uint64_t& milliTime) {
    now = high_resolution_clock::now();
    uint64_t interval = duration_cast<milliseconds>(now - prev).count();
    if (interval >= milliTime) {
        isRed = !isRed;
        prev = now;
    }
}

bool Traffic::isRedLight() const {
    return isRed;
}

void Traffic::render(Engine* engine) {
}