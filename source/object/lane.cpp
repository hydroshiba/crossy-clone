#include "lane.hpp"

Lane::Lane(TextureHolder* holder, Vec2 size, int pos, int len, float speed, int spawnClock, bool isRed, int trafficClock) :
    gridSize(size),
    holder(holder),
    pos(pos),
    length(len),
    grassType(rand() % 3),
    speed(speed),
    traffic(holder, gridSize, {speed > 0 ? float(len) : 1.0f, float(pos)}, {0.0f, speed > 0 ? -105.0f : -40.0f}, isRed, trafficClock),
    clock(spawnClock / 2),
    spawn(spawnClock) {
    }

void Lane::render(Engine* engine, float playerLane) {
    int offset = playerLane + engine->getHeight() / holder->get("ROAD")->getHeight() * 2.0f - 7;
    std::string grassID = "GRASS";

    if (speed != 0) grassID = "ROAD";
    else {
        switch (grassType) {
            case 0: break;
            case 1: grassID += "FLOWER"; break;
            case 2: grassID += "PEBBLE"; break;
        }
    }

    for(int i = 0; i < length; ++i) 
        blocks.push_back(Isometric(holder->get(grassID), gridSize, Vec2({float(i - 1), float(pos + offset)})));

    for(auto& block : blocks)
        block.render(engine);

    if (speed != 0)
        traffic.render(engine, offset, offset + pos - 1);

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

    traffic.process();

    if (traffic.isRedLight()) {
        return;
    }

    if (clock >= spawn) {
        if (speed > 0) addVehicle(float(-1.0f));
        else addVehicle(float(length + 1.0f));
        spawn = random(60, 75);
        clock = 0;
    }


    for (auto& vehicle : vehicles) {
        vehicle.move(speed);
    }

    if (!vehicles.empty() && (vehicles[0].position().x > length + 1.0f || vehicles[0].position().x < -1.0f)) {
        vehicles.erase(vehicles.begin());
    }
    ++clock;
}

void Lane::playsound(Speaker* speaker, Sound& car_honk) {
    speaker->stop();
    speaker->play(car_honk);
}

void Lane::gameoverProcess() {
    if (vehicles.empty()) {
        std::string ambulance = "AMBULANCE_FRONT";
        Vehicle vehicle(holder->get(ambulance), gridSize, Vec2({0.0f, float(this->pos - 1)}), Vec2({0, 0}));
        vehicles.push_back(vehicle);
    }
    vehicles[0].move(0.25f);
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
            Vehicle vehicle(holder->get(ambulance), gridSize, Vec2({0.0f, float(this->pos)}), Vec2({0, gridSize.y * -0.5f}));
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

int Lane::random(int min, int max) const {
    return rand() % (max - min + 1) + min;
}

int Lane::getSpawn() const {
    return spawn;
}

void Lane::addVehicle(float pos) {
    std::string color;
    int rng = rand() % 4;

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
        case 3:
            color = "TRUCK";
            break;
    }

    if(speed > 0) color += "_FRONT";
    else color += "_BACK";

    if (rng != 3) {
        Vehicle vehicle(holder->get(color), gridSize, Vec2({float(pos), float(this->pos)}), Vec2({0.0f, gridSize.y * -0.25f}));
        vehicles.push_back(vehicle);
    }
    else {
        Vehicle vehicle(holder->get(color), gridSize, Vec2({float(pos), float(this->pos)}), Vec2({0.0f, gridSize.y * -0.44f}));
        vehicles.push_back(vehicle);
    }
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