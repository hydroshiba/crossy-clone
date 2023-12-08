#ifndef CREDIT_HPP_
#define CREDIT_HPP_


#include "scene.hpp"
#include "scene_registry.hpp"

class Credit : public Scene {
private:
    bool view;
    int avatarSelected, xSelected, ySelected;

    const Texture TEACHER;
    const Texture ASTRAUNAUT;
    const Texture CAT;
    const Texture FOX;
    const Texture SEAL;

    Sound background;
    // Object title;
    std::vector<Object*> avatars;

    Textbox credit;
    Textbox name;
    Textbox studentId;

public:
    Credit(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Credit();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* CREDIT_HPP_ */