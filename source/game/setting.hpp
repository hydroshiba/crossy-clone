#ifndef SETTING_HPP_
#define SETTING_HPP_

#include <iostream>
#include <fstream>
#include <windows.h>
#include <utility>

enum Volume {
    min = 0,
    low = 250,
    medium = 500,
    high = 750,
    max = 1000
};

enum Sprite {
    duck, chicken, cat
};

class Setting {
private:
    int score[3];
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