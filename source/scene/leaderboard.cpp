#include "leaderboard.hpp"

Leaderboard::Leaderboard(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : Scene(engine, speaker, registry, setting, keyboard, holder),
                                                                                                                                                 cupSelected(1),
                                                                                                                                                 view(false),
                                                                                                                                                 sound("asset/sound/sfx/long-honk.wav", 0){
    cups.push_back(new Object(holder->get("SILVER_CUP"), (engine->getWidth() - holder->get("SILVER_CUP")->getWidth()) / 5, (engine->getHeight() - holder->get("SILVER_CUP")->getHeight() * 1.2)));
    cups.push_back(new Object(holder->get("GOLD_CUP"), (engine->getWidth() - holder->get("GOLD_CUP")->getWidth()) / 2, (engine->getHeight() - holder->get("GOLD_CUP")->getHeight()) * 2 / 5));
    cups.push_back(new Object(holder->get("BRONZE_CUP"), (engine->getWidth() - holder->get("BRONZE_CUP")->getWidth()) * 4 / 5, (engine->getHeight() - holder->get("BRONZE_CUP")->getHeight() * 1.2)));
}
                                                                                                                                                 
Leaderboard::~Leaderboard() {
    for(auto cup : cups) {
        delete cup;
        cup = nullptr;
    }
    for(auto font : leaderboard) {
        delete font;
        font = nullptr;
    }
}

Scene* Leaderboard::process() {
    Scene* next = this;
    Key pressedKey = keyboard->key();

    switch(pressedKey) {
    case Key::LEFT:
        if(cupSelected > 0) {
            cupSelected--;
            
        }
        break;
    case Key::RIGHT:
        if(cupSelected < 2) {
            cupSelected++;
        }
        break;
    case Key::ENTER:
        playsound();
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
    cups[cupSelected]->shift(0, - 50);
    return next;
}

void Leaderboard::render() {
    engine->fill(0, 162, 232);
    if(!view){

        for(auto cup : cups) {
            cup->render(engine);
        }
    }
    else{
        xSelected = cups[cupSelected]->position().x;
        ySelected = cups[cupSelected]->position().y;
        if(cupSelected == 1) ySelected -= 50;
        cups[cupSelected]->shift(cups[1]->position().x / 2 - xSelected, cups[1]->position().y - ySelected);
        cups[cupSelected]->render(engine);
        if(cupSelected == 1) ySelected += 50;
        cups[cupSelected]->shift(xSelected - cups[cupSelected]->position().x, ySelected - cups[cupSelected]->position().y);
    }
    cups[cupSelected]->shift(0, 50);

}

void Leaderboard::playsound() {
    speaker->play(sound);
}