#include "scene_registry.hpp"

SceneRegistry::SceneRegistry(Engine* engine, Speaker* speaker, Setting* setting, Keyboard* keyboard, TextureHolder* holder) {
    scenes.resize(static_cast<int>(SceneID::SIZE));

    scenes[static_cast<int>(SceneID::MENU)] = new Menu(engine, speaker, this, setting, keyboard, holder);
    scenes[static_cast<int>(SceneID::PLAY)] = new Play(engine, speaker, this, setting, keyboard, holder);
    scenes[static_cast<int>(SceneID::OPTION)] = new Option(engine, speaker, this, setting, keyboard, holder);
    scenes[static_cast<int>(SceneID::LEADERBOARD)] = new Leaderboard(engine, speaker, this, setting, keyboard, holder);
    scenes[static_cast<int>(SceneID::CREDIT)] = new Credit(engine, speaker, this, setting, keyboard, holder);
    scenes[static_cast<int>(SceneID::PAUSE)] = new Pause(engine, speaker, this, setting, keyboard, holder);
    scenes[static_cast<int>(SceneID::GAMEOVER)] = new Gameover(engine, speaker, this, setting, keyboard, holder);
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