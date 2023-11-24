#include "option.hpp"

Option::Option(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting): Scene(engine, audio, registry, setting) {

}

Option::~Option() {

}

Scene* Option::process() {
    
    return nullptr;
}

void Option::render() {
    
}

void Option::playsound() {
    // this->audio->playSound(this->buttonSound);
}