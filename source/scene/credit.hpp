#ifndef CREDIT_HPP_
#define CREDIT_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Credit : public Scene {
private:
    bool view;
    int avatarSelected, xSelected, ySelected;

    Sound button_clicked;

    // Object title;
    std::vector<Object*> avatars;
    std::vector<Button*> buttons;

    Textbox credit;
    Textbox studentId;
    std::vector<Textbox> name;

public:
    Credit(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder);
    ~Credit();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* CREDIT_HPP_ */