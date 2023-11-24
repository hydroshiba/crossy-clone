#include "audio.hpp"

AudioDevice::AudioDevice(Setting* setting) : setting(setting) {}

void AudioDevice::load(Sound sound) {
    if(sounds.find(sound) != sounds.end()) return;
    sounds.insert(sound);
    mciSendString(("open \"" + sound.path + "\" type mpegvideo alias " + sound.alias).c_str(), NULL, 0, NULL);
}

void AudioDevice::unload(Sound sound) {
    if(sounds.find(sound) == sounds.end()) return;
    sounds.erase(sound);
    mciSendString(("close " + sound.alias).c_str(), NULL, 0, NULL);
}

void AudioDevice::play(Sound sound) {
    if(sounds.find(sound) == sounds.end()) load(sound);

    Volume volume = sound.sfx ? setting->volSFX() : setting->volMusic();
    mciSendString(("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(volume))).c_str(), NULL, 0, NULL);
    mciSendString(("play " + sound.alias + " from 0").c_str(), NULL, 0, NULL);
}

void AudioDevice::pause(Sound sound) {
    if(sounds.find(sound) == sounds.end()) load(sound);
    mciSendString(("pause " + sound.alias).c_str(), NULL, 0, NULL);
}

void AudioDevice::loop(Sound sound) {
    if(sounds.find(sound) == sounds.end()) load(sound);

    Volume volume = sound.sfx ? setting->volSFX() : setting->volMusic();
    mciSendString(("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(volume))).c_str(), NULL, 0, NULL);
    mciSendString(("play " + sound.alias + " from 0 repeat").c_str(), NULL, 0, NULL);
}

void AudioDevice::incMusic() {
    setting->incMusic();
    for(auto sound : sounds)
        if(!sound.sfx)
            mciSendString(("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(setting->volMusic()))).c_str(), NULL, 0, NULL),
                std::cout << ("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(setting->volMusic()))).c_str() << std::endl;
}

void AudioDevice::decMusic() {
    setting->decMusic();
    for(auto sound : sounds)
        if(!sound.sfx)
            mciSendString(("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(setting->volMusic()))).c_str(), NULL, 0, NULL);
}

void AudioDevice::incSFX() {
    setting->incSFX();
    for(auto sound : sounds)
        if(sound.sfx)
            mciSendString(("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(setting->volSFX()))).c_str(), NULL, 0, NULL);
}

void AudioDevice::decSFX() {
    setting->decSFX();
    for(auto sound : sounds)
        if(sound.sfx)
            mciSendString(("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(setting->volSFX()))).c_str(), NULL, 0, NULL);
}

AudioDevice::~AudioDevice() {
    for(auto sound : sounds) unload(sound);
}