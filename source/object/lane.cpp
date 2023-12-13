#include "lane.hpp"

Lane::Lane(TextureHolder* holder, Vec2 size, int pos, int len, float speed, int spawnClock, bool isRed, int trafficClock) :
    gridSize(size),
    holder(holder),
    pos(pos),
    length(len),
    speed(speed),
    traffic(holder, gridSize, {speed > 0 ? 1.0f : float(len), float(pos)}, {0.0f, 100.0f}, isRed, trafficClock),
    clock(spawnClock / 2),
    spawn(spawnClock) {
    }

void Lane::render(Engine* engine, float playerLane) {
    int offset = playerLane + engine->getHeight() / holder->get("ROAD")->getHeight() * 2 - 2;

    for(int i = 0; i < length; ++i) {
        if (speed != 0) {
            blocks.push_back(Isometric(holder->get("ROAD"), gridSize, Vec2({float(i - 1), float(pos + offset)})));
        }
        else {
            int grassType = rand() % 3;
            switch (grassType)
            {
                case 0:
                    blocks.push_back(Isometric(holder->get("GRASS"), gridSize, Vec2({float(i - 1), float(pos + offset)})));
                    break;
                case 1:
                    blocks.push_back(Isometric(holder->get("GRASSFLOWER"), gridSize, Vec2({float(i - 1), float(pos + offset)})));
                    break;
                case 2:
                    blocks.push_back(Isometric(holder->get("GRASSPEBBLE"), gridSize, Vec2({float(i - 1), float(pos + offset)})));
                    break;
            }
        }
    }

    for(auto& block : blocks)
        block.render(engine);

    if (speed != 0)
        traffic.render(engine, offset, engine->getHeight() / holder->get("ROAD")->getHeight() * 2.0f + 3 + playerLane + pos - 6);

    for(auto& vehicle : vehicles)
        vehicle.render(engine, offset);

    blocks.clear();
}

void Lane::process() {
    // Use VEHICLE_TEXTURE[] to random a texture for vehicle
    // Remember to random spawn and reset clock after clock >= spawn
    if (speed == 0) {
        return;
    }

    if (clock >= spawn && !traffic.isRedLight()) {
        if (speed > 0) addVehicle(float(-1.0f));
        else addVehicle(float(length + 1.0f));
        spawn = rand() % 60 + 60;
        clock = 0;
    }

    traffic.process();

    for (auto& vehicle : vehicles) {
        vehicle.move(speed);
    }

    if (!vehicles.empty() && (vehicles[0].position().x > length + 1.0f || vehicles[0].position().x < -1.0f)) {
        vehicles.erase(vehicles.begin());
    }
    ++clock;
}

void Lane::gameoverProcess() {
    if (vehicles.empty()) {
        std::string ambulance = "AMBULANCE_FRONT";
        Vehicle vehicle(holder->get(ambulance), gridSize, Vec2({0.0f, float(this->pos - 1)}), Vec2({0, 0}));
        vehicles.push_back(vehicle);
    }
    vehicles[0].move(0.1f);
}

void Lane::shift(Vec2 offset) {
    for (auto& vehicle : vehicles) {
        vehicle.shift(offset);
    }
    for (auto& block : blocks) {
        block.shift(offset);
    }
    traffic.shift(offset);
}

bool Lane::collide(Player* player) {
    for (auto& vehicle : vehicles) {
        if (vehicle.collide(player)) {
            vehicles.clear();
            std::string ambulance = "AMBULANCE_FRONT";
            Vehicle vehicle(holder->get(ambulance), gridSize, Vec2({0.0f, float(this->pos - 1)}), Vec2({0, 0}));
            vehicles.push_back(vehicle);

            return true;
        }
    }
    return false;
}

bool Lane::direction() {
    return speed > 0;
}

int Lane::Y() const {
    return pos;
}

float Lane::getSpeed() const {
    return speed;
}

int Lane::getSpawn() const {
    return spawn;
}

void Lane::addVehicle(float pos) {
    std::string color;
    int rng = rand() % 3;

    switch (rng) {
        case 0:
            color = "CAR_BLUE";
            break;
        case 1:
            color = "CAR_ORANGE";
            break;
        case 2:
            color = "TAXI";
            break;
    }

    if(speed > 0) color += "_FRONT";
    else color += "_BACK";

    Vehicle vehicle(holder->get(color), gridSize, Vec2({pos, float(this->pos - 0.5)}), Vec2({0, 0}));
    vehicles.push_back(vehicle);
}

std::vector<byte> Lane::getTrafficGamestate() const {
    auto iToS = [](int num, int strSize) -> std::vector<byte> {
        std::vector<byte> str;
        for (int i = 0; i < strSize; i++) {
            str.push_back(*reinterpret_cast<char*>(&num));
            num >>= 8;
        }
        return str;
    };

    auto bToS = [](bool num) -> std::vector<byte> {
        std::vector<byte> str;
        str.push_back(*reinterpret_cast<char*>(&num));
        return str;
    };

    // Something
    std::vector<byte> gamestate;
    std::vector<byte> tmpState = bToS(traffic.isRedLight());
    std::vector<byte> tmpClock = iToS(traffic.getClock(), 4);
    gamestate.push_back(tmpState[0]);
    for (int i = 0; i < 4; i++) {
        gamestate.push_back(tmpClock[i]);
    }
    return gamestate;
}

std::vector<byte> Lane::getVehiclesGamestate() const {
    auto iToS = [](int num, int strSize) -> std::vector<byte> {
        std::vector<byte> str;
        for (int i = 0; i < strSize; i++) {
            str.push_back(*reinterpret_cast<char*>(&num));
            num >>= 8;
        }
        return str;
    };

    auto fToS = [&](float num, int strSize) -> std::vector<byte> {
        return iToS(*reinterpret_cast<int*>(&num), strSize);
    };

    // Something
    std::vector<byte> gamestate;
    for (auto& vehicle : vehicles) {
        std::vector<byte> tmpPos = fToS(vehicle.position().x, 4);
        for (int i = 0; i < 4; i++) {
            gamestate.push_back(tmpPos[i]);
        }
    }
    return gamestate;
}

Lane::~Lane() {
    vehicles.clear();
}