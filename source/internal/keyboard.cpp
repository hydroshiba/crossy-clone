#include "keyboard.hpp"

Keyboard::Keyboard() : last(Key::DEFAULT), toggle(new bool[256]) {
    memset(toggle, 0, 256);
}

Keyboard::~Keyboard() {
    delete[] toggle;
}

void Keyboard::refresh() {
    last = Key::DEFAULT;

    for(int i = static_cast<int>(Key::A); i <= static_cast<int>(Key::Z); i++)
        last = (pressed(static_cast<Key>(i)) ? static_cast<Key>(i) : last);

    for(int i = static_cast<int>(Key::LEFT); i <= static_cast<int>(Key::DOWN); i++)
        last = (pressed(static_cast<Key>(i)) ? static_cast<Key>(i) : last);

    last = (pressed(Key::SPACE) ? Key::SPACE : last);
    last = (pressed(Key::BACK) ? Key::BACK : last);
    last = (pressed(Key::ENTER) ? Key::ENTER : last);
    last = (pressed(Key::ESC) ? Key::ESC : last);
}

bool Keyboard::pressed(Key key) {
    byte num = static_cast<byte>(key);

    bool down = GetAsyncKeyState(num);
    bool pressed = !down && toggle[num];

    toggle[num] = down;
    return pressed;
}

Key Keyboard::key() {
    Key key = last;
    last = Key::DEFAULT;
    return key;
}