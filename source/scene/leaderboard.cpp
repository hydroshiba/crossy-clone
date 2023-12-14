#include "leaderboard.hpp"

Leaderboard::Leaderboard(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : Scene(engine, speaker, registry, setting, keyboard, holder),
                                                                                                                                                 cupSelected(1),
                                                                                                                                                 view(false),
                                                                                                                                                 button_clicked("asset/sound/sfx/button-click-2.wav"),
                                                                                                                                                 score(holder, "", 0, 0),
                                                                                                                                                 name(holder, "", 0, 0),
                                                                                                                                                 topX(holder, "Top 1", engine->getHeight() / 3 , engine->getWidth() * 2 / 3){
    cups.push_back(new Object(holder->get("SILVER_CUP"), (engine->getWidth() - holder->get("SILVER_CUP")->getWidth()) / 5, (engine->getHeight() - holder->get("SILVER_CUP")->getHeight()) * 3 / 5));
    cups.push_back(new Object(holder->get("GOLD_CUP"), (engine->getWidth() - holder->get("GOLD_CUP")->getWidth()) / 2, (engine->getHeight() - holder->get("GOLD_CUP")->getHeight()) * 3 / 5 - 50));
    cups.push_back(new Object(holder->get("BRONZE_CUP"), (engine->getWidth() - holder->get("BRONZE_CUP")->getWidth()) * 4 / 5, (engine->getHeight() - holder->get("BRONZE_CUP")->getHeight()) * 3 / 5));
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
    cups[cupSelected]->shift(0, -50);
    std::string rank = cupSelected == 0 ? "2" : cupSelected == 1 ? "1" : "3";
    topX.setText("Top " + rank, cups[cupSelected]->position().x, cups[cupSelected]->position().y - 2 * holder->get("A")->getHeight());

    return next;
}

void Leaderboard::render() {
    engine->fill(0, 162, 232);
    if(!view){

        for(auto cup : cups) {
            cup->render(engine);
        }
        topX.render(engine);
    }
    else{
        xSelected = cups[cupSelected]->position().x;
        ySelected = cups[cupSelected]->position().y;
        cups[cupSelected]->shift(engine->getWidth() / 5 - xSelected, engine->getHeight() / 5 - ySelected);
        cups[cupSelected]->render(engine);
        word rank = cupSelected == 0 ? 1 : cupSelected == 1 ? 0 : 2;
        byte* namePlayer = setting->namePlayer(rank);
        if(setting->highscore(rank) == 0){
            name.setText("NA", engine->getWidth() / 2, engine->getHeight() / 3);
        }
        else{
            name.setText(std::string(namePlayer, namePlayer + 8), engine->getWidth() / 2, engine->getHeight() / 3);
        }
        
        score.setText(std::to_string(setting->highscore(rank)), engine->getWidth() / 2, engine->getHeight() / 3 + 2 * holder->get("A")->getHeight());
        name.render(engine);
        score.render(engine);
        cups[cupSelected]->shift(xSelected - engine->getWidth() / 5, ySelected - engine->getHeight() / 5);
    }
    cups[cupSelected]->shift(0, 50);

}

void Leaderboard::playsound() {
    speaker->play(button_clicked);
}