#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <mmsystem.h>
#include <windows.h>

#include <unordered_set>

#include "setting.hpp"
#include "sound.hpp"
#include "typedef.hpp"

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