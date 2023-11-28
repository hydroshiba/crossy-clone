#ifndef MENU_HPP_
#define MENU_HPP_

#include "typedef.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "scene_registry.hpp"

class Menu : public Scene {
private:
    Texture* titleTexture;
    Texture* playTexture;
    Texture* optionTexture;
    Texture* leaderboardTexture;
    Texture* creditTexture;
    Texture* exitTexture;
    
    Object title;

public:
    Menu(int width, int height, Engine* engine, AudioDevice* audio, SceneRegistry* registry, Setting* setting, Keyboard* keyboard);
    ~Menu();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* MENU_HPP_ */