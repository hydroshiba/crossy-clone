#include "option.hpp"

Option::Option(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : Scene(engine, speaker, registry, setting, keyboard, holder), 
                                                                                                                                        button(0),
                                                                                                                                        spriteId(int(setting->spriteID())),
                                                                                                                                        button_clicked("asset/sound/sfx/button-click-2.wav"){
    
    if(setting->volMusic() == Volume::min) musicId = 0;
    else if(setting->volMusic() == Volume::low) musicId = 1;
    else if(setting->volMusic() == Volume::medium) musicId = 2;
    else if(setting->volMusic() == Volume::high) musicId = 3;
    else musicId = 4;

    if(setting->volSFX() == Volume::min) sfxId = 0;
    else if(setting->volSFX() == Volume::low) sfxId = 1;
    else if(setting->volSFX() == Volume::medium) sfxId = 2;
    else if(setting->volSFX() == Volume::high) sfxId = 3;
    else sfxId = 4;

    buttons.push_back(new Button(holder->get("BGM"), holder->get("BGM_CLICKED"), engine->getWidth() / 5, engine->getHeight() / 2 - engine->getHeight() / 4));
    buttons.push_back(new Button(holder->get("SFX"), holder->get("SFX_CLICKED"), engine->getWidth() / 5, engine->getHeight() / 2));
    buttons.push_back(new Button(holder->get("SPRITE"), holder->get("SPRITE_CLICKED"), engine->getWidth() / 5, engine->getHeight() / 2 + engine->getHeight() / 4));

    buttons.push_back(new Button(holder->get("LEFT"), holder->get("LEFT_CLICKED"), engine->getWidth() / 3, buttons[2]->position().y + buttons[2]->size().y / 3));
    buttons.push_back(new Button(holder->get("RIGHT"), holder->get("RIGHT_CLICKED"), engine->getWidth() / 2 + 7 * buttons.back()->size().x / 4, buttons[2]->position().y + buttons[2]->size().y / 3));

    music.push_back(new Object(holder->get("VOLUME_MIN"), engine->getWidth() / 3, buttons[0]->position().y));
    music.push_back(new Object(holder->get("VOLUME_LOW"), engine->getWidth() / 3, buttons[0]->position().y));
    music.push_back(new Object(holder->get("VOLUME_MEDIUM"), engine->getWidth() / 3, buttons[0]->position().y));
    music.push_back(new Object(holder->get("VOLUME_HIGH"), engine->getWidth() / 3, buttons[0]->position().y));
    music.push_back(new Object(holder->get("VOLUME_MAX"), engine->getWidth() / 3, buttons[0]->position().y));

    sfx.push_back(new Object(holder->get("VOLUME_MIN"), engine->getWidth() / 3, buttons[1]->position().y));
    sfx.push_back(new Object(holder->get("VOLUME_LOW"), engine->getWidth() / 3, buttons[1]->position().y));
    sfx.push_back(new Object(holder->get("VOLUME_MEDIUM"), engine->getWidth() / 3, buttons[1]->position().y));
    sfx.push_back(new Object(holder->get("VOLUME_HIGH"), engine->getWidth() / 3, buttons[1]->position().y));
    sfx.push_back(new Object(holder->get("VOLUME_MAX"), engine->getWidth() / 3, buttons[1]->position().y));
    
    sprites.push_back(new Object(holder->get("CHICKEN_DOWN"), (buttons[3]->position().x + buttons[4]->position().x) / 2, buttons[2]->position().y));
    sprites.push_back(new Object(holder->get("DUCK_DOWN"), sprites.back()->position().x, sprites.back()->position().y));
    sprites.push_back(new Object(holder->get("CAT_DOWN"), sprites.back()->position().x, sprites.back()->position().y));
}

Option::~Option() {
    for(auto& button : buttons){
        delete button;
    }

    for(auto& music_ : music){
        delete music_;
    }

    for(auto& sfx_ : sfx){
        delete sfx_;
    }
    for(auto& sprite : sprites){
        delete sprite;
    }
}

Scene* Option::process() {
    Scene* next = this;

    Sprite sprite = setting->spriteID();

    Key pressedKey = keyboard->key();

    switch(spriteId) {
        case 0:
            buttons[3]->press();
            break;
        case 1:
            buttons[3]->release();
            buttons[4]->release();
            break;
        case 2:
            buttons[4]->press();
            break;
    }
    if(pressedKey != Key::DEFAULT) speaker->play(button_clicked);
    switch(pressedKey) {
    case Key::UP:
        if(button > 0) {
            button--;
        }
        break;
    case Key::DOWN:
        if(button < 2) {
            button++;
        }
        break;
    case Key::LEFT:
        switch(button) {
        case 0:
            setting->decMusic(speaker);
            if(musicId > 0) musicId--;
            break;
        case 1:   
            setting->decSFX(speaker);
            if(sfxId > 0) sfxId--;
            break;
        case 2:
            setting->decSprite();
            if(spriteId > 0) {
                spriteId--;
            }
            break;
        }
        break;
    case Key::RIGHT:
        switch(button) {
        case 0:
            setting->incMusic(speaker);
            if(musicId < 4) musicId++;
            break;
        case 1:
            setting->incSFX(speaker);
            if(sfxId < 4) sfxId++;
            break;
        case 2:
            setting->incSprite();
            if(spriteId < 2) {
                spriteId++;
            }
            break;
        }
        break;
    case Key::ESC:
        next = sceneRegistry->scene(SceneID::MENU);
        break;
    }
    buttons[button]->press();

    return next;
}

void Option::render() {    
    engine->fill(0, 162, 232);

    for(auto& button : buttons) {
        button->render(engine);
    }

    music[musicId]->render(engine);
    sfx[sfxId]->render(engine);
    sprites[spriteId]->render(engine);
    buttons[button]->release();
}

void Option::playsound() {
    // this->audio->playSound(this->buttonSound);
}