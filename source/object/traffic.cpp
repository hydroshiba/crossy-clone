#include "traffic.hpp"

Traffic::Traffic(TextureHolder* holder, const Vec2& size, const Vec2& pos, const Vec2& off, bool isRed, int clock) : holder(holder),
                                                                                                                     Isometric(holder->get("TRAFFIC_GREEN"), size, pos, off),
                                                                                                                     isRed(isRed),
                                                                                                                     interval(240),
                                                                                                                     clock(clock) {}

void Traffic::process() {
    if(clock >= interval) {
        isRed = !isRed;
        clock = 0;

        if(isRed)
            texture = holder->get("TRAFFIC_RED");
        else
            texture = holder->get("TRAFFIC_GREEN");

        return;
    }

    ++clock;
}

bool Traffic::isRedLight() const {
    return isRed;
}

int Traffic::getClock() const {
    return clock;
}

void Traffic::render(Engine* engine, int offsetY, int offsetX) {
    if(Isometric::y == 1.0f)
        Isometric::y += offsetY - 1;
    else
        Isometric::y += offsetY;
    if(Isometric::x == 1.0f)
        Isometric::x += offsetX;
    else
        Isometric::x -= offsetX - 1;
    project();
    Isometric::render(engine);
    if(Isometric::y == offsetY)
        Isometric::y -= offsetY - 1;
    else
        Isometric::y -= offsetY;
    if(Isometric::x == 1.0f + offsetX)
        Isometric::x -= offsetX;
    else
        Isometric::x += offsetX - 1;
}