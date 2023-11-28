#include "menu.hpp"

Menu::Menu(int width, int height, Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, audio, registry, setting, keyboard),
    titleTexture(new Texture(TITLE)),
    title((width - titleTexture->getWidth()) / 2, height / 6, titleTexture) {}

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
    delete titleTexture;
}