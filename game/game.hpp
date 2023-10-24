#ifndef GAME_HPP_
#define GAME_HPP_

#include <windows.h>
#include "engine.hpp"

class Game {
private:
    HWND console;
    HDC hdc;
    Engine* engine;
    int width, height;

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