#include "play.hpp"

Play::Play(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : 
    Scene(engine, speaker, registry, setting, keyboard, holder),
    GRASS({Texture("asset/texture/lane/grass.bmp"),
                   Texture("asset/texture/lane/grassflower.bmp"),
                   Texture("asset/texture/lane/grasspebble.bmp")
    }),
    ROAD(Texture("asset/texture/lane/road.bmp")),
    PLAYER_UP(Texture("asset/texture/sprite/" + setting->spriteObject() + "/up.bmp")),
    PLAYER_DOWN(Texture("asset/texture/sprite/" + setting->spriteObject() + "/down.bmp")),
    PLAYER_LEFT(Texture("asset/texture/sprite/" + setting->spriteObject() + "/left.bmp")),
    PLAYER_RIGHT(Texture("asset/texture/sprite/" + setting->spriteObject() + "/right.bmp")),
    VEHICLE_FRONT({
        Texture("asset/texture/car/blue/front.bmp"),
        Texture("asset/texture/car/orange/front.bmp"),
        Texture("asset/texture/truck/front.bmp"),
        Texture("asset/texture/ambulance/front.bmp")
    }),
    VEHICLE_BACK({
        Texture("asset/texture/car/blue/back.bmp"),
        Texture("asset/texture/car/orange/back.bmp"),
        Texture("asset/texture/truck/back.bmp"),
        Texture("asset/texture/ambulance/back.bmp")
    }),
    TRAFFIC({Texture("asset/texture/traffic/red.bmp"), Texture("asset/texture/traffic/green.bmp")}),
    player(PLAYER_UP, PLAYER_DOWN, PLAYER_LEFT, PLAYER_RIGHT, {ROAD.getWidth() * 1.0f, ROAD.getHeight() * 0.95f}, {engine->getWidth() / 2.0f, engine->getHeight() - ROAD.getWidth() / 2.0f}),
    score(0),
    offset(0)
    {
        // Load gamestate
        if (!setting->getGamestate().empty()) loadGamestate(setting->getGamestate());
        else createNewGame();
    }

Scene* Play::process() {

    bool isStopped = false;
    Key pressedKey = keyboard->key();

    switch (pressedKey) {
    //     case Key::UP:
    //         player->move(pressedKey);
    //         score += 1000 * lanes[player->Y() - offset]->getSpeed() / lanes[player->Y() - offset]->getSpawn();
    //         isGameover |= lanes[player->Y() - offset]->collide(player->X());
    //         break;
    //     case Key::DOWN:
    //         if (player->Y() == offset) {
    //             isGameover = true;
    //             break;
    //         }
    //         player->move(pressedKey);
    //         score -= 333;
    //         isGameover |= lanes[player->Y() - offset]->collide(player->X());
    //         break;
    //     case Key::LEFT: case Key::RIGHT:
    //         if (player->X() == 0 || player->X() == engine->getWidth() - player->getWidth()) break;
    //         player->move(pressedKey);
    //         isGameover |= lanes[player->Y() - offset]->collide(player->X());
    //         break;
        case Key::ESC:
            return sceneRegistry->scene(SceneID::MENU);
            break;
        default:
            break;
    }

    // // Update process data
    // if (player->Y() - offset > 10) {
    //     updateProcess();
    // }

    // // Lane processing
    // if (isGameover) {
    //     for (auto lane : lanes) {
    //         lane->gameoverProcess(isStopped, player->X());
    //     }
    // }
    // else for (int i = 0; i < lanes.size(); i++) {
    //     if (i == player->Y() - offset) lanes[i]->process(isGameover, player->X());
    //     else lanes[i]->process(isGameover);
    // }

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
    // Lane rendering
    int minRenderPos = player.Y() - offset;
    int maxRenderPos = minRenderPos + 19;

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
            const Texture& GRASS = randomGrass();
            lanes.push_back(new Lane(GRASS, toInt(tmpPos), engine->getWidth() / GRASS.getWidth(), toFloat(tmpSpeed),
                {{VEHICLE_FRONT[0], VEHICLE_BACK[0]}, {VEHICLE_FRONT[1], VEHICLE_BACK[1]}, {VEHICLE_FRONT[2], VEHICLE_BACK[2]}, {VEHICLE_FRONT[3], VEHICLE_BACK[3]}},
                {TRAFFIC[0], TRAFFIC[1]}, toBool(tmpTraffic), toInt(tmpClock)));
        }
        else {
            lanes.push_back(new Lane(ROAD, toInt(tmpPos), engine->getWidth() / ROAD.getWidth(), toFloat(tmpSpeed),
                {{VEHICLE_FRONT[0], VEHICLE_BACK[0]}, {VEHICLE_FRONT[1], VEHICLE_BACK[1]}, {VEHICLE_FRONT[2], VEHICLE_BACK[2]}, {VEHICLE_FRONT[3], VEHICLE_BACK[3]}},
                {TRAFFIC[0], TRAFFIC[1]}, toBool(tmpTraffic), toInt(tmpClock)));

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

        player = new Player(PLAYER_UP, PLAYER_DOWN, PLAYER_LEFT, PLAYER_RIGHT, {ROAD.getWidth() * 1.0f, ROAD.getHeight() * 0.95f}, {toInt(tmpLane) + offset, toFloat(tmpPos)});
            toInt(tmpLane) + offset, toFloat(tmpPos), tmpName, PLAYER_TEXTURES);
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

void Play::createNewGame() {
    // Create lanes
    for (int i = 0; i < 20; i++) {
        if (needCreateGrassLane()) lanes.push_back(new Lane(getGrassTexture(), 0 - 30 - offset, engine->getWidth() / LANE_TEXTURES[0].getWidth(), 0.0f, VEHICLE_TEXTURE, TRAFFIC));
        else lanes.push_back(new Lane(LANE_TEXTURES[3], 0 - 30 - offset, engine->getWidth() / LANE_TEXTURES[0].getWidth(), rand() % (100 + offset * offset) / 1.0 * 100 + 1, VEHICLE_TEXTURE, TRAFFIC));
    }
}

void Play::updateProcess() {
    // Update score
    score += 1000 * offset / 10;

    // Update offset
    offset++;

    // Update lanes
    if (!lanes.empty()) delete lanes.front();
    lanes.erase(lanes.begin());

    if (needCreateGrassLane()) lanes.push_back(new Lane(getGrassTexture(), 0 - 30 - offset, engine->getWidth() / GRASS[0]->getWidth(), 0.0f, VEHICLE_TEXTURE, TRAFFIC));
    else lanes.push_back(new Lane(*LANE_TEXTURES[3], 0 - 30 - offset, engine->getWidth() / LANE_TEXTURES[0]->getWidth(), rand() % (100 + offset * offset) / 1.0 * 100 + 1, VEHICLE_TEXTURE, TRAFFIC));
}

bool Play::needCreateGrassLane() const {
    return rand() % 100 < (50 - offset / 2);
}

const Texture& Play::randomGrass() const {
    return GRASS[rand() % 3];
}

Play::~Play() {

}