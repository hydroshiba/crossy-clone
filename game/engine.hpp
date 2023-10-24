#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <windows.h>
#include "color.hpp"

class Engine {
private:
    HDC& hdc;
    BITMAPINFO mapinfo;
    HBITMAP bitmap;

    int width, height;
    byte* pixels;

public:
    Engine(HDC hdc, int w, int h);
    ~Engine();

    void set(int x, int y, Color color);
    void set(int x, int y, byte r, byte g, byte b);

    void render();
};

#endif