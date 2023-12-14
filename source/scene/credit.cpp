#include "credit.hpp"

Credit::Credit(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : Scene(engine, speaker, registry, setting, keyboard, holder),
                                                                                                                                         view(false),
                                                                                                                                         avatarSelected(0),
                                                                                                                                         button_clicked("asset/sound/sfx/button-click-2.wav"),
                                                                                                                                         credit(holder, "credit", engine->getWidth() / 2 - engine->getWidth() / 9.5, engine->getHeight() / 3 - engine->getHeight() / 4),
                                                                                                                                         studentId(holder, "", 0, 0) {
    avatars.push_back(new Object(holder->get("CREDIT_TEACHER"), (engine->getWidth() - holder->get("CREDIT_TEACHER")->getWidth()) / 2, engine->getHeight() / 4));
    avatars.push_back(new Object(holder->get("CREDIT_ASTRAUNAUT"), avatars[0]->position().x - avatars[0]->size().x * 5, engine->getHeight() / 2 + engine->getHeight() / 8));
    avatars.push_back(new Object(holder->get("CREDIT_CAT"), avatars[0]->position().x - avatars[0]->size().x * 2, avatars[1]->position().y));
    avatars.push_back(new Object(holder->get("CREDIT_FOX"), avatars[0]->position().x + avatars[0]->size().x * 2, avatars[2]->position().y));
    avatars.push_back(new Object(holder->get("CREDIT_SEAL"), avatars[0]->position().x + avatars[0]->size().x * 5, avatars[3]->position().y));

    name.push_back(Textbox(holder, "", 0, 0));
    name.push_back(Textbox(holder, "", 0, 0));
    buttons.push_back(new Button(holder->get("LEFT"), holder->get("LEFT_CLICKED"), holder->get("LEFT")->getWidth(), engine->getHeight() / 2));
    buttons.push_back(new Button(holder->get("RIGHT"), holder->get("RIGHT_CLICKED"), engine->getWidth() - buttons.back()->size().x * 2, engine->getHeight() / 2));
}

Credit::~Credit() {
    for(auto& avatar : avatars) {
        delete avatar;
    }
}

Scene* Credit::process() {
    Scene* next = this;

    Key pressedKey = keyboard->key();

    if(pressedKey != Key::DEFAULT) speaker->play(button_clicked);

    switch(pressedKey) {
        case Key::UP:
            if(avatarSelected > 0) {
                avatarSelected = 0;
                buttons[0]->press();
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
                if(avatarSelected == 0) buttons[0]->press();
            } else if(view && avatarSelected == 1) {
                avatarSelected = 0;
                buttons[0]->press();
            }
            break;
        case Key::RIGHT:
            if(avatarSelected < 4) {
                avatarSelected++;
                if(avatarSelected == 4) buttons[1]->press();
            }
            break;
        case Key::ENTER:
            view = true;
            break;
        case Key::ESC:
            if(view) {
                view = false;
            } else {
                next = sceneRegistry->scene(SceneID::MENU);
            }
            break;
    }
    if(avatarSelected != 0) {
        buttons[0]->release();
    }
    if(avatarSelected != 4) {
        buttons[1]->release();
    }
    avatars[avatarSelected]->shift(0, -50);
    return next;
}

void Credit::render() {
    engine->fill(0, 162, 232);
    credit.render(engine);
    if(!view) {
        for(auto& avatar : avatars) {
            avatar->render(engine);
        }
    } else {
        switch(avatarSelected) {
            case 0:
                name[0].setText("GV Truong", engine->getWidth() / 3, engine->getHeight() / 3);
                name[1].setText("Toan Thinh", engine->getWidth() / 3, engine->getHeight() / 3 + holder->get("A")->getHeight() * 1.2);
                studentId.setText("", 0, 0);
                break;
            case 1:
                name[0].setText("Dang Thanh Tu", engine->getWidth() / 3, engine->getHeight() / 3);
                name[1].setText("", 0, 0);
                studentId.setText("22127432", engine->getWidth() / 3, engine->getHeight() / 3 + engine->getHeight() / 8);
                break;
            case 2:
                name[0].setText("Nguyen Ngoc", engine->getWidth() / 3, engine->getHeight() / 3);
                name[1].setText("  Anh Tu", engine->getWidth() / 3, engine->getHeight() / 3 + engine->getHeight() / 8);
                studentId.setText("22127433", engine->getWidth() / 3, engine->getHeight() / 3 + 2 * engine->getHeight() / 8);
                break;
            case 3:
                name[0].setText("Bui Ta Phat", engine->getWidth() / 3, engine->getHeight() / 3);
                name[1].setText("", 0, 0);
                studentId.setText("22127320", engine->getWidth() / 3, engine->getHeight() / 3 + engine->getHeight() / 8);
                break;
            case 4:
                name[0].setText("Phan Hai Minh", engine->getWidth() / 3, engine->getHeight() / 3);
                name[1].setText("", 0, 0);
                studentId.setText("22127273", engine->getWidth() / 3, engine->getHeight() / 3 + engine->getHeight() / 8);
                break;
        }
        xSelected = avatars[avatarSelected]->position().x;
        ySelected = avatars[avatarSelected]->position().y;
        if(avatarSelected == 0) ySelected -= 50;
        avatars[avatarSelected]->shift(avatars[0]->position().x / 3 - xSelected, avatars[0]->position().y - ySelected);
        avatars[avatarSelected]->render(engine);
        buttons[0]->render(engine);
        buttons[1]->render(engine);
        for(auto& name_ : name) {
            name_.render(engine);
        }
        if(avatarSelected > 0)
            studentId.render(engine);
        else
            ySelected += 50;
        avatars[avatarSelected]->shift(xSelected - avatars[avatarSelected]->position().x, ySelected - avatars[avatarSelected]->position().y);
    }
    avatars[avatarSelected]->shift(0, 50);
}

void Credit::playsound() {
    // this->audio->playSound(this->buttonSound);
}