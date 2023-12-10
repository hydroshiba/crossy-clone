#include "player.hpp"

Player::Player(const int& lane, const float& pos, const std::string& name, std::vector<const Texture*>& PT) :
    Isometric(*PT[0], {100.0f, 100.0f}, {pos, 0.0f}),
    name(name),
    PLAYER_TEXTURES({{"UP", *PT[0]},
                     {"DOWN", *PT[1]},
                     {"LEFT", *PT[2]},
                     {"RIGHT", *PT[3]}
                     })
    {
    }

void Player::move(const Key& key) {
    switch (key) {
        case Key::UP:
            pos.y += 1;
            break;
        case Key::DOWN:
            pos.y -= 1;
            break;
        case Key::LEFT:
            pos.x -= 1;
            break;
        case Key::RIGHT:
            pos.x += 1;
            break;
        default:
            break;
    }
}

std::string Player::getName() {
    return name;
}

void Player::render(Engine* engine) {
    pos.y = -pos.y + 15;
    project();
    Isometric::render(engine);
    pos.y = -pos.y + 15;
}

void Player::playSound() {
}