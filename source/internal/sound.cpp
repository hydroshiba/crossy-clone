#include "sound.hpp"

Sound::Sound(std::string path) {
    alias = path.substr(path.find_last_of("/"), path.find_last_of(".") - path.find_last_of("/"));
    sfx = (path.find("sfx") != std::string::npos);
}

bool Sound::operator==(const Sound& sound) const {
    return alias == sound.alias;
}