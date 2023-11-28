#include "texture.hpp"

Texture::Texture(const std::string& path) {
    std::ifstream fin(path, std::ios::binary);

    if(!fin) {
        std::cout << "Failed to open file: " << path << std::endl;
        return;
    }

    fin.seekg(18); // Seek to width and height
    fin.read(reinterpret_cast<char*>(&width), sizeof(width));
    fin.read(reinterpret_cast<char*>(&height), sizeof(height));

    fin.seekg(10); // Seek to pixel data offset
    uint32_t dataOffset;
    fin.read(reinterpret_cast<char*>(&dataOffset), sizeof(dataOffset));

    fin.seekg(dataOffset); // Seek to pixel data
    data = new Color[width * height];
    fin.read(reinterpret_cast<char*>(data), width * height * sizeof(Color));

    fin.close();

    for (int i = 0; i < height / 2; ++i) {
        std::swap_ranges(data + i * width, data + (i + 1) * width, data + (height - i - 1) * width);
    }
}

Texture::Texture(int ID) {
    HBITMAP bitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(ID));
    BITMAP bmp;
    if (!bitmap) {
        std::cout << "Failed to load bitmap: " << ID << std::endl;
        exit(1);
    }

    GetObject(bitmap, sizeof(bmp), &bmp);
    width = bmp.bmWidth;
    height = bmp.bmHeight;

    data = new Color[width * height];
    GetBitmapBits(bitmap, width * height * sizeof(Color), data);
    DeleteObject(bitmap);
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

word Texture::getWidth() const {
    return width;
}

word Texture::getHeight() const {
    return height;
}

Texture::~Texture() {
    delete[] data;
}