#include "menu.hpp"

Menu::Menu(Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(engine, audio, registry, setting, keyboard) {
}

Scene* Menu::process() {
    int button = 1;
    bool isExit = false;
    Keyboard keyboard;

    Scene* nextScene = nullptr;

    while (!isExit) {

        keyboard.refresh();
        Key pressedKey = keyboard.key();

        switch (pressedKey) {
        case Key::UP:
            if (button > 1) {
                button--;
            }
            break;
        case Key::DOWN:
            if (button < 5) {
                button++;
            }
            break;
        case Key::ENTER:
            switch (button) {
            case 1:
                nextScene = sceneRegistry->scene(SceneID::MENU);
                break;
            case 2:
                nextScene = sceneRegistry->scene(SceneID::OPTION);
                break;
            case 3:
                nextScene = sceneRegistry->scene(SceneID::LEADERBOARD);
                break;
            case 4:
                nextScene = sceneRegistry->scene(SceneID::CREDIT);
                break;
            case 5:
                isExit = true;
                break;
            }
            break;
        }
    }

    return nextScene;
}

void Menu::render() {
}

void Menu::playsound() {
}

Menu::~Menu() {
}