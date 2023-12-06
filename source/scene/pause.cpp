#include "pause.hpp"

Pause::Pause(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, speaker, registry, setting, keyboard),
    CONTINUE("asset/texture/button/continue.bmp"),
    CONTINUE_CLICKED("asset/texture/button/continue_clicked.bmp"),
    QUIT("asset/texture/button/quit.bmp"),
    QUIT_CLICKED("asset/texture/button/quit_clicked.bmp"),
    isExit(false)
    {
        buttons[0] = new Button(CONTINUE, CONTINUE_CLICKED, (width - CONTINUE.getWidth()) / 4, height * 2 / 3 + 140);
        buttons[1] = new Button(QUIT, QUIT_CLICKED, (width - QUIT.getWidth()) * 3 / 4, height * 2 / 3 + 140);
    }

Pause::~Pause() {
}

Scene* Pause::process() {
    int button = 1;
    isExit = false;

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
                case 2: {
                    // Exit to Menu                
                    nextScene = sceneRegistry->scene(SceneID::MENU);
                    Play* tmpScene = dynamic_cast<Play*>(sceneRegistry->scene(SceneID::PLAY));
                    setting->setGamestate(tmpScene->createGamestate());
                    break;
                }
            }
            isExit = true;
            break;
        }
    }

    buttons[isExit]->press();
    
    return nextScene;
}

void Pause::render() {
    engine->fill(0, 162, 232);

    buttons[0]->render(engine);
    buttons[1]->render(engine);

    buttons[isExit]->release();
}

void Pause::playsound() {
    // this->audio->playSound(this->buttonSound);
}