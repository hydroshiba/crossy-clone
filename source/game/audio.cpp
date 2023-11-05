#include "audio.hpp"

AudioDevice::AudioDevice() {}

void AudioDevice::play(Sound* sound) {
    waveOutWrite(device, &sound->header, sizeof(WAVEHDR));
}

AudioDevice::~AudioDevice() {}