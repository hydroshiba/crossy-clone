#include "play.hpp"

Play::Play(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : Scene(engine, speaker, registry, setting, keyboard, holder),
                                                                                                                                     gridSize({holder->get("GRASS")->getWidth() * 1.0f, holder->get("GRASS")->getHeight() * 0.95f}),
                                                                                                                                     score(0),
                                                                                                                                     scoreBox(holder, std::to_string(score), 0, 0),
                                                                                                                                     offset(0),
                                                                                                                                     frames(0),
                                                                                                                                     player(holder, gridSize, {engine->getWidth() / 2.0f, engine->getHeight() - holder->get("ROAD")->getWidth() / 2.0f}, setting),
                                                                                                                                     background("asset/sound/background.wav", true),
                                                                                                                                     car_crash("asset/sound/sfx/car-crash.wav"),
                                                                                                                                     car_honk("asset/sound/sfx/car-honk.wav"),
                                                                                                                                     step_grass("asset/sound/sfx/step-grass-1.wav"),
                                                                                                                                     step_grass_2("asset/sound/sfx/step-grass-2.wav"),
                                                                                                                                     step_road("asset/sound/sfx/road-step.wav"),
                                                                                                                                     ambulance("asset/sound/sfx/ambulance.wav"),
                                                                                                                                     isGameover(false) {}

Scene* Play::process() {
    if(isGameover) {
        lanes[player.position().y - offset]->gameoverProcess();
        if(lanes[player.position().y - offset]->collide(&player)) {
            // speaker->pause(ambulance);
            speaker->stopSFX();
            dynamic_cast<Gameover*>(sceneRegistry->scene(SceneID::GAMEOVER))->setScore(word(score));
            return sceneRegistry->scene(SceneID::GAMEOVER);
        } else
            return this;
    }

    ++frames;
    if(frames >= 120) frames = 0;

    Key key = keyboard->key();
    if(key == Key::ESC) {
        return sceneRegistry->scene(SceneID::PAUSE);
    }

    if(key == Key::DOWN && player.position().y == offset) {
        isGameover = true;
        return this;
    }

    player.move(key);
    if(key != Key::DEFAULT) {
        if(lanes[player.position().y - offset]->getSpeed() == 0) {
            if(random(0, 1)) {
                speaker->stopSFX();
                speaker->play(step_grass);
            } else {
                speaker->stopSFX();
                speaker->play(step_grass_2);
            }
        } else {
            speaker->stopSFX();
            speaker->play(step_road);
        }
    }

    if(lanes[player.position().y - offset]->collide(&player)) {
        isGameover = true;
        speaker->pause(background);
        speaker->stopSFX();
        speaker->play(car_crash);
        speaker->play(ambulance);
        return this;
    }

    // Update process data
    if(player.position().y - offset > 10) {
        updateProcess();
    }

    for(int i = 0; i < lanes.size(); i++) {
        lanes[i]->process();
    }
    if(lanes[player.position().y - offset]->getSpeed() != 0 && frames == random(60, 120)) lanes[player.position().y - offset]->playsound(speaker, car_honk);

    return this;
}

void Play::render() {
    // Background fill
    // engine->fill(0, 162, 232);

    // Lane and player rendering
    int minRenderPos = player.position().y - offset - 10;
    minRenderPos = minRenderPos < 0 ? 0 : minRenderPos;
    int maxRenderPos = minRenderPos + lanes.size() - 8;

    for(int i = maxRenderPos; i >= minRenderPos; i--) {
        if(i == player.position().y - offset) {
            lanes[i]->render(engine, player.position().y);
            player.render(engine, engine->getHeight() / holder->get("ROAD")->getHeight() * 2.0f + 3);
        } else
            lanes[i]->render(engine, player.position().y);
    }

    // Score rendering
    scoreBox.setText(std::to_string(score), holder->get("S")->getHeight() * 2 / 3, holder->get("S")->getHeight() * 2 / 3);
    scoreBox.render(engine);
}

void Play::playsound() {
    // this->audio->playSound(this->buttonSound);
}

void Play::loadGamestate(const std::vector<std::vector<byte>>& gamestate) {
    auto toInt = [](std::vector<byte> str) -> int {
        // return *reinterpret_cast<int*>(&str[0]);
        int num = 0;
        for(int i = 0; i < str.size(); i++) {
            num += str[i] << (8 * i);
        }
        return num;
    };

    auto toFloat = [](std::vector<byte> str) -> float {
        // return *reinterpret_cast<float*>(&str[0]);
        int num = 0;
        for(int i = 0; i < str.size(); i++) {
            num += str[i] << (8 * i);
        }
        return *reinterpret_cast<float*>(&num);
    };

    auto toBool = [](std::vector<byte> str) -> bool {
        // return *reinterpret_cast<bool*>(&str[0]);
        return *reinterpret_cast<bool*>(&str[0]);
    };

    // Clear old data
    for(auto lane : lanes) {
        delete lane;
    }
    lanes.clear();
    score = 0;
    offset = 0;
    isGameover = false;

    // Handle gamestate[0] : Score and offset
    {
        std::vector<byte> tmpScore, tmpOffset;
        for(int i = 0; i < 4; i++) {
            // tmpScore += gamestate[0][i];
            tmpScore.push_back(gamestate[0][i]);
            // tmpOffset += gamestate[0][i + 4];
            tmpOffset.push_back(gamestate[0][i + 4]);
        }

        score = toInt(tmpScore);
        offset = toInt(tmpOffset);
    }

    // Handle gamestate[1] : lanes
    for(int i = 0; i < gamestate[1].size(); i += 17) {
        std::vector<byte> tmpPos, tmpSpeed, tmpSpawn, tmpTraffic, tmpClock;

        for(int j = i; j < i + 4; j++) {
            // tmpPos += gamestate[1][j];
            tmpPos.push_back(gamestate[1][j]);
        }

        for(int j = i + 4; j < i + 8; j++) {
            // tmpSpeed += gamestate[1][j];
            tmpSpeed.push_back(gamestate[1][j]);
        }

        for(int j = i + 8; j < i + 12; j++) {
            // tmpSpawn += gamestate[1][j];
            tmpSpawn.push_back(gamestate[1][j]);
        }

        // tmpTraffic += gamestate[1][i + 12];
        tmpTraffic.push_back(gamestate[1][i + 12]);

        for(int j = i + 13; j < i + 17; j++) {
            // tmpClock += gamestate[1][j];
            tmpClock.push_back(gamestate[1][j]);
        }

        if(toFloat(tmpSpeed) == 0) {
            lanes.push_back(new Lane(holder, gridSize, toInt(tmpPos), engine->getHeight() / holder->get("GRASS")->getHeight() * 4.0f + 3.0f / (engine->getWidth() / engine->getHeight() * 1.0f), toFloat(tmpSpeed), toInt(tmpSpawn), toBool(tmpTraffic), toInt(tmpClock)));
        } else {
            lanes.push_back(new Lane(holder, gridSize, toInt(tmpPos), engine->getHeight() / holder->get("ROAD")->getHeight() * 4.0f + 3.0f / (engine->getWidth() / engine->getHeight() * 1.0f), toFloat(tmpSpeed), toInt(tmpSpawn), toBool(tmpTraffic), toInt(tmpClock)));
        }
    }

    // Handle gamestate[2] : Player
    {
        std::vector<byte> tmpLane, tmpPos, tmpName;
        // tmpLane += gamestate[2][0];
        tmpLane.push_back(gamestate[2][0]);
        for(int i = 1; i < 5; i++) {
            // tmpPos += gamestate[2][i];
            tmpPos.push_back(gamestate[2][i]);
        }
        // for (int i = 5; i < gamestate[2].size(); i++) {
        //     // tmpName += gamestate[2][i];
        //     tmpName.push_back(gamestate[2][i]);
        // }

        player = Player(holder, {holder->get("ROAD")->getWidth() * 1.0f, holder->get("ROAD")->getHeight() * 0.95f}, {toFloat(tmpPos), float(toInt(tmpLane) + offset)}, setting);
        player.shift(gridSize.x * -0.25f, gridSize.y * -0.15f);
        // toInt(tmpLane) + offset, toFloat(tmpPos), tmpName, PLAYER_TEXTURES);
    }

    // Handle gamestate[3] : Vehicles
    for(int i = 0; i < gamestate[3].size(); i += 5) {
        std::vector<byte> tmpLane, tmpPos;
        // tmpLane += gamestate[3][i];
        tmpLane.push_back(gamestate[3][i]);
        for(int j = i + 1; j < i + 5; j++) {
            // tmpPos += gamestate[3][j];
            tmpPos.push_back(gamestate[3][j]);
        }
        lanes[toInt(tmpLane)]->addVehicle(toFloat(tmpPos));
    }
}

std::vector<std::vector<byte>> Play::createGamestate() const {
    auto iToS = [](int num, int strSize) -> std::vector<byte> {
        std::vector<byte> str;
        str.clear();
        for(int i = 0; i < strSize; i++) {
            str.push_back(*reinterpret_cast<char*>(&num));
            num >>= 8;
        }
        return str;
    };

    auto fToS = [&](float num, int strSize) -> std::vector<byte> {
        return iToS(*reinterpret_cast<int*>(&num), strSize);
    };

    auto bToS = [](bool num) -> std::vector<byte> {
        std::vector<byte> str;
        str.clear();
        str.push_back(*reinterpret_cast<char*>(&num));
        return str;
    };

    std::vector<std::vector<byte>> gamestate;

    // Create gamestate[0] : Score and offset
    gamestate.push_back(std::vector<byte>());
    {
        std::vector<byte> tmpScore = iToS(score, 4);
        std::vector<byte> tmpOffset = iToS(offset, 4);
        for(int i = 0; i < 4; i++) {
            gamestate[0].push_back(tmpScore[i]);
        }
        for(int i = 0; i < 4; i++) {
            gamestate[0].push_back(tmpOffset[i]);
        }
    }

    // Create gamestate[1] : lanes
    gamestate.push_back(std::vector<byte>());
    for(int i = 0; i < lanes.size(); i++) {
        std::vector<byte> tmpPos = iToS(lanes[i]->Y(), 4);
        std::vector<byte> tmpSpeed = fToS(lanes[i]->getSpeed(), 4);
        std::vector<byte> tmpSpawn = iToS(lanes[i]->getSpawn(), 4);
        std::vector<byte> tmpTraffic = lanes[i]->getTrafficGamestate();
        for(int j = 0; j < tmpPos.size(); j++) {
            gamestate[1].push_back(tmpPos[j]);
        }
        for(int j = 0; j < tmpSpeed.size(); j++) {
            gamestate[1].push_back(tmpSpeed[j]);
        }
        for(int j = 0; j < tmpSpawn.size(); j++) {
            gamestate[1].push_back(tmpSpawn[j]);
        }
        for(int j = 0; j < tmpTraffic.size(); j++) {
            gamestate[1].push_back(tmpTraffic[j]);
        }
    }

    // Create gamestate[2] : Player
    gamestate.push_back(std::vector<byte>());
    {
        std::vector<byte> tmpLane = iToS((int)(player.position().y - offset), 1);
        std::vector<byte> tmpPos = fToS(player.position().x, 4);
        // std::vector<byte> tmpName;
        // for (int i = 0; i < player.getName().size(); i++) {
        //     tmpName.push_back(player.getName()[i]);
        // }
        gamestate[2].push_back(tmpLane[0]);
        for(int i = 0; i < 4; i++) {
            gamestate[2].push_back(tmpPos[i]);
        }
        // for (int i = 0; i < tmpName.size(); i++) {
        //     gamestate[2].push_back(tmpName[i]);
        // }
    }

    // Create gamestate[3] : Vehicles
    gamestate.push_back(std::vector<byte>());
    for(int i = 0; i < lanes.size(); i++) {
        std::vector<byte> tmpLane = iToS(i, 1);
        std::vector<byte> tmpGamestate = lanes[i]->getVehiclesGamestate();
        for(int j = 0; j < tmpGamestate.size(); j += 4) {
            gamestate[3].push_back(tmpLane[0]);
            for(int k = 0; k < 4; k++) {
                gamestate[3].push_back(tmpGamestate[j + k]);
            }
        }
    }

    return gamestate;
}

void Play::createNewGame() {
    // Clear old data
    for(auto lane : lanes) {
        delete lane;
    }
    lanes.clear();
    score = 0;
    offset = 0;
    isGameover = false;

    // Create lanes
    for(int i = 0; i < 11; i++) {
        lanes.push_back(new Lane(holder, gridSize, 0 - i - offset, engine->getHeight() / holder->get("GRASS")->getHeight() * 4.0f + 3.0f / (engine->getWidth() / engine->getHeight() * 1.0f), 0.0f));
    }

    for(int i = 11; i < engine->getWidth() / holder->get("ROAD")->getWidth() + engine->getHeight() / holder->get("ROAD")->getHeight() * 2 + 11; i++) {
        if(needCreateGrassLane())
            lanes.push_back(new Lane(holder, gridSize, 0 - i - offset, engine->getHeight() / holder->get("GRASS")->getHeight() * 4.0f + 3.0f / (engine->getWidth() / engine->getHeight() * 1.0f), 0.0f));
        else
            lanes.push_back(new Lane(holder, gridSize, 0 - i - offset, engine->getHeight() / holder->get("ROAD")->getHeight() * 4.0f + 3.0f / (engine->getWidth() / engine->getHeight() * 1.0f), (rand() % (10 + offset / 5) - 5) * 0.05f));
    }

    // Create player
    player = Player(holder, {holder->get("ROAD")->getWidth() * 1.0f, holder->get("ROAD")->getHeight() * 0.95f}, {20.0f, 10.0f}, setting);
    player.shift(gridSize.x * -0.25f, gridSize.y * -0.15f);
}

float Play::percentage(int x) const {
    if(x <= 0) return 1.0f;
    if(x == 1) return 0.96f;
    if(x > 31) return percentage(31);

    float res = percentage(x / 2);
    res *= res;

    if(x % 2) res *= 0.96f;
    return res;
}

int Play::random(int min, int max) const {
    return rand() % (max - min + 1) + min;
}

void Play::updateProcess() {
    // Update score
    score++;

    // Update offset
    offset++;

    // Update lanes
    if(!lanes.empty()) delete lanes.front();
    lanes.erase(lanes.begin());

    int numOfLanes = engine->getWidth() / holder->get("ROAD")->getWidth() + engine->getHeight() / holder->get("ROAD")->getHeight() * 2 + 10;

    if(needCreateGrassLane())
        lanes.push_back(new Lane(holder, gridSize, 0 - numOfLanes - offset, engine->getHeight() / holder->get("GRASS")->getHeight() * 4.0f + 3.0f / (engine->getWidth() / engine->getHeight() * 1.0f), 0.0f));
    else
        lanes.push_back(new Lane(holder, gridSize, 0 - numOfLanes - offset, engine->getHeight() / holder->get("ROAD")->getHeight() * 4.0f + 3.0f / (engine->getWidth() / engine->getHeight() * 1.0f), (rand() % (10 + offset / 5) - 5) * 0.05f));
}

bool Play::needCreateGrassLane() const {
    int x = offset + lanes.size();
    return random(1, 100) <= int(percentage(x) * 100);
}

Play::~Play() {
    for(auto lane : lanes) {
        delete lane;
    }
    lanes.clear();
}