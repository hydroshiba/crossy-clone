#include "pause.hpp"

Pause::Pause(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting): Scene(engine, audio, registry, setting) {

}

Pause::~Pause() {

}

Scene* Pause::process() {
    // if (this->engine->isKeyPressed(this->continueButton)) {
    //     this->playsound();
    //     return registry->play;
    // }
    // else if (this->engine->isKeyPressed(this->quitButton)) {
    //     this->playsound();
    //     return registry->menu;
    // }
    // else {
    //     return this;
    // }
    return nullptr;
}

void Pause::render() {
    
}

void Pause::playsound() {
    // this->audio->playSound(this->buttonSound);
}