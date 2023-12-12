#include "credit.hpp"

Credit::Credit(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : Scene(engine, speaker, registry, setting, keyboard, holder),
                                                                                                                                        view(false),
                                                                                                                                        avatarSelected(0),
                                                                                                                                        background("asset/sound/background.wav"),
                                                                                                                                        credit("credit", engine->getWidth() / 2 - engine->getWidth() / 9.5, engine->getHeight() / 3 - engine->getHeight() / 4, 0.8f, 0.2f),
                                                                                                                                        name("", 0, 0, 0, 0),
                                                                                                                                        studentId("", 0, 0, 0, 0){
    avatars.push_back(new Object(holder->get("CREDIT_TEACHER"), (engine->getWidth() - holder->get("CREDIT_TEACHER")->getWidth()) / 2, engine->getHeight() / 4));
    avatars.push_back(new Object(holder->get("CREDIT_ASTRAUNAUT"), avatars[0]->position().x - avatars[0]->size().x * 5, engine->getHeight() / 2 + engine->getHeight() / 8));
    avatars.push_back(new Object(holder->get("CREDIT_CAT"), avatars[0]->position().x - avatars[0]->size().x * 2, avatars[1]->position().y));
    avatars.push_back(new Object(holder->get("CREDIT_FOX"), avatars[0]->position().x + avatars[0]->size().x * 2, avatars[2]->position().y));
    avatars.push_back(new Object(holder->get("CREDIT_SEAL"), avatars[0]->position().x + avatars[0]->size().x * 5, avatars[3]->position().y));
    

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
    avatars[avatarSelected]->shift(0, - 50);
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
                    name.setText(" GV Truong\nToan Thinh",  engine->getWidth() / 3, engine->getHeight() / 3, 0.8f, 0.2f);
                    break;
                case 1:
                    name.setText("Dang Thanh Tu",  engine->getWidth() / 3, engine->getHeight() / 3, 0.8f, 0.2f);
                    studentId.setText("22127432",  engine->getWidth() / 3, engine->getHeight() / 3 + engine->getHeight() / 8, 0.8f, 0.2f);
                    break;
                case 2:
                    name.setText("Nguyen Ngoc\n  Anh Tu",  engine->getWidth() / 3, engine->getHeight() / 3, 0.8f, 0.2f);
                    studentId.setText("22127433",  engine->getWidth() / 3, engine->getHeight() / 3 + 2 * engine->getHeight() / 8, 0.8f, 0.2f);
                    break;
                case 3:
                    name.setText("Bui Ta Phat",  engine->getWidth() / 3, engine->getHeight() / 3, 0.8f, 0.2f);
                    studentId.setText("22127320",  engine->getWidth() / 3, engine->getHeight() / 3 + engine->getHeight() / 8, 0.8f, 0.2f);
                    break;
                case 4:
                    name.setText("Phan Hai Minh",  engine->getWidth() / 3, engine->getHeight() / 3, 0.8f, 0.2f);
                    studentId.setText("22127273",  engine->getWidth() / 3, engine->getHeight() / 3 + engine->getHeight() / 8, 0.8f, 0.2f);
                    break;
        }
        xSelected = avatars[avatarSelected]->position().x;
        ySelected = avatars[avatarSelected]->position().y;
        avatars[avatarSelected]->shift(avatars[0]->position().x / 3 - xSelected, avatars[0]->position().y - ySelected);
        avatars[avatarSelected]->render(engine);
        name.render(engine);
        if(avatarSelected > 0) studentId.render(engine);
        avatars[avatarSelected]->shift(xSelected, ySelected);
    }
    avatars[avatarSelected]->shift(0, 50);
}

void Credit::playsound() {
    // this->audio->playSound(this->buttonSound);
}