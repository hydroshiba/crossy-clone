#include "gameover.hpp"

Gameover::Gameover(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : 
    Scene(engine, speaker, registry, setting, keyboard, holder),
    QUIT_CLICKED("asset/texture/button/quit_clicked.bmp"),
    quit(QUIT_CLICKED, (width - QUIT_CLICKED.getWidth()) / 2, height * 2 / 3),
    gameover("Gameover", width / 2 - width / 7, height / 3 - height / 6, 0.8f, 0.2f) {}

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
    gameover.render(engine);
    quit.render(engine);
}

void Gameover::playsound() {
    // this->audio->playSound(this->buttonSound);
}