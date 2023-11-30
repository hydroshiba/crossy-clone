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
    void process(const uint64_t& time, hrClock& prev, bool& isGameover, const int& playerPos = -10);
    bool checkCollision(const float& pos);

    ~Lane();
};

#endif