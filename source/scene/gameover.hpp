#ifndef GAMEOVER_HPP_
#define GAMEOVER_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Gameover : public Scene {
private:
    bool isEnterName;
    word score;
    int idxChar;
    const int sizeName;
    std::string namePlayer;
    Texture* LINE;
    Object quit;
    Textbox gameover;
    Object line;
    Textbox name;

public:
    Gameover(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder);
    ~Gameover();

    void setScore(word score);
    Scene* process() override;
    void render() override;
    void playsound() override;
};

#endif /* GAMEOVER_HPP_ */