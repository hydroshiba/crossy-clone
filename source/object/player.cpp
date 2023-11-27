#include "player.hpp"

void Player::move() {
    std::cout << "Player moved" << std::endl;
}

int Player::getPos() {
    return pos;
}

void Player::render() {
    std::cout << sprite << std::endl;
}

void Player::playSound() {
    std::cout << sound << std::endl;
}