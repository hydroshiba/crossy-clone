#include "setting.hpp"

void Setting::save() {
    std::ofstream file("data/setting.dat", std::ios::binary);

    // Magic number padding (3 bytes)
    int magic = 0xDECADE;
    file.write(reinterpret_cast<char*>(&magic), 3);

    // Music + SFX + Sprite (1 byte)
    char packed = (static_cast<int>(music) / static_cast<int>(Volume::low)) << 5;
    packed |= (static_cast<int>(sfx) / static_cast<int>(Volume::low)) << 2;
    packed |= static_cast<int>(sprite);
    file.write(&packed, sizeof(packed));

    // Highscores (12 bytes)
    file.write(reinterpret_cast<char*>(score), sizeof(score));
    file.close();

    // Total: 16 bytes
}

bool Setting::load() {
    std::ifstream file("data/setting.dat", std::ios::binary);
    if(!file.good()) return false;

    // 0000 0000  0000 0000  0000 0000
    // ---- ----  ---- ----  ---- ----
    // D    E     C    A     D    E

    int magic = 0;
    file.read(reinterpret_cast<char*>(&magic), 3);
    if(magic != 0xDECADE) return false;

    // 000 000 00
    // --- --- --
    // MUS SFX SP

    char package = file.get();
    music = static_cast<Volume>((package >> 5) * static_cast<int>(Volume::low));
    sfx = static_cast<Volume>(((package >> 2) & 0x7) * static_cast<int>(Volume::low));
    sprite = static_cast<Sprite>(package & 0x3);

    file.read(reinterpret_cast<char*>(score), sizeof(score));
    file.close();
    return true;
}

Setting::Setting() {
    if(!load()) {
        music = Volume::medium;
        sfx = Volume::medium;
        sprite = Sprite::duck;
        *score = 0;
        save();
    }
}

Setting::~Setting() {
    save();
}

word Setting::highscore(byte rank) {
    return *(reinterpret_cast<word*>(score + rank));
}

Volume Setting::volMusic() {
    return music;
}

Volume Setting::volSFX() {
    return sfx;
}

Sprite Setting::spriteID() {
    return sprite;
}

void Setting::setScore(word score) {
    word* ptr = reinterpret_cast<word*>(this->score);

    for(int i = 0; i < 3; ++i) {
        if(score > *(ptr - i)) std::swap(*(ptr - i), score);
        ++ptr;
    }
}

void Setting::setSprite(Sprite sprite) {
    this->sprite = sprite;
}

void Setting::incMusic() { ++music; }
void Setting::decMusic() { --music; }

void Setting::incSFX() { ++sfx; }
void Setting::decSFX() { --sfx; }