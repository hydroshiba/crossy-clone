#ifndef PLAY_HPP_
#define PLAY_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"
#include "player.hpp"
#include "lane.hpp"

class Play : public Scene {
private:
    Vec2 gridSize;

    bool isGameover;
    int score;
    int offset;
    int frames;

    Player player;
    std::vector<Lane*> lanes;
    
    void updateProcess();
    bool needCreateGrassLane() const;

public:
    Play(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder);
    ~Play();

    void loadGamestate(const std::vector<std::vector<byte>>& gamestate);
    void createNewGame();
    std::vector<std::vector<byte>> createGamestate() const;
    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* PLAY_HPP_ */