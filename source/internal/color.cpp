#include "color.hpp"

Color::Color() : val(0xFF000000) {}
Color::Color(word value) : val(value) {}
Color::Color(byte r, byte g, byte b) : val(0xFF000000 | word(r << 16) | word(g << 8) | b) {}
Color::Color(byte a, byte r, byte g, byte b) : val(word(a << 24) | word(r << 16) | word(g << 8) | b) {}

word const& Color::value() const {
    return val;
}

byte Color::R() const {
    return (val >> 16) & 0xFF;
}

byte Color::G() const {
    return (val >> 8) & 0xFF;
}

byte Color::B() const {
    return val & 0xFF;
}

byte Color::A() const {
    return (val >> 24) & 0xFF;
}

Color Color::operator+=(const Color& other) {
    val = (val & 0xFEFEFEFE) >> 1;
    val += (other.value() & 0xFEFEFEFE) >> 1;
    val += (val & other.value() & 0x01010101);
    return *this;
}

Color Color::operator+(const Color& other) const {
    word res = (val & 0xFEFEFEFE) >> 1;
    res += (other.value() & 0xFEFEFEFE) >> 1;
    res += (val & other.value() & 0x01010101);
    return res;
}