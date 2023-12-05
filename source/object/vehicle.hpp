#ifndef VEHICLE_HPP_
#define VEHICLE_HPP_

#include <iostream>
#include <isometric.hpp>

class Vehicle : public Isometric {
    const Texture& vehicleSprite;
    std::string sound;

public:
    Vehicle(const float& lane, const float& pos, const Texture& sprite, const std::string& sound);
    Vehicle(const int& lane, const float& pos, const Texture& sprite, const std::string& sound);

    bool move(const float& speed, const float& playerPos);
    bool isCollision(const float& pos);
    bool isOut(const float& pos);
    void render();
    void playSound();

    ~Vehicle() = default;
};

#endif