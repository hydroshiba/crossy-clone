#ifndef SETTING_SCENE_HPP_
#define SETTING_SCENE_HPP_
#include "scene.hpp"
#include "scene_registry.hpp"

class SettingScene: public Scene {
private:
    std::string gameTitle;
    std::string quitButton;
    std::string background;
    std::string backgroundMusic;
    std::string buttonSound;

public:
    SettingScene(Engine* engine, AudioDevice* audio ,SceneRegistry* registry, Setting* setting);
    ~SettingScene();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* SETTING_SCENE_HPP_ */