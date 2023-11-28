#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>

#include "typedef.hpp"

class Player {
private:
    int lane;
    float pos;
    std::string sound;   // sound
    std::string sprite;  // sprite

public:
    Player(int lane, float pos, std::string sprite, std::string sound);

    void move(Key key);
    const int& getLane();
    const float& getPos();
    void render();
    void playSound();

    ~Player();
};

#endif