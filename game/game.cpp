#include "game.hpp"

Game::Game() : title("Crossy Clone") {
    // Get console handle & device context
    console = GetConsoleWindow();
    hdc = GetDC(console);
    
    // Maximize window & get window style
    ShowWindow(console, SW_MAXIMIZE);
    DWORD style = GetWindowLong(console, GWL_STYLE);

    // Disable maximize button and resizing ability
    style ^= WS_MAXIMIZEBOX;
    style ^= WS_SIZEBOX;

    // Set window style
    SetWindowLong(console, GWL_STYLE, style);

    // Set title
    SetConsoleTitle(title.c_str());

    // Remove cursor
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // Set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);

    // Disable scrolling
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
    
    // Get window size
    RECT size;
    GetWindowRect(console, &size);
    width = size.right - size.left;
    height = size.bottom - size.top;

    // Create engine
    engine = new Engine(hdc, width, height);

    // Set epoch time
    epoch = high_resolution_clock::now();
    prev = epoch;
}

void Game::run() {
    int cur = 0, numcur = 1;
    uint64_t frames = 0;
    byte count[3] = { 1, 1, 1 }, num[3] = { 1, 1, 1 };

    while (true) {
        for (int x = 0; x < width; x++)
            for (int y = 0; y < height; y++)
                engine->set(x, y, count[2] << 16 | count[1] << 8 | count[0]);

        if (count[cur] == 0 || count[cur] == 255) {
            cur += numcur;
            if (cur == 0 || cur == 2) numcur = -numcur;
        }

        if (count[cur] == 0 || count[cur] == 255) num[cur] = -num[cur];
        count[cur] += num[cur];

        engine->render();
        ++frames;

        high_resolution_clock::time_point now = high_resolution_clock::now();
        uint64_t elapsed = duration_cast<microseconds>(now - prev).count();

        if(elapsed >= 1000000) {
            prev = now;
            SetConsoleTitle((title + " - FPS: " + std::to_string(frames) + " - Resolution: " + std::to_string(width) + "x" + std::to_string(height)).c_str());
            frames = 0;
        }
    }
}

Game::~Game() {
    delete engine;
    ReleaseDC(console, hdc);
    DeleteDC(hdc);
}