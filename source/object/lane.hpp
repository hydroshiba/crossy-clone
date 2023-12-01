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
    float speed;           // speed
    // const Texture sprite;  // sprite
    std::string sprite;

public:
    Lane(const int& pos, const float& speed, const std::string& sprite);

    void render();
    void process(const uint64_t& time, hrClock& prev, bool& isGameover, const float& playerPos = -10);
    bool checkCollision(const float& pos);
    void addVehicle(const float& pos, const std::string& sprite, const std::string& sound);

    virtual ~Lane();
};

#endif