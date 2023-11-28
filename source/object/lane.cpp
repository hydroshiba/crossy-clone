#include "lane.hpp"

Lane::Lane(const int& pos, const int& speed, const std::string& sprite) : pos(pos), speed(speed), sprite(sprite), traffic(pos, false, 0, sprite) {
}

void Lane::render() {
    std::cout << sprite << std::endl;
}

void Lane::process(const int& time, const bool& isRunning, bool& isGameover, const int& playerLane, const float& playerPos) {
    // Thread for traffic light
    std::thread threadTraffic(&Traffic::process, &traffic, time * 7 - time / 2);

    // Thread for moving vehicles
    std::mutex vehiclesMutex;
    std::thread threadMoveVehicles([&isRunning, &vehiclesMutex, &isGameover, &playerLane, &playerPos, this]() {
        while (isRunning) {
            vehiclesMutex.lock();
            for (auto& vehicle : vehicles) {
                vehicle.move(speed);
                if (playerLane == pos && vehicle.isCollision(playerPos)) {
                    isGameover = true;
                }
            }
            if (vehicles[0].isOut(15.5)) {
                vehicles.erase(vehicles.begin());
            }
            vehiclesMutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // adjust this delay as needed
        }
    });

    // Thread for generating vehicles
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        if (traffic.isRedLight()) {
            continue;
        }
        else {
            // Generate vehicle at position -5 (outside the screen) to prevent collision
            Vehicle vehicle(pos, -5, "", "");
            vehiclesMutex.lock();
            vehicles.push_back(vehicle);
            vehiclesMutex.unlock();
        }
    }

    threadTraffic.join();
    threadMoveVehicles.join();
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

Lane::~Lane() {
}