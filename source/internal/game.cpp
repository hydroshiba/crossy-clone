#include "game.hpp"

Game::Game() : title("Crossy Clone"), framerate(60), sound("asset/sound/background.wav", true) {
    // Initialize new window
    initialize();
    hdc = GetDC(window);

    // Devices initialization
    setting = new Setting();
    speaker = new Speaker(setting);
    engine = new Engine(hdc, width, height);
    keyboard = new Keyboard();
    registry = new SceneRegistry(width, height, engine, speaker, setting, keyboard);

    // Set scene
    current = registry->scene(SceneID::MENU);

    // Set epoch time
    epoch = high_resolution_clock::now();
    prev = epoch;
}

void Game::initialize() {
    // Register window class
    WNDCLASS winclass = {};
    winclass.hInstance = GetModuleHandle(NULL);
    winclass.lpszClassName = title.c_str();
    winclass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ICO));

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
        NULL);

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

    width = size.right - size.left;
    height = size.bottom - size.top;

    // Set title
    SetWindowText(window, title.c_str());
}

void Game::process() {
    // Show debug info
    SetWindowText(window, (title + debugInfo()).c_str());

    current = current->process();
    keyboard->refresh();
}

std::string Game::debugInfo() {
    std::string text;

    text += " - FPS: " + std::to_string(framerate);
    text += " - Resolution: " + std::to_string(width) + " x " + std::to_string(height);
    text += " - Scale: " + std::to_string(scale) + "%";

    return text;
}

void Game::render() {
    current->render();
    engine->render();
}

void Game::playsound() {
}

void Game::run() {
    std::cout << static_cast<word>(setting->volMusic()) << std::endl;
    std::cout << static_cast<word>(setting->volSFX()) << std::endl;
    speaker->play(sound);

    while(current != nullptr) {
        MSG msg = {};

        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if(msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        high_resolution_clock::time_point now = high_resolution_clock::now();
        uint64_t elapsed = duration_cast<nanoseconds>(now - prev).count();

        if(elapsed >= duration_cast<nanoseconds>(seconds(1)).count() / framerate) {
            render();
            process();
            prev = now;
        }
    }
}

Game::~Game() {
    delete registry;
    delete keyboard;
    delete speaker;
    delete engine;
    delete setting;

    ReleaseDC(window, hdc);
    DeleteDC(hdc);
}