#ifndef PLAY_HPP_
#define PLAY_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"
#include "player.hpp"
#include "lane.hpp"

class Play : public Scene {
private:
    // std::string background;
    // std::string backgroundMusic;
    // std::string buttonSound;
    Player *player;
    std::vector<Lane*> lanes;
    int score;
    int offset;

    const Texture GRASS1, GRASS2, GRASS3;
    const Texture ROAD;
    const Texture PLAYER_UP, PLAYER_DOWN, PLAYER_LEFT, PLAYER_RIGHT;
    std::vector<const Texture*> laneTextures;

    void loadGamestate(const std::vector<std::vector<char>>& gamestate);
    std::vector<std::vector<char>> createGamestate() const;
    void createNewGame(const std::string& name);
    void updateProcess();
    bool needCreateGrassLane() const;
    const Texture& getGrassTexture() const;

public:
    Play(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Play();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* PLAY_HPP_ */