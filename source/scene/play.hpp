#ifndef PLAY_HPP_
#define PLAY_HPP_
#include "scene.hpp"
#include "scene_registry.hpp"

class Play : public Scene {
private:
    std::string gameTitle;
    std::string quitButton;
    std::string background;
    std::string backgroundMusic;
    std::string buttonSound;

public:
    Play(Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Play();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* PLAY_HPP_ */