#ifndef SETTING_HPP_
#define SETTING_HPP_

#include <iostream>
#include <fstream>
#include <windows.h>
#include <utility>

#include "typedef.hpp"

class Setting {
private:
    byte score[12]; // Saving 3 highscores as a byte array to keep endianess consistent
    Volume music, sfx;
    Sprite sprite;

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
    void setMusic(Volume volume);
    void setSFX(Volume volume);
    void setSprite(Sprite sprite);
};

#endif