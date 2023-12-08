#include "credit.hpp"

Credit::Credit(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(width, height, engine, speaker, registry, setting, keyboard),
                                                                                                                                        view(false),
                                                                                                                                        avatarSelected(0),
                                                                                                                                        TEACHER("asset/texture/credit/3T.bmp"),
                                                                                                                                        ASTRAUNAUT("asset/texture/credit/astraunaut.bmp"),
                                                                                                                                        CAT("asset/texture/credit/cat.bmp"),
                                                                                                                                        FOX("asset/texture/credit/fox.bmp"),
                                                                                                                                        SEAL("asset/texture/credit/seal.bmp"),
                                                                                                                                        background("asset/sound/background.wav"),
                                                                                                                                        credit("credit", width / 2 - width / 9.5, height / 3 - height / 4, 0.8f, 0.2f),
                                                                                                                                        name("", 0, 0, 0, 0),
                                                                                                                                        studentId("", 0, 0, 0, 0){
    avatars.push_back(new Object(TEACHER, (width - TEACHER.getWidth()) / 2, height / 4));
    avatars.push_back(new Object(ASTRAUNAUT, avatars[0]->getX() - avatars[0]->getWidth() * 5, height / 2 + height / 8));
    avatars.push_back(new Object(CAT, avatars[0]->getX() - avatars[0]->getWidth() * 2, avatars[1]->getY()));
    avatars.push_back(new Object(FOX, avatars[0]->getX() + avatars[0]->getWidth() * 2, avatars[2]->getY()));
    avatars.push_back(new Object(SEAL, avatars[0]->getX() + avatars[0]->getWidth() * 5, avatars[3]->getY()));
    

}
                                                                                                                                        
Credit::~Credit() {
    for(auto& avatar : avatars) {
        delete avatar;
    }
}

Scene* Credit::process() {
    Scene* next = this;

    Key pressedKey = keyboard->key();

    switch(pressedKey) {
        case Key::UP:
            if(avatarSelected > 0) {
                avatarSelected = 0;
            }
            break;
        case Key::DOWN:
            if(avatarSelected < 1) {
                avatarSelected = 1;
            }
            break;
        case Key::LEFT:
            if(avatarSelected > 1) {
                avatarSelected--;
            }
            else if(view && avatarSelected == 1) {
                avatarSelected = 0;
            }
            break;
        case Key::RIGHT:
            if(avatarSelected < 4) {
                avatarSelected++;
            }
            break;
        case Key::ENTER:
            view = true;
            break;
        case Key::ESC:
            if(view){
                view = false;
            }
            else{
                next = sceneRegistry->scene(SceneID::MENU);
            }
            break;
    }
    avatars[avatarSelected]->setOffset(avatars[avatarSelected]->getX(), avatars[avatarSelected]->getY() - 50);
    return next;
}

void Credit::render() {
    engine->fill(0, 162, 232);
    credit.render(engine);
    if(!view){
        for(auto& avatar : avatars) {
            avatar->render(engine);
        }
    }
    else{
        switch(avatarSelected) {
                case 0:
                    name.setText(" GV Truong\nToan Thinh",  width / 3, height / 3, 0.8f, 0.2f);
                    break;
                case 1:
                    name.setText("Dang Thanh Tu",  width / 3, height / 3, 0.8f, 0.2f);
                    studentId.setText("22127432",  width / 3, height / 3 + height / 8, 0.8f, 0.2f);
                    break;
                case 2:
                    name.setText("Nguyen Ngoc\n  Anh Tu",  width / 3, height / 3, 0.8f, 0.2f);
                    studentId.setText("22127433",  width / 3, height / 3 + 2 * height / 8, 0.8f, 0.2f);
                    break;
                case 3:
                    name.setText("Bui Ta Phat",  width / 3, height / 3, 0.8f, 0.2f);
                    studentId.setText("22127320",  width / 3, height / 3 + height / 8, 0.8f, 0.2f);
                    break;
                case 4:
                    name.setText("Phan Hai Minh",  width / 3, height / 3, 0.8f, 0.2f);
                    studentId.setText("22127273",  width / 3, height / 3 + height / 8, 0.8f, 0.2f);
                    break;
        }
        xSelected = avatars[avatarSelected]->getX();
        ySelected = avatars[avatarSelected]->getY();
        if(avatarSelected == 0) avatars[avatarSelected]->setOffset(avatars[0]->getX(), avatars[0]->getY() + 50);
        avatars[avatarSelected]->setOffset(avatars[0]->getX() / 3, avatars[0]->getY());
        avatars[avatarSelected]->render(engine);
        name.render(engine);
        if(avatarSelected > 0) studentId.render(engine);
        avatars[avatarSelected]->setOffset(xSelected, ySelected);
    }
    avatars[avatarSelected]->setOffset(avatars[avatarSelected]->getX(), avatars[avatarSelected]->getY() + 50);
}

void Credit::playsound() {
    // this->audio->playSound(this->buttonSound);
}