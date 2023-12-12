#include "pause.hpp"

Pause::Pause(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : 
    Scene(engine, speaker, registry, setting, keyboard, holder),
    quitButton(holder->get("QUIT"), holder->get("QUIT_CLICKED"), (engine->getWidth() - holder->get("QUIT")->getWidth()) * 3 / 4, engine->getHeight() * 2 / 3),
    continueButton(holder->get("CONTINUE"), holder->get("CONTINUE_CLICKED"), (engine->getWidth() - holder->get("CONTINUE")->getWidth()) / 4, engine->getHeight() * 2 / 3),
    button(0),
    pause(holder, "PAUSE", engine->getWidth() / 2 - engine->getWidth() / 10, engine->getHeight() / 3 - engine->getHeight() / 6)
    {
    }

Pause::~Pause() {   
    // delete buttons[0];
    // delete buttons[1];
}

Scene* Pause::process() {

    Scene* nextScene = this;

    Key pressedKey = keyboard->key();

    if (pressedKey == Key::LEFT) {
        button = 0;
        continueButton.press();
        quitButton.release();
    }
    else if (pressedKey == Key::RIGHT) {
        button = 1;
        quitButton.press();
        continueButton.release();
    }
    else if (pressedKey == Key::ENTER) {
        switch(button) {
            case 0:
                // Continue Play
                nextScene = sceneRegistry->scene(SceneID::PLAY);
                break;
            case 1: {
                // Exit to Menu                
                nextScene = sceneRegistry->scene(SceneID::MENU);
                Play* tmpScene = dynamic_cast<Play*>(sceneRegistry->scene(SceneID::PLAY));
                setting->setGamestate(tmpScene->createGamestate());
                break;
            }
        }
    }
    
    return nextScene;
}

void Pause::render() {
    engine->fill(0, 162, 232);
    pause.render(engine);
    quitButton.render(engine);
    continueButton.render(engine);
}

void Pause::playsound() {
    // this->audio->playSound(this->buttonSound);
}