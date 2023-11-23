#include "scene_registry.hpp"

SceneRegistry::SceneRegistry(Engine* engine, AudioDevice* audio, Setting* setting) {
   scenes[MENU] = new Menu(engine, audio, this, setting);
   scenes[PLAY] = NULL;
   scenes[SETTING] = NULL;
   scenes[LEADERBOARD] = NULL;
   scenes[CREDIT] = NULL;
   scenes[PAUSE] = NULL;
   scenes[GAMEOVER] = NULL;
}

SceneRegistry::~SceneRegistry() {

    for(int i = 0; i < 7; i++){

        if(scenes[i] != NULL){

            delete scenes[i];
            scenes[i] = NULL;

        }
    }
}

Scene* SceneRegistry::getScene(SceneType type) {

    if (type >= 0 && type < 7) {
        return scenes[type];
    } else {
        return nullptr;
    }
}