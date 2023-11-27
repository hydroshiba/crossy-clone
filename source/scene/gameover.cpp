#include "gameover.hpp"

Gameover::Gameover(Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(engine, audio, registry, setting, keyboard) {
}

Gameover::~Gameover() {
}

Scene* Gameover::process() {
    // if (this->engine->isKeyPressed(this->quitButton)) {
    //     this->playsound();
    //     return registry->menu;
    // }
    // else {
    //     return this;
    // }
    return nullptr;
}

void Gameover::render() {
}

void Gameover::playsound() {
    // this->audio->playSound(this->buttonSound);
}