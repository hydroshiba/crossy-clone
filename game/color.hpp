#ifndef COLOR_HPP_
#define COLOR_HPP_

using byte = unsigned char;

class Color {
public:
    byte R, G, B, A;

    Color() : R(0), G(0), B(0), A(255) {}
    Color(unsigned int hex) : R((hex >> 16) & 0xFF), G((hex >> 8) & 0xFF), B(hex & 0xFF), A((hex >> 24) &0xFF) {}
    Color(byte r, byte g, byte b, byte a = 0xFF) : R(r), G(g), B(b), A(a) {}
};

#endif