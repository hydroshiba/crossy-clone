#ifndef MENU_HPP_
#define MENU_HPP_
#include "scene.hpp"
#include <conio.h>
#include "scene_registry.hpp"
class Menu : public Scene {
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
    Menu(Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Menu();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* MENU_HPP_ */