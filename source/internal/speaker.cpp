#include "speaker.hpp"

void CALLBACK Speaker::waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
    if (uMsg == WOM_DONE) {
        Sound* sound = reinterpret_cast<Sound*>(dwInstance);
        waveOutWrite(hwo, &sound->header, sizeof(WAVEHDR));
    }
}

Speaker::Speaker() : sfxVolume(static_cast<word>(Volume::medium)), musicVolume(static_cast<word>(Volume::medium)) {
	wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = 2;
    wfx.nSamplesPerSec = 48000;
    wfx.wBitsPerSample = 32;
    wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

	waveOutOpen(&sfxDevice, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	waveOutOpen(&musicDevice, WAVE_MAPPER, &wfx, (DWORD_PTR)waveOutProc, 0, CALLBACK_FUNCTION);

	waveOutSetVolume(sfxDevice, sfxVolume);
	waveOutSetVolume(musicDevice, musicVolume);
}

Speaker::~Speaker() {
	waveOutClose(sfxDevice);
	waveOutClose(musicDevice);
}

void Speaker::play(Sound& sound) {
	HWAVEOUT& device = (sound.background ? musicDevice : sfxDevice);
	waveOutRestart(device);

	if(device == musicDevice && musicPause) {
		musicPause = false;
		waveOutRestart(device);
	}
	
	if(device == sfxDevice && sfxPause) {
		sfxPause = false;
		waveOutRestart(device);
	}

	waveOutPrepareHeader(device, &sound.header, sizeof(WAVEHDR));
	waveOutWrite(device, &sound.header, sizeof(WAVEHDR));
}

void Speaker::pause(Sound& sound) {
	HWAVEOUT& device = (sound.background ? musicDevice : sfxDevice);

	if(device == musicDevice) musicPause = true;
	else sfxPause = true;

	waveOutPause(device);
}

void Speaker::stop() {
	waveOutReset(sfxDevice);
	waveOutReset(musicDevice);
}

void Speaker::setSFXVolume(word volume) {
	sfxVolume = volume;
	waveOutSetVolume(sfxDevice, sfxVolume);
}

void Speaker::setMusicVolume(word volume) {
	musicVolume = volume;
	waveOutSetVolume(musicDevice, musicVolume);
}