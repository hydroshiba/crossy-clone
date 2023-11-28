#include "leaderboard.hpp"

Leaderboard::Leaderboard(int width, int height, Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, audio, registry, setting, keyboard) {}

Leaderboard::~Leaderboard() {
}

Scene* Leaderboard::process() {
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

void Leaderboard::render() {
}

void Leaderboard::playsound() {
    // this->audio->playSound(this->buttonSound);
}