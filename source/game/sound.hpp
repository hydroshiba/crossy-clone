#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <string>

using widestring = std::wstring;

class Sound {
private:
    widestring path;
    std::string alias;

    HWAVEOUT hWaveOut;
    WAVEFORMATEX waveFormat;
    MMCKINFO parentChunk;
    MMCKINFO childChunk;

    char* buffer;
    DWORD bufferSize;

    void load();

public:
    Sound(const widestring& path, const std::string& alias);
    ~Sound();
};

#endif