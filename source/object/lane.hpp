#ifndef LANE_HPP_
#define LANE_HPP_

#include <vector>
#include <thread>
#include <mutex>
#include "vehicle.hpp"
#include "traffic.hpp"
class Lane : public Isometric {
private:
    std::vector<Vehicle*> vehicles;
    Traffic traffic;     // traffic light
    float speed;           // speed
    const Texture& laneSprite;  // sprite
    
    const Texture AMBULANCE_FRONT, AMBULANCE_BACK;
    const Texture BLUE_CAR_FRONT, BLUE_CAR_BACK;
    const Texture ORANGE_CAR_FRONT, ORANGE_CAR_BACK;
    const Texture TRUCK_FRONT, TRUCK_BACK;
    const Texture TRAFFIC_LIGHT_RED, TRAFFIC_LIGHT_GREEN;

public:
    Lane(const float& pos, const float& speed, const Texture& sprite);
    Lane(const int& pos, const float& speed, const Texture& sprite);
    Lane(const float& pos, const float& speed, const bool& trafficState, const Texture& sprite);
    Lane(const int& pos, const float& speed, const bool& trafficState, const Texture& sprite);
    Lane(const Lane& lane);

    void render(const int& offset, const float& playerLane);
    void process(const int& time, hrClock_TP& prev, bool& isGameover, const float& playerPos = -10);
    bool checkCollision(const float& pos);
    void addVehicle(const float& pos, const std::string& sound);
    float getSpeed() const;
    bool getTrafficState() const;
    std::vector<char> getVehiclesGamestate() const;

    virtual ~Lane();
};

#endif