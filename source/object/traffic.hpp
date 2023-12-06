#ifndef TRAFFIC_HPP_
#define TRAFFIC_HPP_

#include <iostream>
#include "typedef.hpp"
#include "isometric.hpp"

class Traffic : public Isometric {
private:
    const Texture& RED;
    bool isRed;  // true = red, false = green

    int interval;
    int clock;
    

public:
    Traffic(const Texture& green, const Texture& red, const Vec2& size, const Vec2& pos, const Vec2& off = {0, 0}, bool isRed = false, int clock = 0);

    void process();
    bool isRedLight() const;
    int getClock() const;

    ~Traffic() = default;
};

#endif