#include "option.hpp"

Option::Option(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(width, height, engine, speaker, registry, setting, keyboard), 
                                                                                                                                        button(0),
                                                                                                                                        spriteId(0),
                                                                                                                                        SPRITE("asset/texture/button/choose-sprite.bmp"),
                                                                                                                                        SPRITE_CLICKED("asset/texture/button/choose-sprite-clicked.bmp"),
                                                                                                                                        CHICKEN("asset/texture/sprite/chicken/down.bmp"),
                                                                                                                                        DUCK("asset/texture/sprite/duck/down.bmp"),
                                                                                                                                        CAT("asset/texture/sprite/chicken/down.bmp"), //cat sprite
                                                                                                                                        MUSIC("asset/texture/volume/bgm.bmp"),
                                                                                                                                        MUSIC_CLICKED("asset/texture/volume/bgm-clicked.bmp"),
                                                                                                                                        SFX("asset/texture/volume/sfx.bmp"), 
                                                                                                                                        SFX_CLICKED("asset/texture/volume/sfx-clicked.bmp"),
                                                                                                                                        MIN_VOLUME("asset/texture/volume/0.bmp"),
                                                                                                                                        LOW_VOLUME("asset/texture/volume/25.bmp"),
                                                                                                                                        MEDIUM_VOLUME("asset/texture/volume/50.bmp"),
                                                                                                                                        HIGH_VOLUME("asset/texture/volume/75.bmp"),
                                                                                                                                        MAX_VOLUME("asset/texture/volume/100.bmp"),
                                                                                                                                        LEFT_ARROW("asset/texture/button/arrow-left.bmp"),
                                                                                                                                        LEFT_ARROW_CLICKED("asset/texture/button/arrow-left-clicked.bmp"),
                                                                                                                                        RIGHT_ARROW("asset/texture/button/arrow-right.bmp"),
                                                                                                                                        RIGHT_ARROW_CLICKED("asset/texture/button/arrow-right-clicked.bmp"),
                                                                                                                                        background("asset/sound/background.wav"){
    
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

    buttons.push_back(new Button(MUSIC, MUSIC_CLICKED, width / 5, height / 2 - height / 4));
    buttons.push_back(new Button(SFX, SFX_CLICKED, width / 5, height / 2));
    buttons.push_back(new Button(SPRITE, SPRITE_CLICKED, width / 5, height / 2 + height / 4));

    buttons.push_back(new Button(LEFT_ARROW, LEFT_ARROW_CLICKED, width / 3, buttons[2]->getY() + buttons[2]->getHeight() / 3));
    buttons.push_back(new Button(RIGHT_ARROW, RIGHT_ARROW_CLICKED, width / 2 + 7 * buttons.back()->getWidth() / 4, buttons[2]->getY() + buttons[2]->getHeight() / 3));

    music.push_back(new Object(MIN_VOLUME, width / 3, buttons[0]->getY()));
    music.push_back(new Object(LOW_VOLUME, width / 3, buttons[0]->getY()));
    music.push_back(new Object(MEDIUM_VOLUME, width / 3, buttons[0]->getY()));
    music.push_back(new Object(HIGH_VOLUME, width / 3, buttons[0]->getY()));
    music.push_back(new Object(MAX_VOLUME, width / 3, buttons[0]->getY()));

    sfx.push_back(new Object(MIN_VOLUME, width / 3, buttons[1]->getY()));
    sfx.push_back(new Object(LOW_VOLUME, width / 3, buttons[1]->getY()));
    sfx.push_back(new Object(MEDIUM_VOLUME, width / 3, buttons[1]->getY()));
    sfx.push_back(new Object(HIGH_VOLUME, width / 3, buttons[1]->getY()));
    sfx.push_back(new Object(MAX_VOLUME, width / 3, buttons[1]->getY()));
    
    sprites.push_back(new Object(CHICKEN, (buttons[3]->getX() + buttons[4]->getX()) / 2, buttons[2]->getY()));
    sprites.push_back(new Object(DUCK, sprites.back()->getX(), sprites.back()->getY()));
    sprites.push_back(new Object(CAT, sprites.back()->getX(), sprites.back()->getY()));
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