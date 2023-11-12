#include "setting.hpp"

void Setting::save(){
    std::ofstream file("data/setting.dat", std::ios::binary);

    // Magic number padding (3 bytes)
    int magic = 0xDECADE;
    file.write(reinterpret_cast<char*>(&magic), 3);

    // Music + SFX + Sprite (1 byte)
    char packed = (music / 250) << 5 | (sfx / 250) << 2 | sprite;
    file.write(reinterpret_cast<char*>(&packed), sizeof(packed));

    // Highscores (3 * 4 bytes)
    file.write(reinterpret_cast<char*>(score), 3 * sizeof(int));
    file.close();

    // File format should look like this (without highscores):
    // 0000 0000  0000 0000  0000 0000  000 000 00
    // ---- ----  ---- ----  ---- ----  --- --- --
    // D    E     C    A     D    E     MUS SFX SP'

    // 0xDECADE is chosen because the value stays the same on different endianess
    // Also it spells out "Decade" which is kinda nice

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
    music = static_cast<Volume>((package >> 5) * 250);
    sfx = static_cast<Volume>(((package >> 2) & 0x7) * 250);
    sprite = static_cast<Sprite>(package & 0x3);

    // 0000 0000  0000 0000  0000 0000
    // ---- ----  ---- ----  ---- ----
    // Highscore  Highscore  Highscore

    file.read(reinterpret_cast<char*>(score), 3 * sizeof(int));
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

int Setting::highscore(int rank) {
    return score[rank];
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

void Setting::setScore(int score) {
    for(int i = 2; i >= 0; --i)
        if(score > this->score[i])
            std::swap(score, this->score[i]);
}

void Setting::setMusic(Volume volume) {
    music = volume;
}

void Setting::setSFX(Volume volume) {
    sfx = volume;
}

void Setting::setSprite(Sprite sprite) {
    this->sprite = sprite;
}