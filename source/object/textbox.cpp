#include "textbox.hpp"

Textbox::Textbox(TextureHolder* holder, std::string textStr, float x, float y) : holder(holder) {
    setText(textStr, x, y);
}

Textbox::~Textbox() {
    for (Isometric* i : text) {
        delete i;
    }
}

Vec2 Textbox::positionChar(int idx) {
    if(idx > text.size()){
        return {0.0f, 0.0f};
    }
    
    return {x + 0.8f * holder->get("0")->getWidth() * idx, y + 0.2f * holder->get("0")->getHeight() * idx};
}

void Textbox::replaceChar(char c, int idx) {
    if(idx > text.size()){
        return;
    }
    if(text[idx] != NULL) delete text[idx];
    if(c == ' '){
        text[idx] = NULL;
        return;
    }

    if(isalnum(c))
        text[idx] = new Isometric(holder->get(std::string(1, c)), {float(holder->get(std::string(1, c))->getWidth()), float(holder->get(std::string(1, c))->getHeight())}, {0.0f, 0.0f}, {x + 0.8f * holder->get(std::string(1, c))->getWidth() * idx, y + 0.2f * holder->get(std::string(1, c))->getHeight() * idx});
}

void Textbox::setText(std::string textStr, float x, float y) {
    //Delete old text
    for (Isometric* i : text) {
        if(i != NULL) delete i;
    }
    text.clear();

    //Create new text
    this->x = x;
    this->y = y;
    numText = 0;
    for(char c : textStr){
        if(c == ' '){
            text.push_back(NULL);
            continue;
        }
        if(isalnum(c))
            text.push_back(new Isometric(holder->get(std::string(1, c)), {float(holder->get(std::string(1, c))->getWidth()), float(holder->get(std::string(1, c))->getHeight())}, {0.0f, 0.0f}, {x + 0.8f * holder->get(std::string(1, c))->getWidth() * numText, y + 0.2f * holder->get(std::string(1, c))->getHeight() * numText}));
        numText++;
    }
}

void Textbox::render(Engine* engine) {
    for (Isometric* i : text) {
        if(i != NULL) i->render(engine);
    }
}