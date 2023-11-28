#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "typedef.hpp"
#include "resource.hpp"
#include "color.hpp"

class Texture {
private:
    word width, height;
    Color* data;

public:
    Texture(int ID);
    Texture(const std::string& path);
    Texture(const Texture& other);
    Texture& operator=(const Texture& other);
    ~Texture();

    word getWidth() const;
    word getHeight() const;

    friend class Engine;
};

#endif