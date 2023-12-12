#include "object.hpp"
#include <iostream>

Object::Object(Texture const * const texture) : x(0), y(0), texture(texture) {}

Object::Object(Texture const * const texture, int x, int y) : x(x), y(y), texture(texture) {}

Vec2 Object::position() const {
	return { float(x), float(y) };
}

Vec2 Object::size() const {
	return {float(texture->width), float(texture->height)};
}

void Object::shift(int dx, int dy) {
	this->x += dx;
	this->y += dy;
}

void Object::render(Engine* engine) {
	engine->textureFill(x, y, texture);
}