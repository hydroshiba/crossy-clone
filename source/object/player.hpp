#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <vector>

#include "typedef.hpp"
#include "isometric.hpp"
#include "keyboard.hpp"
#include "setting.hpp"
#include "texture_holder.hpp"

class Player : public Isometric {
private:
    TextureHolder* holder;
    Setting* setting;
    int direction; // 0 = up, 1 = down, 2 = left, 3 = right
    // std::string name;

public:
    Player(TextureHolder* holder, Vec2 size, Vec2 pos, Setting* setting);

    void move(Key key);
    std::string spriteID();
    void render(Engine* engine, int offset = 0);
    // std::string setName(std::string name);
    // std::string getName() const;
};

#endif