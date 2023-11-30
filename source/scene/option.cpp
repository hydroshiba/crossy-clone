#include "option.hpp"

Option::Option(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, speaker, registry, setting, keyboard) {}

Option::~Option() {
}

Scene* Option::process() {
    bool isExit = false;
    int button = 1;
    Sprite sprite = setting->spriteID();

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
        case Key::LEFT:
            switch(button) {
            case 1:
                --sprite;
                setting->setSprite(sprite);
                break;
            case 2:
                setting->decMusic();
                break;
            case 3:
                setting->decSFX();
                break;
            }
            break;
        case Key::RIGHT:
            switch(button) {
            case 1:
                ++sprite;
                setting->setSprite(sprite);
                break;
            case 2:
                setting->incMusic();
                break;
            case 3:
                setting->incSFX();
                break;
            }
            break;
        case Key::ESC:
            isExit = true;
            break;
        }
    }
    return sceneRegistry->scene(SceneID::MENU);
}

void Option::render() {
}

void Option::playsound() {
    // this->audio->playSound(this->buttonSound);
}