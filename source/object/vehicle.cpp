#include "vehicle.hpp"

Vehicle::Vehicle(const int& lane, const float& pos, const std::string& sprite, const std::string& sound) : lane(lane), pos(pos), sprite(sprite), sound(sound) {
}

void Vehicle::move(const int& speed) {
    pos += speed;
}

bool Vehicle::isCollision(const float& pos) {
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

Vehicle::~Vehicle() {
}