#include "lane.hpp"

Lane::Lane(const Texture& texture, int pos, int len, float speed, const std::vector<std::pair<const Texture&, const Texture&>>& VT, const std::pair<const Texture&, const Texture&>& TT, bool trafficState, int clock):
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
    clock(clock),
    spawn(120) {
        for(int i = 0; i < length; ++i)
            blocks.push_back(Isometric(texture, {texture.getWidth() / 2.0f, texture.getHeight() / 2.0f}, {float(i), float(pos)}));
    }

void Lane::render(Engine* engine) {
    for(auto& block : blocks)
        block.render(engine);
}

void Lane::process() {
    // Use VEHICLE_TEXTURE[] to random a texture for vehicle
    // Remember to random spawn and reset clock after clock >= spawn
}

bool Lane::collide(float pos) {
    for (auto& vehicle : vehicles) {
        if (vehicle.collide(pos)) return true;
    }
    return false;
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
        std::string tmpPos = fToS(vehicle.X(), 4);
        for (int i = 0; i < 8; i++) {
            gamestate.push_back(tmpPos[i]);
        }
    }
    return gamestate;
}