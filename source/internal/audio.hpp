#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <windows.h>
#include <unordered_set>
#include <mmsystem.h>

#include "typedef.hpp"
#include "setting.hpp"
#include "sound.hpp"

class AudioDevice {
private:
    std::unordered_set<Sound> sounds;
    Setting* setting;

    void load(Sound sound);
    void unload(Sound sound);

public:
    AudioDevice(Setting* setting);

    void play(Sound sound);
    void pause(Sound sound);
    void loop(Sound sound);

    void incSFX();
    void decSFX();

    void incMusic();
    void decMusic();

    ~AudioDevice();
};

#endif