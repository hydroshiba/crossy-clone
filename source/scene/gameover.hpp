#ifndef GAMEOVER_HPP_
#define GAMEOVER_HPP_
#include "scene.hpp"
#include "scene_registry.hpp"

class Gameover: public Scene {
private:
    std::string gameTitle;
    std::string quitButton;
    std::string background;
    std::string backgroundMusic;
    std::string buttonSound;

public:
    Gameover(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting);
    ~Gameover();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* GAMEOVER_HPP_ */