#include "scene.hpp"

Scene::Scene(Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting) : engine(engine), audio(audio), sceneRegistry(registry), setting(setting) {}

Scene::~Scene() {
    
}