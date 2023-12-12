#include "play.hpp"

Play::Play(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : 
    Scene(engine, speaker, registry, setting, keyboard, holder),
    player(holder, {holder->get("ROAD")->getWidth() * 1.0f, holder->get("ROAD")->getHeight() * 0.95f}, {engine->getWidth() / 2.0f, engine->getHeight() - holder->get("ROAD")->getWidth() / 2.0f}, setting),
    score(0),
    offset(0),
    gridSize({holder->get("GRASS")->getWidth() * 1.0f, holder->get("GRASS")->getHeight() * 0.95f}),
    isGameover(false)
    {
        // Load gamestate
        // if (!setting->getGamestate().empty()) loadGamestate(setting->getGamestate());
        // else createNewGame();
    }

Scene* Play::process() {

    bool isStopped = false;
    Key pressedKey = keyboard->key();

    switch (pressedKey) {
        case Key::UP:
            player.move(pressedKey);
            score += 1000 * lanes[player.position().y - offset]->getSpeed() / lanes[player.position().y - offset]->getSpawn();
            isGameover |= lanes[player.position().y - offset]->collide(player.position().x);
            break;
        case Key::DOWN:
            if (player.position().y == offset) {
                isGameover = true;
                break;
            }
            player.move(pressedKey);
            score -= 333;
            isGameover |= lanes[player.position().y - offset]->collide(player.position().x);
            break;
        case Key::LEFT: case Key::RIGHT:
            if (player.position().x == 0 || player.position().x == engine->getWidth() - player.size().x) break;
            player.move(pressedKey);
            isGameover |= lanes[player.position().y - offset]->collide(player.position().x);
            break;
        case Key::ESC:
            isStopped = true;
            break;
        default:
            break;
    }

    // Update process data
    if (player.position().y - offset > 10) {
        updateProcess();
    }

    // Lane processing
    if (isGameover) {
        lanes[player.position().y - offset]->gameoverProcess();
        isStopped |= lanes[player.position().y - offset]->collide(player.position().x);
    }
    else for (int i = 0; i < lanes.size(); i++) {
        if (i == player.position().y - offset) {
            lanes[i]->process();
            isGameover |= lanes[i]->collide(player.position().x);
        }
        else {
            lanes[i]->process();
        }
    }

    // Return next scene
    Scene* next = this;
    if (isGameover && isStopped) {
        next = sceneRegistry->scene(SceneID::GAMEOVER);
    }
    else if (isStopped) {
        next = sceneRegistry->scene(SceneID::PAUSE);
    }

    return next;
}

void Play::render() {
    // Background fill
    engine->fill(0, 162, 232);

    // Lane rendering
    int minRenderPos = player.position().y - offset - 5;
    minRenderPos = minRenderPos < 0 ? 0 : minRenderPos;
    int maxRenderPos = minRenderPos + lanes.size() - 11;

    for (int i = maxRenderPos; i >= minRenderPos; i--) {
        lanes[i]->render(engine);
    }

    // Player rendering
    player.render(engine);
}

void Play::playsound() {
    // this->audio->playSound(this->buttonSound);
}

void Play::loadGamestate(const std::vector<std::vector<char>>& gamestate) {
    auto toInt = [](std::vector<char> str) -> int {
        // return *reinterpret_cast<int*>(&str[0]);
        int num = 0;
        for (int i = 0; i < str.size(); i++) {
            num += str[i] << (8 * i);
        }
        return num;
    };

    auto toFloat = [](std::vector<char> str) -> float {
        // return *reinterpret_cast<float*>(&str[0]);
        int num = 0;
        for (int i = 0; i < str.size(); i++) {
            num += str[i] << (8 * i);
        }
        return *reinterpret_cast<float*>(&num);
    };

    auto toBool = [](std::vector<char> str) -> bool {
        // return *reinterpret_cast<bool*>(&str[0]);
        return *reinterpret_cast<bool*>(&str[0]);
    };

    // Handle gamestate[0] : Score and offset
    {
        std::vector<char> tmpScore, tmpOffset;
        for (int i = 0; i < 4; i++) {
            // tmpScore += gamestate[0][i];
            tmpScore.push_back(gamestate[0][i]);
            // tmpOffset += gamestate[0][i + 4];
            tmpOffset.push_back(gamestate[0][i + 4]);
        }

        score = toInt(tmpScore);
        offset = toInt(tmpOffset);
    }

    // Handle gamestate[1] : lanes
    for (int i = 0; i < gamestate[1].size(); i += 17) {
        std::vector<char> tmpPos, tmpSpeed, tmpSpawn, tmpTraffic, tmpClock;
        
        for (int j = i; j < i + 4; j++) {
            // tmpPos += gamestate[1][j];
            tmpPos.push_back(gamestate[1][j]);
        }
        
        for (int j = i + 4; j < i + 8; j++) {
            // tmpSpeed += gamestate[1][j];
            tmpSpeed.push_back(gamestate[1][j]);
        }

        for (int j = i + 8; j < i + 12; j++) {
            // tmpSpawn += gamestate[1][j];
            tmpSpawn.push_back(gamestate[1][j]);
        }

        // tmpTraffic += gamestate[1][i + 12];
        tmpTraffic.push_back(gamestate[1][i + 12]);

        for (int j = i + 13; j < i + 17; j++) {
            // tmpClock += gamestate[1][j];
            tmpClock.push_back(gamestate[1][j]);
        }

        if (toFloat(tmpSpeed) == 0) {
            lanes.push_back(new Lane(holder, gridSize, toInt(tmpPos), engine->getWidth() / holder->get("GRASS")->getWidth() * 2 + 5, toFloat(tmpSpeed), toInt(tmpSpawn), toBool(tmpTraffic), toInt(tmpClock)));
        }
        else {
            lanes.push_back(new Lane(holder, gridSize, toInt(tmpPos), engine->getWidth() / holder->get("ROAD")->getWidth() * 2 + 5, toFloat(tmpSpeed), toInt(tmpSpawn), toBool(tmpTraffic), toInt(tmpClock)));

        }
    }

    // Handle gamestate[2] : Player
    {
        std::vector<char> tmpLane, tmpPos, tmpName;
        // tmpLane += gamestate[2][0];
        tmpLane.push_back(gamestate[2][0]);
        for (int i = 1; i < 5; i++) {
            // tmpPos += gamestate[2][i];
            tmpPos.push_back(gamestate[2][i]);
        }
        // for (int i = 5; i < gamestate[2].size(); i++) {
        //     // tmpName += gamestate[2][i];
        //     tmpName.push_back(gamestate[2][i]);
        // }

        player = Player(holder, {holder->get("ROAD")->getWidth() * 1.0f, holder->get("ROAD")->getHeight() * 0.95f}, {toFloat(tmpPos), float(toInt(tmpLane) + offset)}, setting);
            // toInt(tmpLane) + offset, toFloat(tmpPos), tmpName, PLAYER_TEXTURES);
    }

    // Handle gamestate[3] : Vehicles
    for (int i = 0; i < gamestate[3].size(); i += 5) {
        std::vector<char> tmpLane, tmpPos;
        // tmpLane += gamestate[3][i];
        tmpLane.push_back(gamestate[3][i]);
        for (int j = i + 1; j < i + 5; j++) {
            // tmpPos += gamestate[3][j];
            tmpPos.push_back(gamestate[3][j]);
        }
        lanes[toInt(tmpLane)]->addVehicle(toFloat(tmpPos));
    }
}

std::vector<std::vector<char>> Play::createGamestate() const {
    auto iToS = [](int num, int strSize) -> std::vector<char> {
        std::vector<char> str;
        str.clear();
        for (int i = 0; i < strSize; i++) {
            str.push_back(*reinterpret_cast<char*>(&num));
            num >>= 8;
        }
        return str;
    };

    
    // auto toInt = [](std::vector<char> str) -> int {
    //     // return *reinterpret_cast<int*>(&str[0]);
    //     int num = 0;
    //     for (int i = 0; i < str.size(); i++) {
    //         num += str[i] << (8 * i);
    //     }
    //     return num;
    // };

    auto fToS = [&](float num, int strSize) -> std::vector<char> {
        return iToS(*reinterpret_cast<int*>(&num), strSize);
    };

    auto bToS = [](bool num) -> std::vector<char> {
        std::vector<char> str;
        str.clear();
        str.push_back(*reinterpret_cast<char*>(&num));
        return str;
    };

    std::vector<std::vector<char>> gamestate;

    // Handle gamestate[0] : Score and offset
    gamestate.push_back(std::vector<char>());
    {
        std::vector<char> tmpScore = iToS(score, 4);
        std::vector<char> tmpOffset = iToS(offset, 4);
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
        std::vector<char> tmpPos = iToS(lanes[i]->Y(), 4);
        std::vector<char> tmpSpeed = fToS(lanes[i]->getSpeed(), 4);
        std::vector<char> tmpSpawn = iToS(lanes[i]->getSpawn(), 4);
        std::vector<char> tmpTraffic = lanes[i]->getTrafficGamestate();
        for (int j = 0; j < tmpPos.size(); j++) {
            gamestate[1].push_back(tmpPos[j]);
        }
        for (int j = 0; j < tmpSpeed.size(); j++) {
            gamestate[1].push_back(tmpSpeed[j]);
        }
        for (int j = 0; j < tmpSpawn.size(); j++) {
            gamestate[1].push_back(tmpSpawn[j]);
        }
        for (int j = 0; j < tmpTraffic.size(); j++) {
            gamestate[1].push_back(tmpTraffic[j]);
        }
    }

    // Handle gamestate[2] : Player
    gamestate.push_back(std::vector<char>());
    {
        std::vector<char> tmpLane = iToS((int)(player.position().y - offset), 1);
        std::vector<char> tmpPos = fToS(player.position().x, 4);
        // std::vector<char> tmpName;
        // for (int i = 0; i < player.getName().size(); i++) {
        //     tmpName.push_back(player.getName()[i]);
        // }
        gamestate[2].push_back(tmpLane[0]);
        for (int i = 0; i < 4; i++) {
            gamestate[2].push_back(tmpPos[i]);
        }
        // for (int i = 0; i < tmpName.size(); i++) {
        //     gamestate[2].push_back(tmpName[i]);
        // }
    }
    
    // Handle gamestate[3] : Vehicles
    gamestate.push_back(std::vector<char>());
    for (int i = 0; i < lanes.size(); i++) {
        std::vector<char> tmpLane = iToS(i, 1);
        std::vector<char> tmpGamestate = lanes[i]->getVehiclesGamestate();
        for (int j = 0; j < tmpGamestate.size(); j += 4) {
            gamestate[3].push_back(tmpLane[0]);
            for (int k = 0; k < 4; k++) {
                gamestate[3].push_back(tmpGamestate[j + k]);
            }
        }
    }

    return gamestate;
}

void Play::createNewGame() {
    // Create lanes
    for (int i = 0; i < 6; i++) {
        lanes.push_back(new Lane(holder, gridSize, 0 - i - offset, engine->getWidth() / holder->get("GRASS")->getWidth() * 2 + 5, 0.0f));
    }

    for (int i = 6; i < engine->getWidth() / holder->get("ROAD")->getWidth() + engine->getHeight() / holder->get("ROAD")->getHeight() * 2 + 11; i++) {
        if (needCreateGrassLane()) lanes.push_back(new Lane(holder, gridSize, 0 - i - offset, engine->getWidth() / holder->get("GRASS")->getWidth() * 2 + 5, 0.0f));
        else lanes.push_back(new Lane(holder, gridSize, 0 - i - offset, engine->getWidth() / holder->get("ROAD")->getWidth() * 2 + 5, rand() % (100 + offset * offset) / 1.0 * 100 + 1));
    }

    // Create player
    player = Player(holder, {holder->get("ROAD")->getWidth() * 1.0f, holder->get("ROAD")->getHeight() * 0.95f}, {engine->getWidth() / 2.0f, 5.0f}, setting);
}

void Play::updateProcess() {
    // Update score
    score += 1000 * offset / 10;

    // Update offset
    offset++;

    // Update lanes
    if (!lanes.empty()) delete lanes.front();
    lanes.erase(lanes.begin());

    int numOfLanes = engine->getWidth() / holder->get("ROAD")->getWidth() + engine->getHeight() / holder->get("ROAD")->getHeight() * 2 + 10;

    if (needCreateGrassLane()) lanes.push_back(new Lane(holder, gridSize, 0 - numOfLanes - offset, engine->getWidth() / holder->get("GRASS")->getWidth() * 2 + 5, 0.0f));
    else lanes.push_back(new Lane(holder, gridSize, 0 - numOfLanes - offset, engine->getWidth() / holder->get("ROAD")->getWidth() * 2 + 5, rand() % (100 + offset * offset) / 1.0 * 100 + 1));
}

bool Play::needCreateGrassLane() const {
    return rand() % 100 < (35 - offset / 2 < 35 ? offset / 2 : 35);
}

Play::~Play() {
    for (auto lane : lanes) {
        delete lane;
    }
    lanes.clear();
}