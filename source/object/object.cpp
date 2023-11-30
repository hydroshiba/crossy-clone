#include "object.hpp"
#include <iostream>

Object::Object(int x, int y, const Texture& texture) : x(x), y(y), texture(texture) {}

int Object::getX() {
	return x;
}

int Object::getY() {
	return y;
}

int Object::getWidth() {
	return texture.getWidth();
}

int Object::getHeight() {
	return texture.getHeight();
}

void Object::render(Engine* engine) {
	engine->textureFill(x, y, texture);
}