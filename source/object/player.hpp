#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <vector>

#include "typedef.hpp"
#include "isometric.hpp"

class Player : public Isometric {
private:
    std::string name;

    std::vector<std::pair<const std::string, const Texture&>> PLAYER_TEXTURES;

public:
    Player(const int& lane, const float& pos, const std::string& name, std::vector<const Texture*>& PT);

    void move(const Key& key);
    std::string getName();
    void render(Engine* engine);
    void playSound();
};

#endif