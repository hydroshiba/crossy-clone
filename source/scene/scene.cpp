#include "scene.hpp"

Scene::Scene(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) :
	engine(engine), speaker(speaker), sceneRegistry(registry), setting(setting), keyboard(keyboard), holder(holder) {}

Scene::~Scene() {
}