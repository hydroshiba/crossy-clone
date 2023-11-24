#include "scene_registry.hpp"

SceneRegistry::SceneRegistry(Engine* engine, AudioDevice* audio, Setting* setting) {
    scenes.resize(static_cast<int>(SceneID::SIZE));

    scenes[static_cast<int>(SceneID::MENU)] = new Menu(engine, audio, this, setting);
    scenes[static_cast<int>(SceneID::PLAY)] = nullptr;
    scenes[static_cast<int>(SceneID::SETTING)] = nullptr;
    scenes[static_cast<int>(SceneID::LEADERBOARD)] = nullptr;
    scenes[static_cast<int>(SceneID::CREDIT)] = nullptr;
    scenes[static_cast<int>(SceneID::PAUSE)] = nullptr;
    scenes[static_cast<int>(SceneID::GAMEOVER)] = nullptr;
}

SceneRegistry::~SceneRegistry() {
    for(int i = 0; i < static_cast<int>(SceneID::SIZE); ++i)
        delete scenes[i];
}

Scene* SceneRegistry::scene(SceneID type) {
    unsigned int ID = static_cast<unsigned int>(type);
    if(ID >= scenes.size()) return nullptr;
    return scenes[ID];
}