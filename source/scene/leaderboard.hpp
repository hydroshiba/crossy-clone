#ifndef LEADERBOARD_HPP_
#define LEADERBOARD_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Leaderboard : public Scene {
private:
    const Texture GOLD;
    const Texture SILVER;
    const Texture COPPER;

    Object gold, silver, copper;
public:
    Leaderboard(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Leaderboard();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* LEADERBOARD_HPP_ */