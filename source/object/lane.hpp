#ifndef LANE_HPP_
#define LANE_HPP_

#include <vector>
#include <utility>

#include "lincal.hpp"
#include "vehicle.hpp"
#include "traffic.hpp"
#include "isometric.hpp"
#include "texture_holder.hpp"
#include "player.hpp"

class Lane {
private:
    Vec2 gridSize, offset;
    TextureHolder* holder;

    int pos;
    int length;
    float speed;
    int spawn;
    int clock;
    
    Traffic traffic;
    std::vector<Vehicle> vehicles;
    std::vector<Isometric> blocks;

public:
    Lane(TextureHolder* holder, Vec2 size, int pos, int len, float speed, int spawnClock = 120, bool isRed = false, int trafficClock = 0);

    void render(Engine* engine);
    void process();
    void gameoverProcess();
    void shift(Vec2 off);

    void addVehicle(float pos);
    bool collide(Player* player);
    bool direction();

    int Y() const;
    float getSpeed() const;
    int getSpawn() const;
    
    std::vector<byte> getTrafficGamestate() const;
    std::vector<byte> getVehiclesGamestate() const;

    ~Lane();
};

#endif