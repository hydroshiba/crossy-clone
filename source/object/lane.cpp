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
        for(int i = 0; i < len; ++i)
            blocks.push_back(Isometric(holder->get("ROAD"), gridSize, Vec2({(float)i, (float)pos})));
    }

void Lane::render(Engine* engine) {
    for(auto& block : blocks)
        block.render(engine);
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

    Vehicle vehicle(holder->get(color), gridSize, Vec2({pos, 0}), Vec2({0, 0}));
    vehicles.push_back(vehicle);
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

    // Something
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