#include "typedef.hpp"

Volume& operator++(Volume& volume) {
    switch(volume) {
        case Volume::min:
            return volume = Volume::low;
        case Volume::low:
            return volume = Volume::medium;
        case Volume::medium:
            return volume = Volume::high;
        case Volume::high:
            return volume = Volume::max;
        default:
            return volume = Volume::max;
    }
}

Volume& operator--(Volume& volume) {
    switch(volume) {
        case Volume::max:
            return volume = Volume::high;
        case Volume::high:
            return volume = Volume::medium;
        case Volume::medium:
            return volume = Volume::low;
        case Volume::low:
            return volume = Volume::min;
        default:
            return volume = Volume::min;
    }
}

Sprite& operator++(Sprite& sprite) {
    switch(sprite) {
        case Sprite::duck:
            return sprite = Sprite::cat;
        case Sprite::chicken:
            return sprite = Sprite::duck;
        default:
            return sprite;
    }
}

Sprite& operator--(Sprite& sprite) {
    switch(sprite) {
        case Sprite::cat:
            return sprite = Sprite::duck;
        case Sprite::duck:
            return sprite = Sprite::chicken;
        default:
            return sprite;
    }
}