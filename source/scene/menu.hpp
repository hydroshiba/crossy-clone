#ifndef MENU_HPP_
#define MENU_HPP_
#include "scene.hpp"
#include <conio.h>

class Menu: public Scene {
private:
    std::string gameTitle;
    std::string playButton;
    std::string quitButton;
    std::string continueButton;
    std::string settingsButton;
    std::string scoreboard;
    std::string background;
    std::string backgroundMusic;
    std::string buttonSound;

public:
    Menu(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting);
    ~Menu();

    Scene* process(SceneRegistry const * const registry) override;
    void render() override;
    void playsound() override;
};

#endif /* MENU_HPP_ */