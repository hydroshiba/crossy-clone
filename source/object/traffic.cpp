#include "traffic.hpp"

Traffic::Traffic(const int& lane, const bool& isRed, const int& clock, const std::string& sprite) : lane(lane), isRed(isRed), clock(clock), sprite(sprite) {
}

void Traffic::render() {
    std::cout << sprite;
}

void Traffic::process(const int& time) {
    std::cout << "Traffic process~";
}

bool Traffic::isRedLight() {
    return isRed;
}

Traffic::~Traffic() {
}