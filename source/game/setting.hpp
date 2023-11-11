#ifndef SETTING_H_
#define SETTING_H_
#include <iostream>
#include <windows.h>
#include <fstream>

class Setting{
    static WORD volumeMusic, volumeEffect;
    static bool controlMode;
    Setting(){};
public:
    static void loadSetting();
    static void saveSetting();

    static bool getControlMode();
    static WORD getVolumeMusic();
    static WORD getVolumeEffect();

    static void setControlMode(bool mode);
    static void setVolumeMusic(WORD volume);
    static void setVolumeEffect(WORD volume);
};
#endif