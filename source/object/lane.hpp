#ifndef LANE_HPP_
#define LANE_HPP_

#include <vector>
#include <utility>

#include "vehicle.hpp"
#include "traffic.hpp"

class Lane : public Isometric {
private:
    int length;
    float speed;

    int spawn;
    int clock;

    std::vector<std::pair<const Texture&, const Texture&>> VEHICLE_TEXTURE;
    std::pair<const Texture&, const Texture&> TRAFFIC_TEXTURE;
    
    std::vector<Vehicle> vehicles;
    Traffic traffic;

    std::vector<Isometric> blocks;

public:
    Lane(const Texture& texture, int pos, int len, float speed, const std::vector<std::pair<const Texture&, const Texture&>>& VT, const std::pair<const Texture&, const Texture&>& TT, bool trafficState = false, int clock = 0);

    void render(Engine* engine);
    void process();

    bool collide(float pos);
    float getSpeed() const;
    bool getTrafficState() const;
    std::vector<char> getVehiclesGamestate() const;
};

#endif