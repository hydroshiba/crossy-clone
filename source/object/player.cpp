#include "player.hpp"

Player::Player(TextureHolder* holder, Vec2 size, Vec2 pos, Setting* setting) :
    holder(holder),
    setting(setting),
    direction(0),
    Isometric(holder->get("CHICKEN_UP"), size, pos) {
        texture = holder->get(spriteID());
    }

void Player::move(Key key) {
    if(key == Key::UP) {
        direction = 0;
        ++Isometric::y;
    } else if(key == Key::DOWN) {
        direction = 1;
        --Isometric::y;
    }
    else if(key == Key::LEFT) {
        direction = 2;
        --Isometric::x;
    } else if(key == Key::RIGHT) {
        direction = 3;
        ++Isometric::x;
    }

    texture = holder->get(spriteID());
}

std::string Player::spriteID() {
    std::string str;
    
    if(setting->spriteID() == Sprite::chicken) str = "CHICKEN";
    else if(setting->spriteID() == Sprite::cat) str = "CAT";
    else str = "DUCK";

    if(direction == 0) str += "_UP";
    else if(direction == 1) str += "_DOWN";
    else if(direction == 2) str += "_LEFT";
    else if(direction == 3) str += "_RIGHT";

    return str;
}

void Player::render(Engine* engine, int offset) {
    int tmp = Isometric::y;
    Isometric::y = offset - 11;
    // project();
    Isometric::render(engine);
    Isometric::y = tmp;
}

// std::string Player::setName(std::string name) {
//     this->name = name;
//     return name;
// }

// std::string Player::getName() const {
//     return name;
// }