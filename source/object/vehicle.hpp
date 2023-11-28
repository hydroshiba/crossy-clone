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

    void move(const int& speed);
    bool isCollision(const float& pos);
    bool isOut(const float& pos);
    void render();
    void playSound();

    ~Vehicle();
};

#endif