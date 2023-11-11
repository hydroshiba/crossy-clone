#ifndef MENU_HPP_
#define MENU_HPP_
#include <iostream>
#include "scene.hpp"

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
    Menu();
    ~Menu();

    void process();
    void render();
    void playsound();
};

#endif /* MENU_HPP_ */