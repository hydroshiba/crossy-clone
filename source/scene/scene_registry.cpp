#include "scene_registry.hpp"

SceneRegistry::SceneRegistry(int width, int height, Engine* engine, Speaker* speaker, Setting* setting, Keyboard* keyboard) {
    scenes.resize(static_cast<int>(SceneID::SIZE));

    scenes[static_cast<int>(SceneID::MENU)] = new Menu(width, height, engine, speaker, this, setting, keyboard);
    scenes[static_cast<int>(SceneID::PLAY)] = new Play(width, height, engine, speaker, this, setting, keyboard);
    scenes[static_cast<int>(SceneID::OPTION)] = new Option(width, height, engine, speaker, this, setting, keyboard);
    scenes[static_cast<int>(SceneID::LEADERBOARD)] = new Leaderboard(width, height, engine, speaker, this, setting, keyboard);
    scenes[static_cast<int>(SceneID::CREDIT)] = new Credit(width, height, engine, speaker, this, setting, keyboard);
    scenes[static_cast<int>(SceneID::PAUSE)] = new Pause(width, height, engine, speaker, this, setting, keyboard);
    scenes[static_cast<int>(SceneID::GAMEOVER)] = new Gameover(width, height, engine, speaker, this, setting, keyboard);
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