#include "scene_registry.hpp"

SceneRegistry::SceneRegistry(Engine* engine, AudioDevice* audio, Setting* setting) {
    scenes.resize(static_cast<int>(SceneID::SIZE));

    scenes[static_cast<int>(SceneID::MENU)] = new Menu(engine, audio, this, setting);
    scenes[static_cast<int>(SceneID::PLAY)] = new Play(engine, audio, this, setting);
    scenes[static_cast<int>(SceneID::OPTION)] = new Option(engine, audio, this, setting);
    scenes[static_cast<int>(SceneID::LEADERBOARD)] = new Leaderboard(engine, audio, this, setting);
    scenes[static_cast<int>(SceneID::CREDIT)] = new Credit(engine, audio, this, setting);
    scenes[static_cast<int>(SceneID::PAUSE)] = new Pause(engine, audio, this, setting);
    scenes[static_cast<int>(SceneID::GAMEOVER)] = new Gameover(engine, audio, this, setting);
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