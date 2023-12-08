#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <iostream>

#include "setting.hpp"
#include "speaker.hpp"
#include "engine.hpp"
#include "keyboard.hpp"
#include "typedef.hpp"
#include "object.hpp"
#include "button.hpp"
#include "textbox.hpp"

class SceneRegistry;

class Scene {
protected:
    int width, height;

    Engine* engine;
    Speaker* speaker;
    Setting* setting;
    SceneRegistry* sceneRegistry;
    Keyboard* keyboard;

public:
    Scene(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    virtual ~Scene();

    virtual Scene* process() = 0;
    virtual void render() = 0;
    virtual void playsound() = 0;
};

#endif