#ifndef PAUSE_HPP_
#define PAUSE_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Pause : public Scene {
private:

    int button;

    Button quitButton;
    Button continueButton;

    Textbox pause;
    Sound button_clicked;

public:
    Pause(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder);
    ~Pause();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* PAUSE_HPP_ */