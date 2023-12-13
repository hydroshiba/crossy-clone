#ifndef PLAY_HPP_
#define PLAY_HPP_

#include <random>

#include "scene.hpp"
#include "scene_registry.hpp"
#include "player.hpp"
#include "lane.hpp"
#include "textbox.hpp"

class Play : public Scene {
private:
    Vec2 gridSize;

    Textbox scoreBox;
    bool isGameover;
    int score;
    int offset;
    int frames;
    int laneLength;

    Player player;
    std::vector<Lane*> lanes;
    
    void updateProcess();
    bool needCreateGrassLane(int i) const;

    int random(int min, int max) const;
    float percentage(int x) const;

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