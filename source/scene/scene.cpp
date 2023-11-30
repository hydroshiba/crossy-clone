#include "scene.hpp"

Scene::Scene(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : engine(engine), speaker(speaker), sceneRegistry(registry), setting(setting), keyboard(keyboard) {
}

Scene::~Scene() {
}