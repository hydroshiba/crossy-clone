#ifndef SETTING_HPP_
#define SETTING_HPP_

#include <iostream>
#include <fstream>
#include <windows.h>
#include <utility>

#include "typedef.hpp"

class Setting {
private:
    char score[12];
    Volume music, sfx;
    Sprite sprite;

    bool load();
    void save();

public:
    Setting();
    ~Setting();

    int highscore(int rank);
    Volume volMusic();
    Volume volSFX();
    Sprite spriteID();

    void setScore(int score);
    void setMusic(Volume volume);
    void setSFX(Volume volume);
    void setSprite(Sprite sprite);
};

#endif