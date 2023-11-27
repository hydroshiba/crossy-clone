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
    // Alpha blending
    byte alpha = other.A();
    byte invAlpha = 255 - alpha;

    byte r = (R() * invAlpha + other.R() * alpha) / 255;
    byte g = (G() * invAlpha + other.G() * alpha) / 255;
    byte b = (B() * invAlpha + other.B() * alpha) / 255;

    val = 0xFF000000 | word(r << 16) | word(g << 8) | b;

    return *this;
}

Color Color::operator+(const Color& other) const {
    // Alpha blending
    byte alpha = other.A();
    byte invAlpha = 255 - alpha;

    byte r = (R() * invAlpha + other.R() * alpha) / 255;
    byte g = (G() * invAlpha + other.G() * alpha) / 255;
    byte b = (B() * invAlpha + other.B() * alpha) / 255;

    return Color(r, g, b);
}