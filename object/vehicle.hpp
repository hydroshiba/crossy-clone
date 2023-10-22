#ifndef VEHICLE_HPP_
#define VEHICLE_HPP_
#include <iostream>
using namespace std;
class Vehicle {
    int pos;
    string sprite;
    string sound;
public:
    void move(const bool&);
    void render();
    void playSound();
};

#endif