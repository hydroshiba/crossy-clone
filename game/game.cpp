#include "game.hpp"

Game::Game() {
    console = GetConsoleWindow();
    hdc = GetDC(console);

    SetConsoleTitle("Crossy Clone");
    ShowWindow(console, SW_MAXIMIZE);

    DWORD style = GetWindowLong(console, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(console, GWL_STYLE, style);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    engine = new Engine(hdc, width, height);
}

Game::~Game() {
    delete engine;
    ReleaseDC(console, hdc);
    DeleteDC(hdc);
}