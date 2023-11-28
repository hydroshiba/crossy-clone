#include "menu.hpp"

Menu::Menu(int width, int height, Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, audio, registry, setting, keyboard),
    TITLE(new Texture("asset/texture/title.bmp")),
    START(new Texture("asset/texture/button/start.bmp")), START_CLICKED(new Texture("asset/texture/button/start_clicked.bmp")),
    OPTION(new Texture("asset/texture/button/option.bmp")), OPTION_CLICKED(new Texture("asset/texture/button/option_clicked.bmp")),
    // LEADERBOARD(new Texture("asset/texture/button/leaderboard.bmp")), LEADERBOARD_CLICKED(new Texture("asset/texture/button/leaderboard_clicked.bmp")),
    // CREDIT(new Texture("asset/texture/button/credit.bmp")), CREDIT_CLICKED(new Texture("asset/texture/button/credit_clicked.bmp")),
    QUIT(new Texture("asset/texture/button/quit.bmp")), QUIT_CLICKED(new Texture("asset/texture/button/quit_clicked.bmp")),
    title((width - TITLE->getWidth()) / 2, height / 6, TITLE) {}

Scene* Menu::process() {
    int button = 1;

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
    title.render(engine);
}

void Menu::playsound() {
}

Menu::~Menu() {
    delete TITLE;
    delete START; delete START_CLICKED;
    delete OPTION; delete OPTION_CLICKED;
    // delete LEADERBOARD; delete LEADERBOARD_CLICKED;
    // delete CREDIT; delete CREDIT_CLICKED;
    delete QUIT; delete QUIT_CLICKED;
}