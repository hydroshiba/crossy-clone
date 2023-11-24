#include "play.hpp"

Play::Play(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting): Scene(engine, audio, registry, setting) {

}

Play::~Play() {

}

Scene* Play::process() {
    return nullptr;
}

void Play::render() {
    
}

void Play::playsound() {
    // this->audio->playSound(this->buttonSound);
}