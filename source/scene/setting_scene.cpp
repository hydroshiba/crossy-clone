#include "setting_scene.hpp"

SettingScene::SettingScene(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting): Scene(engine, audio, registry, setting) {

}

SettingScene::~SettingScene() {

}

Scene* SettingScene::process() {
    
    return nullptr;
}

void SettingScene::render() {
    
}

void SettingScene::playsound() {
    // this->audio->playSound(this->buttonSound);
}