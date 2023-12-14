#ifndef TEXTURE_HOLDER_HPP_
#define TEXTURE_HOLDER_HPP_

#include <windows.h>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "typedef.hpp"
#include "texture.hpp"

class TextureHolder {
private:
    std::unordered_map<std::string, Texture*> map;

public:
    TextureHolder();
    ~TextureHolder();

    Texture* const get(const std::string& name) const;
};

#endif