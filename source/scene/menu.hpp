#ifndef MENU_HPP_
#define MENU_HPP_

#include <vector>

#include "scene.hpp"
#include "scene_registry.hpp"

class Menu : public Scene {
private:
    bool isContinueEnabled;
    int defaultButton;
    int button;  // 0 = continue, 1 = start, 2 = option, 3 = leaderboard, 4 = credit, 5 = quit

    Sound button_clicked;
    Object title;
    Object duck_large;

    std::vector<Button*> buttons;

public:
    Menu(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder);
    ~Menu();

    void updateButton();
    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* MENU_HPP_ */