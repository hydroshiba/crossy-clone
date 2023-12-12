#include "gameover.hpp"

Gameover::Gameover(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : 
    Scene(engine, speaker, registry, setting, keyboard, holder),
    isEnterName(false),
    idxChar(0),
    sizeName(10),
    score(0),
    LINE(new Texture("asset/texture/line60x23.bmp")),
    quit(holder->get("QUIT_CLICKED"), (engine->getWidth() - holder->get("QUIT_CLICKED")->getWidth()) / 2, engine->getHeight() * 2 / 3),
    gameover(holder, "Gameover", engine->getWidth() / 2 - engine->getWidth() / 7, engine->getHeight() / 3 - engine->getHeight() / 6),
    name(holder, "          ", engine->getWidth() / 2 - engine->getWidth() / 7, engine->getHeight() / 3 - engine->getHeight() / 6),
    line(LINE, engine->getWidth() / 2 - engine->getWidth() / 7, engine->getHeight() / 3 - engine->getHeight() / 6 + 80){
    namePlayer.resize(sizeName);
    for(int i = 0; i < sizeName; i++){
        namePlayer[i] = ' ';
    }
}

Gameover::~Gameover() {
}

void Gameover::setScore(word score) {
    this->score = score;
    isEnterName = setting->setScore(score);
}

Scene* Gameover::process() {
    Scene* next = this;
    Key pressedKey = keyboard->key();
    if(isEnterName){
        char c;
        switch(pressedKey){
            case Key::LEFT:
                if(idxChar > 0){
                    idxChar--;
                }
                break;
            case Key::RIGHT: case Key::SPACE:
                if(idxChar < sizeName - 1){
                    idxChar++;
                }
                break;
            case Key::A:    case Key::B:    case Key::C:    case Key::D:
            case Key::E:    case Key::F:    case Key::G:    case Key::H:
            case Key::I:    case Key::J:    case Key::K:    case Key::L:
            case Key::M:    case Key::N:    case Key::O:    case Key::P:
            case Key::Q:    case Key::R:    case Key::S:    case Key::T:
            case Key::U:    case Key::V:    case Key::W:    case Key::X:
            case Key::Y:    case Key::Z:    case Key::ZERO: case Key::ONE:
            case Key::TWO:  case Key::THREE:case Key::FOUR: case Key::FIVE:
            case Key::SIX:  case Key::SEVEN:case Key::EIGHT:case Key::NINE:
                c = static_cast<char>(pressedKey);
                name.replaceChar(c , idxChar);
                namePlayer[idxChar] = c;
                if(idxChar < sizeName - 1){
                    idxChar++;
                }
                break;
            case Key::BACK:{
                name.replaceChar(' ', idxChar);
                namePlayer[idxChar] = ' ';
                if(idxChar > 0){
                    idxChar--;
                }
                break;
            }
            case Key::ENTER:{
                // setting->setName(namePlayer);
                isEnterName = false;
                for(int i = 0; i < sizeName; i++){
                    namePlayer[i] = ' ';
                }
                break;
            }
        }
    }
    else if(pressedKey == Key::ENTER || pressedKey == Key::ESC){
        next = sceneRegistry->scene(SceneID::MENU);
    }

    line.shift(name.positionChar(idxChar).x - line.position().x, name.positionChar(idxChar).y - line.position().y);
    return next;
}

void Gameover::render() {
    engine->fill(0, 162, 232);
    if(isEnterName){
        line.render(engine);
        name.render(engine);
    }
    else{
        gameover.render(engine);
    }
}

void Gameover::playsound() {
    // this->audio->playSound(this->buttonSound);
}