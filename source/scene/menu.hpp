#ifndef MENU_HPP_
#define MENU_HPP_

#include <vector>

#include "typedef.hpp"
#include "object.hpp"
#include "button.hpp"
#include "scene.hpp"
#include "scene_registry.hpp"

class Menu : public Scene {
private:
    int button;  // 1: Play, 2: Option, 3: Leaderboard, 4: Credit, 5: Quit

    const Texture TITLE;
    const Texture CONTINUE, CONTINUE_CLICKED;
    const Texture START, START_CLICKED;
    const Texture OPTION, OPTION_CLICKED;
    const Texture LEADERBOARD, LEADERBOARD_CLICKED;
    const Texture CREDIT, CREDIT_CLICKED;
    const Texture QUIT, QUIT_CLICKED;

    Sound background;
    Object title;

    std::vector<Button*> buttons;

public:
    Menu(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Menu();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* MENU_HPP_ */