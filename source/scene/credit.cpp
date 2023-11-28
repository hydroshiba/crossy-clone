#include "credit.hpp"

Credit::Credit(int width, int height, Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, audio, registry, setting, keyboard) {}

Credit::~Credit() {
}

Scene* Credit::process() {
    bool isExit = false;

    while(!isExit) {
        keyboard->refresh();
        Key pressedKey = keyboard->key();

        if(pressedKey == Key::ESC) {
            isExit = true;
        }
    }

    return sceneRegistry->scene(SceneID::MENU);
}

void Credit::render() {
}

void Credit::playsound() {
    // this->audio->playSound(this->buttonSound);
}