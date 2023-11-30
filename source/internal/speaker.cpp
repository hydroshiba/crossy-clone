#include "speaker.hpp"

Speaker::Speaker(Setting* setting) : sfxVolume(static_cast<word>(setting->volSFX())), musicVolume(static_cast<word>(setting->volMusic())) {
	wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = 2;
    wfx.nSamplesPerSec = 48000;
    wfx.wBitsPerSample = 32;
    wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

	waveOutOpen(&sfxDevice, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	waveOutOpen(&musicDevice, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	waveOutSetVolume(sfxDevice, sfxVolume);
	waveOutSetVolume(musicDevice, musicVolume);
}

Speaker::~Speaker() {
	waveOutClose(sfxDevice);
	waveOutClose(musicDevice);
}

void Speaker::play(Sound& sound) {
	HWAVEOUT& device = (sound.background ? musicDevice : sfxDevice);
	waveOutPrepareHeader(device, &sound.header, sizeof(WAVEHDR));
	waveOutWrite(device, &sound.header, sizeof(WAVEHDR));
}

void Speaker::pause(Sound& sound) {
	HWAVEOUT& device = (sound.background ? musicDevice : sfxDevice);
	waveOutPause(device);
}

void Speaker::setSFXVolume(word volume) {
	sfxVolume = volume;
	waveOutSetVolume(sfxDevice, sfxVolume);
}

void Speaker::setMusicVolume(word volume) {
	musicVolume = volume;
	waveOutSetVolume(musicDevice, musicVolume);
}