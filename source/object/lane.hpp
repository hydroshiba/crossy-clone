#ifndef LANE_HPP_
#define LANE_HPP_

#include <vector>
#include "vehicle.hpp"
#include "traffic.hpp"

class Lane {
private:
    int y; //y position
    std::vector<Vehicle> vehicles;
    Traffic traffic; //traffic light
    bool direction; //true = left, false = right
    std::string sprite; //sprite

public:
    void render();
    void process(int time);
};

#endif