#ifndef TRAFFIC_HPP_
#define TRAFFIC_HPP_

#include <iostream>
#include "typedef.hpp"
#include "isometric.hpp"
#include "texture_holder.hpp"

class Traffic : public Isometric {
private:
    TextureHolder* holder;
    bool isRed;  // true = red, false = green

    int interval;
    int clock;

public:
    Traffic(TextureHolder* holder, const Vec2& size, const Vec2& pos, const Vec2& off = {0, 0}, bool isRed = false, int clock = 0);

    void process();
    bool isRedLight() const;
    int getClock() const;
    void render(Engine* engine, int offsetY, int offsetX = 0);

    ~Traffic() = default;
};

#endif