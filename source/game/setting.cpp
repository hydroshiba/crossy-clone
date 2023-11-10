#include "setting.h"

WORD Setting::volumeMusic = 50;
WORD Setting::volumeEffect = 50;
bool Setting::controlMode = true;

void Setting::loadSetting(){
    std::ifstream ifs("setting.dat", std::ios::binary);
    if(!ifs.good()) return;

    char marker;
    ifs.read(&marker, sizeof(marker));
    if(marker != 's') {
        ifs.close();
        return;
    }
    ifs.read(reinterpret_cast<char*>(&controlMode), sizeof(bool));
    ifs.read(reinterpret_cast<char*>(&volumeMusic), sizeof(WORD));
    ifs.read(reinterpret_cast<char*>(&volumeEffect), sizeof(WORD));
    ifs.close();
}

void Setting::saveSetting(){
    std::ofstream ofs("setting.dat", std::ios::binary);
    if(!ofs.good()) return;
    char marker = 's';
    ofs.write(&marker, sizeof(marker));
    ofs.write(reinterpret_cast<char*>(&controlMode), sizeof(bool));
    ofs.write(reinterpret_cast<char*>(&volumeMusic), sizeof(WORD));
    ofs.write(reinterpret_cast<char*>(&volumeEffect), sizeof(WORD));
    ofs.close();
}

bool Setting::getControlMode(){
    return controlMode;
}

WORD Setting::getVolumeMusic(){
    return volumeMusic;
}

WORD Setting::getVolumeEffect(){
    return volumeEffect;
}

void Setting::setControlMode(bool mode){
    controlMode = mode;
}

void Setting::setVolumeMusic(WORD volume){
    if(volume <= 100) volumeMusic = volume;
}

void Setting::setVolumeEffect(WORD volume){
    if(volume <= 100) volumeEffect = volume;
}
