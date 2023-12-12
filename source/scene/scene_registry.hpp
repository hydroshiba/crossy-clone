#ifndef SCENE_REGISTRY_HPP_
#define SCENE_REGISTRY_HPP_

#include <vector>

#include "menu.hpp"
#include "option.hpp"
#include "pause.hpp"
#include "play.hpp"
#include "gameover.hpp"
#include "leaderboard.hpp"
#include "credit.hpp"

enum class SceneID {
    MENU,
    OPTION,
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
    SceneRegistry(Engine* engine, Speaker* speaker, Setting* setting, Keyboard* keyboard, TextureHolder* holder);
    ~SceneRegistry();

    Scene* scene(SceneID type);
};

#endif