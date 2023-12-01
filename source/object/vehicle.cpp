#include "vehicle.hpp"

Vehicle::Vehicle(const int& lane, const float& pos, const std::string& sprite, const std::string& sound) : lane(lane), pos(pos), sprite(sprite), sound(sound) {
}

bool Vehicle::move(const float& speed, const float& playerPos) {
    if (playerPos <= pos + speed && playerPos >= pos && playerPos != -10) {
        pos = playerPos - 1;
        return false;
    }
    pos += speed;
    return true;
}

bool Vehicle::isCollision(const float& pos) {
    if (pos == -10) {
        return false;
    }
    return this->pos == pos;
}

bool Vehicle::isOut(const float& pos) {
    return this->pos > pos;
}

void Vehicle::render() {
    std::cout << sprite;
}

void Vehicle::playSound() {
    std::cout << "Play sound...";
}