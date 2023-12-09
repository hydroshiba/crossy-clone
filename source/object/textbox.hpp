#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_

#include <vector>
#include "isometric.hpp"

class Textbox {
    float x, y;
    float idxX;
    float idxY;
    float ratioX, ratioY;
    std::vector<Isometric*> text;
    static std::vector<Texture> FONT;
public:
    Textbox(std::string textStr, float x, float y, float ratioX, float ratioY);
    ~Textbox();

    Vec2 getOffset3D(int idxChar);
    void replaceChar(char c, int idx);
    void addText(std::string textStr);
    void setText(std::string textStr, float x, float y, float ratioX, float ratioY);
    void render(Engine* engine);
};
#endif