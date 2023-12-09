#include "textbox.hpp"

std::vector<Texture> Textbox::FONT = {
    Texture("asset/font/0.bmp"),
    Texture("asset/font/1.bmp"),
    Texture("asset/font/2.bmp"),
    Texture("asset/font/3.bmp"),
    Texture("asset/font/4.bmp"),
    Texture("asset/font/5.bmp"),
    Texture("asset/font/6.bmp"),
    Texture("asset/font/7.bmp"),
    Texture("asset/font/8.bmp"),
    Texture("asset/font/9.bmp"),
    
    Texture("asset/font/A.bmp"),
    Texture("asset/font/B.bmp"),
    Texture("asset/font/C.bmp"),
    Texture("asset/font/D.bmp"),
    Texture("asset/font/E.bmp"),
    Texture("asset/font/F.bmp"),
    Texture("asset/font/G.bmp"),
    Texture("asset/font/H.bmp"),
    Texture("asset/font/I.bmp"),
    Texture("asset/font/J.bmp"),
    Texture("asset/font/K.bmp"),
    Texture("asset/font/L.bmp"),
    Texture("asset/font/M.bmp"),
    Texture("asset/font/N.bmp"),
    Texture("asset/font/O.bmp"),
    Texture("asset/font/P.bmp"),
    Texture("asset/font/Q.bmp"),
    Texture("asset/font/R.bmp"),
    Texture("asset/font/S.bmp"),
    Texture("asset/font/T.bmp"),
    Texture("asset/font/U.bmp"),
    Texture("asset/font/V.bmp"),
    Texture("asset/font/W.bmp"),
    Texture("asset/font/X.bmp"),
    Texture("asset/font/Y.bmp"),
    Texture("asset/font/Z.bmp")
};

Textbox::Textbox(std::string textStr, float x, float y, float ratioX, float ratioY) {
    setText(textStr, x, y, ratioX, ratioY);
}

Textbox::~Textbox() {
    for (Isometric* i : text) {
        delete i;
    }
}

Vec2 Textbox::getOffset3D(int idxChar) {
    if(idxChar >= text.size()){
        return {0.0f, 0.0f};
    }
    if(text[idxChar] == NULL){
        return  {x + idxChar * FONT[0].getWidth() * ratioX, y + idxChar * FONT[0].getHeight() * ratioY + idxY * FONT[0].getHeight()};
    }
    return {float(text[idxChar]->getX()), float(text[idxChar]->getY())};
}

void Textbox::replaceChar(char c, int idx) {
    if(idx > text.size()){
        return;
    }
    Vec2 offset = getOffset3D(idx);
    delete text[idx];
    if(c == ' '){
        text[idx] = NULL;
        return;
    }

    if(c >= '0' && c <= '9'){
        float w = FONT[c - '0'].getWidth();
        float h = FONT[c - '0'].getHeight();
        text[idx] = new Isometric(FONT[c - '0'], {w, h}, {0.0f, 0.0f}, {offset.x, offset.y});
        return;
    }
    if(!isalpha(c)){
        return;
    }
    float w = FONT[c - 'A' + 10].getWidth();
    float h = FONT[c - 'A' + 10].getHeight();
    text[idx] = new Isometric(FONT[c - 'A' + 10], {w, h}, {0.0f, 0.0f}, {offset.x, offset.y});

}

void Textbox::addText(std::string textStr) {
    float w = 1, h = 1;
    for(char c : textStr){
        if(c == ' '){
            idxX++;
            text.push_back(NULL);
            continue;
        }
        if(c == '\n'){
            idxX = 0.0f;
            idxY++;
            continue;
        }
        if(c >= '0' && c <= '9'){
            w = FONT[c - '0'].getWidth();
            h = FONT[c - '0'].getHeight();
            text.push_back(new Isometric(FONT[c - '0'], {w, h}, {0.0f, 0.0f}, {x + idxX * w * ratioX, y + idxX * h * ratioY + idxY * h}));
        } else if(isalpha(c)){
            c = toupper(c);
            w = FONT[c - 'A' + 10].getWidth();
            h = FONT[c - 'A' + 10].getHeight();
            text.push_back(new Isometric(FONT[c - 'A' + 10], {w, h}, {0.0f, 0.0f}, {x + idxX * w * ratioX, y + idxX * h * ratioY + idxY * h}));
        }
        idxX++;
    }
}

void Textbox::setText(std::string textStr, float x, float y, float ratioX, float ratioY) {
    //Delete old text
    for (Isometric* i : text) {
        if(i != NULL) delete i;
    }
    text.clear();

    //Create new text
    this->x = x;
    this->y = y;
    this->ratioX = ratioX;
    this->ratioY = ratioY;
    idxX = idxY = 0.0f;
    float w = 1, h = 1;
    for(char c : textStr){
        if(c == ' '){
            idxX++;
            text.push_back(NULL);
            continue;
        }
        if(c == '\n'){
            idxX = 0.0f;
            idxY++;
            continue;
        }
        if(c >= '0' && c <= '9'){
            w = FONT[c - '0'].getWidth();
            h = FONT[c - '0'].getHeight();
            text.push_back(new Isometric(FONT[c - '0'], {w, h}, {0.0f, 0.0f}, {x + idxX * w * ratioX, y + idxX * h * ratioY + idxY * h}));
        } else if(isalpha(c)){
            c = toupper(c);
            w = FONT[c - 'A' + 10].getWidth();
            h = FONT[c - 'A' + 10].getHeight();
            text.push_back(new Isometric(FONT[c - 'A' + 10], {w, h}, {0.0f, 0.0f}, {x + idxX * w * ratioX, y + idxX * h * ratioY + idxY * h}));
        }
        idxX++;
    }
}

void Textbox::render(Engine* engine) {
    for (Isometric* i : text) {
        if(i != NULL) i->render(engine);
    }
}