#ifndef TRAFFIC_HPP_
#define TRAFFIC_HPP_

#include <iostream>

class Traffic {
private:
    int lane;
    bool isRed;  // true = red, false = green
    int clock;
    std::string sprite;

public:
    void render();
    void process();
};

#endif