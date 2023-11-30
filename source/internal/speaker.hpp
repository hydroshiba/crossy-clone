#ifndef SPEAKER_HPP_
#define SPEAKER_HPP_

#include "typedef.hpp"
#include "setting.hpp"
#include "sound.hpp"

class Speaker {
private:
	WAVEFORMATEX wfx;
	HWAVEOUT sfxDevice;
	HWAVEOUT musicDevice;

	word sfxVolume, musicVolume;
	static void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

public:
	Speaker(Setting* setting);
	~Speaker();

	void play(Sound& sound);
	void pause(Sound& sound);
	void stop();

	void setSFXVolume(word volume);
	void setMusicVolume(word volume);
};

#endif