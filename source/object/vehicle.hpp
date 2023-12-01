#ifndef VEHICLE_HPP_
#define VEHICLE_HPP_

#include <iostream>

class Vehicle {
    int lane;
    float pos;
    std::string sprite;
    std::string sound;

public:
    Vehicle(const int& lane, const float& pos, const std::string& sprite, const std::string& sound);

    bool move(const float& speed, const float& playerPos);
    bool isCollision(const float& pos);
    bool isOut(const float& pos);
    void render();
    void playSound();
};

#endif