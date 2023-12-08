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
    //Create isometric objects for each character in textStr
    float idx = 0.0f;
    float w, h;
    for(char c : textStr){
        if(c >= '0' && c <= '9'){
            w = FONT[c - '0'].getWidth();
            h = FONT[c - '0'].getHeight();
            text.push_back(new Isometric(FONT[c - '0'], {w, h}, {0.0f, 0.0f}, {x + idx * w * ratioX, y + idx * h * ratioY}));
        } else if(isalnum(c)){
            c = toupper(c);
            w = FONT[c - 'A' + 10].getWidth();
            h = FONT[c - 'A' + 10].getHeight();
            text.push_back(new Isometric(FONT[c - 'A' + 10], {w, h}, {0.0f, 0.0f}, {x + idx * w * ratioX, y + idx * h * ratioY}));
        }
        idx++;
    }
}

Textbox::~Textbox() {
    for (Isometric* i : text) {
        delete i;
    }
}

void Textbox::render(Engine* engine) {
    for (Isometric* i : text) {
        i->render(engine);
    }
}