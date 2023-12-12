#ifndef PLAY_HPP_
#define PLAY_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"
#include "player.hpp"
#include "lane.hpp"

class Play : public Scene {
private:
    const Texture ROAD;
    const Texture GRASS[3];

    const Texture PLAYER_UP;
    const Texture PLAYER_DOWN;
    const Texture PLAYER_LEFT;
    const Texture PLAYER_RIGHT;

    const Texture VEHICLE_FRONT[4];
    const Texture VEHICLE_BACK[4];
    const Texture TRAFFIC[2];

    Player player;
    std::vector<Lane*> lanes;
    bool isGameover;
    int score;
    int offset;

    void createNewGame();
    void updateProcess();
    bool needCreateGrassLane() const;
    const Texture& randomGrass() const;

public:
    Play(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder);
    ~Play();

    void loadGamestate(const std::vector<std::vector<char>>& gamestate);
    void createNewGame(const std::string& name);
    std::vector<std::vector<char>> createGamestate() const;
    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* PLAY_HPP_ */