#ifndef OPTION_HPP_
#define OPTION_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Option : public Scene {
private:
    std::string gameTitle;
    std::string quitButton;
    std::string background;
    std::string backgroundMusic;
    std::string buttonSound;

public:
    Option(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Option();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* OPTION_HPP_ */