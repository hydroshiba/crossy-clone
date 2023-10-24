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

void Engine::set(int x, int y, Color color) {
    set(x, y, color.R, color.G, color.B);
}

void Engine::set(int x, int y, byte r, byte g, byte b) {
    byte* pixel = pixels + (x + y * width) * 4;

    pixel[0] = b;
    pixel[1] = g;
    pixel[2] = r;
    pixel[3] = 0;
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