#ifndef TRAFFIC_HPP_
#define TRAFFIC_HPP_

#include <iostream>
#include "typedef.hpp"
#include "texture.hpp"
using hrClock = high_resolution_clock::time_point;

class Traffic {
private:
    int lane;
    bool isRed;  // true = red, false = green
    int clock;
    std::string sprite;

public:
    Traffic(const int& lane, const bool& isRed, const int& clock, const std::string& sprite);

    void render();
    void process(const uint64_t& time, hrClock& prev, hrClock& now);
    bool isRedLight();

    ~Traffic();
};

#endif