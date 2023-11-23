#ifndef SCENE_HPP_
#define SCENE_HPP_
#include <iostream>
#include "setting.hpp"
#include "audio.hpp"
#include "engine.hpp"
#include "scene_registry.hpp"

class Scene {
protected:
    Engine* engine;
    AudioDevice* audio;
    SceneRegistry* sceneRegistry;
    Setting* setting;
public:
    Scene(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting);

    virtual ~Scene();

    virtual Scene* process(SceneRegistry const * const registry) = 0;
    virtual void render() = 0;
    virtual void playsound() = 0;
};

#endif