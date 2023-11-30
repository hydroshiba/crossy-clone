#include "traffic.hpp"

Traffic::Traffic(const int& lane, const bool& isRed, const int& clock, const std::string& sprite) : lane(lane), isRed(isRed), clock(clock), sprite(sprite) {
}

void Traffic::render() {
    std::cout << sprite;
}

void Traffic::process(const int& time, hrClock& prev, hrClock& now) {
    uint64_t interval = duration_cast<milliseconds>(now - prev).count();
    if (interval >= time) {
        isRed = !isRed;
        prev = now;
    }
}

bool Traffic::isRedLight() {
    return isRed;
}

Traffic::~Traffic() {
}