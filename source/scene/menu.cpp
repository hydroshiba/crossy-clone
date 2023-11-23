#include "menu.hpp"
#include "scene_registry.hpp"

Menu::Menu(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting) : Scene(engine, audio, registry, setting) {
    
}

Scene* Menu::process(SceneRegistry const * const registry) {

    int option = 1;
    Scene* nextScene = NULL;
    while (true) {
        //render();

        char key = _getch();

        switch (key) {
        case 72:
            if (option > 1) {
                option--;
            }
            break;
        case 80:
            if (option < 3) {
                option++;
            }
            break;
        case 13:
            switch (option) {
            case 1:
                nextScene = sceneRegistry->getScene(MENU); 
                break;
            case 2:
                break;
            case 3:
                break;
            }
        default:
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