#include "option.hpp"

Option::Option(int width, int height, Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard) : Scene(width, height, engine, speaker, registry, setting, keyboard), 
                                                                                                                                        button(0),
                                                                                                                                        arrow(0),
                                                                                                                                        musicId(2),
                                                                                                                                        sfxId(2),
                                                                                                                                        spriteId(0),
                                                                                                                                        SPRITE("asset/texture/volume/bgm.bmp"), //sprite
                                                                                                                                        SPRITE_CLICKED("asset/texture/volume/sfx.bmp"), //sprite clicked
                                                                                                                                        CHICKEN("asset/texture/sprite/chicken/down.bmp"),
                                                                                                                                        DUCK("asset/texture/sprite/duck/down.bmp"),
                                                                                                                                        CAT("asset/texture/sprite/chicken/down.bmp"), //cat sprite
                                                                                                                                        MUSIC("asset/texture/volume/bgm.bmp"),
                                                                                                                                        MUSIC_CLICKED("asset/texture/volume/sfx.bmp"), //music clicked
                                                                                                                                        SFX("asset/texture/volume/sfx.bmp"), 
                                                                                                                                        SFX_CLICKED("asset/texture/volume/bgm.bmp"), // sfx clicked
                                                                                                                                        MIN_VOLUME("asset/texture/volume/0.bmp"),
                                                                                                                                        LOW_VOLUME("asset/texture/volume/25.bmp"),
                                                                                                                                        MEDIUM_VOLUME("asset/texture/volume/50.bmp"),
                                                                                                                                        HIGH_VOLUME("asset/texture/volume/75.bmp"),
                                                                                                                                        MAX_VOLUME("asset/texture/volume/100.bmp"),
                                                                                                                                        LEFT_ARROW("asset/texture/button/arrow-left.bmp"),
                                                                                                                                        LEFT_ARROW_CLICKED("asset/texture/button/arrow-right.bmp"), //left arrow clicked
                                                                                                                                        RIGHT_ARROW("asset/texture/button/arrow-right.bmp"),
                                                                                                                                        RIGHT_ARROW_CLICKED("asset/texture/button/arrow-left.bmp"), //right arrow clicked
                                                                                                                                        background("asset/sound/background.wav"){
    buttons.push_back(new Button(MUSIC, MUSIC_CLICKED, width / 5, (height - SFX.getHeight()) / 2 - 200));
    buttons.push_back(new Button(SFX, SFX_CLICKED, width / 5, (height - SFX.getHeight()) / 2));
    buttons.push_back(new Button(SPRITE, SPRITE_CLICKED, width / 5, (height - SFX.getHeight()) / 2 + 200));

    buttons.push_back(new Button(LEFT_ARROW, LEFT_ARROW_CLICKED, width / 3, buttons[2]->getY() + 10));
    buttons.push_back(new Button(RIGHT_ARROW, RIGHT_ARROW_CLICKED, buttons.back()->getX() + buttons.back()->getWidth() + 300, buttons[2]->getY() + 10));

    music.push_back(new Object(width / 3, buttons[0]->getY(), MIN_VOLUME));
    music.push_back(new Object(width / 3, buttons[0]->getY(), LOW_VOLUME));
    music.push_back(new Object(width / 3, buttons[0]->getY(), MEDIUM_VOLUME));
    music.push_back(new Object(width / 3, buttons[0]->getY(), HIGH_VOLUME));
    music.push_back(new Object(width / 3, buttons[0]->getY(), MAX_VOLUME));

    sfx.push_back(new Object(width / 3, buttons[1]->getY(), MIN_VOLUME));
    sfx.push_back(new Object(width / 3, buttons[1]->getY(), LOW_VOLUME));
    sfx.push_back(new Object(width / 3, buttons[1]->getY(), MEDIUM_VOLUME));
    sfx.push_back(new Object(width / 3, buttons[1]->getY(), HIGH_VOLUME));
    sfx.push_back(new Object(width / 3, buttons[1]->getY(), MAX_VOLUME));
    
    sprites.push_back(new Object(buttons[3]->getX() + 170, buttons[2]->getY(), CHICKEN));
    sprites.push_back(new Object(buttons[3]->getX() + 170, buttons[2]->getY(), DUCK));
    sprites.push_back(new Object(buttons[3]->getX() + 170, buttons[2]->getY(), CAT));


    
                                                                                                    
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
        arrow = 3;
        switch(button) {
        case 0:
            setting->decMusic();
            if(musicId > 0) musicId--;
            break;
        case 1:   
            setting->decSFX();
            if(sfxId > 0) sfxId--;
            break;
        case 2:
            setting->decSprite();
            if(spriteId > 0) {
                spriteId--;
                buttons[arrow]->press();
            }
            break;
        }
        break;
    case Key::RIGHT:
        arrow = 4;
        switch(button) {
        case 0:
            setting->incMusic();
            if(musicId < 4) musicId++;
            break;
        case 1:
            setting->incSFX();
            if(sfxId < 4) sfxId++;
            break;
        case 2:
            setting->incSprite();
            if(spriteId < 2) {
                spriteId++;
                buttons[arrow]->press();
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
    if(arrow != 0) {
        buttons[arrow]->release();
        arrow = 0;
    }
}

void Option::playsound() {
    // this->audio->playSound(this->buttonSound);
}