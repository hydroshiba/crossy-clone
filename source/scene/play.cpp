#include "play.hpp"

Play::Play(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, speaker, registry, setting, keyboard) {
        // Load gamestate
        if (!setting->getGamestate().empty()) loadGamestate(setting->getGamestate());
        else createNewGame("");
    }

Scene* Play::process() {
    bool isGameover = false;
    bool isStopped = false;

    bool isRunning = true;

    high_resolution_clock::time_point prev;

    std::vector<uint64_t> laneTime(lanes.size());
    uint64_t time = 8000;
    for (int i = 0; i < laneTime.size(); i++) {
        laneTime[i] = rand() % time + 1;
        time -= offset * offset * offset / 100;
    }

    // Player processing
    do {
        keyboard->refresh();
        Key pressedKey = keyboard->key();

        switch (pressedKey) {
            case Key::UP:
                player->move(pressedKey);
                score += 20000000 / laneTime[player->getLane() - offset];
                lanes[player->getLane() - offset].checkCollision(player->getPos());
                break;
            case Key::DOWN:
                player->move(pressedKey);
                score -= 333;
                lanes[player->getLane() - offset].checkCollision(player->getPos());
                break;
            case Key::LEFT: case Key::RIGHT:
                player->move(pressedKey);
                lanes[player->getLane() - offset].checkCollision(player->getPos());
                break;
            case Key::ESC:
                isStopped = true;
                break;
            default:
                break;
        }

        // Lane processing
        for (int i = 0; i < lanes.size(); i++) {
            if (i == player->getLane() - offset) {
                lanes[i].process(laneTime[i], prev, isGameover, player->getPos());
            }
            else lanes[i].process(laneTime[i], prev, isGameover);
        }

        if (player->getLane() - offset == 10) {
            updateLane();
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

void Play::createNewGame(const std::string& name) {
    // Score and offset
    score = 0;
    offset = 0;

    // Lanes
    lanes.clear();
    for (int i = 0; i < 20; i++) {
        float speed = rand() % (10000 + offset * offset * offset) / 1.0 * 100 + 1;
        lanes.push_back(Lane(0, speed, "asset/texture/lane"));
    }

    // Player
    player = new Player(0, 500, name, "asset/texture/player", "asset/sound/player");
}

void Play::updateLane() {
    // Update score
    score += 1000 + 1000 * offset / 10;

    // Update offset
    offset++;

    // Update lanes
    lanes.erase(lanes.begin());
    lanes.push_back(Lane(19 + offset, rand() % (10000 + offset * offset * offset) / 1.0 * 100 + 1, "asset/texture/lane"));
}

Play::~Play() {
    // this->audio->stopSound(this->buttonSound);
    delete player;
}