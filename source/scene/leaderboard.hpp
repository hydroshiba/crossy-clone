#ifndef LEADERBOARD_HPP_
#define LEADERBOARD_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Leaderboard : public Scene {
private:
    std::string gameTitle;
    std::string quitButton;
    std::string background;
    std::string backgroundMusic;
    std::string buttonSound;

public:
    Leaderboard(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Leaderboard();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* LEADERBOARD_HPP_ */