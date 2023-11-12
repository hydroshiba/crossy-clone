#ifndef COLOR_HPP_
#define COLOR_HPP_

#include "typedef.hpp"

class Color {
private:
    word val;

public:
    Color();
    Color(word value);
    Color(byte r, byte g, byte b);
    Color(byte a, byte r, byte g, byte b);

    word const& value() const;
    byte R() const;
    byte G() const;
    byte B() const;
    byte A() const;

    Color operator+(const Color& other) const;
    Color operator+=(const Color& other);

    friend class Engine;
};

#endif