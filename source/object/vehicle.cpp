#include "vehicle.hpp"

Vehicle::Vehicle(const float& lane, const float& pos, const Texture& sprite, const std::string& sound) :
    Isometric(sprite, {100.0f, 100.0f}, {lane, pos}),
    vehicleSprite(sprite),
    sound(sound)
    {

    }

Vehicle::Vehicle(const int& lane, const float& pos, const Texture& sprite, const std::string& sound) :
    Isometric(sprite, {100.0f, 100.0f}, {static_cast<float>(lane), pos}),
    vehicleSprite(sprite),
    sound(sound)
    {

    }

bool Vehicle::move(const float& speed, const float& playerPos) {
    if (playerPos <= this->X() + speed && playerPos >= this->X() && playerPos != -10) {
        this->pos.x = playerPos - 1;
        return false;
    }
    this->pos.x += speed;
    return true;
}

bool Vehicle::isCollision(const float& pos) {
    if (pos == -10) {
        return false;
    }
    return this->X() == pos;
}

bool Vehicle::isOut(const float& pos) {
    return this->X() > pos;
}

void Vehicle::render() {
}

void Vehicle::playSound() {
}