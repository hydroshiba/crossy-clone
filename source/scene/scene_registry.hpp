#ifndef SCENE_REGISTRY_HPP_
#define SCENE_REGISTRY_HPP_

#include <vector>

#include "menu.hpp"
// #include "pause.hpp"
// #include "play.hpp"
// #include "gameover.hpp

enum class SceneID {
    MENU,
    SETTING,
    LEADERBOARD,
    CREDIT,
    PLAY,
    PAUSE,
    GAMEOVER,
    SIZE
};

class SceneRegistry {
private:
    std::vector<Scene*> scenes;

public:
    SceneRegistry(Engine* engine, AudioDevice* audio, Setting* setting);
    ~SceneRegistry();

    Scene* scene(SceneID type);
};

#endif