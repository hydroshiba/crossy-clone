#include "menu.hpp"

Menu::Menu(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : Scene(engine, speaker, registry, setting, keyboard, holder),
                                                                                                                                    defaultButton(setting->getGamestate().size() ? 0 : 1),
                                                                                                                                    isContinueEnabled(setting->getGamestate().size() ? true : false),
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
                                                                                                                                    CREDIT("asset/texture/button/credit.bmp"), //credit
                                                                                                                                    CREDIT_CLICKED("asset/texture/button/credit_clicked.bmp"), //credit clicked
                                                                                                                                    QUIT("asset/texture/button/quit.bmp"),
                                                                                                                                    QUIT_CLICKED("asset/texture/button/quit_clicked.bmp"),
                                                                                                                                    DUCK_X2("asset/texture/sprite/duck/duck_x2.bmp"),
                                                                                                                                    button_clicked("asset/sound/sfx/button-click-2.wav"),
                                                                                                                                    title(TITLE, (width - TITLE.getWidth()) / 5, (height - TITLE.getHeight()) / 2),
                                                                                                                                    duck_x2(DUCK_X2, (width - DUCK_X2.getWidth()) * 4 / 5, (height - DUCK_X2.getHeight()) / 2){
    buttons.push_back(new Button(CONTINUE, CONTINUE_CLICKED, (width - CONTINUE.getWidth()) / 2, (height - CONTINUE.getHeight()) / 2.75));
    buttons.push_back(new Button(START, START_CLICKED, (width - START.getWidth()) / 2, isContinueEnabled ? buttons.back()->getY() + buttons.back()->getHeight() * 0.55 : (height - START.getHeight()) / 2.75));
    buttons.push_back(new Button(OPTION, OPTION_CLICKED, (width - OPTION.getWidth()) / 2, buttons.back()->getY() + buttons.back()->getHeight() * 0.55));
    buttons.push_back(new Button(LEADERBOARD, LEADERBOARD_CLICKED, (width - LEADERBOARD.getWidth()) / 2, buttons.back()->getY() + buttons.back()->getHeight() * 0.55));
    buttons.push_back(new Button(CREDIT, CREDIT_CLICKED, (width - CREDIT.getWidth()) / 2, buttons.back()->getY() + buttons.back()->getHeight() * 0.55));
    buttons.push_back(new Button(QUIT, QUIT_CLICKED, (width - QUIT.getWidth()) / 2, buttons.back()->getY() + buttons.back()->getHeight() * 0.55)); 
}

void Menu::updateButton() {
    if(isContinueEnabled == setting->getGamestate().empty()){
        isContinueEnabled = !isContinueEnabled;
        buttons[button]->release();
        button = defaultButton = isContinueEnabled ? 0 : 1;
        int y = isContinueEnabled ? buttons[0]->getY() + buttons[0]->getHeight() * 0.55 : (height - START.getHeight()) / 2.75;
        buttons[1]->setOffset(buttons[1]->getX(), y);
        for(int i = 2; i < buttons.size(); i++) {
            buttons[i]->setOffset(buttons[i]->getX(), buttons[i - 1]->getY() + buttons[i - 1]->getHeight() * 0.55);
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
            play->createNewGame("");
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
    duck_x2.render(engine);

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