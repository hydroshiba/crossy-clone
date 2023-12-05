#include "lane.hpp"

Lane::Lane(const float& pos, const float& speed, const Texture& sprite) :
    Isometric(sprite, {100.0f, 100.0f}, {pos, 0.0f}),
    speed(speed),
    laneSprite(sprite),
    traffic(pos, TRAFFIC_LIGHT_RED, TRAFFIC_LIGHT_GREEN),
    AMBULANCE_FRONT("asset/texture/ambulance/front.bmp"),
    AMBULANCE_BACK("asset/texture/ambulance/back.bmp"),
    BLUE_CAR_FRONT("asset/texture/car/blue/front.bmp"),
    BLUE_CAR_BACK("asset/texture/car/blue/back.bmp"),
    ORANGE_CAR_FRONT("asset/texture/car/orange/front.bmp"),
    ORANGE_CAR_BACK("asset/texture/car/orange/back.bmp"),
    TRUCK_FRONT("asset/texture/truck/front.bmp"),
    TRUCK_BACK("asset/texture/truck/back.bmp"),
    TRAFFIC_LIGHT_RED("asset/texture/traffic/red.bmp"),
    TRAFFIC_LIGHT_GREEN("asset/texture/traffic/green.bmp")
    {
    
    }

Lane::Lane(const int& pos, const float& speed, const Texture& sprite) :
    Isometric(sprite, {100.0f, 100.0f}, {static_cast<float>(pos), 0.0f}),
    speed(speed),
    laneSprite(sprite),
    traffic(pos, TRAFFIC_LIGHT_RED, TRAFFIC_LIGHT_GREEN),
    AMBULANCE_FRONT("asset/texture/ambulance/front.bmp"),
    AMBULANCE_BACK("asset/texture/ambulance/back.bmp"),
    BLUE_CAR_FRONT("asset/texture/car/blue/front.bmp"),
    BLUE_CAR_BACK("asset/texture/car/blue/back.bmp"),
    ORANGE_CAR_FRONT("asset/texture/car/orange/front.bmp"),
    ORANGE_CAR_BACK("asset/texture/car/orange/back.bmp"),
    TRUCK_FRONT("asset/texture/truck/front.bmp"),
    TRUCK_BACK("asset/texture/truck/back.bmp"),
    TRAFFIC_LIGHT_RED("asset/texture/traffic/red.bmp"),
    TRAFFIC_LIGHT_GREEN("asset/texture/traffic/green.bmp")
    {
    
    }

Lane::Lane(const Lane& lane) :
    Isometric(laneSprite, {100.0f, 100.0f}, {lane.Y(), 0.0f}),
    speed(lane.speed),
    laneSprite(lane.laneSprite),
    traffic(lane.traffic),
    AMBULANCE_FRONT(lane.AMBULANCE_FRONT),
    AMBULANCE_BACK(lane.AMBULANCE_BACK),
    BLUE_CAR_FRONT(lane.BLUE_CAR_FRONT),
    BLUE_CAR_BACK(lane.BLUE_CAR_BACK),
    ORANGE_CAR_FRONT(lane.ORANGE_CAR_FRONT),
    ORANGE_CAR_BACK(lane.ORANGE_CAR_BACK),
    TRUCK_FRONT(lane.TRUCK_FRONT),
    TRUCK_BACK(lane.TRUCK_BACK),
    TRAFFIC_LIGHT_RED(lane.TRAFFIC_LIGHT_RED),
    TRAFFIC_LIGHT_GREEN(lane.TRAFFIC_LIGHT_GREEN)
    {
    
    }

Lane::Lane(const float& pos, const float& speed, const bool& trafficState, const Texture& sprite) :
    Isometric(sprite, {100.0f, 100.0f}, {pos, 0.0f}),
    speed(speed),
    laneSprite(sprite),
    traffic(pos, trafficState, TRAFFIC_LIGHT_RED, TRAFFIC_LIGHT_GREEN),
    AMBULANCE_FRONT("asset/texture/ambulance/front.bmp"),
    AMBULANCE_BACK("asset/texture/ambulance/back.bmp"),
    BLUE_CAR_FRONT("asset/texture/car/blue/front.bmp"),
    BLUE_CAR_BACK("asset/texture/car/blue/back.bmp"),
    ORANGE_CAR_FRONT("asset/texture/car/orange/front.bmp"),
    ORANGE_CAR_BACK("asset/texture/car/orange/back.bmp"),
    TRUCK_FRONT("asset/texture/truck/front.bmp"),
    TRUCK_BACK("asset/texture/truck/back.bmp"),
    TRAFFIC_LIGHT_RED("asset/texture/traffic/red.bmp"),
    TRAFFIC_LIGHT_GREEN("asset/texture/traffic/green.bmp")
    {
    
    }

Lane::Lane(const int& pos, const float& speed, const bool& trafficState, const Texture& sprite) :
    Isometric(sprite, {100.0f, 100.0f}, {static_cast<float>(pos), 0.0f}),
    speed(speed),
    laneSprite(sprite),
    traffic(pos, trafficState, TRAFFIC_LIGHT_RED, TRAFFIC_LIGHT_GREEN),
    AMBULANCE_FRONT("asset/texture/ambulance/front.bmp"),
    AMBULANCE_BACK("asset/texture/ambulance/back.bmp"),
    BLUE_CAR_FRONT("asset/texture/car/blue/front.bmp"),
    BLUE_CAR_BACK("asset/texture/car/blue/back.bmp"),
    ORANGE_CAR_FRONT("asset/texture/car/orange/front.bmp"),
    ORANGE_CAR_BACK("asset/texture/car/orange/back.bmp"),
    TRUCK_FRONT("asset/texture/truck/front.bmp"),
    TRUCK_BACK("asset/texture/truck/back.bmp"),
    TRAFFIC_LIGHT_RED("asset/texture/traffic/red.bmp"),
    TRAFFIC_LIGHT_GREEN("asset/texture/traffic/green.bmp")
    {
    
    }

void Lane::render(const int& offset, const float& playerLane) {
    int posOnScreen = this->Y() + offset + playerLane + 19;
}

void Lane::process(const int& time, hrClock_TP& prev, bool& isGameover, const float& playerPos) {
    hrClock_TP now = high_resolution_clock::now();
    uint64_t interval = duration_cast<milliseconds>(now - prev).count();
    traffic.process(time * 7 - time * 1 / 2);

    if (interval >= time && !traffic.isRedLight()) {
        if (rand() % 3 == 0) {
            if (speed > 0) {
                vehicles.push_back(new Vehicle(this->Y(), 150, BLUE_CAR_BACK, "asset/sound/car"));
            }
            else {
                vehicles.push_back(new Vehicle(this->Y(), -5, BLUE_CAR_FRONT, "asset/sound/car"));
            }
        }
        else if (rand() % 3 == 1) {
            if (speed > 0) {
                vehicles.push_back(new Vehicle(this->Y(), 150, TRUCK_BACK, "asset/sound/truck"));
            }
            else {
                vehicles.push_back(new Vehicle(this->Y(), -5, TRUCK_FRONT, "asset/sound/truck"));
            }
        }
        else {
            if (speed > 0) {
                vehicles.push_back(new Vehicle(this->Y(), 150, ORANGE_CAR_BACK, "asset/sound/car"));
            }
            else {
                vehicles.push_back(new Vehicle(this->Y(), -5, ORANGE_CAR_FRONT, "asset/sound/car"));
            }
        }
        prev = high_resolution_clock::time_point();
    }

    for (auto& vehicle : vehicles) {
        if (!vehicle->move(speed, playerPos)) {
            vehicles.clear();
            vehicles.push_back(new Vehicle(this->Y(), -5, AMBULANCE_BACK, "asset/sound/ambluance"));
            isGameover = true;
            break;
        }
    }

    if (vehicles.size() > 0 && vehicles[0]->isOut(150)) {
        delete vehicles[0];
        vehicles.erase(vehicles.begin());
    }

    if (!isGameover) {
        return;
    }

    while (!vehicles[0]->move(speed, playerPos)) {
    }
}

bool Lane::checkCollision(const float& pos) {
    for (auto& vehicle : vehicles) {
        if (vehicle->isCollision(pos)) {
            vehicle->playSound();
            return true;
        }
    }
    return false;
}

void Lane::addVehicle(const float& pos, const std::string& sound) {
    if (rand() % 3 == 0) {
        if (speed > 0) {
            vehicles.push_back(new Vehicle(this->Y(), 150, BLUE_CAR_BACK, sound));
        }
        else {
            vehicles.push_back(new Vehicle(this->Y(), -5, BLUE_CAR_FRONT, sound));
        }
    }
    else if (rand() % 3 == 1) {
        if (speed > 0) {
            vehicles.push_back(new Vehicle(this->Y(), 150, TRUCK_BACK, sound));
        }
        else {
            vehicles.push_back(new Vehicle(this->Y(), -5, TRUCK_FRONT, sound));
        }
    }
    else {
        if (speed > 0) {
            vehicles.push_back(new Vehicle(this->Y(), 150, ORANGE_CAR_BACK, sound));
        }
        else {
            vehicles.push_back(new Vehicle(this->Y(), -5, ORANGE_CAR_FRONT, sound));
        }
    }
}

float Lane::getSpeed() const {
    return speed;
}

bool Lane::getTrafficState() const {
    return traffic.isRedLight();
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
        for (int i = 0; i < 8; i++) {
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