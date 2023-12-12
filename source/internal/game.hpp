#ifndef GAME_HPP_
#define GAME_HPP_

#include <windows.h>
#include <chrono>
#include <string>
#include <filesystem>
#include <thread>

#include "typedef.hpp"
#include "engine.hpp"
#include "speaker.hpp"
#include "keyboard.hpp"
#include "resource.hpp"
#include "setting.hpp"
#include "scene_registry.hpp"
#include "texture_holder.hpp"

class Game {
private:
    HWND window;
    HDC hdc;

    int width, height, scale, framerate;

    std::string title;
    high_resolution_clock::time_point epoch, prev;

    Engine* engine;
    Setting* setting;
    Speaker* speaker;
    Keyboard* keyboard;
    TextureHolder* holder;
    SceneRegistry* registry;

    Scene* current;

    Sound sound;

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