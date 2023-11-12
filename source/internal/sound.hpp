#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <windows.h>
#include <mmsystem.h>
#include <string>

#include "typedef.hpp"

class Sound {
private:
    std::string alias;

public:
    Sound(std::string path);
    ~Sound();

    void play();
    void stop();
};

#endif