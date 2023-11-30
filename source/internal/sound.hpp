#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "typedef.hpp"

class Sound {
private:
    WAVEHDR header;
    bool background;
    std::vector<char> buffer;    

public:
    Sound(std::string path, bool background = false);
    ~Sound() = default;

    friend class Speaker;
};

#endif