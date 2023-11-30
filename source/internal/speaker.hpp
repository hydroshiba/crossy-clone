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

public:
	Speaker(Setting* setting);
	~Speaker();

	void play(Sound& sound);
	void pause(Sound& sound);

	void setSFXVolume(word volume);
	void setMusicVolume(word volume);
};

#endif