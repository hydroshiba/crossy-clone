#ifndef VEHICLE_HPP_
#define VEHICLE_HPP_

#include <iostream>
#include "isometric.hpp"

class Vehicle : public Isometric {

public:
    Vehicle(Texture const * const texture, const Vec2& size, const Vec2& pos, const Vec2& off);

    void move(float speed);
    bool collide(float pos);
    void render(Engine* engine);
};

#endif