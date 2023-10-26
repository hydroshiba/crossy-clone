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

void Engine::fill(word value) {
    //auto fillQuater = [this, value](int x, int y) {
    //    for(int j = 0; j < height / 2; ++j) {
    //        byte* row = pixels + (j + y) * width * 4;
    //        for(int i = 0; i < width / 2; ++i) {
    //            byte* pixel = row + (i + x) * 4;
    //            memset(pixel++, value & 0xFF, 1);
    //            memset(pixel++, (value >> 8) & 0xFF, 1);
    //            memset(pixel, (value >> 16) & 0xFF, 1);
    //        }
    //    }
    //};

    //std::thread t1(fillQuater, 0, 0);
    //std::thread t2(fillQuater, width / 2, 0);
    //std::thread t3(fillQuater, 0, height / 2);
    //std::thread t4(fillQuater, width / 2, height / 2);

    //t1.join();
    //t2.join();
    //t3.join();
    //t4.join();

    for (int y = 0; y < height; y++) {
        byte* row = pixels + y * width * 4;
        for (int x = 0; x < width; x++) {
            byte* pixel = row + x * 4;
            memset(pixel++, value & 0xFF, 1);
            memset(pixel++, (value >> 8) & 0xFF, 1);
            memset(pixel, (value >> 16) & 0xFF, 1);
        }
    }
}

void Engine::fill(const Color& color) {
    fill(color.val);
}

void Engine::fill(byte r, byte g, byte b) {
    fill((word(r) << 16) | (word(g) << 8) | b);
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