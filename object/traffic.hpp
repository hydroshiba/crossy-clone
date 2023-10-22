#ifndef TRAFFIC_HPP_
#define TRAFFIC_HPP_
#include <iostream>
using namespace std;
class Traffic {
    bool isRed; //true = red, false = green
    int clock;
    string sprite;
public:
    void render();
    void process();
};

#endif