#include "player.hpp"
using namespace std;

void Player::move() {
    cout << "Player moved" << endl;
}

int Player::getPos() {
    return x;
}

void Player::render() {
    cout << sprite << endl;
}

void Player::playSound() {
    cout << sound << endl;
}