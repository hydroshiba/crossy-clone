#include "menu.hpp"
#include "scene_registry.hpp"

Menu::Menu(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting) : Scene(engine, audio, registry, setting) {
    
}

Scene* Menu::process(SceneRegistry const * const registry) {
    return nullptr;
}

void Menu::render() {

}

void Menu::playsound() {

}

Menu::~Menu() {

}