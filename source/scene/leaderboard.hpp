#ifndef LEADERBOARD_HPP_
#define LEADERBOARD_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Leaderboard : public Scene {
private:
    bool view;
    int cupSelected, xSelected, ySelected;
    Sound button_clicked;
    std::vector<Object*> cups;
    Textbox score;
    Textbox name;
    Textbox topX;
public:
    Leaderboard(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder);
    ~Leaderboard();

    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* LEADERBOARD_HPP_ */