#include "play.hpp"

Play::Play(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, speaker, registry, setting, keyboard),
    GRASS1("asset/texture/lane/grass.bmp"),
    GRASS2("asset/texture/lane/grassflower.bmp"),
    GRASS3("asset/texture/lane/grasspebble.bmp"),
    ROAD("asset/texture/lane/road.bmp"),
    PLAYER_UP("asset/texture/sprite/" + setting->spriteObject() + "/up.bmp"),
    PLAYER_DOWN("asset/texture/sprite/" + setting->spriteObject() + "/down.bmp"),
    PLAYER_LEFT("asset/texture/sprite/" + setting->spriteObject() + "/left.bmp"),
    PLAYER_RIGHT("asset/texture/sprite/" + setting->spriteObject() + "/right.bmp")
    {
        // Load gamestate
        if (!setting->getGamestate().empty()) loadGamestate(setting->getGamestate());
        else createNewGame("");
    }

Scene* Play::process() {

    bool isGameover = false;
    bool isStopped = false;
    bool isRunning = true;

    high_resolution_clock::time_point prev = high_resolution_clock::now();
    high_resolution_clock::time_point prevSpawn = prev;

    std::vector<int> laneTime(lanes.size());

    do {
        high_resolution_clock::time_point now = high_resolution_clock::now();
        uint64_t elapsed = duration_cast<nanoseconds>(now - prev).count();
        if (elapsed < duration_cast<nanoseconds>(seconds(1)).count() / engine->fps()) continue;

        if (prevSpawn.time_since_epoch().count() == 0 || prevSpawn == prev) {
            for (int i = 0; i < lanes.size(); i++) {
                laneTime[i] == rand() % 1500 + 500;
            }
            prevSpawn = now;
        }

        keyboard->refresh();
        Key pressedKey = keyboard->key();

        switch (pressedKey) {
            case Key::UP:
                player->move(pressedKey);
                score += 20000 / laneTime[player->Y() - offset];
                lanes[player->Y() - offset]->checkCollision(player->X());
                break;
            case Key::DOWN:
                if (player->Y() == offset) {
                    isGameover = true;
                    break;
                }
                player->move(pressedKey);
                score -= 333;
                lanes[player->Y() - offset]->checkCollision(player->X());
                break;
            case Key::LEFT: case Key::RIGHT:
                player->move(pressedKey);
                lanes[player->Y() - offset]->checkCollision(player->X());
                break;
            case Key::ESC:
                isStopped = true;
                break;
            default:
                break;
        }

        // Update process data
        if (player->getLane() - offset > 10) {
            updateProcess();
        }

        // Lane processing
        for (int i = 0; i < lanes.size(); i++) {
            if (i == player->Y() - offset) lanes[i]->process(laneTime[i], prevSpawn, isGameover, player->X());
            else lanes[i]->process(laneTime[i], prevSpawn, isGameover);
        }

        // Lane rendering
        int minRenderPos = player->Y() - offset;
        int maxRenderPos = minRenderPos + 19;

        for (int i = maxRenderPos; i >= minRenderPos; i--) {
            lanes[i]->render(offset, player->Y());
        }

        // Player rendering
        player->render();

        prev = now;
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

void Play::loadGamestate(const std::vector<std::vector<char>>& gamestate) {
    auto toInt = [](std::string str) -> int {
        return *reinterpret_cast<int*>(&str[0]);
    };

    auto toFloat = [](std::string str) -> float {
        return *reinterpret_cast<float*>(&str[0]);
    };

    auto toBool = [](std::string str) -> bool {
        return *reinterpret_cast<bool*>(&str[0]);
    };

    // Handle gamestate[0] : Score and offset
    {
        std::string tmpScore = "", tmpOffset = "";
        for (int i = 0; i < 4; i++) {
            tmpScore += gamestate[0][i];
            tmpOffset += gamestate[0][i + 4];
        }

        score = toInt(tmpScore);
        offset = toInt(tmpOffset);
    }

    // Handle gamestate[1] : lanes
    for (int i = 0; i < gamestate[1].size(); i += 9) {
        std::string tmpPos = "", tmpSpeed = "", tmpTraffic = "";
        
        for (int j = i; j < i + 4; j++) {
            tmpPos += gamestate[1][j];
        }
        
        for (int j = i + 4; j < i + 8; j++) {
            tmpSpeed += gamestate[1][j];
        }

        tmpTraffic += gamestate[1][i + 8];

        if (toFloat(tmpSpeed) == 0) lanes.push_back(new Lane(toInt(tmpPos), toFloat(tmpSpeed), toBool(tmpTraffic), getGrassTexture()));
        else lanes.push_back(new Lane(toInt(tmpPos), toFloat(tmpSpeed), toBool(tmpTraffic), ROAD));
    }

    // Handle gamestate[2] : Player
    {
        std::string tmpLane = "", tmpPos = "", tmpName = "";
        tmpLane += gamestate[2][0];
        for (int i = 1; i < 5; i++) {
            tmpPos += gamestate[2][i];
        }
        for (int i = 5; i < gamestate[2].size(); i++) {
            tmpName += gamestate[2][i];
        }

        player = new Player(toInt(tmpLane) + offset, toFloat(tmpPos), tmpName, PLAYER_UP, PLAYER_DOWN, PLAYER_LEFT, PLAYER_RIGHT, "");
    }

    // Handle gamestate[3] : Vehicles
    for (int i = 0; i < gamestate[3].size(); i += 9) {
        std::string tmpLane = "", tmpPos = "";
        tmpLane += gamestate[3][i];
        for (int j = i + 1; j < i + 9; j++) {
            tmpPos += gamestate[3][j];
        }
        lanes[toInt(tmpLane) - offset]->addVehicle(toFloat(tmpPos), "asset/sound/");
    }
}

std::vector<std::vector<char>> Play::createGamestate() const {
    auto iToS = [](int num, int strSize) -> std::string {
        std::string str = "";
        for (int i = 0; i < strSize; i++) {
            str += *reinterpret_cast<char*>(&num);
            num >>= 8;
        }
        return str;
    };

    auto fToS = [&](float num, int strSize) -> std::string {
        return iToS(*reinterpret_cast<int*>(&num), strSize);
    };

    auto bToS = [](bool num) -> std::string {
        return *reinterpret_cast<std::string*>(&num);
    };

    std::vector<std::vector<char>> gamestate;

    // Handle gamestate[0] : Score and offset
    gamestate.push_back(std::vector<char>());
    {
        std::string tmpScore = iToS(score, 4);
        std::string tmpOffset = iToS(offset, 4);
        for (int i = 0; i < 4; i++) {
            gamestate[0].push_back(tmpScore[i]);
        }
        for (int i = 0; i < 4; i++) {
            gamestate[0].push_back(tmpOffset[i]);
        }
    }

    // Handle gamestate[1] : lanes
    gamestate.push_back(std::vector<char>());
    for (int i = 0; i < lanes.size(); i++) {
        std::string tmpPos = iToS(lanes[i]->Y(), 4);
        std::string tmpSpeed = fToS(lanes[i]->getSpeed(), 4);
        std::string tmpTraffic = bToS(lanes[i]->getTrafficState());
        for (int j = 0; j < 4; j++) {
            gamestate[1].push_back(tmpPos[j]);
        }
        for (int j = 0; j < 4; j++) {
            gamestate[1].push_back(tmpSpeed[j]);
        }
        gamestate[1].push_back(tmpTraffic[0]);
    }

    // Handle gamestate[2] : Player
    gamestate.push_back(std::vector<char>());
    {
        std::string tmpLane = iToS((int)(player->Y() - offset), 1);
        std::string tmpPos = fToS(player->X(), 4);
        std::string tmpName = player->getName();
        gamestate[2].push_back(tmpLane[0]);
        for (int i = 0; i < 4; i++) {
            gamestate[2].push_back(tmpPos[i]);
        }
        for (int i = 0; i < tmpName.size(); i++) {
            gamestate[2].push_back(tmpName[i]);
        }
    }
    
    // Handle gamestate[3] : Vehicles
    gamestate.push_back(std::vector<char>());
    for (int i = 0; i < lanes.size(); i++) {
        std::string tmpLane = iToS(i, 1);
        std::vector<char> tmpGamestate = lanes[i]->getVehiclesGamestate();
        for (int j = 0; j < tmpGamestate.size(); j++) {
            gamestate[3].push_back(tmpGamestate[j]);
        }
    }

    return gamestate;
}

void Play::createNewGame(const std::string& name) {
    // Score and offset
    score = 0;
    offset = 0;

    // Lanes initialization
    lanes.push_back(new Lane(0, 0, GRASS1));
    for (int i = 1; i < 30; i++) {
        if (needCreateGrassLane()) {
            lanes.push_back(new Lane(0 - i - offset, 0, getGrassTexture()));
        }
        else lanes.push_back(new Lane(0 - i - offset, rand() % (100 + offset * offset) / 1.0 * 100 + 1, ROAD));
    }

    // Player
    player = new Player(0, 500, name, PLAYER_UP, PLAYER_DOWN, PLAYER_LEFT, PLAYER_RIGHT, "");
}

void Play::updateProcess() {
    // Update score
    score += 1000 * offset / 10;

    // Update offset
    offset++;

    // Update lanes
    if (!lanes.empty()) delete lanes.front();
    lanes.erase(lanes.begin());
    lanes.push_back(new Lane(0 - 30 - offset, rand() % (100 + offset * offset) / 1.0 * 100 + 1, ROAD));
}

bool Play::needCreateGrassLane() const {
    return rand() % 100 < (50 - offset / 2);
}

const Texture& Play::getGrassTexture() const {
    switch (rand() % 3) {
        case 0:
            return GRASS1;
        case 1:
            return GRASS2;
        case 2:
            return GRASS3;
        default:
            return GRASS1;
    }
}

Play::~Play() {
    // this->audio->stopSound(this->buttonSound);
    delete player;
    for (auto lane : lanes) {
        delete lane;
    }
}