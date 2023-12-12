#include "gameover.hpp"

Gameover::Gameover(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : 
    Scene(engine, speaker, registry, setting, keyboard, holder),
    quit(holder->get("QUIT_CLICKED"), (engine->getWidth() - holder->get("QUIT_CLICKED")->getWidth()) / 2, engine->getHeight() * 2 / 3),
    gameover(holder, "Gameover", engine->getWidth() / 2 - engine->getWidth() / 7, engine->getHeight() / 3 - engine->getHeight() / 6) {}

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