#include "gameover.hpp"

Gameover::Gameover(Engine* engine, Speaker* speaker, SceneRegistry* registry, Setting* setting, Keyboard* keyboard, TextureHolder* holder) : 
    Scene(engine, speaker, registry, setting, keyboard, holder),
    isEnterName(-1),
    idxChar(0),
    sizeName(8),
    LINE(new Texture("asset/texture/line60x23.bmp")),
    quit(holder->get("QUIT_CLICKED"), (engine->getWidth() - holder->get("QUIT_CLICKED")->getWidth()) / 2, engine->getHeight() * 2 / 3),
    gameover(holder, "Gameover", engine->getWidth() / 2 - engine->getWidth() / 7, engine->getHeight() / 3 - engine->getHeight() / 6),
    name(holder, "        ", engine->getWidth() / 2 - engine->getWidth() / 6, engine->getHeight() / 3 + 2 * holder->get("A")->getHeight()),
    line(LINE, engine->getWidth() / 2 - engine->getWidth() / 6, engine->getHeight() / 3 + 3 * holder->get("A")->getHeight()),
    topX(holder, "", engine->getWidth() / 2 - engine->getWidth() / 10, engine->getHeight() / 3 - engine->getHeight() / 4){
    for(int i = 0; i < sizeName; i++){
        namePlayer[i] = ' ';
    }
}

Gameover::~Gameover() {
}

void Gameover::setScore(word score) {
    isEnterName = setting->setScore(score);
}

Scene* Gameover::process() {
    Scene* next = this;
    Key pressedKey = keyboard->key();
    if(isEnterName != 3){
        gameover.setText("Enter your name", engine->getWidth() / 5, engine->getHeight() / 3 - engine->getHeight() / 8);
        topX.setText("Top " + std::to_string(isEnterName + 1), engine->getWidth() / 2 - engine->getWidth() / 10, engine->getHeight() / 3 - engine->getHeight() / 4);
        int prevIdxChar = idxChar;
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
                setting->setNames(namePlayer, isEnterName);
                isEnterName = 3;
                idxChar = 0;
                gameover.setText("Gameover", engine->getWidth() / 2 - engine->getWidth() / 6, engine->getHeight() / 6);    
                name.setText("        ", engine->getWidth() / 2 - engine->getWidth() / 6, engine->getHeight() / 3 + 2 * holder->get("A")->getHeight());
                line.shift(-idxChar * LINE->getWidth(), -idxChar * LINE->getHeight());
                for(int i = 0; i < sizeName; i++){
                    namePlayer[i] = ' ';
                }
                next = sceneRegistry->scene(SceneID::MENU);
                break;
            }
        }
    line.shift((idxChar - prevIdxChar) * LINE->getWidth(), (idxChar - prevIdxChar) * LINE->getHeight());
    }
    else if(pressedKey == Key::ENTER || pressedKey == Key::ESC){
        next = sceneRegistry->scene(SceneID::MENU);
    }

    return next;
}

void Gameover::render() {
    engine->fill(0, 162, 232);
    gameover.render(engine);
    if(isEnterName != 3){
        topX.render(engine);
        line.render(engine);
        name.render(engine);
    }
    else{
        quit.render(engine);
    }
}

void Gameover::playsound() {
    // this->audio->playSound(this->buttonSound);
}