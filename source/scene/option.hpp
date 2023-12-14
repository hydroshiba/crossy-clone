#ifndef OPTION_HPP_
#define OPTION_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Option : public Scene {
private:
    int button;
    int musicId;
    int sfxId;
    int spriteId;

    Sound button_clicked;

    std::vector<Object*> music;
    std::vector<Object*> sfx;
    std::vector<Object*> sprites;
    std::vector<Button*> buttons;
public:
    Option(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder);
    ~Option();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* OPTION_HPP_ */