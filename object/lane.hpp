#ifndef LANE_HPP_
#define LANE_HPP_
#include <iostream>
#include <vector>
#include "vehicle.hpp"
#include "traffic.hpp"

class Lane {
    private:
        std::vector<Vehicle> vehicles;
        Traffic traffic; //traffic light
        bool direction; //true = left, false = right
        std::string sprite; //sprite
    public:
        void render();
        void process(int);
};

#endif