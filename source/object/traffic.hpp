#ifndef TRAFFIC_HPP_
#define TRAFFIC_HPP_

#include <iostream>
#include "typedef.hpp"
#include "isometric.hpp"
using hrClock_TP = high_resolution_clock::time_point;

class Traffic : public Isometric {
private:
    bool isRed;  // true = red, false = green
    hrClock_TP prev, now;
    const Texture& trafficRed, trafficGreen;

public:
    Traffic(const float& pos, const Texture& red, const Texture& green);
    Traffic(const int& pos, const Texture& red, const Texture& green);
    Traffic(const float& pos, const bool& isRed, const Texture& red, const Texture& green);
    Traffic(const int& pos, const bool& isRed, const Texture& red, const Texture& green);

    void process(const uint64_t& milliTime);
    bool isRedLight() const;
    void render(Engine* engine);

    ~Traffic() = default;
};

#endif