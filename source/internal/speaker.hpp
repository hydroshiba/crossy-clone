#ifndef SPEAKER_HPP_
#define SPEAKER_HPP_

#include "typedef.hpp"
#include "sound.hpp"

class Speaker {
private:
    WAVEFORMATEX wfx;
    HWAVEOUT sfxDevice;
    HWAVEOUT musicDevice;

    bool sfxPause = false;
    bool musicPause = false;

    word sfxVolume, musicVolume;
    static void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

public:
    Speaker();
    ~Speaker();

    void play(Sound& sound);
    void pause(Sound& sound);
    void stop();
    void stopSFX();
    void stopMusic();

    void setSFXVolume(word volume);
    void setMusicVolume(word volume);

    friend class Setting;
};

#endif