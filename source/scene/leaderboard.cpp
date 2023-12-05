#include "leaderboard.hpp"

Leaderboard::Leaderboard(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(width, height, engine, speaker, registry, setting, keyboard),
                                                                                                                                                 cupSelected(1),
                                                                                                                                                 view(false),
                                                                                                                                                 GOLD("asset/texture/cup/gold.bmp"),
                                                                                                                                                 SILVER("asset/texture/cup/silver.bmp"),
                                                                                                                                                 COPPER("asset/texture/cup/copper.bmp"){
    cups.push_back(new Object(SILVER, (width - SILVER.getWidth()) / 2 - 400, (height - SILVER.getHeight()) / 3 + 180));
    cups.push_back(new Object(GOLD, (width - GOLD.getWidth()) / 2, (height - GOLD.getHeight()) / 3));
    cups.push_back(new Object(COPPER, (width - COPPER.getWidth()) / 2 + 400, (height - COPPER.getHeight()) / 3 + 180));
}
                                                                                                                                                 
Leaderboard::~Leaderboard() {
    for(auto cup : cups) {
        delete cup;
        cup = nullptr;
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
    cups[cupSelected]->setOffset(cups[cupSelected]->getX(), cups[cupSelected]->getY() - 50);
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
        xSelected = cups[cupSelected]->getX();
        ySelected = cups[cupSelected]->getY();
        if(cupSelected == 1) cups[cupSelected]->setOffset(cups[1]->getX(), cups[1]->getY() + 50);
        cups[cupSelected]->setOffset(cups[1]->getX() / 2, cups[1]->getY() / 2);
        cups[cupSelected]->render(engine);
        cups[cupSelected]->setOffset(xSelected, ySelected);
    }
    cups[cupSelected]->setOffset(cups[cupSelected]->getX(), cups[cupSelected]->getY() + 50);

}

void Leaderboard::playsound() {
    // this->audio->playSound(this->buttonSound);
}