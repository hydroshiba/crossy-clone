#include "sceneRegistry.hpp"

SceneRegistry::SceneRegistry() {
    menu = new Menu;
    //play = new Play;
    //pause = new Pause;
    //gameover = new Gameover;
}

SceneRegistry::~SceneRegistry(){
    delete menu;
    delete play;
    delete pause;
    delete gameover;

    menu = NULL;
    play = NULL;
    pause = NULL;
    gameover = NULL;
}