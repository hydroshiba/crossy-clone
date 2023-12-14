#include "isometric.hpp"

Isometric::Isometric(Texture const* const texture, const Vec2& size) : Object(texture),
                                                                       x(0),
                                                                       y(0),
                                                                       width(size.x),
                                                                       height(size.y),
                                                                       offset({0, 0}),
                                                                       transform({0.5f * width, -0.5f * width,
                                                                                  0.25f * height, 0.25f * height}) {}

Isometric::Isometric(Texture const* const texture, const Vec2& size, const Vec2& pos) : Object(texture),
                                                                                        x(pos.x),
                                                                                        y(pos.y),
                                                                                        width(size.x),
                                                                                        height(size.y),
                                                                                        offset({0, 0}),
                                                                                        transform({0.5f * width, -0.5f * width,
                                                                                                   0.25f * height, 0.25f * height}) {}

Isometric::Isometric(Texture const* const texture, const Vec2& size, const Vec2& pos, const Vec2& off) : Object(texture),
                                                                                                         x(pos.x),
                                                                                                         y(pos.y),
                                                                                                         width(size.x),
                                                                                                         height(size.y),
                                                                                                         offset(off),
                                                                                                         transform({0.5f * width, -0.5f * width,
                                                                                                                    0.25f * height, 0.25f * height}) {}

void Isometric::render(Engine* engine) {
    project();
    Object::render(engine);
}

void Isometric::shift(int dx, int dy) {
    offset.x += dx;
    offset.y += dy;
}

void Isometric::shift(const Vec2& df) {
    offset.x += df.x;
    offset.y += df.y;
}

void Isometric::project() {
    Vec2 res = transform * Vec2({x, y}) + offset;
    Object::x = res.x;
    Object::y = res.y;
}

Vec2 Isometric::position() const {
    return Vec2({x, y});
}

Vec2 Isometric::size() const {
    return Vec2({width, height});
}

Vec2 Isometric::collisionSize() const {
    float w = (texture->getWidth() - width * 0.5f) / (width * 0.5f);
    float h = (texture->getHeight() - height * 0.5f) / (height * 0.5f);
    return Vec2({w, h});
}
