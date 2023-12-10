#ifndef VEHICLE_HPP_
#define VEHICLE_HPP_

#include <iostream>
#include <isometric.hpp>

class Vehicle : public Isometric {

public:
    Vehicle(const Texture& texture, const Vec2& size, const Vec2& pos, const Vec2& offset3D);

    void move(const float& speed);
    bool collide(const float& pos);
    void render(Engine* engine);
};

#endif