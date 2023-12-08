#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_

#include <vector>
#include "isometric.hpp"

class Textbox {
    std::vector<Isometric*> text;
    static std::vector<Texture> FONT;
public:
    Textbox(std::string textStr, float x, float y, float ratioX, float ratioY);
    ~Textbox();
    void render(Engine* engine);
};
#endif