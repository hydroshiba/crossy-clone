#ifndef SCENE_HPP_
#define SCENE_HPP_
#include <iostream>

class SceneRegistry;
class Scene {
protected:
    SceneRegistry* sceneRegistry;
public:
    Scene(SceneRegistry* registry);
    virtual ~Scene();

    virtual void process() = 0;
    virtual void render() = 0;
    virtual void playsound() = 0;
};

#endif