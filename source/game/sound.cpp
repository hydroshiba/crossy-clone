#include "sound.hpp"

Sound::Sound(const widestring &path, const std::string &alias) : path(path), alias(alias) {
    load();
}

void Sound::load() {
    // Open file
    auto file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    // Get file size
    auto fileSize = GetFileSize(file, NULL);

    // Allocate memory
    buffer = new char[fileSize];

    // Read file
    ReadFile(file, buffer, fileSize, NULL, NULL);

    // Close file
    CloseHandle(file);

    // Get wave format
    memcpy(&waveFormat, buffer + 20, sizeof(WAVEFORMATEX));

    // Get data chunk
    parentChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    parentChunk.cksize = fileSize - 44;
    parentChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    parentChunk.dwDataOffset = 44;

    // Get child chunk
    childChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    childChunk.cksize = 16;
    childChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    childChunk.dwDataOffset = 20;

    // Open wave out
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, NULL, NULL, CALLBACK_NULL);

    // Prepare header
    WAVEHDR waveHeader;
    waveHeader.lpData = buffer + 44;
    waveHeader.dwBufferLength = fileSize - 44;
    waveHeader.dwBytesRecorded = 0;
    waveHeader.dwUser = 0;
    waveHeader.dwFlags = 0;
    waveHeader.dwLoops = 0;
    waveHeader.lpNext = NULL;
    waveHeader.reserved = 0;
}