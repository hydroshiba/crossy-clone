#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <windows.h>
#include <mmsystem.h>
#include <string>

#include "typedef.hpp"

class Sound {
private:
    bool sfx;
    std::string path, alias;

public:
    Sound(std::string path);
    bool operator==(const Sound& sound) const;

    friend class AudioDevice;
    friend struct std::hash<Sound>;
};

namespace std {
    template <>
    struct hash<Sound> {
        size_t operator()(const Sound& sound) const {
            return hash<string>()(sound.alias);
        }
    };
}

#endif