#include "scene_registry.hpp"

SceneRegistry::SceneRegistry(Engine* engine, AudioDevice* audio, Setting* setting) {
   menu = new Menu(engine, audio, this, setting);
   play = NULL;
   pause = NULL;
   gameover = NULL;
}

SceneRegistry::~SceneRegistry() {
    if (menu) {
        delete menu;
        menu = NULL;
    }

    if (play) {
        delete play;
        play = NULL;
    }

    if (pause) {
        delete pause;
        pause = NULL;
    }

    if (gameover) {
        delete gameover;
        gameover = NULL;
    }
}