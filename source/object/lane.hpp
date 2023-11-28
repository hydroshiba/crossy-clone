#ifndef LANE_HPP_
#define LANE_HPP_

#include <vector>
#include <thread>
#include <mutex>
#include "vehicle.hpp"
#include "traffic.hpp"

class Lane {
private:
    int pos;             // position
    std::vector<Vehicle> vehicles;
    Traffic traffic;     // traffic light
    int speed;           // speed
    std::string sprite;  // sprite

public:
    Lane(const int& pos, const int& speed, const std::string& sprite);

    void render();
    void process(const int& time, const bool& isRunning, bool& isGameover, const int& playerLane, const float& playerPos);
    bool checkCollision(const float& pos);

    ~Lane();
};

#endif