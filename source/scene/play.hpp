#ifndef PLAY_HPP_
#define PLAY_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"
#include "player.hpp"
#include "lane.hpp"
#include "textbox.hpp"

class Play : public Scene {
private:
    Vec2 gridSize;

    bool isGameover;
    int score;
    Textbox scoreBox;
    int offset;
    int frames;

    Player player;
    std::vector<Lane*> lanes;

    Sound car_crash;
    Sound car_honk;
    Sound step_grass;
    Sound step_road;
    
    float percentage(int x) const;
    int random(int min, int max) const;

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