#ifndef PAUSE_HPP_
#define PAUSE_HPP_
#include "scene.hpp"
#include "scene_registry.hpp"

class Pause : public Scene {
private:
    std::string gameTitle;
    std::string quitButton;
    std::string continueButton;
    std::string background;
    std::string backgroundMusic;
    std::string buttonSound;

public:
    Pause(Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Pause();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* PAUSE_HPP_ */