#include "lane.hpp"

Lane::Lane(TextureHolder* holder, Vec2 size, int pos, int len, float speed, int spawnClock, bool isRed, int trafficClock) :
    gridSize(size),
    holder(holder),
    pos(pos),
    length(len),
    speed(speed),
    traffic(holder, gridSize, {speed > 0 ? 0.0f : float(len + 5), float(pos)}, {float(0), float(0)}, isRed, trafficClock),
    clock(spawnClock - 1),
    spawn(spawnClock) {
        if (speed == 0) {
            grassType = rand() % 3;
        }
    }

void Lane::render(Engine* engine, int playerLane) {
    int offset = playerLane + engine->getHeight() / holder->get("ROAD")->getHeight() * 2 - 2;

    for(int i = 0; i < length; ++i) {
        if (speed != 0) {
            blocks.push_back(Isometric(holder->get("ROAD"), gridSize, Vec2({float(i - 1), float(pos + offset)})));
        }
        else {
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

    traffic.render(engine);

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

    if (clock >= spawn) {
        addVehicle(0.0f);
        clock = 0;
    }

    for (auto& vehicle : vehicles) {
        vehicle.move(speed);
    }
    ++clock;
}

void Lane::gameoverProcess() {
    vehicles[0].move(120.0f);
}

bool Lane::collide(float pos) {
    for (auto& vehicle : vehicles) {
        if (vehicle.collide(pos)) {
            vehicles.clear();
            std::string ambulance = "AMBULANCE";
            if (speed > 0) ambulance += "_FRONT";
            else ambulance += "_BACK";
            Vehicle vehicle(holder->get(ambulance), gridSize, Vec2({pos, 0}), Vec2({0, 0}));
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

std::vector<char> Lane::getTrafficGamestate() const {
    auto iToS = [](int num, int strSize) -> std::vector<char> {
        std::vector<char> str;
        for (int i = 0; i < strSize; i++) {
            str.push_back(*reinterpret_cast<char*>(&num));
            num >>= 8;
        }
        return str;
    };

    auto bToS = [](bool num) -> std::vector<char> {
        std::vector<char> str;
        str.push_back(*reinterpret_cast<char*>(&num));
        return str;
    };

    // Something
    std::vector<char> gamestate;
    std::vector<char> tmpState = bToS(traffic.isRedLight());
    std::vector<char> tmpClock = iToS(traffic.getClock(), 4);
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

    // Something
    std::vector<char> gamestate;
    for (auto& vehicle : vehicles) {
        std::string tmpPos = fToS(vehicle.position().x, 4);
        for (int i = 0; i < 4; i++) {
            gamestate.push_back(tmpPos[i]);
        }
    }
    return gamestate;
}

Lane::~Lane() {
}