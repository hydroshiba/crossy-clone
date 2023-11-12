#ifndef TYPEDEF_HPP_
#define TYPEDEF_HPP_

#include <chrono>
#include <string>

using byte = unsigned char;
using word = unsigned int;

using widestring = std::wstring;
using namespace std::chrono;

enum Volume {
    min = 0,
    low = 250,
    medium = 500,
    high = 750,
    max = 1000
};

enum Sprite {
    duck, chicken, cat
};

#endif