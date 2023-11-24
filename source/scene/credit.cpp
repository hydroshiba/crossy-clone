#include "credit.hpp"

Credit::Credit(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting): Scene(engine, audio, registry, setting) {

}

Credit::~Credit() {

}

Scene* Credit::process() {
    
    return sceneRegistry->scene(SceneID::MENU);
}

void Credit::render() {
    
}

void Credit::playsound() {
    // this->audio->playSound(this->buttonSound);
}