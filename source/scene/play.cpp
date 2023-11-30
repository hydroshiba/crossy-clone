#include "play.hpp"

Play::Play(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, speaker, registry, setting, keyboard) {}

Scene* Play::process() {
    bool isGameover = false;
    bool isStopped = false;

    bool isRunning = true;

    high_resolution_clock::time_point prev;

    std::vector<int> laneTime(lanes.size());
    for (int i = 0; i < laneTime.size(); i++) {
        laneTime[i] = 100;
    }

    // Player processing
    do {
        keyboard->refresh();
        Key pressedKey = keyboard->key();

        switch (pressedKey) {
            case Key::UP:
                player->move(pressedKey);
                offset++;
                break;
            case Key::DOWN:
                player->move(pressedKey);
                offset--;
                break;
            case Key::LEFT: case Key::RIGHT:
                player->move(pressedKey);
                break;
            case Key::ESC:
                isStopped = true;
                break;
            default:
                break;
        }

        // Lane processing
        for (int i = 0; i < lanes.size(); i++) {
            lanes[i].process(laneTime[i], prev, isGameover, player->getPos());
            laneTime[i] = 100 - (offset * 10);
        }

        isRunning = !isStopped && !isGameover;
    } while (isRunning);
    
    // Return next scene
    Scene* next = nullptr;
    if (isGameover) {
        next = sceneRegistry->scene(SceneID::GAMEOVER);
    }
    else if (isStopped) {
        next = sceneRegistry->scene(SceneID::PAUSE);
    }

    return next;
}

void Play::render() {
}

void Play::playsound() {
    // this->audio->playSound(this->buttonSound);
}

Play::~Play() {
    // this->audio->stopSound(this->buttonSound);
}