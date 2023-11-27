#include "pause.hpp"

Pause::Pause(Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(engine, audio, registry, setting, keyboard) {
}

Pause::~Pause() {
}

Scene* Pause::process() {
    int button = 1;
    bool isExit = false;

    Scene* nextScene = nullptr;

    while(!isExit) {

        keyboard->refresh();
        Key pressedKey = keyboard->key();

        switch(pressedKey) {
        case Key::UP:
            if(button > 1) {
                button--;
            }
            break;
        case Key::DOWN:
            if(button < 3) {
                button++;
            }
            break;
        case Key::ENTER:
            switch(button) {
            case 1:
                // Continue Play
                nextScene = sceneRegistry->scene(SceneID::PLAY);
                break;
            case 2:
                // Exit to Menu                
                nextScene = sceneRegistry->scene(SceneID::MENU);
                break;
            }
            isExit = true;
            break;
        }
    }
    return nextScene;
}

void Pause::render() {
}

void Pause::playsound() {
    // this->audio->playSound(this->buttonSound);
}