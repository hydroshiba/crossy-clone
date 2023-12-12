#include "leaderboard.hpp"

Leaderboard::Leaderboard(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : Scene(engine, speaker, registry, setting, keyboard, holder),
                                                                                                                                                 cupSelected(1),
                                                                                                                                                 view(false),
                                                                                                                                                 GOLD("asset/texture/cup/gold.bmp"),
                                                                                                                                                 SILVER("asset/texture/cup/silver.bmp"),
                                                                                                                                                 COPPER("asset/texture/cup/copper.bmp"),
                                                                                                                                                 L("asset/font/L.bmp"),
                                                                                                                                                 E("asset/font/E.bmp"),
                                                                                                                                                 A("asset/font/A.bmp"),
                                                                                                                                                 D("asset/font/D.bmp"),
                                                                                                                                                 R("asset/font/R.bmp"),
                                                                                                                                                 B("asset/font/B.bmp"),
                                                                                                                                                 O("asset/font/O.bmp"),
                                                                                                                                                 sound("asset/sound/sfx/long-honk.wav", 0){
    cups.push_back(new Object(SILVER, (width - SILVER.getWidth()) / 5, (height - SILVER.getHeight())));
    cups.push_back(new Object(GOLD, (width - GOLD.getWidth()) / 2, (height - GOLD.getHeight()) * 3 / 5));
    cups.push_back(new Object(COPPER, (width - COPPER.getWidth()) * 4 / 5, (height - COPPER.getHeight())));

    leaderboard.push_back(new Object(L, width / 4, height / 16));
    leaderboard.push_back(new Object(E, leaderboard.back()->getX() + 5 * L.getWidth() / 6, leaderboard.back()->getY() + L.getHeight() / 4));
    leaderboard.push_back(new Object(A, leaderboard.back()->getX() + 5 * L.getWidth() / 6, leaderboard.back()->getY() + L.getHeight() / 4));
    leaderboard.push_back(new Object(D, leaderboard.back()->getX() + 5 * L.getWidth() / 6, leaderboard.back()->getY() + L.getHeight() / 4));
    leaderboard.push_back(new Object(E, leaderboard.back()->getX() + 5 * L.getWidth() / 6, leaderboard.back()->getY() + L.getHeight() / 4));
    leaderboard.push_back(new Object(R, leaderboard.back()->getX() + 5 * L.getWidth() / 6, leaderboard.back()->getY() + L.getHeight() / 4));
    leaderboard.push_back(new Object(B, leaderboard.back()->getX() + 5 * L.getWidth() / 6, leaderboard.back()->getY() + L.getHeight() / 4));
    leaderboard.push_back(new Object(O, leaderboard.back()->getX() + 5 * L.getWidth() / 6, leaderboard.back()->getY() + L.getHeight() / 4));
    leaderboard.push_back(new Object(A, leaderboard.back()->getX() + 5 * L.getWidth() / 6, leaderboard.back()->getY() + L.getHeight() / 4));
    leaderboard.push_back(new Object(R, leaderboard.back()->getX() + 5 * L.getWidth() / 6, leaderboard.back()->getY() + L.getHeight() / 4));
    leaderboard.push_back(new Object(D, leaderboard.back()->getX() + 5 * L.getWidth() / 6, leaderboard.back()->getY() + L.getHeight() / 4));
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
    cups[cupSelected]->setOffset(cups[cupSelected]->getX(), cups[cupSelected]->getY() - 50);
    return next;
}

void Leaderboard::render() {
    engine->fill(0, 162, 232);
    if(!view){

        for(auto cup : cups) {
            cup->render(engine);
        }
        // for(auto font : leaderboard) {
        //     font->render(engine);
        // }
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
    speaker->play(sound);
}