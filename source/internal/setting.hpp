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
    byte name[3][8]; // Saving 3 names as a byte array to keep endianess consistent
    Volume music, sfx;
    Sprite sprite;
    std::vector<std::vector<byte>> gamestate;

    bool load();
    void save();

public:
    Setting(Speaker* speaker);
    ~Setting();

    word highscore(byte rank) const;
    Volume volMusic() const;
    Volume volSFX() const;
    Sprite spriteID() const;
    std::string spriteObject() const;
    std::vector<std::vector<byte>> getGamestate() const;

    int setScore(word score);
    void setNames(byte name[8], int rank);
    void setGamestate(std::vector<std::vector<byte>> state);

    void incMusic(Speaker* speaker);
    void decMusic(Speaker* speaker);

    void incSFX(Speaker* speaker);
    void decSFX(Speaker* speaker);

    void incSprite();
    void decSprite();
};

#endif