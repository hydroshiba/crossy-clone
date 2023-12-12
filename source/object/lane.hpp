#ifndef LANE_HPP_
#define LANE_HPP_

#include <vector>
#include <utility>

#include "lincal.hpp"
#include "vehicle.hpp"
#include "traffic.hpp"
#include "isometric.hpp"
#include "texture_holder.hpp"

class Lane {
private:
    Vec2 gridSize;
    TextureHolder* holder;

    int length;
    float speed;
    int spawn;
    int clock;
    
    Traffic traffic;
    std::vector<Vehicle> vehicles;
    std::vector<Isometric> blocks;

public:
    Lane(TextureHolder* holder, Vec2 size, int pos, int len, float speed, const Traffic& traffic, int clock = 0, int spawn = 120);

    void render(Engine* engine);
    void process();

    void addVehicle(float pos);
    bool collide(float pos);
    bool direction();

    float getSpeed() const;
    int getSpawn() const;
    
    std::vector<char> getTrafficGamestate() const;
    std::vector<char> getVehiclesGamestate() const;

    ~Lane();
};

#endif