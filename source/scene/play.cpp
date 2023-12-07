#include "play.hpp"

Play::Play(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : 
    Scene(width, height, engine, speaker, registry, setting, keyboard),
    player(nullptr),
    lanes(),
    isGameover(false),
    score(0),
    offset(0),
    LANE_TEXTURES({new Texture("asset/texture/lane/grass.bmp"),
                   new Texture("asset/texture/lane/grassflower.bmp"),
                   new Texture("asset/texture/lane/grasspebble.bmp"),
                   new Texture("asset/texture/lane/road.bmp")
    }),
    PLAYER_TEXTURES({new Texture("asset/texture/sprite/" + setting->spriteObject() + "/up.bmp"),
                     new Texture("asset/texture/sprite/" + setting->spriteObject() + "/down.bmp"),
                     new Texture("asset/texture/sprite/" + setting->spriteObject() + "/left.bmp"),
                     new Texture("asset/texture/sprite/" + setting->spriteObject() + "/right.bmp")
    }),
    VEHICLE_TEXTURE({{Texture("asset/texture/car/blue/front.bmp"), Texture("asset/texture/car/blue/back.bmp")},
                     {Texture("asset/texture/car/orange/front.bmp"), Texture("asset/texture/car/orange/back.bmp")},
                     {Texture("asset/texture/truck/front.bmp"), Texture("asset/texture/truck/back.bmp")},
                     {Texture("asset/texture/ambulance/front.bmp"), Texture("asset/texture/ambulance/back.bmp")}
    }),
    TRAFFIC_TEXTURE(Texture("asset/texture/traffic/red.bmp"), Texture("asset/texture/traffic/green.bmp"))
    {
    }

Scene* Play::process() {
    bool isStopped = false;

    keyboard->refresh();
    Key pressedKey = keyboard->key();

    switch (pressedKey) {
        case Key::UP:
            player->move(pressedKey);
            score += 1000 * lanes[player->Y() - offset]->getSpeed() / lanes[player->Y() - offset]->getSpawn();
            isGameover |= lanes[player->Y() - offset]->collide(player->X());
            break;
        case Key::DOWN:
            if (player->Y() == offset) {
                isGameover = true;
                break;
            }
            player->move(pressedKey);
            score -= 333;
            isGameover |= lanes[player->Y() - offset]->collide(player->X());
            break;
        case Key::LEFT: case Key::RIGHT:
            if (player->X() == 0 || player->X() == engine->getWidth() - player->getWidth()) break;
            player->move(pressedKey);
            isGameover |= lanes[player->Y() - offset]->collide(player->X());
            break;
        case Key::ESC:
            isStopped |= true;
            break;
        default:
            break;
    }

    // Update process data
    if (player->Y() - offset > 10) {
        updateProcess();
    }

    // Lane processing
    if (isGameover) {
        for (auto lane : lanes) {
            lane->gameoverProcess(isStopped, player->X());
        }
    }
    else for (int i = 0; i < lanes.size(); i++) {
        if (i == player->Y() - offset) lanes[i]->process(isGameover, player->X());
        else lanes[i]->process(isGameover);
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
    // // Lane rendering
    // int minRenderPos = player->Y() - offset;
    // int maxRenderPos = minRenderPos + 19;

    // for (int i = maxRenderPos; i >= minRenderPos; i--) {
    //     lanes[i]->render(engine, player->Y());
    // }

    // // Player rendering
    // player->render();
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
    for (int i = 0; i < gamestate[1].size(); i += 17) {
        std::string tmpPos = "", tmpSpeed = "", tmpSpawn = "", tmpTraffic = "", tmpClock = "";
        
        for (int j = i; j < i + 4; j++) {
            tmpPos += gamestate[1][j];
        }
        
        for (int j = i + 4; j < i + 8; j++) {
            tmpSpeed += gamestate[1][j];
        }

        for (int j = i + 8; j < i + 12; j++) {
            tmpSpawn += gamestate[1][j];
        }

        tmpTraffic += gamestate[1][i + 12];

        for (int j = i + 13; j < i + 17; j++) {
            tmpClock += gamestate[1][j];
        }

        if (toFloat(tmpSpeed) == 0) {
            const Texture& GRASS = getGrassTexture();
            lanes.push_back(new Lane(GRASS, toInt(tmpPos), engine->getWidth() / GRASS.getWidth() * 2, toFloat(tmpSpeed), VEHICLE_TEXTURE, TRAFFIC_TEXTURE, toBool(tmpTraffic), toInt(tmpClock), toInt(tmpSpawn)));
        }
        else {
            lanes.push_back(new Lane(*LANE_TEXTURES[3], toInt(tmpPos), engine->getWidth() / LANE_TEXTURES[3]->getWidth() * 2, toFloat(tmpSpeed), VEHICLE_TEXTURE, TRAFFIC_TEXTURE, toBool(tmpTraffic), toInt(tmpClock), toInt(tmpSpawn)));
        }
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

        player = new Player(toInt(tmpLane) + offset, toFloat(tmpPos), tmpName, PLAYER_TEXTURES);
    }

    // Handle gamestate[3] : Vehicles
    for (int i = 0; i < gamestate[3].size(); i += 5) {
        std::string tmpLane = "", tmpPos = "";
        tmpLane += gamestate[3][i];
        for (int j = i + 1; j < i + 5; j++) {
            tmpPos += gamestate[3][j];
        }
        lanes[toInt(tmpLane) - offset]->addVehicle(toFloat(tmpPos));
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
    }

    // Handle gamestate[2] : Player
    gamestate.push_back(std::vector<char>());
    {
        std::vector<char> tmpLane = iToS((int)(player->Y() - offset), 1);
        std::vector<char> tmpPos = fToS(player->X(), 4);
        std::vector<char> tmpName;
        for (int i = 0; i < player->getName().size(); i++) {
            tmpName.push_back(player->getName()[i]);
        }
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
        std::vector<char> tmpLane = iToS(i, 1);
        std::vector<char> tmpGamestate = lanes[i]->getVehiclesGamestate();
        for (int j = 0; j < tmpGamestate.size(); j += 4) {
            gamestate[3].push_back(tmpLane[j]);
            for (int k = 0; k < 4; k++) {
                gamestate[3].push_back(tmpGamestate[j + k]);
            }
        }
    }

    return gamestate;
}

void Play::createNewGame(const std::string& name) {
    std::cout << "Creating new game" << std::endl;
    delete player;
    for (auto lane : lanes) {
        delete lane;
    }
    lanes.clear();

    // Score and offset
    score = 0;
    offset = 0;

    // Lanes initialization
    lanes.push_back(new Lane(*LANE_TEXTURES[0], 0 - offset, engine->getWidth() / LANE_TEXTURES[0]->getWidth() * 2, 0.0f, VEHICLE_TEXTURE, TRAFFIC_TEXTURE, false, 0, 120));
    for (int i = 1; i < 30; i++) {
        std::cout << "Creating lane " << i << std::endl;
        if (needCreateGrassLane()) {
            lanes.push_back(new Lane(getGrassTexture(), 0 - i - offset, engine->getWidth() / LANE_TEXTURES[0]->getWidth() * 2, 0.0f, VEHICLE_TEXTURE, TRAFFIC_TEXTURE, false, 0, rand() % 60 + 60));
        }
        else {
            lanes.push_back(new Lane(*LANE_TEXTURES[3], 0 - i - offset, engine->getWidth() / LANE_TEXTURES[0]->getWidth() * 2, rand() % (100 + offset * offset) / 1.0 * 100 + 1, VEHICLE_TEXTURE, TRAFFIC_TEXTURE, false, 0, rand() % 60 + 60));
        }
    }

    // Player
    player = new Player(0, engine->getWidth() / 2.0f, name, PLAYER_TEXTURES);
}

void Play::updateProcess() {
    // Update score
    score += 1000 * offset / 10;

    // Update offset
    offset++;

    // Update lanes
    if (!lanes.empty()) delete lanes.front();
    lanes.erase(lanes.begin());

    if (needCreateGrassLane()) lanes.push_back(new Lane(getGrassTexture(), 0 - 30 - offset, engine->getWidth() / LANE_TEXTURES[0]->getWidth() * 2, 0.0f, VEHICLE_TEXTURE, TRAFFIC_TEXTURE, false, 0, rand() % 60 + 60));
    else lanes.push_back(new Lane(*LANE_TEXTURES[3], 0 - 30 - offset, engine->getWidth() / LANE_TEXTURES[0]->getWidth() * 2, rand() % (100 + offset * offset) / 1.0 * 100 + 1, VEHICLE_TEXTURE, TRAFFIC_TEXTURE, false, 0, rand() % 60 + 60));
}

bool Play::needCreateGrassLane() const {
    return rand() % 100 < (50 - offset / 2);
}

const Texture& Play::getGrassTexture() const {
    return *LANE_TEXTURES[rand() % 3];
}

Play::~Play() {
    // this->audio->stopSound(this->buttonSound);
    delete player;
    for (auto lane : lanes) {
        delete lane;
    }
    for (auto texture : LANE_TEXTURES) {
        delete texture;
    }
    for (auto texture : PLAYER_TEXTURES) {
        delete texture;
    }
}