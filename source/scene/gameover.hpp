#ifndef GAMEOVER_HPP_
#define GAMEOVER_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Gameover : public Scene {
private:
    const Texture QUIT_CLICKED;

    Object quit;

public:
    Gameover(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Gameover();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* GAMEOVER_HPP_ */