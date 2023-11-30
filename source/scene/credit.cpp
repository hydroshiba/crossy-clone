#include "credit.hpp"

Credit::Credit(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, speaker, registry, setting, keyboard) {}

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