#ifndef SETTING_HPP_
#define SETTING_HPP_

#include <iostream>
#include <fstream>
#include <windows.h>
#include <utility>
#include <vector>

#include "typedef.hpp"

class Setting {
private:
    byte score[12];  // Saving 3 highscores as a byte array to keep endianess consistent
    Volume music, sfx;
    Sprite sprite;
    std::vector<std::string> gamestate;

    bool load();
    void save();

public:
    Setting();
    ~Setting();

    word highscore(byte rank);
    Volume volMusic();
    Volume volSFX();
    Sprite spriteID();

    void setScore(word score);
    void setSprite(Sprite sprite);

    void incMusic();
    void decMusic();

    void incSFX();
    void decSFX();
};

#endif