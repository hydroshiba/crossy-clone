#ifndef SCENE_HPP_
#define SCENE_HPP_
#include <iostream>
#include "setting.hpp"
#include "audio.hpp"
#include "engine.hpp"

class SceneRegistry;
class Scene {
protected:
    Engine* engine;
    AudioDevice* audio;
    SceneRegistry* sceneRegistry;
    Setting* setting;
public:
    Scene(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting);

    virtual ~Scene();

    virtual Scene* process() = 0;
    virtual void render() = 0;
    virtual void playsound() = 0;
};

#endif