#ifndef SCENE_REGISTRY_HPP_
#define SCENE_REGISTRY_HPP_

#include "menu.hpp"

// #include "pause.hpp"
// #include "play.hpp"
// #include "gameover.hpp
enum SceneType {
    MENU,
    SETTING,
    LEADERBOARD,
    CREDIT,
    PLAY,
    PAUSE,
    GAMEOVER
};
class SceneRegistry {
    private:
        Scene* scenes[7];

    public:
        SceneRegistry(Engine* engine, AudioDevice* audio , Setting* setting);
        ~SceneRegistry();

        Scene* getScene(SceneType type);
    };


#endif