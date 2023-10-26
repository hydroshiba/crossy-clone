#include "game.hpp"

Game::Game() : title("Crossy Clone"), frames(0) {
    // Get console handle & device context
    console = GetConsoleWindow();
    hdc = GetDC(console);
    
    // Maximize window & disable resizing
    ShowWindow(console, SW_MAXIMIZE);
    DWORD style = GetWindowLong(console, GWL_STYLE);
    style ^= WS_MAXIMIZEBOX;
    style ^= WS_SIZEBOX;
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

    // Get scale
    scale = []() -> int {
        auto activeWindow = GetActiveWindow();
        HMONITOR monitor = MonitorFromWindow(activeWindow, MONITOR_DEFAULTTONEAREST);

        // Get the logical width of the monitor
        MONITORINFOEX monitorInfoEx;
        monitorInfoEx.cbSize = sizeof(monitorInfoEx);
        GetMonitorInfo(monitor, &monitorInfoEx);
        auto logicWidth = monitorInfoEx.rcMonitor.right - monitorInfoEx.rcMonitor.left;

        // Get the physical width of the monitor
        DEVMODE devMode;
        devMode.dmSize = sizeof(devMode);
        devMode.dmDriverExtra = 0;
        EnumDisplaySettings(monitorInfoEx.szDevice, ENUM_CURRENT_SETTINGS, &devMode);
        auto physicWidth = devMode.dmPelsWidth;

        // Calculate the scaling factor
        return (physicWidth * 100) / logicWidth;
    }();

    // Correct window size
    width *= scale; width /= 100;
    height *= scale; height /= 100;

    // Create engine
    engine = new Engine(hdc, width, height);

    // Set epoch time
    epoch = high_resolution_clock::now();
    prev = epoch;
}

std::string Game::debugInfo() {
    std::string text;

    text += " - FPS: " + std::to_string(frames);
    text += " - Resolution: " + std::to_string(width) + " x " + std::to_string(height);
    text += " - Scale: " + std::to_string(scale) + "%";

    return text;
}

void Game::render() {
    int cur = 0, numcur = 1;
    byte count[3] = { 1, 1, 1 }, num[3] = { 1, 1, 1 };

    while (true) {
        engine->fill(count[2] << 16 | count[1] << 8 | count[0]);

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
            frames = int(float(elapsed / 1000000.0) * frames);
            SetConsoleTitle((title + debugInfo()).c_str());
            prev = now;
            frames = 0;
        }
    }
}

void Game::playsound() {
    
}

void Game::run() {
    render();
}

Game::~Game() {
    delete engine;
    ReleaseDC(console, hdc);
    DeleteDC(hdc);
}