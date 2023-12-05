#include "credit.hpp"

Credit::Credit(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(width, height, engine, speaker, registry, setting, keyboard),
                                                                                                                                        TEACHER("asset/texture/credit/3T.bmp"),
                                                                                                                                        ASTRAUNAUT("asset/texture/credit/astraunaut.bmp"),
                                                                                                                                        CAT("asset/texture/credit/cat.bmp"),
                                                                                                                                        FOX("asset/texture/credit/fox.bmp"),
                                                                                                                                        SEAL("asset/texture/credit/seal.bmp"),
                                                                                                                                        teacher(TEACHER, (width - TEACHER.getWidth()) / 2, height / 4),
                                                                                                                                        astraunaut(ASTRAUNAUT, teacher.getX() - teacher.getWidth() * 6, height / 2 + height / 8),
                                                                                                                                        cat(CAT, teacher.getX() - teacher.getWidth() * 2, height / 2 + height / 8),
                                                                                                                                        fox(FOX, teacher.getX() + teacher.getWidth() * 2, height / 2 + height / 8),
                                                                                                                                        seal(SEAL, teacher.getX() + teacher.getWidth() * 6, height / 2 + height / 8),
                                                                                                                                        // title(TITLE, width / 2, height / 4),
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