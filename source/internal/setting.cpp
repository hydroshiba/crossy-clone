#include "setting.hpp"

void Setting::save() {
    // Create data folder if not exist
    std::filesystem::create_directory("data");

    // Save setting
    std::ofstream file("data/setting.dat", std::ios::binary);

    // Magic number padding (3 bytes)
    int magic = 0xDECADE;
    file.write(reinterpret_cast<char*>(&magic), 3);

    // Music + SFX + Sprite (1 byte)
    byte packed = (static_cast<word>(music) / static_cast<word>(Volume::low)) << 5;
    packed |= (static_cast<word>(sfx) / static_cast<word>(Volume::low)) << 2;
    packed |= static_cast<word>(sprite);
    file.write(reinterpret_cast<char*>(&packed), sizeof(packed));

    // Highscores (12 + 24 bytes)
    file.write(reinterpret_cast<char*>(score), sizeof(score));
    for(int i = 0; i < 3; i++) {
        file.write(reinterpret_cast<char*>(name[i]), sizeof(name[i]));
    }
    file.close();

    // Total: 16 bytes

    // Save gamestate
    file.open("data/gamestate.dat", std::ios::binary);

    // Magic number padding (3 bytes)
    magic = 0xDEFCAD;
    file.write(reinterpret_cast<char*>(&magic), 3);

    // EOF address (4 bytes)
    int eofAddress = 35;
    for(int i = 0; i < gamestate.size(); i++) {
        eofAddress += gamestate[i].size();
    }

    // Address padding (32 bytes)
    int address = 35;
    for(int i = 0; i < 8; i++) {
        if(i < gamestate.size()) {
            file.write(reinterpret_cast<char*>(&address), sizeof(address));
            address += gamestate[i].size();
        } else {
            address = eofAddress;
            file.write(reinterpret_cast<char*>(&address), sizeof(address));
        }
    }

    // Seek to the start of the gamestate data
    file.seekp(35, std::ios::beg);

    // Gamestate (??? byte)
    for(int i = 0; i < gamestate.size(); i++) {
        byte* buffer = new byte[gamestate[i].size() + 1];
        for(int j = 0; j < gamestate[i].size(); j++) {
            buffer[j] = gamestate[i][j];
        }
        buffer[gamestate[i].size()] = '\0';
        file.write(reinterpret_cast<char*>(buffer), gamestate[i].size());
        delete[] buffer;
    }

    file.close();

    // Total: 35 + ??? bytes
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

    char get = file.get();
    byte package = static_cast<byte>(get);

    music = static_cast<Volume>((package >> 5U) * static_cast<word>(Volume::low));
    sfx = static_cast<Volume>(((package >> 2U) & 0x7U) * static_cast<word>(Volume::low));
    sprite = static_cast<Sprite>(package & 0x3);

    // Read highscores
    file.read(reinterpret_cast<char*>(score), sizeof(score));
    for(int i = 0; i < 3; i++) {
        file.read(reinterpret_cast<char*>(name[i]), sizeof(name[i]));
    }
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
    byte* buffer = nullptr;
    file.read(reinterpret_cast<char*>(&bottom), sizeof(bottom));
    std::streampos nextAddress = file.tellg();
    while(nextAddress != 35 && file.read(reinterpret_cast<char*>(&top), sizeof(top))) {
        if(top == 35) break;

        gamestate.push_back(std::vector<byte>());

        nextAddress += 4;
        file.seekg(bottom, std::ios::beg);

        buffer = new byte[top - bottom + 1];
        buffer[top - bottom] = '\0';
        file.read(reinterpret_cast<char*>(buffer), top - bottom);
        for(int i = 0; i < top - bottom; i++) {
            gamestate.back().push_back(buffer[i]);
        }

        delete[] buffer;
        file.seekg(nextAddress, std::ios::beg);
        bottom = top;
    }

    file.close();

    return true;
}

Setting::Setting(Speaker* speaker) {
    if(!load()) {
        music = Volume::medium;
        sfx = Volume::medium;
        sprite = Sprite::duck;
        *score = 0;
    }

    speaker->setMusicVolume(static_cast<word>(music));
    speaker->setSFXVolume(static_cast<word>(sfx));
}

Setting::~Setting() {
    save();
}

word Setting::highscore(word rank) const {
    if(rank > 2) return 0;
    return *(reinterpret_cast<const word*>(score) + rank);
}

byte* Setting::namePlayer(word rank) const {
    if(rank > 2) {
        return nullptr;
    }
    return const_cast<byte*>(name[rank]);
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

std::string Setting::spriteObject() const {
    switch(sprite) {
        case Sprite::duck:
            return "duck";
        case Sprite::cat:
            return "cat";
        case Sprite::chicken:
            return "chicken";
        default:
            return "duck";
    }
}

word Setting::setScore(word score) {
    word topHighscore = 3;
    word* scorePtr = reinterpret_cast<word*>(this->score);
    for(int i = 0; i < 3; i++) {
        if(score > *(scorePtr + i)) {
            topHighscore = i;
            for(int j = 2; j > i; j--) {
                *(scorePtr + j) = *(scorePtr + j - 1);
                for(int k = 0; k < 8; k++) {
                    name[j][k] = name[j - 1][k];
                }
            }
            *(scorePtr + i) = score;
            break;
        }
    }

    return topHighscore;
}

void Setting::setNames(byte name[8], int rank) {
    for(int i = 0; i < 8; ++i) {
        this->name[rank][i] = name[i];
    }
}

void Setting::incMusic(Speaker* speaker) {
    ++music;
    speaker->setMusicVolume(static_cast<word>(music));
}
void Setting::decMusic(Speaker* speaker) {
    --music;
    speaker->setMusicVolume(static_cast<word>(music));
}

void Setting::incSFX(Speaker* speaker) {
    ++sfx;
    speaker->setSFXVolume(static_cast<word>(sfx));
}

void Setting::decSFX(Speaker* speaker) {
    --sfx;
    speaker->setSFXVolume(static_cast<word>(sfx));
}

void Setting::incSprite() { ++sprite; }
void Setting::decSprite() { --sprite; }

std::vector<std::vector<byte>> Setting::getGamestate() const { return gamestate; }
void Setting::setGamestate(std::vector<std::vector<byte>> state) { gamestate = state; }