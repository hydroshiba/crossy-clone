#include "player.hpp"

Player::Player(const int& lane, const float& pos, const std::string& name, const Texture& up, const Texture& down, const Texture& left, const Texture& right, const std::string& sound) :
    Isometric(up, {100.0f, 100.0f}, {pos, 0.0f}),
    lane(lane),
    pos(pos),
    name(name),
    sound(sound),
    playerSpriteUp(up),
    playerSpriteDown(down),
    playerSpriteLeft(left),
    playerSpriteRight(right)
    {
    }

void Player::move(const Key& key) {
    switch (key) {
        case Key::UP:
            lane += 1;
            break;
        case Key::DOWN:
            lane -= 1;
            break;
        case Key::LEFT:
            pos -= 1;
            break;
        case Key::RIGHT:
            pos += 1;
            break;
        default:
            break;
    }
}

int Player::getLane() {
    return lane;
}

float Player::getPos() {
    return pos;
}

std::string Player::getName() {
    return name;
}

void Player::render() {
}

void Player::playSound() {
}