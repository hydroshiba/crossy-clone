#ifndef SCENE_REGISTRY_HPP_
#define SCENE_REGISTRY_HPP_

#include "scene.hpp"
#include "menu.hpp"
// #include "pause.hpp"
// #include "play.hpp"
// #include "gameover.hpp

class SceneRegistry{
private:
    const Scene* menu;
    const Scene* play;
    const Scene* pause;
    const Scene* gameover;
public:
    SceneRegistry();
    ~SceneRegistry();
    friend class Scene;
    friend class Menu;
    friend class Play;
    friend class Pause;
    friend class Gameover;
};

#endif