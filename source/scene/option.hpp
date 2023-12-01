#ifndef OPTION_HPP_
#define OPTION_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Option : public Scene {
private:
    int button;
    int arrow;
    int musicId;
    int sfxId;
    int spriteId;
    
    const Texture SPRITE, SPRITE_CLICKED;
    const Texture CHICKEN, DUCK, CAT;
    const Texture MUSIC, MUSIC_CLICKED;
    const Texture SFX, SFX_CLICKED;
    const Texture MIN_VOLUME;
    const Texture LOW_VOLUME;
    const Texture MEDIUM_VOLUME;
    const Texture HIGH_VOLUME;
    const Texture MAX_VOLUME;
    const Texture LEFT_ARROW, LEFT_ARROW_CLICKED;
    const Texture RIGHT_ARROW, RIGHT_ARROW_CLICKED;

    Sound background;

    std::vector<Object*> music;
    std::vector<Object*> sfx;
    std::vector<Object*> sprites;
    std::vector<Button*> buttons;
public:
    Option(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Option();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* OPTION_HPP_ */