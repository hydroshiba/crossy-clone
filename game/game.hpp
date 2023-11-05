#ifndef GAME_HPP_
#define GAME_HPP_

#include <windows.h>
#include <chrono>
#include <string>

#include "engine.hpp"
using namespace std::chrono;

class Game {
private:
    HWND window;
    HDC hdc;
    Engine* engine;

    int width, height, scale;
    int frames;
    float framesAVG;
    std::string title;
    high_resolution_clock::time_point epoch, prev;
    
    int cur = 0, numcur = 1;
    byte count[3] = { 1, 1, 1 }, num[3] = { 1, 1, 1 };

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