#ifndef CREDIT_HPP_
#define CREDIT_HPP_


#include "scene.hpp"
#include "scene_registry.hpp"

class Credit : public Scene {
private:
    // const Texture TITLE;
    const Texture TEACHER;
    const Texture ASTRAUNAUT;
    const Texture CAT;
    const Texture FOX;
    const Texture SEAL;

    Sound background;
    // Object title;
    Object teacher;
    Object astraunaut;
    Object cat;
    Object fox;
    Object seal;

public:
    Credit(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Credit();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* CREDIT_HPP_ */