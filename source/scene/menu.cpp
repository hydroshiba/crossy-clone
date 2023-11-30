#include "menu.hpp"

Menu::Menu(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(width, height, engine, speaker, registry, setting, keyboard),
                                                                                                                                     button(1),
                                                                                                                                     TITLE("asset/texture/title.bmp"),
                                                                                                                                     CONTINUE("asset/texture/button/continue.bmp"),
                                                                                                                                     CONTINUE_CLICKED("asset/texture/button/continue_clicked.bmp"),
                                                                                                                                     START("asset/texture/button/start.bmp"),
                                                                                                                                     START_CLICKED("asset/texture/button/start_clicked.bmp"),
                                                                                                                                     OPTION("asset/texture/button/option.bmp"),
                                                                                                                                     OPTION_CLICKED("asset/texture/button/option_clicked.bmp"),
                                                                                                                                     LEADERBOARD("asset/texture/button/leaderboard.bmp"),
                                                                                                                                     LEADERBOARD_CLICKED("asset/texture/button/leaderboard_clicked.bmp"),
                                                                                                                                     CREDIT("asset/texture/button/credit.bmp"),
                                                                                                                                     CREDIT_CLICKED("asset/texture/button/credit_clicked.bmp"),
                                                                                                                                     QUIT("asset/texture/button/quit.bmp"),
                                                                                                                                     QUIT_CLICKED("asset/texture/button/quit_clicked.bmp"),
                                                                                                                                     background("asset/sound/background.wav"),
                                                                                                                                     title((width - TITLE.getWidth()) / 2, height / 6, TITLE) {
    if(setting->getGamestate().size())
        buttons.push_back(new Button(CONTINUE, CONTINUE_CLICKED, (width - CONTINUE.getWidth()) / 2, height / 2));

    buttons.push_back(new Button(START, START_CLICKED, (width - START.getWidth()) / 2, buttons.size() ? buttons.back()->getY() + 100 : height / 2));
    buttons.push_back(new Button(OPTION, OPTION_CLICKED, (width - OPTION.getWidth()) / 2, buttons.back()->getY() + 100));
    buttons.push_back(new Button(LEADERBOARD, LEADERBOARD_CLICKED, (width - LEADERBOARD.getWidth()) / 2, buttons.back()->getY() + 100));
    buttons.push_back(new Button(CREDIT, CREDIT_CLICKED, (width - CREDIT.getWidth()) / 2, buttons.back()->getY() + 100));
    buttons.push_back(new Button(QUIT, QUIT_CLICKED, (width - QUIT.getWidth()) / 2, buttons.back()->getY() + 100));
}

Scene* Menu::process() {
    Scene* next = this;
    Key pressedKey = keyboard->key();

    switch(pressedKey) {
    case Key::UP:
        if(button > 1) {
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
        case 1:
            next = sceneRegistry->scene(SceneID::MENU);
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

    return next;
}

void Menu::render() {
    engine->fill(0, 162, 232);
    title.render(engine);
    for(auto& button : buttons) {
        button->render(engine);
    }
}

void Menu::playsound() {
}

Menu::~Menu() {
}