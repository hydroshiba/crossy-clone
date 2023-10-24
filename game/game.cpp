#include "game.hpp"
#include <iostream>

Game::Game() {
    // Get console handle & device context
    console = GetConsoleWindow();
    hdc = GetDC(console);

    // Set title
    SetConsoleTitle("Crossy Clone");
    
    // Maximize window & disable resizing
    ShowWindow(console, SW_MAXIMIZE);
    DWORD style = GetWindowLong(console, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(console, GWL_STYLE, style);

    // Get window size
    RECT size;
    GetWindowRect(console, &size);
    width = size.right - size.left;
    height = size.bottom - size.top;

    // Remove cursor
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // Set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);

    // Disable scrolling
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);

    // Create engine
    engine = new Engine(hdc, width, height);
}

void Game::run() {
    int cur = 0, numcur = 1;
	byte count[3] = { 1, 1, 1 }, num[3] = { 1, 1, 1 };

    while (true) {
        for (int x = 0; x < width; x++)
            for (int y = 0; y < height; y++)
                engine->set(x, y, count[2], count[1], count[0]);

        if (count[cur] == 0 || count[cur] == 255) {
			cur += numcur;
			if (cur == 0 || cur == 2) numcur = -numcur;
		}

		if (count[cur] == 0 || count[cur] == 255) num[cur] = -num[cur];
		count[cur] += num[cur];

        engine->render();
    }
}

Game::~Game() {
    delete engine;
    ReleaseDC(console, hdc);
    DeleteDC(hdc);
}