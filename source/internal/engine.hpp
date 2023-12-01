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
    int framerate;
    byte* pixels;

public:
    Engine(HDC& hdc, int w, int h, int fps);
    ~Engine();

    void set(int x, int y, word value);
    void set(int x, int y, const Color& color);
    void set(int x, int y, byte r, byte g, byte b);

    void fill(word value);
    void fill(const Color& color);
    void fill(byte r, byte g, byte b);

    void textureFill(int x, int y, Texture const * const texture);
    void textureFill(int x, int y, const Texture& texture);

    int getWidth() const;
    int getHeight() const;
    int fps() const;

    void render();
};

#endif