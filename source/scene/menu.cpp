#include "menu.hpp"

Menu::Menu(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : Scene(engine, speaker, registry, setting, keyboard, holder),
                                                                                                                                    defaultButton(setting->getGamestate().size() ? 0 : 1),
                                                                                                                                    isContinueEnabled(setting->getGamestate().size() ? true : false),
                                                                                                                                    button(defaultButton),
                                                                                                                                    button_clicked("asset/sound/sfx/button-click-2.wav"),
                                                                                                                                    title(holder->get("TITLE"), (engine->getWidth() - holder->get("TITLE")->getWidth()) / 5, (engine->getHeight() - holder->get("TITLE")->getHeight()) / 2),
                                                                                                                                    duck_large(holder->get("DUCK_LARGE"), (engine->getWidth() - holder->get("DUCK_LARGE")->getWidth()) * 4 / 5, (engine->getHeight() - holder->get("DUCK_LARGE")->getHeight()) / 2){
    buttons.push_back(new Button(holder->get("CONTINUE"), holder->get("CONTINUE_CLICKED"), (engine->getWidth() - holder->get("CONTINUE")->getWidth()) / 2, (engine->getHeight() - holder->get("CONTINUE")->getHeight()) / 2.75));
    buttons.push_back(new Button(holder->get("START"), holder->get("START_CLICKED"), (engine->getWidth() - holder->get("START")->getWidth()) / 2, isContinueEnabled ? buttons.back()->position().y + buttons.back()->size().y * 0.55 : (engine->getHeight() - holder->get("START")->getHeight()) / 2.75));
    buttons.push_back(new Button(holder->get("OPTION"), holder->get("OPTION_CLICKED"), (engine->getWidth() - holder->get("OPTION")->getWidth()) / 2, buttons.back()->position().y + buttons.back()->size().y * 0.55));
    buttons.push_back(new Button(holder->get("LEADERBOARD"), holder->get("LEADERBOARD_CLICKED"), (engine->getWidth() - holder->get("LEADERBOARD")->getWidth()) / 2, buttons.back()->position().y + buttons.back()->size().y * 0.55));
    buttons.push_back(new Button(holder->get("CREDIT"), holder->get("CREDIT_CLICKED"), (engine->getWidth() - holder->get("CREDIT")->getWidth()) / 2, buttons.back()->position().y + buttons.back()->size().y * 0.55));
    buttons.push_back(new Button(holder->get("QUIT"), holder->get("QUIT_CLICKED"), (engine->getWidth() - holder->get("QUIT")->getWidth()) / 2, buttons.back()->position().y + buttons.back()->size().y * 0.55));
}

void Menu::updateButton() {
    if(isContinueEnabled == setting->getGamestate().empty()){
        isContinueEnabled = !isContinueEnabled;
        buttons[button]->release();
        button = defaultButton = isContinueEnabled ? 0 : 1;
        int y = isContinueEnabled ? buttons[0]->position().y + buttons[0]->size().y * 0.55 : (engine->getHeight() - holder->get("START")->getHeight()) / 2.75;
        buttons[1]->shift(0, y - buttons[1]->position().y);
        for(int i = 2; i < buttons.size(); i++) {
            buttons[i]->shift(0, buttons[i - 1]->position().y - buttons[i]->position().y + (buttons[i - 1]->size().y - buttons[i]->size().y ) * 0.55);
        }
    }

}

Scene* Menu::process() {
    Scene* next = this;
    Key pressedKey = keyboard->key();

    switch(pressedKey) {
    case Key::UP:
        if(button > defaultButton) {
            button--;
        }
        break;
    case Key::DOWN:
        if(button < 5) {
            button++;
        }
        break;
    case Key::ENTER:
        // speaker->play(button_clicked);
        switch(button) {
        case 0: {
            next = sceneRegistry->scene(SceneID::PLAY); //continue
            Play* play = dynamic_cast<Play*>(next);
            play->loadGamestate(setting->getGamestate());
            break;
        }
        case 1: {
            next = sceneRegistry->scene(SceneID::PLAY);
            setting->setGamestate({});
            Play* play = dynamic_cast<Play*>(next);
            play->createNewGame();
            break;
        }
        case 2:
            next = sceneRegistry->scene(SceneID::OPTION);
            break;
        case 3:
            next = sceneRegistry->scene(SceneID::LEADERBOARD);
            break;
        case 4:
            next = sceneRegistry->scene(SceneID::CREDIT);
            break;
        case 5:
            next = nullptr;
            break;
        }
        break;
    case Key::ESC:
        next = nullptr;
        break;
    }

    buttons[button]->press();
    return next;
}

void Menu::render() {
    updateButton();
    engine->fill(0, 162, 232);
    title.render(engine);
    duck_large.render(engine);

    for(int i = defaultButton; i < buttons.size(); i++) {
        buttons[i]->render(engine);
    }

    buttons[button]->release();
}

void Menu::playsound() {
}

Menu::~Menu() {
    for(auto& button : buttons) {
        delete button;
    }
}