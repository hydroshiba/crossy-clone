#include "game.hpp"

Game::Game() : title("Crossy Clone"), frames(0), framesAVG(0) {
    // Get path
    path = std::filesystem::current_path();

    // Initialize new window
    initialize();
    hdc = GetDC(window);

    // Create engine
    engine = new Engine(hdc, width, height);

    // Set epoch time
    epoch = high_resolution_clock::now();
    prev = epoch;
}

void Game::initialize() {
    // Register window class
    WNDCLASS winclass = {};
    winclass.hInstance = GetModuleHandle(NULL);
    winclass.lpszClassName = title.c_str();
    winclass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(icon));

    winclass.lpfnWndProc = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT {
		if(msg == WM_CLOSE) return PostQuitMessage(0), 0;
		return DefWindowProc(hwnd, msg, wParam, lParam);
	};

    RegisterClass(&winclass);

    // Create the window
    window = CreateWindow(
        title.c_str(),
        title.c_str(),
        WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

    ShowWindow(window, SW_MAXIMIZE);

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

    // Get window size
    RECT size;
    GetWindowRect(window, &size);
    width = size.right - size.left; width *= scale; width /= 100;
    height = size.bottom - size.top; height *= scale; height /= 100;

    // Set title
    SetWindowText(window, title.c_str());
}

void Game::process() {
    // Process input
    if (GetAsyncKeyState(VK_ESCAPE)) PostQuitMessage(0);
}

std::string Game::debugInfo() {
    std::string text;

    text += " - FPS: " + std::to_string(frames);
    text += " - Average FPS: " + std::to_string(framesAVG);
    text += " - Resolution: " + std::to_string(width) + " x " + std::to_string(height);
    text += " - Scale: " + std::to_string(scale) + "%";

    return text;
}

void Game::render() {
    engine->fill(Color(count[2] << 16 | count[1] << 8 | count[0]));

    if (count[cur] == 0 || count[cur] == 255) {
        cur += numcur;
        if (cur == 0 || cur == 2) numcur = -numcur;
    }

    if (count[cur] == 0 || count[cur] == 255) num[cur] = -num[cur];
    count[cur] += num[cur];

    engine->render();
}

void Game::playsound() {
    
}

void Game::run() {
    while(true) {
        MSG msg = {};

        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        process();
        render();
        ++frames;

        high_resolution_clock::time_point now = high_resolution_clock::now();
        uint64_t elapsed = duration_cast<microseconds>(now - prev).count();
        uint64_t totalElapsed = duration_cast<microseconds>(now - epoch).count();

        if(elapsed >= 1000000) {
            int num = int(totalElapsed) / 1000000;

            frames = int(float(elapsed / 1000000.0) * frames);
            framesAVG -= framesAVG / num;
            framesAVG += float(frames) / num;

            SetWindowText(window, (title + debugInfo()).c_str());
            prev = now;
            frames = 0;
        }
    }
}

Game::~Game() {
    delete engine;
    ReleaseDC(window, hdc);
    DeleteDC(hdc);
}