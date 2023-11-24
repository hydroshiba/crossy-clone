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

Volume& operator++(Volume& volume);
Volume& operator--(Volume& volume);

Sprite& operator++(Sprite& sprite);
Sprite& operator--(Sprite& sprite);

#endif