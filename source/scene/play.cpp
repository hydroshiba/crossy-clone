#include "play.hpp"

Play::Play(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, speaker, registry, setting, keyboard) {
        // Load gamestate
        loadGamestate(setting->getGamestate());
    }

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

void Play::loadGamestate(const std::vector<std::string>& gamestate) {
    auto toInt = [](std::string str) -> int {
        return *reinterpret_cast<int*>(&str[0]);
    };

    auto toFloat = [](std::string str) -> float {
        return *reinterpret_cast<float*>(&str[0]);
    };

    // Handle gamestate[0]
    {
        std::string tmpScore = "", tmpOffset = "";
        for (int i = 0; i < 4; i++) {
            tmpScore += gamestate[0][i];
            tmpOffset += gamestate[0][i + 4];
        }

        score = toInt(tmpScore);
        offset = toInt(tmpOffset);
    }

    // Handle gamestate[1]
    for (int i = 0; i < gamestate[1].size(); i += 5) {
        std::string tmpPos = "", tmpSpeed = "";
        
        tmpPos += gamestate[1][i];
        
        for (int j = i + 1; j < i + 5; j++) {
            tmpSpeed += gamestate[1][j];
        }

        lanes.push_back(Lane(toInt(tmpPos), toFloat(tmpSpeed), ""));
    }

    // Handle gamestate[2]
    {
        std::string tmpLane = "", tmpPos = "", tmpName = "";
        tmpLane += gamestate[2][0];
        for (int i = 1; i < 5; i++) {
            tmpPos += gamestate[2][i];
        }
        for (int i = 5; i < gamestate[2].size(); i++) {
            tmpName += gamestate[2][i];
        }

        player = new Player(toInt(tmpLane), toFloat(tmpPos), tmpName, "", "");
    }

    // Handle gamestate[3]
    for (int i = 0; i < gamestate[3].length(); i += 5) {
        std::string tmpLane = "", tmpPos = "";
        tmpLane += gamestate[3][i];
        for (int j = i + 1; j < i + 5; j++) {
            tmpPos += gamestate[3][j];
        }
        lanes[std::stoi(tmpLane)].addVehicle(toFloat(tmpPos), "asset/texture/car", "asset/sound/car");
    }

    // Handdle gamestate[4]
    for (int i = 0; i < gamestate[4].length(); i++) {
        std::string tmpLane = "", tmpPos = "";
        tmpLane += gamestate[4][i];
        for (int j = i + 1; j < i + 5; j++) {
            tmpPos += gamestate[4][j];
        }
        lanes[std::stoi(tmpLane)].addVehicle(toFloat(tmpPos), "asset/texture/truck", "asset/sound/truck");
    }
}

Play::~Play() {
    // this->audio->stopSound(this->buttonSound);
    delete player;
}