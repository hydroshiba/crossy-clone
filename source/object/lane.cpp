#include "lane.hpp"

Lane::Lane(const Texture& texture, int pos, int len, float speed, const std::vector<std::pair<const Texture&, const Texture&>>& VT, const std::pair<const Texture&, const Texture&>& TT, bool trafficState, int clock, int spawn):
    Isometric(texture, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {0.0f, float(pos)}),
    length(len),
    speed(speed),
    VEHICLE_TEXTURE(VT),
    TRAFFIC_TEXTURE(TT),
    traffic(TRAFFIC_TEXTURE.first, TRAFFIC_TEXTURE.second,
        {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f},
        {(speed > 0.0f ? 0.0f : float(length)), float(pos)},
        {0.0f, 0.0f},
        trafficState,
        clock),
    clock(spawn),
    spawn(120) {
    }

void Lane::render(Engine* engine, int playerPos) {
    // int realPos = pos.y + playerPos + 19;
    // for(auto& block : blocks)
    //     block.render(engine);

    
    // Calculate render offset
    int offset = playerPos + Y() + (engine->getWidth() / texture.getWidth() + engine->getHeight() * 2 / texture.getHeight() + 1) / 2;

    for(int i = 0; i < length; ++i)
        blocks.push_back(Isometric(texture, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {float(i - 1) * 2, float(offset) * 2}));

    // Render lane texture
    // for (int i = 0; i < engine->getWidth() / texture.getWidth() * 2; ++i) {
    //     engine->textureFill(i * texture.getWidth(), Y() * texture.getHeight(), texture);
    // }

    // Render additional elements (blocks)
    for (auto& block : blocks) {
        block.render(engine);
    }

    // // Render traffic light
    // if (trafficState) {
    //     engine->drawTexture(trafficTexture[0], (engine->getWidth() - trafficTexture[0].getWidth()) / 2, Y() * texture.getHeight());
    // } else {
    //     engine->drawTexture(trafficTexture[1], (engine->getWidth() - trafficTexture[1].getWidth()) / 2, Y() * texture.getHeight());
    // }

    // Render vehicles
    for (auto& vehicle : vehicles) {
        vehicle->render(engine);
    }

    blocks.clear();
}

void Lane::process(bool& isGameover, Engine* engine, float playerPos) {
    // Use VEHICLE_TEXTURE[] to random a texture for vehicle
    // Remember to random spawn and reset clock after clock >= spawn
    if (speed == 0) {
        return;
    }

    if (clock >= spawn) {
        clock = 0;
        int random = rand() % 3;
        if (speed > 0.0f) {
            vehicles.push_back(new Vehicle(VEHICLE_TEXTURE[random].first, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {0.0f, float(Y() + playerPos + (engine->getWidth() / texture.getWidth() + engine->getHeight() * 2 / texture.getHeight() + 1) / 2 ) * 2}, {0.0f, 0.0f}));
        } else {
            vehicles.push_back(new Vehicle(VEHICLE_TEXTURE[random].second, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {float(length), float(Y() + playerPos + (engine->getWidth() / texture.getWidth() + engine->getHeight() * 2 / texture.getHeight() + 1) / 2 ) * 2}, {0.0f, 0.0f}));
        }

        for (auto& vehicle : vehicles) {
            vehicle->move(speed);
            isGameover |= vehicle->collide(playerPos);
        }

        if (vehicles[0]->X() > length || vehicles[0]->X() < 0) {
            delete vehicles[0];
            vehicles.erase(vehicles.begin());
        }

        traffic.process();

        if (!isGameover) {
            return;
        }

        for (auto& vehicle : vehicles) {
            delete vehicle;
        }
        vehicles.clear();
        if (speed > 0.0f) {
            vehicles.push_back(new Vehicle(VEHICLE_TEXTURE[3].first, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {0.0f, float(length)}, {0.0f, 0.0f}));
        } else {
            vehicles.push_back(new Vehicle(VEHICLE_TEXTURE[3].second, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {float(length), 0.0f}, {0.0f, 0.0f}));
        }

        return;
    }

    ++clock;
}

void Lane::gameoverProcess(bool& isStopped, float playerPos) {
    if (vehicles.size() == 0) {
        if (speed > 0.0f) {
            vehicles.push_back(new Vehicle(VEHICLE_TEXTURE[3].first, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {0.0f, float(length)}, {0.0f, 0.0f}));
        } else {
            vehicles.push_back(new Vehicle(VEHICLE_TEXTURE[3].second, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {float(length), 0.0f}, {0.0f, 0.0f}));
        }
    }
    if (speed > 0.0f) {
        vehicles[0]->move(120);
    }
    else {
        vehicles[0]->move(-120);
    }
    isStopped |= vehicles[0]->collide(playerPos);
}

bool Lane::collide(float pos) {
    for (auto& vehicle : vehicles) {
        if (vehicle->collide(pos)) return true;
    }
    return false;
}

float Lane::getSpeed() const {
    return speed;
}

int Lane::getSpawn() const {
    return spawn;
}

void Lane::addVehicle(float pos) {
    int random = rand() % 3;
    if (speed > 0.0f) {
        vehicles.push_back(new Vehicle(VEHICLE_TEXTURE[random].first, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {0.0f, float(length)}, {0.0f, 0.0f}));
    } else {
        vehicles.push_back(new Vehicle(VEHICLE_TEXTURE[random].second, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {float(length), 0.0f}, {0.0f, 0.0f}));
    }
}

std::vector<char> Lane::getTrafficGamestate() const {
    auto iToS = [](int num, int strSize) -> std::string {
        std::string str = "";
        for (int i = 0; i < strSize; i++) {
            str += *reinterpret_cast<char*>(&num);
            num >>= 8;
        }
        return str;
    };

    auto bToS = [](bool num) -> std::string {
        std::string str = "";
        str += *reinterpret_cast<char*>(&num);
        return str;
    };

    std::vector<char> gamestate;
    std::string tmpState = bToS(traffic.isRedLight());
    std::string tmpClock = iToS(traffic.getClock(), 4);
    gamestate.push_back(tmpState[0]);
    for (int i = 0; i < 4; i++) {
        gamestate.push_back(tmpClock[i]);
    }
    return gamestate;
}

std::vector<char> Lane::getVehiclesGamestate() const {
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

    std::vector<char> gamestate;
    for (auto& vehicle : vehicles) {
        std::string tmpPos = fToS(vehicle->X(), 4);
        for (int i = 0; i < 4; i++) {
            gamestate.push_back(tmpPos[i]);
        }
    }
    return gamestate;
}

Lane::~Lane() {
    for (auto& vehicle : vehicles) {
        delete vehicle;
    }
    vehicles.clear();
}