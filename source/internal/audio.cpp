#include "audio.hpp"

AudioDevice::AudioDevice(Setting* setting) : setting(setting) {}

void AudioDevice::load(Sound sound) {
    if(sounds.find(sound) != sounds.end()) return;
    sounds.insert(sound);
    mciSendString(("open \"" + sound.alias + "\" type mpegvideo alias " + sound.alias).c_str(), NULL, 0, NULL);
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

void AudioDevice::incSFX() {
    if(setting->volSFX() == Volume::max) return;
    setting->setSFX(static_cast<Volume>(static_cast<int>(setting->volSFX()) + 1));
    
    for(auto sound : sounds) if(sound.sfx)
        mciSendString(("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(setting->volSFX()))).c_str(), NULL, 0, NULL);
}

void AudioDevice::decSFX() {
    if(setting->volSFX() == Volume::min) return;
    setting->setSFX(static_cast<Volume>(static_cast<int>(setting->volSFX()) - 1));

    for(auto sound : sounds) if(sound.sfx)
        mciSendString(("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(setting->volSFX()))).c_str(), NULL, 0, NULL);
}

void AudioDevice::incMusic() {
    if(setting->volMusic() == Volume::max) return;
    setting->setMusic(static_cast<Volume>(static_cast<int>(setting->volMusic()) + 1));

    for(auto sound : sounds) if(!sound.sfx)
        mciSendString(("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(setting->volMusic()))).c_str(), NULL, 0, NULL);
}

void AudioDevice::decMusic() {
    if(setting->volMusic() == Volume::min) return;
    setting->setMusic(static_cast<Volume>(static_cast<int>(setting->volMusic()) - 1));

    for(auto sound : sounds) if(!sound.sfx)
        mciSendString(("setaudio " + sound.alias + " volume to " + std::to_string(static_cast<int>(setting->volMusic()))).c_str(), NULL, 0, NULL);
}

AudioDevice::~AudioDevice() {
    for(auto sound : sounds) unload(sound);
}