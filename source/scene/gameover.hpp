#ifndef GAMEOVER_HPP_
#define GAMEOVER_HPP_

#include "scene.hpp"
#include "scene_registry.hpp"

class Gameover : public Scene {
private:
    word isEnterName;
    int idxChar;
    const int sizeName;
    byte namePlayer[8];

    Texture* LINE;
    
    Object quit;
    Object line;
    
    Textbox gameover;
    Textbox topX;
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