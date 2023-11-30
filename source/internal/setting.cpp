#include "setting.hpp"

void Setting::save() {
    // Save setting
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

    // Save gamestate
    file.open("data/gamestate.dat", std::ios::binary);

    // Magic number padding (3 bytes)
    magic = 0xDEFCAD;
    file.write(reinterpret_cast<char*>(&magic), 3);

    // Address padding (32 bytes)
    int address = 35;
    for(int i = 0; i < 8; i++) {
        if (i < gamestate.size()) {
            file.write(reinterpret_cast<char*>(&address), sizeof(address));
            address += gamestate[i].size();
        } else {
            address = 0;
            file.write(reinterpret_cast<char*>(&address), sizeof(address));
        }
    }

    // Seek to the start of the gamestate data
    file.seekp(35, std::ios::beg);

    // Gamestate (??? byte)
    for(int i = 0; i < gamestate.size(); i++) {
        file.write(gamestate[i].c_str(), gamestate[i].size());
    }

    file.close();

    // Total: 3 + ??? bytes
}

bool Setting::load() {
    // Read setting
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

    // Read gamestate
    file.open("data/gamestate.dat", std::ios::binary);
    if(!file.good()) return false;
    gamestate.clear();

    // 0000 0000  0000 0000  0000 0000
    // ---- ----  ---- ----  ---- ----
    // D    E     F    C     A    D

    file.read(reinterpret_cast<char*>(&magic), 3);
    if(magic != 0xDEFCAD) return false;

    int bottom = 0;
    int top = 0;
    int nextAddress = 0;
    char* buffer = nullptr;
    file.read(reinterpret_cast<char*>(&bottom), sizeof(bottom));
    while (nextAddress != 35 && file.read(reinterpret_cast<char*>(&top), sizeof(top))) {
        gamestate.push_back(std::string());

        nextAddress = file.tellg();
        nextAddress += 4;
        file.seekg(bottom, std::ios::beg);

        buffer = new char[top - bottom];
        file.read(buffer, top - bottom);
        gamestate.back().assign(buffer, top - bottom);

        delete[] buffer;
        file.seekg(nextAddress, std::ios::beg);
        bottom = top;
    }

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

word Setting::highscore(byte rank) const {
    return *(reinterpret_cast<word*>(const_cast<byte*>(score) + rank));
}

Volume Setting::volMusic() const {
    return music;
}

Volume Setting::volSFX() const {
    return sfx;
}

Sprite Setting::spriteID() const {
    return sprite;
}

void Setting::setScore(word score) {
    word* ptr = reinterpret_cast<word*>(this->score);

    for(int i = 0; i < 3; ++i) {
        if(score > *(ptr - i)) std::swap(*(ptr - i), score);
        ++ptr;
    }
}

void Setting::incMusic() { ++music; }
void Setting::decMusic() { --music; }

void Setting::incSFX() { ++sfx; }
void Setting::decSFX() { --sfx; }

void Setting::incSprite() { ++sprite; }
void Setting::decSprite() { --sprite; }

std::vector<std::string> Setting::getGamestate() const { return gamestate; }
void Setting::setGamestate(std::vector<std::string> state) { gamestate = state; }