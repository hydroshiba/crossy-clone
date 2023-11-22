#include "scene.hpp"

Scene::Scene(SceneRegistry* registry) : sceneRegistry(registry) {}

Scene::~Scene() {
    delete sceneRegistry;
    sceneRegistry = NULL;
}