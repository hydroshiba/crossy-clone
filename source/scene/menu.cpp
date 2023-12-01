#include "menu.hpp"

Menu::Menu(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(width, height, engine, speaker, registry, setting, keyboard),
                                                                                                                                     defaultButton(setting->getGamestate().size() ? 0 : 1),
                                                                                                                                     button(defaultButton),
                                                                                                                                     TITLE("asset/texture/title.bmp"),
                                                                                                                                     CONTINUE("asset/texture/button/continue.bmp"),
                                                                                                                                     CONTINUE_CLICKED("asset/texture/button/continue_clicked.bmp"),
                                                                                                                                     START("asset/texture/button/start.bmp"),
                                                                                                                                     START_CLICKED("asset/texture/button/start_clicked.bmp"),
                                                                                                                                     OPTION("asset/texture/button/option.bmp"),
                                                                                                                                     OPTION_CLICKED("asset/texture/button/option_clicked.bmp"),
                                                                                                                                     LEADERBOARD("asset/texture/button/leaderboard.bmp"),
                                                                                                                                     LEADERBOARD_CLICKED("asset/texture/button/leaderboard_clicked.bmp"),
                                                                                                                                     CREDIT("asset/texture/button/leaderboard.bmp"), //credit
                                                                                                                                     CREDIT_CLICKED("asset/texture/button/leaderboard_clicked.bmp"), //credit clicked
                                                                                                                                     QUIT("asset/texture/button/quit.bmp"),
                                                                                                                                     QUIT_CLICKED("asset/texture/button/quit_clicked.bmp"),
                                                                                                                                     background("asset/sound/background.wav"),
                                                                                                                                     title((width - TITLE.getWidth()) / 2, height / 10, TITLE) {
    if(setting->getGamestate().size()){
        buttons.push_back(new Button(CONTINUE, CONTINUE_CLICKED, (width - CONTINUE.getWidth()) / 2, height / 6 + 180));
        
    }
    buttons.push_back(new Button(START, START_CLICKED, (width - START.getWidth()) / 2, buttons.size() ? buttons.back()->getY() + 60 : height / 6 + 180));
    buttons.push_back(new Button(OPTION, OPTION_CLICKED, (width - OPTION.getWidth()) / 2, buttons.back()->getY() + 60));
    buttons.push_back(new Button(LEADERBOARD, LEADERBOARD_CLICKED, (width - LEADERBOARD.getWidth()) / 2, buttons.back()->getY() + 60));
    buttons.push_back(new Button(CREDIT, CREDIT_CLICKED, (width - CREDIT.getWidth()) / 2, buttons.back()->getY() + 60));
    buttons.push_back(new Button(QUIT, QUIT_CLICKED, (width - QUIT.getWidth()) / 2, buttons.back()->getY() + 60));
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
        switch(button) {
        case 0:
            next = sceneRegistry->scene(SceneID::PLAY); //continue
            break;
        case 1:
            next = sceneRegistry->scene(SceneID::PLAY);
            setting->setGamestate({});
            break;
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

    buttons[button - defaultButton]->press();

    return next;
}

void Menu::render() {
    engine->fill(0, 162, 232);
    title.render(engine);

    for(auto& button : buttons) {
        button->render(engine);
    }
    
    buttons[button - defaultButton]->release();
}

void Menu::playsound() {
}

Menu::~Menu() {
}