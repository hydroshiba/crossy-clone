#include "game.hpp"
#include <iostream>

Game::Game() {
    console = GetConsoleWindow();
    hdc = GetDC(console);

    SetConsoleTitle("Crossy Clone");
    ShowWindow(console, SW_MAXIMIZE);

    DWORD style = GetWindowLong(console, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(console, GWL_STYLE, style);

    RECT size;
    GetWindowRect(console, &size);
    width = size.right - size.left;
    height = size.bottom - size.top;

    engine = new Engine(hdc, width, height);
}

void Game::run() {
    int cur = 0, numcur = 1;
	byte count[3] = { 1, 1, 1 }, num[3] = { 1, 1, 1 };

    while (true) {
        for (int x = 0; x < width; x++)
            for (int y = 0; y < height; y++)
                engine->set(x, y, count[0], count[1], count[2]);

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