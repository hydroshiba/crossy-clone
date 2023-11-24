#include "vehicle.hpp"

void Vehicle::move(const bool& direction) {
    if(direction) {
        std::cout << "Move left";
    } else
        std::cout << "Move right";
}

void Vehicle::render() {
    std::cout << sprite;
}

void Vehicle::playSound() {
    std::cout << "Play sound...";
}