#include "texture.hpp"

Texture::Texture(const std::string& path) {
    std::ifstream fin(path, std::ios::binary);

    if(!fin) {
        std::cerr << "Failed to open texture file: " << path << std::endl;
        exit(1);
    }

    fin.seekg(18);  // Seek to width and height
    fin.read(reinterpret_cast<char*>(&width), sizeof(width));
    fin.read(reinterpret_cast<char*>(&height), sizeof(height));

    fin.seekg(10);  // Seek to pixel data offset
    uint32_t dataOffset;
    fin.read(reinterpret_cast<char*>(&dataOffset), sizeof(dataOffset));

    fin.seekg(dataOffset);  // Seek to pixel data
    data = new Color[width * height];
    fin.read(reinterpret_cast<char*>(data), width * height * sizeof(Color));

    fin.close();
    std::reverse(data, data + width * height);
}

Texture::Texture(const Texture& other) : width(other.width), height(other.height) {
    data = new Color[width * height];
    memcpy(data, other.data, width * height * sizeof(Color));
}

Texture& Texture::operator=(const Texture& other) {
    if(this != &other) {
        width = other.width;
        height = other.height;
        delete[] data;
        data = new Color[width * height];
        memcpy(data, other.data, width * height * sizeof(Color));
    }
    return *this;
}

Texture::~Texture() {
    delete[] data;
}