#include "button.hpp"

Button::Button(Texture const* const idle, Texture const* const pressed, int x, int y) : Object(idle, x, y), pressed(pressed) {
}

void Button::press() {
    selected = true;
}

void Button::release() {
    selected = false;
}

void Button::render(Engine* engine) {
    if(selected) {
        engine->textureFill(x, y, pressed);
    } else {
        engine->textureFill(x, y, texture);
    }
}