#include "play.hpp"

Play::Play(int width, int height, Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, audio, registry, setting, keyboard) {}

Scene* Play::process() {
    bool isGameover = false;
    bool isStopped = false;

    bool isRunning = true;

    // Thread for lane processing
    std::vector<std::thread> laneThreads;
    for (auto lane : lanes) {
        laneThreads.emplace_back([&]() {
            lane.process(100, isRunning, isGameover, player->getLane(), player->getPos());
        });
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
        }

        isRunning = !isStopped && !isGameover;
    } while (isRunning);

    // Join all threads
    for (auto& laneThread : laneThreads) {
        laneThread.join();
    }
    
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