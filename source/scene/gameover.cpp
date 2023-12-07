#include "gameover.hpp"

Gameover::Gameover(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, speaker, registry, setting, keyboard),
    QUIT_CLICKED("asset/texture/button/quit_clicked.bmp"),
    quit(QUIT_CLICKED, (width - QUIT_CLICKED.getWidth()) / 2, height * 2 / 3) {}

Gameover::~Gameover() {
}

Scene* Gameover::process() {
    Scene* next = this;
    Key pressedKey = keyboard->key();
    if(pressedKey == Key::ENTER) {
        next = sceneRegistry->scene(SceneID::MENU);
    }

    return next;
}

void Gameover::render() {
    engine->fill(0, 162, 232);
    quit.render(engine);
}

void Gameover::playsound() {
    // this->audio->playSound(this->buttonSound);
}