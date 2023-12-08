#ifndef PAUSE_HPP_
#define PAUSE_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Pause : public Scene {
private:
    const Texture CONTINUE, CONTINUE_CLICKED;
    const Texture QUIT, QUIT_CLICKED;

    int button;

    Button quitButton;
    Button continueButton;

    Textbox pause;

public:
    Pause(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Pause();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* PAUSE_HPP_ */