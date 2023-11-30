#include "engine.hpp"

Engine::Engine(HDC& hdc, int w, int h) : width(w), height(h), hdc(hdc) {
    ZeroMemory(&mapinfo, sizeof(BITMAPINFO));

    mapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    mapinfo.bmiHeader.biWidth = width;
    mapinfo.bmiHeader.biHeight = -height;
    mapinfo.bmiHeader.biPlanes = 1;
    mapinfo.bmiHeader.biBitCount = 32;

    bitmap = CreateDIBSection(hdc, &mapinfo, DIB_RGB_COLORS, (void**)&pixels, nullptr, 0);
}

void Engine::set(int x, int y, word value) {
    word* pixel = (word*)(pixels + ((x + y * width) << 2));
    *pixel = value;
}

void Engine::set(int x, int y, const Color& color) {
    set(x, y, color.val);
}

void Engine::set(int x, int y, byte r, byte g, byte b) {
    set(x, y, (word(r) << 16) | (word(g) << 8) | b);
}

void Engine::fill(word value) {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width * 4; x += 4) {
            word* pixel = (word*)(pixels + x + y * width * 4);
            *pixel = value;
        }
    }
}

void Engine::fill(const Color& color) {
    fill(color.val);
}

void Engine::fill(byte r, byte g, byte b) {
    fill((word(r) << 16) | (word(g) << 8) | b);
}

void Engine::textureFill(int x, int y, Texture const * const texture) {
    for(int j = 0; j < texture->height; j++) {
        for(int i = 0; i < texture->width; i++) {
            Color* pixel = (Color*)(pixels + ((x + i) + (y + j) * width) * 4);
            *pixel += texture->data[(i % texture->width) + (j % texture->height) * texture->width];
        }
    }
}

void Engine::textureFill(int x, int y, const Texture& texture) {
    textureFill(x, y, &texture);
}

int Engine::getWidth() const {
    return width;
}

int Engine::getHeight() const {
    return height;
}

void Engine::render() {
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBit = (HBITMAP)SelectObject(memDC, bitmap);
    BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, oldBit);
    DeleteDC(memDC);
}

Engine::~Engine() {
    DeleteObject(bitmap);
}