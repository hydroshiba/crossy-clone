#include "lane.hpp"

Lane::Lane(const int& pos, const float& speed, const std::string& sprite) : pos(pos), speed(speed), sprite(sprite), traffic(pos, false, 0, sprite) {
}

void Lane::render() {
    std::cout << sprite << std::endl;
}

void Lane::process(const uint64_t& time, hrClock& prev, bool& isGameover, const float& playerPos) {
    hrClock now = high_resolution_clock::now();
    uint64_t interval = duration_cast<milliseconds>(now - prev).count();
    traffic.process(time * 7 - time * 1 / 2, prev, now);

    if (interval >= time && !traffic.isRedLight()) {
        vehicles.push_back(Vehicle(pos, -5, "", ""));
        prev = now;
    }

    for (auto& vehicle : vehicles) {
        vehicle.move(speed);
        if (vehicle.isCollision(playerPos)) {
            vehicle.playSound();
            isGameover = true;
        }
    }

    if (vehicles[0].isOut(150)) {
        vehicles.erase(vehicles.begin());
    }
}

bool Lane::checkCollision(const float& pos) {
    for (auto& vehicle : vehicles) {
        if (vehicle.isCollision(pos)) {
            vehicle.playSound();
            return true;
        }
    }
    return false;
}

void Lane::addVehicle(const float& pos, const std::string& sprite, const std::string& sound) {
    vehicles.push_back(Vehicle(this->pos, pos, sprite, sound));
}