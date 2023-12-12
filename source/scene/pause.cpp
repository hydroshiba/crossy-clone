#include "pause.hpp"

Pause::Pause(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : 
    Scene(engine, speaker, registry, setting, keyboard, holder),
    CONTINUE("asset/texture/button/continue.bmp"),
    CONTINUE_CLICKED("asset/texture/button/continue_clicked.bmp"),
    QUIT("asset/texture/button/quit.bmp"),
    QUIT_CLICKED("asset/texture/button/quit_clicked.bmp"),
    quitButton(QUIT, QUIT_CLICKED, (width - QUIT.getWidth()) * 3 / 4, height * 2 / 3),
    continueButton(CONTINUE, CONTINUE_CLICKED, (width - CONTINUE.getWidth()) / 4, height * 2 / 3),
    button(0),
    pause("PAUSE", width / 2 - width / 10, height / 3 - height / 6, 0.8f, 0.2f)
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