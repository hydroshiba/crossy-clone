#include "scene.hpp"

Scene::Scene(int width, int height, Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : engine(engine), audio(audio), sceneRegistry(registry), setting(setting), keyboard(keyboard) {
}

Scene::~Scene() {
}