#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>

#include "typedef.hpp"
#include "object.hpp"

class Player {
private:
    int lane;
    float pos;
    std::string name;
    std::string sound;   // sound
    std::string sprite;  // sprite

public:
    Player(const int& lane, const float& pos, const std::string& name, const std::string& sprite, const std::string& sound);

    void move(const Key& key);
    int getLane();
    float getPos();
    void render();
    void playSound();
};

#endif