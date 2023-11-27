#ifndef TYPEDEF_HPP_
#define TYPEDEF_HPP_

#include <chrono>
#include <string>

using byte = unsigned char;
using little = unsigned short;
using word = unsigned int;

using widestring = std::wstring;
using namespace std::chrono;

enum class Volume {
    min = 0,
    low = 250,
    medium = 500,
    high = 750,
    max = 1000
};

enum class Sprite {
    duck,
    chicken,
    cat
};

enum class Key {
    DEFAULT = 0x00,
    
    BACK = 0x08,
    ENTER = 0x0D,
    ESC = 0x1B,
    SPACE = 0x20,
    LEFT = 0x25, UP, RIGHT, DOWN,
    
    ZERO = 0x30, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
    A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};

Volume& operator++(Volume& volume);
Volume& operator--(Volume& volume);

Sprite& operator++(Sprite& sprite);
Sprite& operator--(Sprite& sprite);

#endif