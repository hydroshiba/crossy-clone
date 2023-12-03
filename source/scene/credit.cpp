#include "credit.hpp"

Credit::Credit(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(width, height, engine, speaker, registry, setting, keyboard),
                                                                                                                                        TEACHER("asset/texture/credit/3T.bmp"),
                                                                                                                                        ASTRAUNAUT("asset/texture/credit/astraunaut.bmp"),
                                                                                                                                        CAT("asset/texture/credit/cat.bmp"),
                                                                                                                                        FOX("asset/texture/credit/fox.bmp"),
                                                                                                                                        SEAL("asset/texture/credit/seal.bmp"),
                                                                                                                                        teacher((width - TEACHER.getWidth()) / 2, height / 4, TEACHER),
                                                                                                                                        astraunaut(teacher.getX() - teacher.getWidth() * 6, height / 2 + height / 8, ASTRAUNAUT),
                                                                                                                                        cat(teacher.getX() - teacher.getWidth() * 2, height / 2 + height / 8, CAT),
                                                                                                                                        fox(teacher.getX() + teacher.getWidth() * 2, height / 2 + height / 8, FOX),
                                                                                                                                        seal(teacher.getX() + teacher.getWidth() * 6, height / 2 + height / 8, SEAL),
                                                                                                                                        // title(width / 2, height / 4, TITLE),
                                                                                                                                        background("asset/sound/background.wav"){}
                                                                                                                                        
Credit::~Credit() {
}

Scene* Credit::process() {
    Scene* next = this;

    Key pressedKey = keyboard->key();

    if(pressedKey == Key::ESC) {
        next = sceneRegistry->scene(SceneID::MENU);
    }
    return next;
}

void Credit::render() {
    engine->fill(0, 162, 232);
    // title.render(engine);
    teacher.render(engine);
    astraunaut.render(engine);
    cat.render(engine);
    fox.render(engine);
    seal.render(engine);
}

void Credit::playsound() {
    // this->audio->playSound(this->buttonSound);
}