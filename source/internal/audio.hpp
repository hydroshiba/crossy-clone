#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <windows.h>
#include <mmsystem.h>

#include "sound.hpp"

class AudioDevice {
private:

public:
    AudioDevice();
    ~AudioDevice();

    void play(Sound* sound);
    void stop(Sound* sound);
};

#endif