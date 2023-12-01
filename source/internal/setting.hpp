#ifndef SETTING_HPP_
#define SETTING_HPP_

#include <iostream>
#include <fstream>
#include <windows.h>
#include <utility>
#include <vector>

#include "typedef.hpp"
#include "speaker.hpp"

class Setting {
private:
    byte score[12];  // Saving 3 highscores as a byte array to keep endianess consistent
    Volume music, sfx;
    Sprite sprite;
    std::vector<std::string> gamestate;

    bool load();
    void save();

public:
    Setting(Speaker* speaker);
    ~Setting();

    word highscore(byte rank) const;
    Volume volMusic() const;
    Volume volSFX() const;
    Sprite spriteID() const;
    std::vector<std::string> getGamestate() const;

    void setScore(word score);
    void setGamestate(std::vector<std::string> state);

    void incMusic(Speaker* speaker);
    void decMusic(Speaker* speaker);

    void incSFX(Speaker* speaker);
    void decSFX(Speaker* speaker);

    void incSprite();
    void decSprite();
};

#endif