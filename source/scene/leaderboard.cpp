#include "leaderboard.hpp"

Leaderboard::Leaderboard(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting): Scene(engine, audio, registry, setting) {
    
}

Leaderboard::~Leaderboard() {

}

Scene* Leaderboard::process() {
    return sceneRegistry->scene(SceneID::MENU);
}

void Leaderboard::render() {
    
}

void Leaderboard::playsound() {
    // this->audio->playSound(this->buttonSound);
}