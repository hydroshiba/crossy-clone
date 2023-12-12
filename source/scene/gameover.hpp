#ifndef GAMEOVER_HPP_
#define GAMEOVER_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Gameover : public Scene {
private:

    Object quit;
    Textbox gameover;

public:
    Gameover(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder);
    ~Gameover();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* GAMEOVER_HPP_ */