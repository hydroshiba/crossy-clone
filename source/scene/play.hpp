#ifndef PLAY_HPP_
#define PLAY_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"
#include "player.hpp"
#include "lane.hpp"

class Play : public Scene {
private:
    Player *player;
    std::vector<Lane*> lanes;
    bool isGameover;
    int score;
    int offset;

    std::vector<const Texture*> LANE_TEXTURES;
    std::vector<const Texture*> PLAYER_TEXTURES;
    std::vector<std::pair<const Texture&, const Texture&>> VEHICLE_TEXTURE;
    std::pair<const Texture&, const Texture&> TRAFFIC_TEXTURE;

    void updateProcess();
    bool needCreateGrassLane() const;
    const Texture& getGrassTexture() const;

public:
    Play(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Play();

    void loadGamestate(const std::vector<std::vector<char>>& gamestate);
    void createNewGame(const std::string& name);
    std::vector<std::vector<char>> createGamestate() const;
    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* PLAY_HPP_ */