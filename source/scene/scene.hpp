#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <iostream>

#include "setting.hpp"
#include "audio.hpp"
#include "engine.hpp"
#include "keyboard.hpp"

class SceneRegistry;

class Scene {
protected:
    int width, height;

    Engine* engine;
    AudioDevice* audio;
    Setting* setting;
    SceneRegistry* sceneRegistry;
    Keyboard* keyboard;

public:
    Scene(int width, int height, Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    virtual ~Scene();

    virtual Scene* process() = 0;
    virtual void render() = 0;
    virtual void playsound() = 0;
};

#endif