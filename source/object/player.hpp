#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>

#include "typedef.hpp"
#include "isometric.hpp"

class Player : public Isometric {
private:
    int lane;
    float pos;
    std::string name;
    std::string sound;   // sound
    std::string sprite;  // sprite

    const Texture playerSpriteUp;
    const Texture playerSpriteDown;
    const Texture playerSpriteLeft;
    const Texture playerSpriteRight;

public:
    Player(const int& lane, const float& pos, const std::string& name, const Texture& up, const Texture& down, const Texture& left, const Texture& right, const std::string& sound);

    void move(const Key& key);
    int getLane();
    float getPos();
    std::string getName();
    void render();
    void playSound();
};

#endif