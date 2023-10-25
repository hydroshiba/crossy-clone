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
    byte* pixel = pixels + (x + y * width) * 4;
    memset(pixel++, value & 0xFF, 1);
    memset(pixel++, (value >> 8) & 0xFF, 1);
    memset(pixel, (value >> 16) & 0xFF, 1);
}

void Engine::set(int x, int y, const Color& color) {
    set(x, y, color.val);
}

void Engine::set(int x, int y, byte r, byte g, byte b) {
    set(x, y, (word(r) << 16) | (word(g) << 8) | b);
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