#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <windows.h>
#include <thread>
#include <future>

#include "typedef.hpp"
#include "color.hpp"
#include "texture.hpp"

class Engine {
private:
    HDC& hdc;
    BITMAPINFO mapinfo;
    HBITMAP bitmap;

    int width, height;
    byte* pixels;

public:
    Engine(HDC& hdc, int w, int h);
    ~Engine();

    void set(int x, int y, word value);
    void set(int x, int y, const Color& color);
    void set(int x, int y, byte r, byte g, byte b);

    void fill(word value);
    void fill(const Color& color);
    void fill(byte r, byte g, byte b);

    void textureFill(int x, int y, const Texture& texture);

    void render();
};

#endif