#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_

#include <vector>
#include "isometric.hpp"
#include "texture_holder.hpp"

class Textbox {
    int x, y;
    int numText;
    std::vector<Isometric*> text;
    TextureHolder* holder;

public:
    Textbox(TextureHolder* holder, std::string textStr, float x, float y);
    ~Textbox();

    Vec2 positionChar(int idx);
    void replaceChar(char c, int idx);
    void setText(std::string textStr, float x, float y);
    void render(Engine* engine);
};
#endif