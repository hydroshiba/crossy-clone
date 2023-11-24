#ifndef GAME_HPP_
#define GAME_HPP_

#include <windows.h>

#include <chrono>
#include <filesystem>
#include <string>
#include <thread>

#include "audio.hpp"
#include "engine.hpp"
#include "resource.hpp"
#include "scene_registry.hpp"
#include "setting.hpp"
#include "typedef.hpp"

class Game {
private:
    HWND window;
    HDC hdc;

    int width, height, scale, frames;
    float framesAVG;

    std::string title;
    high_resolution_clock::time_point epoch, prev;

    Engine* engine;
    Setting* setting;
    AudioDevice* audio;
    SceneRegistry* registry;

    int cur = 0, numcur = 1;
    byte count[3] = {1, 1, 1}, num[3] = {1, 1, 1};

    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;
    Game& operator=(const Game&) = delete;

    void initialize();
    void render();
    void process();
    void playsound();

    std::string debugInfo();

public:
    Game();
    ~Game();

    void run();
};

#endif