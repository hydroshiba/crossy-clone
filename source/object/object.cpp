#include "object.hpp"

Object::Object(int x, int y, const Texture& texture) : x(x), y(y), texture(texture) {}

Object::~Object() {}

void Object::render(Engine* engine) {
	engine->textureFill(x, y, texture);
}