#include "setting.hpp"

void Setting::save(){
    std::ofstream file("settings.dat", std::ios::binary);

    // Volumes + sprite + magic number padding (4 byte)

    // 0000 0000  0000 0000  0000 0000  000 000 00
    // ---- ----  ---- ----  ---- ----  --- --- --
    // D    E     C    A     D    E     MUS SFX SP

    int packed = (music / 250) << 5 | (sfx / 250) << 2 | sprite;
    packed |= (0xDECADE << 8); // Magic number padding
    file.write(reinterpret_cast<char*>(&packed), sizeof(packed));

    // Highscores (3 * 4 bytes)
    file.write(reinterpret_cast<char*>(score), 3 * sizeof(int));
    file.close();

    // Total: 16 bytes
}

bool Setting::load() {
    std::ifstream ifs("setting.dat", std::ios::binary);
    if(!ifs.good()) return false;

    int package = 0;
    ifs.read(reinterpret_cast<char*>(&package), sizeof(package));
    if((package >> 8) != 0xDECADE) return false;

    package &= 0xFF;
    music = static_cast<Volume>((package >> 5) & 0b11);
    sfx = static_cast<Volume>((package >> 2) & 0b11);
    sprite = static_cast<Sprite>(package & 0b11);

    ifs.read(reinterpret_cast<char*>(score), 3 * sizeof(int));
    ifs.close();
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