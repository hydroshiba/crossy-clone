#include "sound.hpp"

Sound::Sound(std::string path, bool background) : background(background) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    buffer.resize(size);
    if(!file.read(buffer.data(), size)) {
        std::cout << "Error reading file!" << std::endl;
    }

    header.lpData = buffer.data();
    header.dwBufferLength = buffer.size();
    header.dwFlags = (background ? WHDR_BEGINLOOP | WHDR_ENDLOOP : 0);
    header.dwLoops = (background ? -1 : 0);
}