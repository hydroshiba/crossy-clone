#ifndef VEHICLE_HPP_
#define VEHICLE_HPP_

#include <iostream>

class Vehicle {
    int pos;
    std::string sprite;
    std::string sound;
public:
    void move(const bool&);
    void render();
    void playSound();
};

#endif