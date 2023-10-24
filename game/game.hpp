#ifndef GAME_HPP_
#define GAME_HPP_

#include <windows.h>
#include <chrono>
#include <string>

#include "engine.hpp"
using namespace std::chrono;

class Game {
private:
    HWND console;
    HDC hdc;
    Engine* engine;

    int width, height;
    std::string title;
    high_resolution_clock::time_point epoch, prev;

    Game(const Game&) = delete;
    Game(Game&&) = delete;

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

public:
    Game();
    ~Game();
    
    void run();
};

#endif