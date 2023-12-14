#include "leaderboard.hpp"

Leaderboard::Leaderboard(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : Scene(engine, speaker, registry, setting, keyboard, holder),
                                                                                                                                                   cupSelected(1),
                                                                                                                                                   view(false),
                                                                                                                                                   button_clicked("asset/sound/sfx/button-click-2.wav"),
                                                                                                                                                   score(holder, "", 0, 0),
                                                                                                                                                   name(holder, "", 0, 0),
                                                                                                                                                   topX(holder, "Top 1", engine->getHeight() / 3, engine->getWidth() * 2 / 3) {
    cups.push_back(new Object(holder->get("SILVER_CUP"), (engine->getWidth() - holder->get("SILVER_CUP")->getWidth()) / 5, (engine->getHeight() - holder->get("SILVER_CUP")->getHeight()) * 3 / 5));
    cups.push_back(new Object(holder->get("GOLD_CUP"), (engine->getWidth() - holder->get("GOLD_CUP")->getWidth()) / 2, (engine->getHeight() - holder->get("GOLD_CUP")->getHeight()) * 3 / 5 - 50));
    cups.push_back(new Object(holder->get("BRONZE_CUP"), (engine->getWidth() - holder->get("BRONZE_CUP")->getWidth()) * 4 / 5, (engine->getHeight() - holder->get("BRONZE_CUP")->getHeight()) * 3 / 5));

    buttons.push_back(new Button(holder->get("LEFT"), holder->get("LEFT_CLICKED"), holder->get("LEFT")->getWidth(), engine->getHeight() / 2));
    buttons.push_back(new Button(holder->get("RIGHT"), holder->get("RIGHT_CLICKED"), engine->getWidth() - buttons.back()->size().x * 2, engine->getHeight() / 2));
}

Leaderboard::~Leaderboard() {
    for(auto cup : cups) {
        delete cup;
        cup = nullptr;
    }

    for(auto button : buttons) {
        delete button;
        button = nullptr;
    }
}

Scene* Leaderboard::process() {
    Scene* next = this;
    Key pressedKey = keyboard->key();

    if(pressedKey != Key::DEFAULT) speaker->play(button_clicked);

    switch(pressedKey) {
        case Key::LEFT:
            if(cupSelected > 0) {
                cupSelected--;
                if(cupSelected == 0) buttons[0]->press();
            }
            break;
        case Key::RIGHT:
            if(cupSelected < 2) {
                cupSelected++;
                if(cupSelected == 2) buttons[1]->press();
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
    cups[cupSelected]->shift(0, -50);
    std::string rank = cupSelected == 0 ? "2" : cupSelected == 1 ? "1"
                                                                 : "3";
    topX.setText("Top " + rank, cups[cupSelected]->position().x, cups[cupSelected]->position().y - 2 * holder->get("A")->getHeight());

    if(cupSelected == 1) {
        buttons[0]->release();
        buttons[1]->release();
    }
    return next;
}

void Leaderboard::render() {
    engine->fill(0, 162, 232);
    if(!view) {
        for(auto cup : cups) {
            cup->render(engine);
        }
        topX.render(engine);
    } else {
        xSelected = cups[cupSelected]->position().x;
        ySelected = cups[cupSelected]->position().y;
        cups[cupSelected]->shift(engine->getWidth() / 5 - xSelected, engine->getHeight() / 5 - ySelected);
        cups[cupSelected]->render(engine);
        word rank = cupSelected == 0 ? 1 : cupSelected == 1 ? 0
                                                            : 2;
        byte* namePlayer = setting->namePlayer(rank);
        if(setting->highscore(rank) == 0) {
            name.setText("NULL", engine->getWidth() / 2, engine->getHeight() / 3);
        } else {
            name.setText(std::string(namePlayer, namePlayer + 8), engine->getWidth() / 2, engine->getHeight() / 3);
        }

        score.setText(std::to_string(setting->highscore(rank)), engine->getWidth() / 2, engine->getHeight() / 3 + 2 * holder->get("A")->getHeight());
        buttons[0]->render(engine);
        buttons[1]->render(engine);
        name.render(engine);
        score.render(engine);
        cups[cupSelected]->shift(xSelected - engine->getWidth() / 5, ySelected - engine->getHeight() / 5);
    }
    cups[cupSelected]->shift(0, 50);
}

void Leaderboard::playsound() {
}