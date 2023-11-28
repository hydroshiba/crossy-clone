#include "player.hpp"

void Player::move(Key key) {
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

const int& Player::getLane() {
    return lane;
}

const float& Player::getPos() {
    return pos;
}

void Player::render() {
    std::cout << sprite << std::endl;
}

void Player::playSound() {
    std::cout << sound << std::endl;
}