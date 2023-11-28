#ifndef PLAY_HPP_
#define PLAY_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"
#include "player.hpp"
#include "lane.hpp"

class Play : public Scene {
private:
    std::string background;
    std::string backgroundMusic;
    std::string buttonSound;
    Player *player;
    std::vector<Lane> lanes;
    int offset;

public:
    Play(int width, int height, Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Play();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* PLAY_HPP_ */