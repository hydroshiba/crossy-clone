#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <windows.h>
#include <mmsystem.h>

class AudioDevice {
private:
    HWAVEOUT device;
    WAVEFORMATEX format;
    WAVEHDR header;

public:
    AudioDevice();
    ~AudioDevice();
};

#endif