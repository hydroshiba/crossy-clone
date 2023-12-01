#include "player.hpp"

Player::Player(const int& lane, const float& pos, const std::string& name, const std::string& sprite, const std::string& sound) : lane(lane), pos(pos), name(name), sprite(sprite), sound(sound) {
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

void Player::render() {
}

void Player::playSound() {
}