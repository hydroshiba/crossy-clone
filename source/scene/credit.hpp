#ifndef CREDIT_HPP_
#define CREDIT_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Credit : public Scene {
private:
    std::string gameTitle;
    std::string quitButton;
    std::string background;
    std::string backgroundMusic;
    std::string buttonSound;

public:
    Credit(int width, int height, Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Credit();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* CREDIT_HPP_ */