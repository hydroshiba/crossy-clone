#include "gameover.hpp"

Gameover::Gameover(Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(engine, audio, registry, setting, keyboard) {
}

Gameover::~Gameover() {
}

Scene* Gameover::process() {
    bool isExit = false;

    while (!isExit) {

        keyboard->refresh();
        Key pressedKey = keyboard->key();

        if(pressedKey == Key::ENTER) {
            isExit = true;
        }
    }

    return sceneRegistry->scene(SceneID::MENU);
}

void Gameover::render() {
}

void Gameover::playsound() {
    // this->audio->playSound(this->buttonSound);
}