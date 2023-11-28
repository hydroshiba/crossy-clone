#include "object.hpp"
#include <iostream>

Object::Object(int x, int y, Texture* texture) : x(x), y(y), texture(texture) {}

Object::~Object() {
}

void Object::render(Engine* engine) {
	engine->textureFill(x, y, texture);
}